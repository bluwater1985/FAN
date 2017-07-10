/********************************************************************************/
/* Filename:	main.c							 								*/
/* Function:	�����������������������										*/
/* Mcu:			MB89F538														*/
/* Freq:		4.9152MHZ(Cyrstal),Tcy=1.2378us									*/
/* compilier:	Softune workbench												*/

/********************************************************************************/

//================================================================================
/*
	Description about the program:

log:
	2006.08.10
	��ѹ����ͬʱ���е����
	����ƽ�⴦��
	2005.12.28
	�Ĵӻ�����ʱ4WV�Ҷ�������
	2005.12.08
	�޸Ĺ���ƽ�ֳ�ʹ�ã��߼�����12.07�ʼ�
	2005.11.22
	�޸Ĺ���ƽ�ֳ�ʹ�ã��߼�����11.22�ʼ�
	2005.11.08(V2.1)
	�޸�MDSB220�������Ƚϴ���see eng.c
	2005.10.21(V2.1)
	�޸Ĵӻ�����ģʽ�²�����������BUG
	�޸�ͣ��ģʽ�½���ģʽδ���BUG
	��ѹ���������ϰ�ͣ������ԭ��Ϊ��������
	2005.09.23(V2.1)
	ͨѶ���Ը��ƣ�����ͨѶBUG������ʱ��ѹ����������ʱFAN�����,��EXV4���� BUG
	�·�������иĶ�
	2005.09.02(V2.0)
	��֣���շ�ӳ�ڻ�ȫ������ʱ����ճ����У�����ĿǰͨѶ�ϴ������⣬��������Ϊ��
	������ڻ���ͨѶ�߶�����һ���������ⲻ�������ͨѶ���ϣ�MCU���յ�50HZ�ķ����źţ���
	����ͨѶ��ȫ���ϵ������Լ�⵽ͨѶ����
	����ʽ��1����ͨѶ����2����Ӳ���ϼ���������������
	2005.09.01(V2.0)
	�ӻ�ͨѶ���ϱ���ʱ����ԭ��3���Ӹ�Ϊ����
	2005.08.25(V2.0)
	��������ʹ�����߼�����20050825���ʼ�
	2005.08.19(V2.0)
	��������ʹ�����߼�
	2005.08.04(V2.0)
	��������ʹ�����߼������ڻ�����ʹ��
	2005.07.12(V1.2)
	�����ӻ�ϵͳ��������ͬʱ��˪����ֹ��ѹ����
	2005.07.08(V1.2)
	�ĵ�ѹ���Ϸ���������
	2005.07.07(V1.1)
	�����ӻ�����ƽ�����书��
	2005.07.04(V1.0)
	�޸�ѹ����ѹ���ϲ��ָܻ��Ĵ��������������ʾ
	2005.06.23(V0.2)
	���ӵ�ѹ�ͺ͵�����ѹ���������Զ�ʶ��
	2005.04.05(V0.1)
	��ɻ������ܣ�δ�еĹ����У�1�����ݼ�¼��2��������3����ʾ
	������/�ӻ�����
	2004.11.01��test��

*/
//================================================================================

#define		__CPU_MB89530__
#define		__CPU_MB89530_SERIES

#include	"define.h"				// �Զ���Ĵ洢��
#include	"includeh.h"			// ����ͷ�ļ�
#include	"includec.h"			// �����ļ�
#include	"math.h"				// ��ѧͷ�ļ�

//================================================================================
//	main program
//================================================================================
void main(void)
{
	unsigned char i,j,buf[5],x[5];
	unsigned int t;
	unsigned int temp;
	__DI();									// ���ж�

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
	init();									// ��ʼ��Ӳ��
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
	read_testkey();							// �����Լ�
	if ( queue != q_test )
	{
		read_code();						// ������
		selftest();							// ϵͳ�Լ�
	}

	select_ps();							// ѹ��������ѡ��
//	flags.sort_sp = sp_i;				// �����͵�

	COMMIN = txd;
	COMMPC = rxd;							// MAX485 turn to input mode
	IO_SMC11.bit.SOE = 1;					// ����UO2λΪ�����SEE P414
	IO_TCR = 0;
	IO_TMCR.byte = 0x03;					// enable interrupt of timer
	IO_SMC22.byte = txd1mode;
	i = IO_SIDR2;						// clear���յ�������
	IO_SMC22.bit.RERC = 0;					// clr errors flag
/*
	time_comp_run_h[0]=0;
	time_comp_run_h[1]=1;
	time_comp_run_h[2]=2;
	time_comp_run_h[3]=3;
*/	
	for( ;; )
	{
		__EI();								// ���ж�
		if ( queue == q_test )
		{
			if ( COMMPC == rxd && time_byte_pc > 10 )
			{								// 8ʱ����ͨѶ���ã������ز���
				IO_SSD1.bit.TIE = 0;		// disable HS-Txd int
				IO_SSD1.bit.RIE = 1;		// enable HS-Rxd int
				time_byte_pc = 0;
				if ( byte_rxd_pcbak == byte_rxd_pc )// ���Ȳ���
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
		else if ( config[2] & 0x80 )		// �������ڻ�
		{
			if ( COMMIN == txd )			// ����״̬
				comm_unit_txd();
			else
				comm_unit_rxd();			// ����״̬

			if ( (COMMPC == rxd) && (time_byte_pc > 8) )
			{								// 8ʱ����ͨѶ���ã������ز���
				IO_SSD1.bit.TIE = 0;		// disable HS-Txd int
				IO_SSD1.bit.RIE = 1;		// enable HS-Rxd int
				time_byte_pc = 0;
				if ( byte_rxd_pcbak == byte_rxd_pc )// ���Ȳ���
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
			{								// 8ʱ����ͨѶ���ã������ز���
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
		if ( time_exv >= ms32 )				// 32.0ms ��ʱ
		{
			IO_WDTC = 0x05;				// clear watchdog
			time_exv = 0;
			if ( queue == q_test )		// ����ģʽ
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
					input_det();			// �����źż��
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
				flags.anyerr = 0;				// ��ѯ���޹���
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
					mea_lowp_i();				// 1s����ѹ��1��
					if ( unit_set >= SET_B2 )
						mea_hip_i();			// 1s����ѹ��1��
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
						I2C_W( 0xa0,buf,0x70+i*4,3);// ѹ��������ʱ��
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
						ctrl_exv();			// ���Ƶ������ͷ�
						
					if ( config[2] & 0x80 )	// ����
					{
						get_E();			// ��������
						nop;
						cal_pwm();			// ѹ�����������
						nop;
						get_pwm();			// ����dig_pwm��������ѹ��������ʱ��
					}
					else					// �ӻ��������������
					{
						if ( queue == q_def )	// �ӻ����ڳ�˪ģʽ
						{
							eng_slave = SCOMP[0]+SCOMP[1]+SCOMP[2]+SCOMP[3];
						}
//						if ( queue == q_def_stop )
//							eng_slave = 0;
						ctrl_slave_comp();
					}
				}
				if ( config[2] & 0x80 )		// ����
				{
					ctrl_fix_comp(m_u);		// ���ƶ���ѹ����
				}
				else
				{
					ctrl_fix_comp(s_u);		// ���ƶ���ѹ����
				}
			}
		}
	}
}

//================================================================================
// end of file
//================================================================================