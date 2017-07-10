#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/pwm.h>
#include <gpio.h>
#include <soc/gpio.h>
#include "humidity_temperature.h"

#define DEBUG_EN 0
#if DEBUG_EN
#define PWHERE  printk("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
#define PDEBUG(fmt, args...) printk(fmt, ##args);
#else
#define PWHERE ;
#define PDEBUG(fmt, args...) ;
#endif

#define DEVICE_ADDR 0x44

#define HEX_CODE_READ_STATUS_REG 0XF32D
#define HEX_CODE_SINGLE_SHOT_MOD_MEDIUM_DISABLED_READ 0X240B
#define HEX_CODE_PERIODIC_DATA_ACQUISITION_MODE_MEDIUM_1MPS 0X2126
#define HEX_CODE_READOUT_OF_MEASUREMENT_RESULTS_FOR_PERIODIC_MODE 0XE000


#define DEVICE_NAME "hum_tem"

static struct i2c_client *gclient=NULL;

#define uchar unsigned char
#define POLY 0x31
#define CRC8_INIT_VALUE 0xff
static uchar crc8(unsigned char *addr, int num)  
{  
   int i;  
   uchar crc=CRC8_INIT_VALUE;
    for (; num > 0; num--)              	/* Step through bytes in memory */  
    {  
        crc = crc ^ (*addr  );     		/* Fetch byte from memory, XOR into CRC top byte*/  
        for (i = 0; i < 8; i  )             /* Prepare to rotate 8 bits */  
        {  
            if (crc & 0x80)           		 /* b7 is set... */  
                crc = (crc << 1) ^ POLY;    /* rotate and XOR with polynomic */  
            else                          		/* b7 is clear... */  
                crc <<= 1;                 	 /* just rotate */  
        }                            			 /* Loop for 8 bits */  
        crc &= 0xFF;                  	/* Ensure CRC remains 16-bit value */  
    }                              		 /* Loop until num=0 */  
    return(crc);                   		 /* Return updated CRC */  
}  

#define TMPERATURE_VALUED_MASK	 0x01
#define HUMIDITY_VALUED_MASK 		 0x02
static int readout_results_for_periodic_mode(int *tmperature, int *humidity, int *data_valued) {
	struct i2c_msg msg[2];
	int ret;
	int tmp_tmperature;
	int tmp_humidity;
	char buf_read[6];
	char buf_write[3];
	msg[0].addr = gclient->addr;
	msg[0].flags = gclient->flags;
	msg[0].len = 2;
	msg[0].buf = (char *)buf_write;
	buf_write[0] = (HEX_CODE_READOUT_OF_MEASUREMENT_RESULTS_FOR_PERIODIC_MODE>>8)&0XFF;
	buf_write[1] = (HEX_CODE_READOUT_OF_MEASUREMENT_RESULTS_FOR_PERIODIC_MODE)&0XFF;

	msg[1].addr = gclient->addr;
	msg[1].flags = gclient->flags | I2C_M_RD;
	msg[1].len = 6;
	msg[1].buf = (char *)buf_read;
	PWHERE;
	*data_valued = 0;
	ret=i2c_transfer(gclient->adapter, msg, 2);
	if (ret <0) {
		PDEBUG("i2c_transfer error, func:%s line:%d\n", __FUNCTION__, __LINE__);
		return ret;
	} else if (ret == 2) {
		tmp_tmperature = buf_read[0]&0xff;
		tmp_tmperature <<= 8;
		tmp_tmperature |= buf_read[1]&0xff;
		ret = 0;
		if (buf_read[2] != crc8((uchar*)buf_read, 2) ) {
			ret = -1;
			PDEBUG("tmperature crc check error, func:%s line:%d\n", __FUNCTION__, __LINE__);
		}
		else {
			*tmperature =175*tmp_tmperature/65535-45;
			*data_valued |= TMPERATURE_VALUED_MASK;
			PDEBUG("tmperature crc ok, tmperature:%d\n", *tmperature);
		}
		
		tmp_humidity = buf_read[3]&0xff;
		tmp_humidity <<= 8;
		tmp_humidity |= buf_read[4]&0xff;
		if (buf_read[5] != crc8((uchar*)&buf_read[3], 2) ) {
			ret = -1;
			PDEBUG("humidity crc check error, func:%s line:%d\n", __FUNCTION__, __LINE__);
		} else {
			*humidity = 100*tmp_humidity/65535;
			*data_valued |= HUMIDITY_VALUED_MASK;
			PDEBUG("humidity crc ok, humidity:%d%%\n", *humidity);
		}
		return ret;
	} else {
		PDEBUG("i2c_transfer mybe error, please retry again, func:%s line:%d \n", __FUNCTION__, __LINE__);
		return -1;
	}
}

static int read_tmperature_and_humidity(int *tmperature, int *humidity) {
		int retry_times;
		char buf_write[3];
		int ret ;
		int part_data_valued_flag;
		int part_data_valued_flag_retry=0;
	
		retry_times=3;		
retry:    ret = readout_results_for_periodic_mode(tmperature, humidity, &part_data_valued_flag);		    
	       if (ret <0 && retry_times--) {
			part_data_valued_flag_retry |= part_data_valued_flag;
			if ( (part_data_valued_flag_retry&TMPERATURE_VALUED_MASK) && (part_data_valued_flag_retry&HUMIDITY_VALUED_MASK)) {
				return 0;
			}
			msleep(3000);
			goto retry;
	       } else {
			if (retry_times <= 0) {
				PDEBUG("read tmperature and humidity error, func:%s line:%d\n" , __FUNCTION__, __LINE__);
				buf_write[0]=(HEX_CODE_PERIODIC_DATA_ACQUISITION_MODE_MEDIUM_1MPS>>8)&0XFF;
				buf_write[1]=HEX_CODE_PERIODIC_DATA_ACQUISITION_MODE_MEDIUM_1MPS&0XFF;
				//buf_write[2]=crc8(buf_write, 2);
				ret = i2c_master_send(gclient, buf_write, 2);
				if (ret <0) {
					PDEBUG("set sensor in periodic data acquisition mode failed, func:%s line:%d\n" , __FUNCTION__, __LINE__);
					return ret;
				} 
				return -1;
			}
			return 0;
	    }	
}

static long SHT3x_DIS_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	humidity_temperature_st *tmp;
	int tmper=0;
	int humi=0;
	if (!gclient){
		printk("no invalued humidity and temperature device SHT3x_DIS found\n");
		return -1;
	}
	switch (cmd) {
		case READ_TMPERATURE_AND_HUMIDITY:
			if (read_tmperature_and_humidity(&tmper, &humi) <0 ) {
				PDEBUG("read tmperature and humidity error, func:%s line:%d\n", __FUNCTION__, __LINE__);
				return -1;
			} 
			PDEBUG("readed tmp:%x hum:%x\n", tmper, humi);	
			tmp = (	humidity_temperature_st *)arg;
			if (copy_to_user(&(tmp->tmperature), &tmper, sizeof(int))) {
				PDEBUG("copy_to_user error, %s:%d\n", __FUNCTION__, __LINE__);
				return -EFAULT;
			}
			if (copy_to_user(&(tmp->humidity), &humi, sizeof(int))) {
				PDEBUG("copy_to_user error, %s:%d\n", __FUNCTION__, __LINE__);
				return -EFAULT;
			}
			break;
		
		default:
			return -EFAULT;
	}
	return 0;
}


static struct file_operations SHT3x_DIS_fops = {
	.owner	= THIS_MODULE,
	.unlocked_ioctl	= SHT3x_DIS_ioctl,
};


static struct miscdevice SHT3x_DIS_dev = {
        .minor =	MISC_DYNAMIC_MINOR,
        .name =		DEVICE_NAME,
        .fops =		&SHT3x_DIS_fops,
};



static int humidity_temperature_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	char buf_write[3];
	int ret ;
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
	{
		dev_err(&client->dev, "Must have I2C_FUNC_I2C.\n");
		printk("humidity_temperature_probe failed, Must Sourport I2C_FUNC_I2C\n");
		return -ENODEV;
	}

	if (misc_register(&SHT3x_DIS_dev) != 0) {
		printk(KERN_INFO "Could not register misc. dev for SHT3x_DIS\n");
		return -ENODEV;
	}

	buf_write[0]=(HEX_CODE_PERIODIC_DATA_ACQUISITION_MODE_MEDIUM_1MPS>>8)&0XFF;
	buf_write[1]=HEX_CODE_PERIODIC_DATA_ACQUISITION_MODE_MEDIUM_1MPS&0XFF;

	ret = i2c_master_send(client, buf_write, 2);
	
	if (ret<0 ) {
		printk("humidity temperature sensor SHT3x-DIS probe failed\n");
		return -ENODEV;
	}

	printk("humidity_temperature_probe success\n");
	gclient=client;	
	
	return 0;
}

static int humidity_temperature_remove(struct i2c_client *client)
{
	return 0;
}


static const struct i2c_device_id humidity_temperature_SHT3x_DIS_id[] = {
	{ DEVICE_NAME, 0 },
	{ }
};


static struct i2c_driver humidity_temperature_SHT3x_DIS = {
	.probe		= humidity_temperature_probe,
	.remove		= humidity_temperature_remove,
	.id_table	= humidity_temperature_SHT3x_DIS_id,
	.driver = {
		.name	= DEVICE_NAME,
		.owner = THIS_MODULE,
	},
};


static int __devinit SHT3x_DIS_init(void)
{
	printk("register i2c  dev for SHT3x_DIS\n");
	i2c_add_driver(&humidity_temperature_SHT3x_DIS);
	return 0;
}

static void __exit SHT3x_DIS_exit(void)
{
	i2c_del_driver(&humidity_temperature_SHT3x_DIS);
	printk("unregister i2c dev for SHT3x_DIS\n");
}


module_init(SHT3x_DIS_init);
module_exit(SHT3x_DIS_exit);

/* Module information */
MODULE_AUTHOR("xiecf");
MODULE_DESCRIPTION("SHT3x_DIS driver");
MODULE_LICENSE("GPL");