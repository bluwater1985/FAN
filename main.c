/************************************************************************/
/*               (C) Fujitsu Semiconductor Europe GmbH (FSEU)           */
/*                                                                      */
/* The following software deliverable is intended for and must only be  */
/* used for reference and in an evaluation laboratory environment.      */
/* It is provided on an as-is basis without charge and is subject to    */
/* alterations.                                                         */
/* It is the user's obligation to fully test the software in its        */
/* environment and to ensure proper functionality, qualification and    */
/* compliance with component specifications.                            */
/*                                                                      */
/* In the event the software deliverable includes the use of open       */
/* source components, the provisions of the governing open source       */
/* license agreement shall apply with respect to such software          */
/* deliverable.                                                         */
/* FSEU does not warrant that the deliverables do not infringe any      */
/* third party intellectual property right (IPR). In the event that     */
/* the deliverables infringe a third party IPR it is the sole           */
/* responsibility of the customer to obtain necessary licenses to       */
/* continue the usage of the deliverable.                               */
/*                                                                      */
/* To the maximum extent permitted by applicable law FSEU disclaims all */
/* warranties, whether express or implied, in particular, but not       */
/* limited to, warranties of merchantability and fitness for a          */
/* particular purpose for which the deliverable is not designated.      */
/*                                                                      */
/* To the maximum extent permitted by applicable law, FSEU's liability  */
/* is restricted to intentional misconduct and gross negligence.        */
/* FSEU is not liable for consequential damages.                        */
/*                                                                      */
/* (V1.5)                                                               */
/************************************************************************/
/** \file main.c
 **
 ** main file
 **
 ** for support & help please contact mcu_ticket.fseu@de.fujitsu.com
 **
 ** History:
 **   - 2011-06-06  1.0  MSc  First Version
 **   - 2012-10-02  1.1  MSc  Startup settings now in mcuconfig.h
 ************************************************************************/
#include "mcu.h"
#include "base_types.h"
#include "string.h"
#include "main.h"
//#include "I2C.h"

//humidity
//chahumidityr Rx_Data_Buf1[21];
//power
#define _Natural__
#define LED1  PDR0_P04
#define ON 1
#define OFF 0
char temp_led =0;
char time_Nature_50ms;
char time_Nature_flag;
char time_60s_flag;

char time_10MS;
char time_100MS;
char time_1S;
char time_1M;
char time_1H;
char time_5S;
char time_9S;
char time_1000MS;
char Motor_Clk_Hz;
char Motor_Clk_Lh;
char Motor_Stop_Flag;
char Motor_allow_run;
char First_Power_On;
char First_Power_timer;
char temp1[10];
char temp2[10];
char temp3[10];
char tem_data[3];
char hum_data[3];
char Buzzer_onoff_flag;

char count_10ms;
char i;
char i1;
char i2;
char *P1;
char *P2;
unsigned int  Fan_speed;
unsigned int  Fan_speed_temp;

unsigned int  step_motor_mun;
unsigned int  step_motor_mun_bak;
unsigned int  step_set_mun;
unsigned int temp_int;
unsigned time_1ms;
long int tem;
long int hum;
int tem1;

unsigned int use_time;
unsigned int speed_level;
char step_motor_onoff;
char step_motor_bit;
char step_num;
char step_num_bak;
char step_motor_clockwise;
char step_motor_clockwise_bak;
char step_motor_first_run;
char Fan_De_speed;
char Fan_De_speed_timer;
char step_timer_10MS;
char time_5MS;
char timer_1s;
char timer_60s;
char I2c_W_flag1;
char I2c_W_flag2;
char Lighting_Levels;
char I2c_R_Th_Starting;
char I2c_R_Th_Read;
char hum1;
char temH1;
char temL1;
char speed1;
char speed2;
char speed3;
char speed4;
char child_lock;
char Tx_Allow_flag;
char reception_time;
char updata_ready;
extern char display_blink_time;
char	Ext_Pin_flag =0;
char	Fg_time;
char Fg_timer_0 = 0;
char Fg_timer_1 = 0;

const char Step_motor_phase[]={0xe3,0xe7,0xe5,0xed,0xe9,0xf9,0xf1,0xf3};  //顺时针转
extern char ReaDat;
extern char key_value_onoff;
extern char key_value_swing;
extern char key_value_timer;
extern char Buzzer_time;
extern char key_off_flag;
extern char key_onoff;
extern char key_status_swing2;
extern char key_status_swing1;
extern char key_swing_onoff;
extern unsigned int timer_off;
extern char display_allow;
extern char display_value;
extern char key_display_onoff;
extern char key_display_swing;
extern char key_display_timer;
extern char key_status_timer1;
extern char key_status_timer2;
extern char Get_Down_Allow;
extern char net_tx_queue;
extern char Props_Allow;
extern char Tx_Data_Buffer[50];
extern char Rx_Data_Buffer[34];
extern char key_display_Natural;
extern char Natural_Mode;
#define Motor_Clk PDR6_P66
#define Motor_Brk PDR6_P67
#define Motor_Fg  PDR0_P01
#define Buzzer_port PDR1_P10
#define KEY_NUM       2
#define IIC_NUM       1
#define	WriteDeviceAddress      0xa0
#define	ReadDviceAddress        0xa1
#define PAGEWORD		8
#define NOP()		 __asm(" NOP")
#define Step_A PDR6_P62
#define Step_B PDR6_P63
#define Step_C PDR6_P64
#define Step_D PDR6_P65
#define LED1  PDR0_P04
#define LED2  PDR0_P05
#define LED3  PDR0_P06
#define LED4  PDR0_P07
#define Wake_Up PDR0_P03
#define WiFi_LED  PDR1_P01



extern void I2C_W(	unsigned char device,\
			unsigned char *source,\
			unsigned char address,\
			unsigned char count);	//一次操作字节数
/*
unsigned char device,\//;			
unsigned char *source,\//;					//数据源地址
unsigned char address,\//;					//目标地址
unsigned char count);					//一次操作字节数
*/
extern void I2C_R(	unsigned char writecmd,\
			unsigned char readcmd,\
			unsigned char *source,\
			unsigned char address,\
			unsigned char count);//一次操作字节数
/*
unsigned char writecmd,\//;					//器件写命令字 0xa0
unsigned char readcmd,\//;					//器件读命令字 0xa1
unsigned char *source\,//;					//数据源地址
unsigned char address\,//;					//目标地址
unsigned char count);					//一次操作字节数
*/
extern void Read_Measurement(unsigned char *source,unsigned char count);
extern void Starting_Measurement(void);
extern void Key_scan(void);
extern void display_Buzzer(void);
extern void Tx_Wifi_data(void);
extern void Rx_Wifi_data(void);
extern void Result_Wifi_data(void);
extern void Natural_run(void);

void delay_ms(unsigned int count_ms)
{ 
	time_1ms = 0;
	while(time_1ms<count_ms*2)
    	{
		time_1ms++;      
		WDTC=0x35;	//Clear watch dog timer
    	}
}

void Temp_hum_cal(void)
{
	tem=0;
	tem=temp3[0]<<8;
	tem=tem+temp3[1];
	tem=1750*tem;
	tem=tem/0xfffe;
	tem=tem-450;
	tem1=tem;
	tem_data[2]=tem1/0x64;
	tem1=tem1-100*tem_data[2];
	tem_data[1]=tem1/0x0a;
	tem1=tem1-10*tem_data[1];
	tem_data[0]=tem1+0x30;
	tem_data[1]=tem_data[1]+0x30;
	tem_data[2]=tem_data[2]+0x30;
	hum=0;
	hum=temp3[3]<<8;
	hum=hum+temp3[4];
	hum=hum*100;
	hum=hum/0xfffe;
	hum1=hum;
	hum_data[1]=hum1/0x0a;
	hum1=hum1-10*hum_data[1];
	hum_data[0]=hum1+0x30;
	hum_data[1]=hum_data[1]+0x30;
	hum_data[2]=0x30;
}


void MCU_initialization(void)  //ATMLH650   64DM  Y  A7TJDA
{
	char i;
	__DI();
	
	//system clock
	SYCC=0x1c;		//机器时钟无分频
	WATR=0X0a;          //00001010
	PLLC==0xe0;			//主时钟2分频
	SYCC2=0xf1;		//选择主时钟 1111 0001

	SYSC=0xcc;		//0x1100 1100	主时钟振荡，复位脚 ，bit2选择P62/P63/P64/P65/P66/P67为PPG输出
	
	//IO port
	PDR0=0;
	DDR0=0xfc;	//1111 1100
	
	PDR1=0;
	DDR1=0x2f;	//DDR1=0xca;   0010 1111
	
	PDR6=0;
	DDR6=0xfC;	//1111 1100
	
	PDRG=0x06;
	DDRG=0x04;             //0000 0100
	PSSR0=0x04;            //0000 0100
	BRSR0=0X11;            //0010 0010  波特率设为115200
	SMC10=0x0c;            //0000 1100  内部时钟，8位数据位，1位停止位，无校验位
	SMC20=0x40;            //0100 0000   0111 1000
	NOP();
	NOP();
	NOP();    	
	AIDRL=0Xff;

	//外部引脚中断
	//P01为中断输入
	EIC00 = 0x30;	// 0011 0000	P01上升沿触发
	
	
	//Timer初始化
    	T00CR0=0xd2;   //1101 0010		CLK = MCLK/32 = 500KHz
	T00CR1=0xa2;   //1010 0010		
    	TMCR0=0x20;       //0010 0000
	T00DR=0x80;		//128分频,周期256us

	//8/16bit PPG初始化
	/*PCn1:		8/16-bit PPG timer n1 control register				*/
	/*	*/
	/*	*/
	/*PCn0:		8/16-bit PPG timer n0 control register				*/
	/*PPSn1:		8/16-bit PPG timer n1 cycle setting buffer register	*/
	/*PPSn0:		8/16-bit PPG timer n0 cycle setting buffer register	*/
	/*PDSn1:	8/16-bit PPG timer n1 duty setting buffer register	*/
	/*PDSn0:	8/16-bit PPG timer n0 duty setting buffer register	*/
	/*PPGS:		8/16-bit PPG start register						*/
	/*REVC:		8/16-bit PPG output reverse register				*/
	

	
	PC00=0x00;    //PPG SET  0010 1000
	PPS00=0xe0;
	PDS00=0x20;
	
	PC10=0x2c;    //PPG SET  0010 1000
	PPS10=0xac;
	PDS10=0x56;

	PC20=0x2b;              //0010 1101
	PPS20=240;
	PDS20=240;	
	
	PPGS=0x15;             //0001 0101	
	REVC=0x00;
	
	SYSC_PPGSEL=1;
	
	PSSR0=0x04;            //0000 0100
	BRSR0=0X11;            //0010 0010  波特率设为115200
	SMC10=0x0c;            //0000 1100  内部时钟，8位数据位，1位停止位，无校验位
	SMC20=0x40;            //0100 0000   0111 1000
	SMC20_RXE=1;
	SMC20_RIE=1;          //接收中断
		
	TBTC=0x41;		//0100 0001	Enables interrupt     主时钟FCH = 16MHz (1ms interval) 0100 1001
//	UART0_init ();
	InitIrqLevels();	// initialise Interrupt level register and IRQ vector table
	__EI();
}
__interrupt void Time8PpgOutCh00(void)
{
	  PC00_PUF0=0;	  
}

__interrupt void Time8PpgOutCh10(void)
{
	  PC10_PUF0=0;
}

__interrupt void Time8PpgOutCh20(void)
{
     PC20_PUF0=0;
}

__interrupt void Ext_Pin_Interrupt(void)
{
	EIC00_EIR1 = 0;
	
	if(Ext_Pin_flag == 0)
		Fg_time = Fg_timer_0;
	else if(Ext_Pin_flag ==1)
		Fg_time = Fg_timer_1;
	
	Ext_Pin_flag = !Ext_Pin_flag;
	
}
__interrupt void Time8LoadProcess(void)	// 1ms中断
{
	char led_on_off = 1;
	T00CR1_IF=0;	

	if (step_timer_10MS<9)
		step_timer_10MS++;
	else
	{
		step_motor_bit=1;
		step_timer_10MS=0;
				
		if(time_Nature_50ms <3)
			time_Nature_50ms ++;
		else
		{
			time_Nature_50ms =0;
			time_Nature_flag = 1;
			step_motor_bit=1;
		}
		

	       if (timer_1s<99)	
	            timer_1s++;
	       else
	       {
	       	//LED1 = temp_led;
			//temp_led = !temp_led;
		
			timer_1s=0;
			I2c_R_Th_Starting=1;

			if(timer_60s<3)
			{
				timer_60s++;
			}	  
			else
			{
				timer_60s=0;
				time_60s_flag = 1;
			}	
		}
		   
		if (key_display_Natural==1)
		{   
			if (display_blink_time<=99)//15)
				display_blink_time++;
			else
				display_blink_time=0;
		}
		else
			display_blink_time=0;			
	}
	
	if (key_value_swing)
	{	
		step_motor_onoff=1;
		if (step_motor_bit==1)
		{	
			step_motor_bit=0;
			switch (step_num)
			{
				case 0:
			        Step_A=1;
				    Step_B=0;
				    Step_C=0;
				    Step_D=0;
				    break;
			    case 1:
			        Step_A=1;
				    Step_B=1;
				    Step_C=0;
				    Step_D=0;
				    break;	
			    case 2:
			        Step_A=0;
				    Step_B=1;
				    Step_C=0;
				    Step_D=0;
				    break;
			    case 3:
			        Step_A=0;
				    Step_B=1;
				    Step_C=1;
				    Step_D=0;
				    break;						
			    case 4:
			        Step_A=0;
				    Step_B=0;
				    Step_C=1;
				    Step_D=0;
				    break;		
			    case 5:
			        Step_A=0;
				    Step_B=0;
				    Step_C=1;
				    Step_D=1;
				    break;		
		     	case 6:
			        Step_A=0;
				    Step_B=0;
				    Step_C=0;
				    Step_D=1;
				    break;		
			    case 7:
			        Step_A=1;
				    Step_B=0;
				    Step_C=0;
				    Step_D=1;
				    break;		
			    default: 
		            break;
		}

		if (step_motor_mun>0)
		{	
			step_motor_mun--;
        		if (step_motor_clockwise==1)
			{
				if(step_num<7)
					step_num++;
				else
					step_num=0;
			}
			else
			{
				if(step_num>0)
					step_num--;
				else
					step_num=7;	
			}
		}	 
		else
		{
			step_motor_mun=step_set_mun;
			if (step_motor_clockwise==1)
				step_motor_clockwise=0;
			else
				step_motor_clockwise=1;
		}
		step_num_bak=step_num;
		step_motor_clockwise_bak=step_motor_clockwise;
		step_motor_mun_bak=step_motor_mun;
                     				
		}	
	}
	else
	{	
		step_motor_mun=0;
		step_motor_onoff=0;
		Step_A=0;
		Step_B=0;
		Step_C=0;
		Step_D=0;
    } 
	
}
__interrupt void timerbase_timer (void)  //128uS timer
{
 	TBTC_TBIF=0;
	
	if (reception_time<=200)
		reception_time++;
	if(time_5MS < 39)
		time_5MS ++;
	else
		time_5MS =0;
	
	if(time_10MS<78)
		time_10MS++;
	else
	{
		time_10MS=0;
		
		if (time_100MS<10)
			time_100MS++;
		else
		{
			time_100MS=0;
			Fan_De_speed=1;
		   	Get_Down_Allow=1;
		   	net_tx_queue=1;
		   	Tx_Allow_flag=1;
		}             
		count_10ms=count_10ms+1;
		if(Buzzer_onoff_flag==0)
	  	{
			if (Buzzer_time>0)
				Buzzer_time--;   
			else
				PPGS_PEN10=0; 		   		   
		}
		else
			PPGS_PEN10=0;
		if(time_1000MS<100)
			time_1000MS++;
		else
		{
			if (First_Power_timer>0)
				First_Power_timer--;
			if (time_5S>0)
				time_5S--;
			if (time_9S>0)
				time_9S--;			
			time_1000MS=0;
			if(time_1S<59)
				time_1S++;
			else
			{
				if (timer_off>0)
					timer_off--;
				time_1S=0;
				if(time_1M<59)	
					time_1M++;
				else
				{
					time_1M=0;
					if(time_1H<23)
						time_1H++;
					else
						time_1H=0;
				}					
			}
			Props_Allow=1;
			net_tx_queue=1;			
		}
	}	

/*
    if (Motor_Clk_Hz<=Fan_speed)
         Motor_Clk_Hz++;
    else
         Motor_Clk_Hz=0; 
	if (Motor_allow_run==1)
	{	
	    Motor_Brk=1;
	   if (Motor_Clk_Hz>=Motor_Clk_Lh)
       {
           Motor_Clk=1;
        }
        else
       {
            Motor_Clk=0;
        }
	}
*/
	//计算FG信号的周期，10ms一次采样
	if(time_5MS == 1)
	{
		if(Ext_Pin_flag == 0)
		{
			Fg_timer_0 ++;
			Fg_timer_1 = 0;
		}
		else	if(Ext_Pin_flag == 1)
		{
			Fg_timer_0 = 0;
			Fg_timer_1 ++;
		}
	}


}

__interrupt void I2C_Ch0(void)
{
	 NOP();
	 IBCR00_WUF=0;
}
__interrupt void Rx_Tx_Reception(void)
{

	SMC20_RERC=0;
	if(SSR0_RDRF)
  	{    
    		//if (reception_time>=30)
		//ReaDat=0;
		Rx_Data_Buffer[ReaDat]=RDR0;
		ReaDat++;	
		reception_time=0;
		SSR0_RDRF=0;
  	} 	
}


							
void main(void)
{

 
	MCU_initialization();
	Motor_Stop_Flag=0;
	time_Nature_flag = 0;
	Fan_speed=Stop_fan;
	Wake_Up=1;
	Buzzer_time=Buzzer_long;
	key_value_onoff=1;
	First_Power_On=1;
	First_Power_timer=10;
	Lighting_Levels=0x31;
	Buzzer_onoff_flag=0;
	I2c_R_Th_Starting=0;
	updata_ready=0;
	Fan_speed_temp = 225;
	DDRG=0x04;
	PDR1_P13=1;
		
	for(;;)
   	{
		
		if(Lighting_Levels==0x30)       //Lighting  Level max:0  min:2
		{
           		PDS00=0xd0;			
		}	
		else 
		{ 
		    	if (Lighting_Levels==0x31) 
            		{
				PDS00=0x20;
			}
           		else
                		PDS00=0x00;    				
		}
		//if (Buzzer_onoff_flag==0)      //buzzer on/off
		//PPGS_PEN10=0;   
		if (I2c_W_flag1==1)
		{
		    if (step_timer_10MS==3)
			{
               		I2c_W_flag1=0;
				I2C_W(0xa0,temp1,0x30,10);
			   	NOP();
			   	WDTC=0x35;
            		}			  
		}
		
        	WDTC=0x35;
			
		Key_scan();	
		
        	if (Natural_Mode==1)
        	{	
			Natural_run();	
		}	
			
		if (key_onoff==1)
       	{
			Motor_allow_run=1;
			Motor_Stop_Flag=1;
			
			if(Natural_Mode==0)
				PDS20=Fan_speed; 
		}


		else
		{
			if (Motor_Stop_Flag==1)       //关机后慢慢减速
			{

				if (time_100MS==5&&Fan_De_speed==1)
				{	
					Fan_De_speed=0;
					if(Fan_speed<L_speed_fan)
                    			{
						Fan_speed=Fan_speed+5;
 						Motor_allow_run=1;							
						PDS20=Fan_speed; 
					}					     
					else
					{
						Motor_Brk=0;  
						Motor_Clk=0;
						Motor_allow_run=0;
						key_value_swing=0;
 						Motor_Stop_Flag=0;
						Motor_Stop_Flag=0;	
						Fan_speed_temp = 225;
						PDS20=Stop_fan; 
					}
				}				
			}
            		else
            		{
				Motor_Brk=0;  
				Motor_Clk=0;
				key_value_swing=0;
				Motor_allow_run=0;
				PDS20=Stop_fan; 
			}				

		}
		if (key_value_timer>0)
		{
			if (timer_off==0)
			{
				key_onoff=0;
				key_off_flag=1;
				Buzzer_time=Buzzer_long;
				PPGS_PEN10=1; 		
				step_motor_first_run=1;
				key_value_timer=0;
			}
		}

        WDTC=0x35;		
 
    }

}
