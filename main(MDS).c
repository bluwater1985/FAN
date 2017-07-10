/********************************************************************************/
/* Filename:	main.c							 								*/
/* Function:	数码涡旋室外机控器主程序										*/
/* Mcu:			MB89F538														*/
/* Freq:		4.9152MHZ(Cyrstal),Tcy=1.2378us									*/
/* compilier:	Softune workbench												*/

/********************************************************************************/

//================================================================================
/*
	Description about the program:

log:
	2006.08.10
	改压缩机同时运行的组合
	改油平衡处理
	2005.12.28
	改从机故障时4WV乱动作错误
	2005.12.08
	修改供张平现场使用，逻辑见彭12.07邮件
	2005.11.22
	修改供张平现场使用，逻辑见彭11.22邮件
	2005.11.08(V2.1)
	修改MDSB220的能力比较错误，see eng.c
	2005.10.21(V2.1)
	修改从机调试模式下不随主机更新BUG
	修改停机模式下紧急模式未清除BUG
	低压传感器故障按停机处理，原来为紧急运行
	2005.09.23(V2.1)
	通讯明显改善，修正通讯BUG和制冷时高压传感器故障时FAN无输出,修EXV4发热 BUG
	新风机拨码有改动
	2005.09.02(V2.0)
	据郑汉钦反映内机全部掉电时外机照常运行，经查目前通讯上存在问题，具体现象为：
	外机接内机的通讯线断任意一根，外机检测不到内外机通讯故障（MCU接收到50HZ的方波信号），
	两跟通讯线全部断掉都可以检测到通讯故障
	处理方式：1，该通讯处理；2，在硬件上加上拉和下拉电阻
	2005.09.01(V2.0)
	从机通讯故障保护时间由原来3分钟改为分钟
	2005.08.25(V2.0)
	能力补偿使用新逻辑，见20050825彭邮件
	2005.08.19(V2.0)
	能力补偿使用新逻辑
	2005.08.04(V2.0)
	能力补偿使用新逻辑，与内机配套使用
	2005.07.12(V1.2)
	对主从机系统，不允许同时除霜，防止低压故障
	2005.07.08(V1.2)
	改低压故障阀调整功能
	2005.07.07(V1.1)
	加主从机能力平均分配功能
	2005.07.04(V1.0)
	修改压力低压故障不能恢复的错误，增加数码管显示
	2005.06.23(V0.2)
	增加电压型和电流型压力传感器自动识别
	2005.04.05(V0.1)
	完成基本功能，未有的功能有：1，数据记录；2，按键；3，显示
	增加主/从机处理
	2004.11.01（test）

*/
//================================================================================

#define		__CPU_MB89530__
#define		__CPU_MB89530_SERIES

#include	"define.h"				// 自定义的存储器
#include	"includeh.h"			// 函数头文件
#include	"includec.h"			// 函数文件
#include	"math.h"				// 数学头文件

//================================================================================
//	main program
//================================================================================
void main(void)
{
	unsigned char i,j,buf[5],x[5];
	unsigned int t;
	unsigned int temp;
	__DI();									// 关中断

/*
	COMP[0] = 6;
	COMP[1] = 6;
	COMP[2] = 6;
	COMP[3] = 6;
	SCOMP[0] = 5;
	SCOMP[1] = 5;
	SCOMP[2] = 5;
	SCOMP[3] = 5;
	num_comp = 4;
	cap_sys = 24;
	time_chg_queue = 0;
	flags.no1 = 1;
	low_pressure = 14;
	temp_buf[TH1] = 750;
	hi_pressure = 190;
	err[6] = 0xff;
	err[7] = 0x0;
	config[2] = 0;
	queue = q_cool;	

	temp_buf[TH9] = 130;
	temp_buf[TH10] = 345;
	temp_buf[TH11] = 45;
	step[3] = 150;
	hicmin = 150;
	cap_all = 14000;

	for ( i=0; i < num_comp; i++)
	{
		time_comp_run_h[i] = i;
	}
	
	out_stu[2] |= 0xf0;
	unit_set = SET_B2;
	for(;;)
	{
		ctrl_fan();

	}

*/
	init();									// 初始化硬件
	write_MC14094(FAN_EV_OUT);
	disp_code(C_R,C_E,C_S,C_T);				// disp rest
	write_74hc164(dbuf,4 );				//
	init_para();

	j = 0;
	for ( i=0; i<10; i++ )
	{
		delay(10);
		if ( PIN_ERR == 0 )	
			j ++;
	}
	if ( j > 7 )
	{
		disp_code(C_R,D_4,D_1,D_0);			// disp r410
		write_74hc164(dbuf,4 );				//
		for(;;);
	}
        IO_PDR1.byte = 0x06;
	j = 0;
	for ( i=0; i<10; i++ )
	{
		delay(10);
		if ( PIN_ERR == 0 )	
			j ++;
	}        		
        if (j>7)
            R22_HZ=HZ60;
        else
            R22_HZ=HZ50;	
	IO_PDR2.byte = 0x02;
	read_testkey();							// 读测试键
	if ( queue != q_test )
	{
		read_code();						// 读拨码
		selftest();							// 系统自检
	}

	select_ps();							// 压力传感器选择
//	flags.sort_sp = sp_i;				// 电流型的

	COMMIN = txd;
	COMMPC = rxd;							// MAX485 turn to input mode
	IO_SMC11.bit.SOE = 1;					// 允许UO2位为输出，SEE P414
	IO_TCR = 0;
	IO_TMCR.byte = 0x03;					// enable interrupt of timer
	IO_SMC22.byte = txd1mode;
	i = IO_SIDR2;						// clear接收到的数据
	IO_SMC22.bit.RERC = 0;					// clr errors flag
/*
	time_comp_run_h[0]=0;
	time_comp_run_h[1]=1;
	time_comp_run_h[2]=2;
	time_comp_run_h[3]=3;
*/	
	for( ;; )
	{
		__EI();								// 开中断
		if ( queue == q_test )
		{
			if ( COMMPC == rxd && time_byte_pc > 10 )
			{								// 8时主从通讯良好，主与监控不行
				IO_SSD1.bit.TIE = 0;		// disable HS-Txd int
				IO_SSD1.bit.RIE = 1;		// enable HS-Rxd int
				time_byte_pc = 0;
				if ( byte_rxd_pcbak == byte_rxd_pc )// 长度不变
				{
					if ( byte_rxd_pc > 4 )
					{
						comm_test();
					}
					byte_rxd_pc = 0;
				}
				byte_rxd_pcbak = byte_rxd_pc;
			}
		}
		else if ( config[2] & 0x80 )		// 主机接内机
		{
			if ( COMMIN == txd )			// 发送状态
				comm_unit_txd();
			else
				comm_unit_rxd();			// 接收状态

			if ( (COMMPC == rxd) && (time_byte_pc > 8) )
			{								// 8时主从通讯良好，主与监控不行
				IO_SSD1.bit.TIE = 0;		// disable HS-Txd int
				IO_SSD1.bit.RIE = 1;		// enable HS-Rxd int
				time_byte_pc = 0;
				if ( byte_rxd_pcbak == byte_rxd_pc )// 长度不变
				{
					if ( byte_rxd_pc > 5 )
					{
						if (rxd_pc[3] == self_addr )
							comm_pc();
					}
					byte_rxd_pc = 0;
				}
				byte_rxd_pcbak = byte_rxd_pc;
			}
		}
		else	// slave unit
		{
			COMMIN = rxd;
			IO_SMC22.bit.RXE = 0;	// UART RXD1 off
			IO_SMC22.bit.RIE = 0;	// UART RXD1 off
			if ( (COMMPC == rxd) && (time_byte_pc > 8) )
			{								// 8时主从通讯良好，主与监控不行
				time_byte_pc = 0;
				if ( byte_rxd_pcbak == byte_rxd_pc )
				{
					if ( byte_rxd_pc > 15 )
					{
						if ( (rxd_pc[0] == 100 ) || (rxd_pc[0] == 0x80) )
							comm_master();
					}
					byte_rxd_pc = 0;
					for ( i=0;i<len_rxd_pc;i++)
					{
						rxd_pc[i]=0;
					}
				}
				byte_rxd_pcbak = byte_rxd_pc;
			}
		}

		if ( flags.chgpara )
		{
			flags.chgpara = 0;
			for ( i=0;i<5;i++ )
			{
				j = i<<2;
				store_set_para(config+j+4,j+0x10);
			}
		}
		if ( flags.delrom )
		{
			flags.delrom = 0;
			buf[0] =0;
			buf[1] =0;
			buf[2] =0;
			buf[3] =0;
			for ( i=0;i<4;i++ )
			{
				delay(20);
				I2C_W( 0xa0,buf,4*i+0x70,4);
			}
		}
		if ( time_exv >= ms32 )				// 32.0ms 定时
		{
			IO_WDTC = 0x05;				// clear watchdog
			time_exv = 0;
			if ( queue == q_test )		// 测试模式
			{
 				if ( time_chg_queue > 21 )
 				{
					read_code();
				}
				read_feedback();
			}
			else
			{
				drive_exv(0);				// exv1 ctrl
				drive_exv(1);				// exv2 ctrl
				drive_exv(2);				// exv3 ctrl
				drive_exv(3);				// exv4 ctrl

				if ( time_input_det++ >= 2 )
				{
					time_input_det = 0;
					input_det();			// 输入信号检测
				}

				scankey();
				if ( key )
				{
					operatekey();
					write_74hc164(dbuf,4 );
					key = 0;
//					time_disp_dly = 0;
					disp_5s=0;
				}
				flags.anyerr = 0;				// 查询有无故障
				for(i=0;i<10;i++)
				{
					if ( err[i] )
					{
						flags.anyerr = 1;
						break;
					}
				}
				if ( time_disp >= dms500 )		// 500ms update display
				{

					time_disp=0;
					cnt_500ms ++;
					disp_update();				// update display buffer
					if(updata_f==1)
						write_74hc164(dbuf,4 );
				}
			}
		}
		if ( time_base >= s1 )	// 1s
		{
			time_base -= s1;
			time_count();						// time count of system
			if ( flags.sort_sp == sp_i )
			{
				if ( time_adc >= d_time_adc )	// 1s temp measure
				{
					time_adc = 0;
					mea_lowp_i();				// 1s测量压力1次
					if ( unit_set >= SET_B2 )
						mea_hip_i();			// 1s测量压力1次
				}
			}
			if ( flag_comprun & 0x0f )
			{
				for (i=0;i<num_comp;i++)
				{
					j = 1;
					j <<= i;
					if ( flag_comprun & j )
					{
						delay(10);
						j = ~j;
						flag_comprun &= j;
						buf[0]= time_comp_run_h[i];
						buf[1]= time_comp_run_l[i];
						buf[2]= time_comp_run_m[i];
						I2C_W( 0xa0,buf,0x70+i*4,3);// 压缩机运行时间
					}
				}
			}
			if ( (queue != q_reset) && (queue != q_test) )
			{
				if ( config[2] & 0x80 )
				{
				    	if (hi_pressure >= 260)
				    	{
				    		if(frist_hi==0)
				    		{
				        		time_ctrl = d_time_ctrl;
				        		frist_hi=1;
				        	}
				        }
				    	else if (hi_pressure <240)
				    	{
				    		frist_hi=0;
				       		//flags.aa=0;
					}
				}       
				if ( time_ctrl >= d_time_ctrl)
				{  
					//flags.aa=0;
					time_ctrl = 0;
					if ( time_adjexv >= 40 )
						ctrl_exv();			// 控制电子膨胀阀
						
					if ( config[2] & 0x80 )	// 主机
					{
						get_E();			// 能力计算
						nop;
						cal_pwm();			// 压缩机输出控制
						nop;
						get_pwm();			// 根据dig_pwm计算数码压缩机运行时间
					}
					else					// 从机的能力输出控制
					{
						if ( queue == q_def )	// 从机处于除霜模式
						{
							eng_slave = SCOMP[0]+SCOMP[1]+SCOMP[2]+SCOMP[3];
						}
//						if ( queue == q_def_stop )
//							eng_slave = 0;
						ctrl_slave_comp();
					}
				}
				if ( config[2] & 0x80 )		// 主机
				{
					ctrl_fix_comp(m_u);		// 控制定速压缩机
				}
				else
				{
					ctrl_fix_comp(s_u);		// 控制定速压缩机
				}
			}
		}
	}
}

//================================================================================
// end of file
//================================================================================