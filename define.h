/*===============================================================================
// Filename:	defineout.h
// Function:	�����������������ͷ�ļ�
// Mcu:			MB89F538PFM
// Freq:		6MHZ(Cyrstal),Tcy=0.5us
// compilier:	Softune workbench
// Ver:			test
// CreatDate:	2004-11-04
//=============================================================================*/

#ifndef		__define
#define		__define
#define		__CPU_MB89530__
#define		__CPU_MB89530_SERIES
#include	"_mb89530.h"

	#define	NEWPCB
	#define	nop			__wait_nop()
	#define	clrwdt()	(IO_WDTC = 0x05)	// clear watchdog

	#define		version		24

//==============================================================================
//	Ӳ���Ķ���
//	��������ѹ������ϵͳ��ʹ��A��
//	����ѹ�������ϵ�ϵͳ��ʹ��B��
//	P0:EXV1
//	P2:EXV2
//	P1:EXV3
//	P3:EXV4
//  P53<-->P13
//	P55<-->P30

//==============================================================================
	#define	RLY_ON		1
	#define	RLY_OFF		0

	#define	RLY1			IO_PDR0.bit.P01
	#define	RLY2			IO_PDR0.bit.P02
	#define	RLY3			IO_PDR0.bit.P03

	#ifndef	NEWPCB
	#define	RLY4			IO_PDR5.bit.P55
	#define	RLY7			IO_PDR5.bit.P53
	#else
	#define	RLY4			IO_PDR3.bit.P30
	#define	RLY7			IO_PDR1.bit.P13
	#endif

	#define	RLY5			IO_PDR4.bit.P40
	#define	RLY6			IO_PDR4.bit.P41
	#define	RLY8			IO_PDR2.bit.P22
	#define	RLY9			IO_PDR2.bit.P23

/*==============================================================================
//	ֻʹ��A��ʱ���������
//=============================================================================*/

	#define	cfg1_4WV		RLY6			// 4WVa
	#define	cfg1_FANH		RLY5			// ����
	#define	cfg1_FANL		RLY4			// ����
	#define	cfg1_EV1		RLY3			// ��ŷ�1
	#define	cfg1_EV2		RLY2			// ��ŷ�2

/*===============================================================================
//	ʹ��A���B��ʱ���������
//==============================================================================*/

	#define	cfg2_COMP4		RLY6			// ����3
	#define	cfg2_4WVA		RLY5			// 4WVa
	#define	cfg2_4WVB		RLY4			// 4WVb

	#define	cfg2_FANH1		0x80			// B�� ����
	#define	cfg2_FANL1		0x40			// B�� ����
	#define	cfg2_FANH2		0x20			// B�� ����
	#define	cfg2_FANL2		0x10			// B�� ����
	#define	cfg2_FANH3		0x08			// B�� ����
	#define	cfg2_FANL3		0x04			// B�� ����
	#define	cfg2_EV1		0x02			// B�� ��ŷ�1
	#define	cfg2_EV2		0x01			// B�� ��ŷ�2

/*===============================================================================
//	������Ϣ����
//==============================================================================*/
	#define	cfg_COMP1		RLY9			// ����ѹ����
	#define	cfg_COMP2		RLY8			// ����1
	#define	cfg_COMP3		RLY7			// ����2

	#define	PWM_V		IO_PDR0.bit.P00		// PWM���

	#define	COMMIN		IO_PDR3.bit.P31		// �����ڻ�ͨѶRS485���ƣ�1/0������/����

	#define	I2C_SDA		IO_PDR4.bit.P42
	#define	I2C_SCK		IO_PDR4.bit.P43
	#define	COMMPC		IO_PDR4.bit.P44		// ����ͨѶRS485���ƣ�1/0������/����

	#define	SDA_DIR		IO_DDR4.bit.P42
	#define	SCK_DIR		IO_DDR4.bit.P43

	#ifndef	NEWPCB
	#define	INH		IO_PDR1.bit.P13		// INH = 0
	#define	SDA_14094	IO_PDR3.bit.P30		// 14094.SDA & 164.SDA
	#define	SDA_164		IO_PDR3.bit.P30		// 164.SDA
	#else
	#define	INH		IO_PDR5.bit.P53		// INH = 0
	#define	SDA_14094	IO_PDR5.bit.P55		// 14094.SDA & 164.SDA
	#define	SDA_164		IO_PDR5.bit.P55		// 164.SDA
	#endif

	#define	HI_PRE		0x01				// ��ѹ���˿�
	#define	LO_PRE		0x02				// ��ѹ���˿�
	#define	DIG_OVER	0x04				// ����ѹ�������ؼ��
	#define	FIX_OVER1	0x08				// ����ѹ����1���ؼ��
	#define	FIX_OVER2	0x10				// ����ѹ����2���ؼ��
	#define	FIX_OVER3	0x20				// ����ѹ����3���ؼ��


	#define	CS_14094	IO_PDR5.bit.P54		// 14094.CS
	#define	CLK_14094	IO_PDR5.bit.P57		// 14094.CLK
	#define	CLK_164		IO_PDR5.bit.P56		// 164.Clk

	#define	PIN_ERR		        IO_PDR6.bit.P60	// ���ϼ�⣬����Ϊ0������Ϊ1
	#define	K1			IO_PDR6.bit.P61	//
	#define	K2			IO_PDR6.bit.P62	//
	#define	K3			IO_PDR6.bit.P63	//
	#define	K4			IO_PDR6.bit.P64	//

	#define	PORT_EXV1	IO_PDR1.byte
	#define	PORT_EXV2	IO_PDR3.byte
	#define	PORT_EXV3	IO_PDR2.byte
	#define	PORT_EXV4	IO_PDR0.byte

/*===============================================================================
	���ݵĶ���
===============================================================================*/
	#define	max_unit		32//48		// ����ڻ�֧������
	#define	len_rxd_in		82			// �����ڻ����ݳ���
	#define	len_rxd_pc		72			// �����ڻ����ݳ���

	#define	CH_HI			2			// ADC1 ��ѹ������
	#define	CH_LOW			1			// ADC2 ��ѹ������

	#define	SET_B1			2			// MDSB080~MDSA120
	#define	SET_B2			3			// MDSB150
	#define	SET_B3			4			// MDSA180~MDSA220
	#define	SET_B4			5			// MDSA260~MDSA320

	#define	FSTOP			0
	#define	FLP 			1
	#define	FL   			2
	#define	FHL 			3
	#define	FH   			4
	#define	FM				5
	#define	FML				6
	#define	FHM				7
        #define P3                     130
        #define P4                     160
        #define P5                     170
        #define P6                     180
	#define	offmode			0			// �ػ�
	#define	coolmode		1			// ����
	#define	heatmode		2			// ����
	#define	automode		3			// �Զ�
	#define	fanmode			4			// �ͷ�
	#define	drymode			5			// ��ʪ
	#define	defmode			6			// ��˪
	#define	testmode		7			// �����

/* ϵͳ���ж���*/
	#define	q_null		 	0			// �ػ�״̬
	#define	q_reset		 	1			// ϵͳ��λ����
	#define	q_cool_start 	2			// ���俪������
	#define	q_cool		 	3			// ������������
	#define	q_cool_stop	 	4			// ����ػ�����
	#define	q_def_start	 	5			// ��˪��ʼ����
	#define	q_def		 	6			// ��˪��������
	#define	q_def_stop		7			// ��˪��������
	#define	q_heat_start 	8			// ���ȿ�������
	#define	q_heat 		 	9			// ������������
	#define	q_heat_stop  	10			// ���ȹػ�����
	#define	q_err		 	11			// ѹ�����ߵ�ѹ��������
	#define	q_err_protect	12			// ���Թ�����������
	#define	q_test			13			// ��������
	#define	q_openexv		14			// ����

//�� err_cnt���ֵ�λ��
//	#define	edov			0			// �������
//	#define	efov1			1			// ����1����
//	#define	efov2			2			// ����2����
//	#define	efov3			3			// ����3����
	#define	ehi				4			// 0:��ѹ
	#define	elo				5			// 1:��ѹ

	#define	h6				21600		// 6hour for oil recovery heat mode
	#define	h4				14400		// 4hour for oil recovery cool mode

	#define	m45				2700		// 45min
	#define	m25				25			// 25min

	#define	m5				5			// 5min
	#define	m4				240			// 4min
	#define	m3				120			// 3min
	#define	m2				2			// 2min
	#define	m1				60			// 1min
	#define	s320			320			// 320s
	#define	s280			280			// 10min -320s
	#define	s55				55			// 55s for 4_wv exchange
	#define	s5				156			// 32*152 = 5s
	#define	s2				62			// 32*62 = 2s
	#define	s1				150			// 6.66*150=1s

	#define	ms1500			1500		// 1500ms
	#define	ms500			500			// 500ms
	#define	ms200			200			// 200ms
	#define	ms100			100			// 100ms
	#define	ms50			50			// 50 ms for rec ack timer
	#define	ms10			10			// 10ms
	#define	tm1ms			64307		// 16bit timer/count timer for 1ms
	#define	ms32			32			// 32ms��for exv drive

	#define	d_time_hex		5			// �Ƚ����л�ʱ��������λΪS
	#define	d_time_fan		30			// ����л�ʱ��������λΪS
	#define	d_time_comp_off	5			// ѹ�����ر��л����
	#define	d_time_comp_on	40			// ѹ���������л����

	#define	d_time_recwait	10			// ���յȴ�ʱ��10ms

	#define	d_time_ctrl		40			// 40s
	#define	d_time_adc		150		// 0.5s

	#define	dms5000			750			// 5s(��ʾ��������Ϊ1/150s)
	#define	dms2000			300			// 2s(��ʾ��������Ϊ1/150s)
	#define	dms1500			225			// 1.5s(��ʾ��������Ϊ1/150s)
	#define	dms1000			150			// 1s(��ʾ��������Ϊ1/150s)
	#define	dms500			75			// 0.5s(��ʾ��������Ϊ1/150s)

	#define	sp_i			0			// ������ѹ��������
	#define	sp_u			1			// ��ѹ��ѹ��������

	#define	output			1
	#define	input			0

	#define	frame_loop		5			// ͨѶ��ѯ֡

	#define	target_superheat_max	20	// ���Ŀ����ȶȣ�����10��
	#define	target_superheat_min	-20	// ��СĿ����ȶȣ�����10��

	#define	D_0				0xC0
	#define	D_1				0xF9
	#define	D_2				0xA4
	#define	D_3				0xB0
	#define	D_4				0x99
	#define	D_5				0x92
	#define	D_6				0x82
	#define	D_7				0xF8
	#define	D_8				0x80
	#define	D_9				0x90
	#define	D_A				0x88
	#define	D_B				0x83
	#define	D_C				0xc6//A7
	#define	D_D				0xA1
	#define	D_E				0x86
	#define	D_F				0x8E

	#define	C_A				0x88
	#define	C_B				0x83
	#define	C_C				0xc6//A7
	#define	C_D				0xA1
	#define	C_E				0x86
	#define	C_F				0x8E
	#define	C_H				0x89
	#define	C_L				0xC7
	#define	C_N				0xC8
	#define	C_o				0xA3
	#define	C_O				0xC0
	#define	C_P				0x8C
	#define	C_R				0xAF
	#define	C_S				0x92
	#define	C_T				0x87
	#define	C_U				0xC1
	#define	C_Y				0x91
	#define	C_X				0xff
	#define	line			0xbf		// '-'
	#define	C_DOT			0x7f		// "."
	#define	bline			0xF7		// '_'

	#define	rxd				0			// for RS485 dir,0 rec
	#define	txd				1			// for RS485 dir,1 txd

	#define	txd1mode		0x39		// set uart1 as txd mode rxd1mode
	#define	rxd1mode		0x52		// set uart1 as rxd mode
	#define	txd2mode		0x30		// set uart2 as txd mode
	#define	rxd2mode		0x08		// set uart2 as rxd mode

	#define	TH1				0			// �����¶ȴ�����
	#define	TH2				1			// 1#�����¶ȴ�����
	#define	TH3				2			// 1#�����¶ȴ�����
	#define	TH4				3			// 2#�����¶ȴ�����
	#define	TH5				4			// 2#�����¶ȴ�����
	#define	TH6				5			// 3#�����¶ȴ�����
	#define	TH7				6			// 3#�����¶ȴ�����
	#define	TH8				7			// �����¶ȴ�����
	#define	TH9				8			// �����¶ȴ�����
	#define	TH10			        9			// ������¶ȴ�����
	#define	TH11			        10			// ������¶ȴ�����
	#define	TH12			        11			// �����¶ȴ�����

	#define	dir_exv1		0x01		// �������ͷ�1�˶�����
	#define	dir_exv2		0x02		// �������ͷ�2�˶�����
	#define	dir_exv3		0x04		// �������ͷ�3�˶�����
	#define	dir_exv4		0x08		// �������ͷ�4�˶�����
	#define	dir_exv1bak		0x10		// �������ͷ�1�ϴ��˶�����
	#define	dir_exv2bak		0x20		// �������ͷ�2�ϴ��˶�����
	#define	dir_exv3bak		0x40		// �������ͷ�3�ϴ��˶�����
	#define	dir_exv4bak		0x80		// �������ͷ�4�ϴ��˶�����

	#define	psw_openexv		0x3366		// ����
	#define	psw_def			0xe001		// �ֶ���˪
	#define	psw_clrerr		0xe002		// ����ϼ�¼
	#define	psw_serve		0x0755		// ��������
	#define	psw_factory		0xeb00		// ��������

	#define	dm_run_mode		0			//��ʾ����ģʽ
	#define	dm_curr_para	        1			//��ʾʵʱ����
	#define	dm_set_para		2			//��ʾ���ò���
	#define	dm_curr_err		3			//��ǰ�Ĺ��ϴ���
	#define	dm_his_err		4			//����Ĺ��ϴ���
	#define	dm_unit_para	        5			//��ʾ�ڻ�����/ʵʱ����
	#define	dm_operate		6			//��ʾ����
	#define	dm_modify_para	        7			//��ʾ����

	#define	max_dispmode	8			//�����ʾģʽ��
	#define	max_curr_para	23			//��ʾʵʱ����
	#define	max_set_para	23			//��ʾ���ò���
	#define	max_scan_para	3			//��ʾ��ѯ�����ò���
	#define	max_curr_err	4			//��ǰ�Ĺ��ϴ���
	#define	max_his_err	16			//����Ĺ��ϴ���
	#define	max_unit_para	18			//��ʾ�ڻ�����/ʵʱ����
	#define	max_modify_para	16			//��ʾ�ڻ�����/ʵʱ����
	#define	max_psw			7			//��ʾ����

	#define	keyspd		7				// �����ٶȿ���
	#define	key1		1
	#define	key2		2
	#define	key3		3
	#define	key4		4

	#define	addr_para	2	// ���ò�����EEPROM�е���ʼ��ַ
        #define HZ50            0
        #define HZ60            1
        #define EIC1            90
        #define EIC2            90
        #define EIC3            90 
        #define EIC4            90  
        #define EIC5            90        
        #define EIC6            90
// ���²�����config�е�λ��
//	version				0
//	sw1					1
//	sw2					2
//	sw3					3
//	����4������̻��������ã�����16���������
	#define	DefA		4	//��˪�����A�㣨-15~-2�棬Ĭ��Ϊ-6�棬�仯��Ϊ1�棩�������ű�ʾ
	#define	DefB		5	//��˪�����B�㣨-30~-15�棬Ĭ��Ϊ-24�棬�仯��Ϊ1�棩�������ű�ʾ
	#define	DefTemp		6	//��˪�����¶ȣ�5~20��,Ĭ��Ϊ12�棬�仯��Ϊ1�棩��ʵ��ֵ
	#define	DefIT		7	//��˪���ʱ�䣨25~90min��Ĭ��Ϊ45min���仯��Ϊ1min����ʵ��ֵ        
	#define	DefRT		8	//��˪����ʱ�䣨5~15min��Ĭ��Ϊ10min���仯��Ϊ1min����ʵ��ֵ         
	#define	NT			9	//������ʱʱ�䣨3~9hour��Ĭ��Ϊ6hour���仯��Ϊ1hour����ʵ��ֵ
	#define	nStep1		10	//����ʱ������ϵ��step1��0.1~5��Ĭ��Ϊ1���仯��Ϊ0.1�����Ŵ�10������
	#define	nStep2		11	//����ʱ������ϵ��step2��0~5��Ĭ��Ϊ0.5���仯��Ϊ0.1�����Ŵ�10������
	#define	TscA1		12	//���ȶ��¶�1��0~TscA2��,Ĭ��Ϊ32�棬�仯��Ϊ1�棩��ʵ��ֵ                      
	#define	TscA2		13	//���ȶ��¶�2��TscA1~50��,Ĭ��Ϊ40�棬�仯��Ϊ1�棩��ʵ��ֵ                     
	#define	TscT1		14	//�����Ŀ���¶�1��0~TscT2,Ĭ��Ϊ3�棬�仯��Ϊ1�棩��ʵ��ֵ                         
	#define	TscT2		15	//�����Ŀ���¶�1��TscT1~TscT3,Ĭ��Ϊ8�棬�仯��Ϊ1�棩��ʵ��ֵ                     
	#define	TscT3		16	//�����Ŀ���¶�1��TscT2~50��,Ĭ��Ϊ12�棬�仯��Ϊ1�棩��ʵ��ֵ                     
	#define	factor_j	17	//���Ȳ�����������
	#define	factor_m	18	//��������˥��ϵ��
	#define	umid		19	//�ڻ������¶�

// 1����ʾ���ʵʱ���� ���룺0PXX ��22��
/*
00���������ͷ�1����
01���������ͷ�2����
02���������ͷ�3����
03���������ͷ�4����
04������������
05������ѹ����PWM�ٷֱ�
06��TH1
07��TH2
08��TH3
09��TH4
10��TH5
11��TH6
12��TH7
13��TH8
14��TH9
15��TH10
16��TH11
17��TH12
18����ѹ
19����ѹ
20�������ǰʵ�ʹ��ȶ�
21�������ǰĿ����ȶ�
22���ڻ�����ƽ���¶�
*/

// 2����ʾ���Ӳ����Ϣ/���ò��� ���룺0CXX ��30��
/*
00���������汾
01�������ַ��
02������A/B
03������/�ȱ�C/H
04�������ڻ�����
05�����÷���ʼ����
06����������
07��DefA
08��DefB
09��DefTemp
10��DefIT
11��DefRT
12��NT
13��nStep1
14��nStep2
15��TscA1
16��TscA2
17��TscT1
18��TscT2
19��TscT3
20��factor_j
21��factor_m
22��pip3
*/

// 3����ʾ��ǰ���Թ��� ���룺ECXX ����
// 4������Ĺ��ϴ��� ���룺ESXX ��16��
// 5����ʾ���� ���룺----
// 6����ʾ�ڻ�ʵʱ���� ���룺UPXX ��
/*
01���ڻ�����汾
02������
03������0��MCC��1��MCK��2��MCM��3��MWM��4��MDB��
04���߿��������¶�
05���߿�������ģʽ��STOP��ͣ����COOL�����䣻HEAT�����ȣ�FAN���ͷ磻DRY����ʪ��
06���߿������÷��٣�F0��ͣ��F1�����٣�F2�����٣�F3�����٣�F4���Զ���
07���ڻ�����ģʽ��STOP��ͣ����COOL�����䣻HEAT�����ȣ�FAN���ͷ磻DRY����ʪ��DEF����˪��TEST������
08���ڻ��������ͷ�����
09���ڻ���������ٷֱ�
10���ڻ������¶�
11���ڻ������¶�
12���ڻ������¶�
13���ڻ��ط��¶�
14�����ϲ�ѯ
*/

/*===============================================================================
	λ���ݶ���
================================================================================*/
//err[6]
	#define	bit_err_sys		7	// ϵͳ����
	#define	bit_err_rom		6	// ����������
	#define	bit_err_low		5	// ��ѹ����
	#define	bit_err_hi		4	// ��ѹ����
	#define	bit_err_f3ov	3	// FIX3����
	#define	bit_err_f2ov	2	// FIX2����
	#define	bit_err_f1ov	1	// FIX1����
	#define	bit_err_dov		0	// DIG����

//err[7]
	#define	bit_err_scom	        7	// �ӻ�ͨѶ
	#define	bit_err_r407	        6	// ��ýй©
	#define	bit_err_tsca	        5	// ���ȶ�̫С
	#define	bit_err_urg		4	// ��������
	#define	bit_err_out		3	// �����¶ȹ��߹��ͱ���
	#define	bit_err_4wv		2	// 4WV����
	#define	bit_err_comm	        1	// ͨѶ����
	#define	bit_err_dhi		0	// �����¶ȹ���

//err[8]
	#define	bit_err_th8		7	// TH8��·/��·
	#define	bit_err_th7		6	// TH7��·/��·
	#define	bit_err_th6		5	// TH6��·/��·
	#define	bit_err_th5		4	// TH5��·/��·
	#define	bit_err_th4		3	// TH4��·/��·
	#define	bit_err_th3		2	// TH3��·/��·
	#define	bit_err_th2		1	// TH2��·/��·
	#define	bit_err_th1		0	// TH1��·/��·

//err[9]
	#define	bit_err_nocom	        6	// �����ͨѶȫ��
	#define	bit_err_ls		5	// ��ѹ��������·/��·
	#define	bit_err_hs		4	// ��ѹ��������·/��·
	#define	bit_err_th12	        3	// TH12��·/��·
	#define	bit_err_th11	        2	// TH11��·/��·
	#define	bit_err_th10	        1	// TH10��·/��·
	#define	bit_err_th9		0	// TH9��·/��·


	#define	comp1_on		0	// ������ѹ����1����
	#define	comp2_on		1	// ������ѹ����2����
	#define	comp3_on		2	// ������ѹ����3����
	#define	comp4_on		3	// ������ѹ����4����
	#define	comp1_off		4	// �ض���ѹ����1����
	#define	comp2_off		5	// �ض���ѹ����2����
	#define	comp3_off		6	// �ض���ѹ����3����
	#define	comp4_off		7	// �ض���ѹ����4����

	#define	m_u				1
	#define	s_u				0

#define		toilb		5400
//#define		toilb		300		//cuimin20071022 test
#define		toilr		5400	// 1.5hour
//#define		toilr		300		//cuimin20071022 test

unsigned char comprunflag;		// ѹ����on/off requare flag
unsigned char compstu;
unsigned char crunning;
/*===============================================================================
	��־λ����
================================================================================*/

struct flag
{
	unsigned char USE_A			:1;	// ��ʹ����A��SET_A1 SET_A2 SET_B1
	unsigned char delrom		:1;	// 0/1,����ⲿ������
	unsigned char anyerr		:1;	// 0/1,����й���
	unsigned char fleshwin		:1;	// 0/1,��׼/�·����
//	unsigned char oil_ban		:1;	// 0/1,no/��ƽ��
//	unsigned char oil_rec		:1;	// 0/1,no/�ͻָ�
	unsigned char fend			:1;	// 0/1
	unsigned char run_heat		:1;	// 0/1,�״���������
	unsigned char dir			:1;	// 0/1,����dec/inc
	unsigned char chgpara		:1;	// 0/1,�޸����ò���
	unsigned char inc			:1;	// 0/1,����
	unsigned char dec			:1;	// 0/1,����
	unsigned char incstop		:1;	// 0/1,����ֹͣ
	unsigned char decstop		:1;	// 0/1,����ֹͣ
	unsigned char slave			:1;	// 0/1,��/�дӻ�
//	unsigned char fdef			:1;	// 0/1,������˪
	unsigned char sort_sp		:1;	// 0/1,current/voltage
	unsigned char no1			:1;	// 0/1,�״ο�������
	unsigned char dlt_eng		:1;	// 0/1,���¹��߼�������
	unsigned char deg			:1; // 0/1,�޼���
	unsigned char or		:3;	// 0/1,��
	unsigned char ob			:1;	// 0/1,��ƽ��
	unsigned char cd		:1;	// 0/1,ѹ������ʱ��������
	//unsigned char aa		:1;
        unsigned char cnt_cap1           :1;				// ��������0.7~1.0�����ü�����
        unsigned char cnt_cap2		:1;		// ��������1.0~1.2�����ü�����
        unsigned char sh_out_hig        :1;   //�������ȶȹ��߹��䷧���ڱ�־
        unsigned char first_sh_out_hig  :1;    //�״λ������ȶȹ��߹��䷧���ڱ�־
        unsigned char d_def_hi		:1;		//��˪ʱ��ѹ���� cuimin20071025
}flags;

/*===============================================================================
//	ȫ�ֱ�������
===============================================================================*/

unsigned char flag_comprun;			// ��¼ѹ�������б��
//D0:COMP1
//D1:COMP2
//D2:COMP3
//D3:COMP4

unsigned char Tsct;				// Ŀ����ȶ�(�Ŵ�10��)
int Tsca;					// ʵ�ʹ��ȶ�(�Ŵ�10��)
int step1;					// ����ʵ�ʹ��ȶȺ�Ŀ����ȶȼ���Ŀ��ȱ仯(�Ŵ�10��)
int step2[3];					// ���ݽ��̺ͻ����¶ȼ���Ŀ��ȱ仯(�Ŵ�10��)
unsigned char R22_HZ;                           //50HZ��60HZ������
unsigned char num_in;				// �ڻ�����
unsigned char cap_sys;				// ϵͳ�ܹ��ʣ�100X
unsigned int  cap_all_bak;			// ��һ�������ڻ�����������
unsigned int  cap_all;				// ���������ڻ���������������1000��
unsigned int  cap_act;				// ʵ���������󱶷�
unsigned int  cap_all_temp;                     //
unsigned int  eng_bc;				// ����������
unsigned char cnt_th1;				// �������������ü�����(TH1����)
unsigned char cnt_hi;				// �������������ü�����(��ѹ����)
unsigned char eng_inv;				// �������������ü�ʱ��
unsigned char menddef;				// ����������˪
unsigned char senddef;				// �ӻ�������˪
//unsigned char time_eng_hi_limit;                 //����ѹ������ʱÿ���ڼ��������15%����ʱ
unsigned char key;				// ����
unsigned char keybak;				// ����
unsigned char keycnt;				// ������ʱ
unsigned char psw[4];				// ����
unsigned char pswcnt;				// �������
signed   char pa_input;				//�������λ��
signed   char mod_point;	 		//�޸Ĳ�����ָ��
unsigned char op_grade;				//����������
unsigned char out_stu2_bak;                     //��һ��ѹ����״̬
unsigned char dir_exv;				// �������ͷ����з���1/0������/����
/*
//	D7		D6		D5		D4		D3		D2		D1		D0
//	exvbak4	exv3bak	exv2bak	exv1bak	exv4	exv3	exv2	exv1
*/

signed 	 char exv_pos[4];			// ����λ�� -128 ~ +127
unsigned int  chg_step[4];			// �������ͷ��ı䲽��
unsigned int  chg_stepbak[4];		        // �������ͷ��ı䲽������
int step[4];					// �������ͷ�ʵ�ʲ���
int init_step[4];				// ���õ����ͷ���ʼ����

unsigned char FAN_EV_OUT;			// ����͵�ŷ�����Ĵ���
unsigned char FAN_EV_OUTBAK;		        // ����͵�ŷ�����Ĵ�������

unsigned char cnt_eadd;				// ������������
unsigned char p_eadd;				// ������������

unsigned char time_input_det;		        // �����źż��

unsigned int  time_reset;			// ��λʱ�䣬��������ʱ����Ŀ����ȶ�,unit:s
unsigned int  time_cmp_dlt;			// ������ȶ��ã����αȽ�DLT��ʱ���� 320S

unsigned char time_ddsm;			// ��˪����ʱ,unit:min
unsigned char time_ddss;			// ��˪����ʱ,unit:ms
unsigned char time_drm;				// ��˪����ʱ��,unit:min
unsigned char time_drs;				// ��˪����ʱ��,unit:s

unsigned char time_hpress;			// ��ѹ���ʱ��>320ms��Ϊ�ǹ���
unsigned char time_lpress;			// ��ѹ���ʱ��>320ms��Ϊ�ǹ���
unsigned char time_cov[4];			// ѹ�����������ʱ��

unsigned int  time_compall_off;		// ����ѹ����ȫ��ֹͣʱ��ʼ��ʱ��������ͨ������,unit:s
unsigned int  time_comp_on[4];		// ѹ��������ʱ��ʼ��ʱ��������С����ʱ�䱣��,unit:s
unsigned char time_comp_off[4];		// ѹ����ֹͣʱ��ʼ��ʱ������ͣ������,unit:s
unsigned char time_mea_dlt;		// ����ѹ���������¶ȼ��ʱ������unit:s
unsigned char time_dlt_high;		// ����ѹ���������¶ȹ��߼��ʱ�䣬unit:s
unsigned char time_base;		// 1s������ʱ
unsigned char time_adc;			// �����¶�ʱ����

unsigned int  time_chg_queue;		// �����л�ʱ��ʱ����λΪS
unsigned char time_hex;			// �Ƚ����л�ʱ��������λΪS
unsigned char time_fan;			// ����л�ʱ��������λΪS
unsigned char time_comp;		// ѹ�����������

unsigned char time_exv_stop[4];		// �������ͷ�����ֹͣ��ʱ500ms�ȶ�
unsigned char time_exv;			// �������ͷ�������ʱ150msÿ��
unsigned char time_adjexv;		// ��������ǰ3���Ӳ��ɵ���
unsigned char time_eadd;		// ������������
unsigned char time_disp;		// display for 1s and off for 0.5s,cycle

unsigned int  time_dig_onbak;		// ����ѹ�������������ʱ��ʱ����,unit:ms
unsigned int  time_dig_offbak;		// ����ѹ�������������ʱ��ʱ����,unit:ms
unsigned int  time_dig_on;		// ����ѹ�������������ʱ��ʱ����,unit:ms
unsigned int  time_dig_off;		// ����ѹ�������������ʱ��ʱ����,unit:ms
unsigned char time_ctrl;		// ����ʱ�䣬��d_time_ctrl��Ӧ

unsigned int  time_err[6][2];
// 0:�������,1:����1����,2:����2����,3:����3����,4:��ѹ,5:��ѹ
unsigned char err_cnt[6];			// ���ϼ���
// 0:�������,1:����1����,2:����2����,3:����3����,4:��ѹ,5:��ѹ
/*
unsigned int  time_oil_rec_det;		// �ͻָ����ʱ�䣬unit:sec
unsigned int  time_oil_rec_run;		// �ͻָ�����ʱ�䣬unit:sec

unsigned char time_balance_run;		// ��ƽ������ʱ��
		 long time_balance_det;		// ��ƽ�������
*/
unsigned char time_comp_run_h[4];	// ����Сʱ���ֽ�
unsigned char time_comp_run_l[4];	// ����Сʱ���ֽ�
unsigned char time_comp_run_m[4];	// ���з���
unsigned char time_comp_run_s[4];	// ��������

unsigned char time_fan_th1;		// �������µ������
unsigned char time_defrost;		// ��˪���ʱ��S
unsigned int  time_invdef;		// ���γ�˪���
unsigned char time_heat_sec;		// ��������ʱ������
unsigned char time_heat_min;		// ��������ʱ�����

unsigned int  time_th8_over;		// ���������¶ȷ�Χ�ı�������

unsigned int  time_tscafail;		// ����ʱʵ�ʹ��ȶ�С��2����ʱ��S
unsigned int  time_TH12fail;		// TH12���ϱ�������ʱ��S
unsigned int  time_LSfail;			// LS���ϱ�������ʱ��S
unsigned char flag_inn_com;		//������һ̫�ڻ�ͨ�Ź��ϱ�־

unsigned int  time_keepstub;		//
unsigned int  time_oilb;
unsigned int  time_keepstur;		//
unsigned int  time_oilr;


unsigned char rxd_in[len_rxd_in];     // �������ڻ����ݻ�����
unsigned char rxd_inbak[max_unit][19];// ���յ����ڻ����������
//[0]������汾
//[1]������1������λΪ���ͣ�����λΪ����
//[2]������2������/����/ˮ��/�����ڷ�/��ͨ�ڷ�/�·�/�����2/�����1
//[3]������3������
//[4]���߿���ģʽ��1
//[5]���߿���ģʽ��2
//[6]���ڻ�����ģʽ
//[7]������
//[8]���߿�������
//[9]���ڻ�������100
//[10]���ڻ�������10
//[11]����������
//[12]��inlet temp
//[13]��midlet temp
//[14]��outlet temp
//[15]��indoor temp
//[16]��in+mid
//[17]��out+indoor
//[18]������

unsigned char txd_in[60];				// ���͵����ڻ����ݻ�����
unsigned char rxd_pc[len_rxd_pc];		// �������ռ�������ݻ�����
unsigned char rxd_pcbak[3][max_unit+4];	// ���ռ�������ݻ���������3������У�����������,����������
// ���ݴ�����ʽ��
// 1��[0]:cmd:7/8
// ��CMDΪ7ʱ��
//	[1]���ڻ���N
//	[2]���߿���ģʽ��1
//	[3]���߿���ģʽ��2
//	[4]~[N+3]Ϊ�ڻ���ַ��
// ��CMDΪ8ʱ��
//	[1]���߿���ģʽ��1
//	[2]���߿���ģʽ��2

unsigned char hic_state;                        //��ǰ���䷧״̬
unsigned char hic_state_bak;                    //��һ�ι��䷧״̬
unsigned char sh_out_time;                     //���ڹ��䷧60S��ʱ
unsigned char ini_sh_out_time;                  //���ڹ��䷧��ʼ��ʱ
unsigned char ini_hicset[8];                    //���䷧�ڲ�ͬ�����µĳ�ʼ����
unsigned char txd_pc[250];			// ���͵�����������ݻ�������1+1+1+10+1+9*16+1+1
unsigned char txd_loop;				// ÿ������������ʹ���������ʱ��ʼ����
unsigned char rxd_count;			// ���ʹ�����������4����ʱ���͹㲥���ݣ���������ѯ����
unsigned char byte_rxd_in;			// ���յ����ڻ��ֽ���
unsigned char byte_txd_in;			// ���͵����ڻ��ֽ���
unsigned char byte_rxd_pc;			// ���յ���λ���ֽ���
unsigned char byte_txd_pc;			// ���͵���λ���ֽ���
unsigned char byte_rxd_pcbak;		        // �������ݳ��ȱ���
unsigned char temp_bak1;
unsigned char comm_in_en[6];		        // ���ڻ�ͨѶ�����־λ
unsigned char unit_run[6];			// ���ڻ����б�־λ��1/0����/ֹͣ���淽���вμ�10.4

unsigned int time_rec_in;			// �����������ڻ������ۼ�ʱ��
unsigned char time_byte_in;			// �������ڻ����������ֽ�ʱ����
unsigned char time_byte_pc;			// ������λ����������ʱ����
unsigned char time_comm_slave;		        // �ӻ�ͨѶ����

unsigned char uchCRCHi;
unsigned char uchCRCLo;

unsigned char cnt_500ms;			// ��ʾ��


unsigned char count_yellow;			// ����ѹ���������¶Ƚ����ɫ����ʱ������
unsigned char fan_spd;				// ���ٿ��ƣ�0/1/2/3��ͣ/��/��/��
unsigned char unit_addr;			// ��ѯ�����ڻ����
unsigned char cur_pcbak;			// ������������ջ��������ڻ����ؿ�����

int	TH8BAK;							// �����¶ȣ��Ŵ�10����ȡ�����з��ţ�
int	temp_buf[12];					// �¶ȣ��Ŵ�10����ȡ�����з��ţ�
int     dig_pwm;				// ����ѹ������PWMռ�ձ�,�Ŵ�10��ȡ��
int     dig_pwm_bak;				// ����ѹ������PWMռ�ձȱ���,�Ŵ�10��ȡ��
signed char target_superheat;		        // ���Ŀ����ȶȣ���������ʱ�������ͷ��Ŀ���
unsigned char mea_p;				// ��ʱ�����¶�ָ��

unsigned int  hi_pressure;			// ��ѹֵ,40s�����ڵ�ƽ��ֵ���Ŵ�10X
unsigned int  low_pressure;			// ��ѹֵ,40s�����ڵ�ƽ��ֵ���Ŵ�10X
unsigned char cnt_hipre;			// ѹ�����Դ���
unsigned char cnt_lowpre;			// ѹ�����Դ���
unsigned int  hp_buf[8];			// ��ѹ
unsigned int  lp_buf[8];			// ��ѹ

signed char dpoint_row;				// ��ѡ��
signed char dpoint;					// ��ֵѡ��
unsigned char dbufcnt;				// ��ʾ������������
unsigned char dbuf[4];				// ��ʾ����������Ϊdbuf[3]����Ϊdbuf[0]
unsigned char dispmode;				// ��ʾģʽ
unsigned int  disp_5s;				// ��ʾˢ��5S����
unsigned char updata_f;				//����ˢ�±��

unsigned char err_det;				//
//D7	D6		D5		D4		D3   	D2		D1		D0
//				COMP4	COMP3	COMP2	COMP1	LOW		HI
unsigned char err_point_row;		// ���ϼ�����
unsigned char err_point;			// ���ϼ�����
//unsigned char err_com_point;		// ͨѶ���ϼ�����
unsigned char err_rec[16];			// ������EEPROM��Ĺ��ϼ�¼
unsigned char err_rec_end;			// ��ǰ�Ĺ��ϱ�β
unsigned char err_rec_cur;			// �������ϵ�ָ��λ��
unsigned char err[10];				// ����
/*
//0:	D7		D6		D5		D4		D3   	D2		D1		D0
//		7#		6#		5#	 	4#		3#		2#		1#		0#
//1:	D7		D6		D5		D4		D3   	D2		D1		D0
//		15#		14#		13#	 	12#		11#		10#		9#		8#
//2:	D7		D6		D5		D4		D3   	D2		D1		D0
//		23#		22#		21#	 	20#		19#		18#		17#		16#
//...
//6:	D7		D6		D5		D4		D3   	D2		D1		D0
//		SYSTEM	EEPROM	��ѹ����	��ѹ����	F3_OV	F2_OV	F1_OV	D_OV
//7:	D7		D6		D5		D4		D3		D2		D1		D0
//		�ӻ�ͨѶ	��ýй©	Tsca<2	��������	���±���	4WV		COMM	DLT_HI
//8:	D7		D6		D5		D4		D3   	D2		D1		D0
//		TH8		TH7 	TH6		TH5		TH4		TH3		TH2		TH1
//9:	D7		D6		D5	 	D4	  	D3   	D2		D1		D0
//				ͨѶȫ�� ��ѹ̽ͷ ��ѹ̽ͷ	TH12	TH11	TH10	TH9
*/

signed   char paraadj;				// ��������ʱ������
signed   char parabak;				// ��������ʱ������
unsigned char queue;				// ���ж��У�queue[0] Ϊ��ǰ����ģʽ��queue[0] Ϊ��������ģʽ
unsigned char queuebak;				// ��������ʱ������ǰ����ģʽ

unsigned char num_comp;				// ѹ����̨��
unsigned char num_sv;				// ��ŷ�����
unsigned char num_4wv;				// 4ͨ������
//unsigned int  exv_init_open[4];		// �������ͷ�У���ĳ�ʼ����
unsigned char COMP[4];				// ����ѹ����������
unsigned char self_addr;			// ������ַ
signed char config[22];				// ��������ã����ͨѶЭ��10.1
//[0]�� ����汾
//[1]�� ����1
//[2]�� ����2
//[3]�� ����3
//[4]�� Byte5	DefA��˪�����A�㣨-15~-2�棬Ĭ��Ϊ-6�棬�仯��Ϊ1�棩�������ű�ʾ
//[5]�� Byte6	DefB��˪�����B�㣨-30~-15�棬Ĭ��Ϊ-24�棬�仯��Ϊ1�棩�������ű�ʾ
//[6]�� Byte7   DefTemp��˪�����¶ȣ�5~20��,Ĭ��Ϊ12�棬�仯��Ϊ1�棩��ʵ��ֵ
//[7]�� Byte8	DefIT��˪���ʱ�䣨25~90min��Ĭ��Ϊ45min���仯��Ϊ1min����ʵ��ֵ
//[8]�� Byte9	DefRT��˪����ʱ�䣨5~15min��Ĭ��Ϊ10min���仯��Ϊ1min����ʵ��ֵ
//[9]�� Byte10	NT������ʱʱ�䣨3~9hour��Ĭ��Ϊ6hour���仯��Ϊ1hour����ʵ��ֵ
//[10]��Byte11	nStep1����ʱ������ϵ��step1��0.1~5��Ĭ��Ϊ2���仯��Ϊ0.1�����Ŵ�10������
//[11]��Byte12	nStep2����ʱ������ϵ��step2��0~5��Ĭ��Ϊ0.5���仯��Ϊ0.1�����Ŵ�10������
//[12]��Byte13	TscA1��0~TscA2��,Ĭ��Ϊ32�棬�仯��Ϊ1�棩��ʵ��ֵ
//[13]��Byte14	TscA2��TscA1~50��,Ĭ��Ϊ40�棬�仯��Ϊ1�棩��ʵ��ֵ
//[14]��Byte15	TscT1��0~TscT2,Ĭ��Ϊ3�棬�仯��Ϊ1�棩��ʵ��ֵ
//[15]��Byte16	TscT2��TscT1~TscT3,Ĭ��Ϊ8�棬�仯��Ϊ1�棩��ʵ��ֵ
//[16]��Byte17	TscT3��TscT2~50��,Ĭ��Ϊ12�棬�仯��Ϊ1�棩��ʵ��ֵ
//[17]��Byte18	factor_j
//[18]��Byte19	factor_m
//[19]��Byte20	���ܲ���3
//[20]: Byte21  TsctĿ����ȶȣ�1~10��Ĭ��ֵΪ5�棩
unsigned char out_stu[3];			// ��Э��10.3 byte2,3,4
//[0]��ģʽ
//[1]�����+��ŷ�״̬
//[2]����ͨ��+����ѹ����״̬

unsigned char unit_set;				// ������������

unsigned char data_out[33];			// �������Ǭ����Ų���õ�

unsigned char cnt_addexv_ls;		// ѹ������ʱ����
unsigned char cnt_addexv_th1;		// ���¹��߱�������

unsigned char cnt_openexv;			// ��ѹ���ͱ�������

unsigned char hicset;				// ���䷧���ó�ʼ����
unsigned int  hicmax;				// ���䷧��󿪶�
unsigned char hicmin;				// ���䷧��С����
unsigned char defexv;				// ��˪�󷧻ָ�����
unsigned char tab[4];
struct rt
{
	unsigned char week;				//
	unsigned char hour;				//
	unsigned char min;				//
	unsigned char sec;				//
}RTC;								// Real time clock

unsigned char SCOMP[4];				// �ӻ�COMP
unsigned char eng_slave;			// ������ڻ�������

unsigned char data_slave[72];		// �ӻ�����

unsigned char flag_frist_dlt;		//��һ����������
unsigned char frist_hi;			//��һ��ѹ����ѹ26
/*===============================================================================
	������ ���õ�ȱʡ����
===============================================================================*/
const signed char para_defalt[] =
//cfg[4]  5		6	7	8	9	10	11	12	13	14	15	16	17	18	19
	{-6,  -24,	15,	45,	10,	6,	20,	5,	32,	40,	3,	8,	12,	24,	10,	37,   50};
//	 FA	   E8	0C	28	0A	06	14	05	20	28	03	08	0C	18	0A	0A
const signed char para_max[] =
	{-2,  -15,	20,	90,	15,	9,	50,	50,	40,	50,	10,	20,	30,	50,	30,	50,   100};

const signed char para_min[] =
	{-15, -30,	5,	25,	5,	3,	1,	0,	0,	20,	0,	0,	0,	10,	10,	20,  10 };

const unsigned char zexv[8] =
	{ 0x10,0x30,0x20,0x60,0x40,0xc0,0x80,0x90};

const unsigned char fexv[8] =
	{ 0x80,0xc0,0x40,0x60,0x20,0x30,0x10,0x90};

const unsigned int init_open[4] =		// ��ʼ����
	{ 150,200,250,300 };

/*===============================================================================
	K2/K3����ʱ��ʾ���ݺͷ�Χ
===============================================================================*/
const unsigned char disp_zone[] =
{
	26,				// ��ʾ���ʵʱ����
	30,				// ��ʾ���Ӳ����Ϣ/���ò���
	30,				// ��ʾ������ò���
	60,				// ��ʾ��ǰ���Թ���
	16,				// ����Ĺ��ϴ���
	14,				// ��ʾ�ڻ�ʵʱ����
	15				// ��ʾ����0-f
};

/*===============================================================================
	�ڻ���������λ��HP ������10��
===============================================================================*/
const unsigned char cap_tab[] =
	{8,10,15,18,23,25,30,40,50,60,9,11,28,32,35,45,80,100,120,180,220,65,240};
//	{8,10,15,18,23,25,30,40,50,60,70,80,90,100,110,120};
    //8
/*===============================================================================
	�ڻ�����ģʽ��
===============================================================================*/
const unsigned char run_unitmode_tab[][4] =
{
	{C_X,C_O,C_F,C_F},	// disp "off"
	{C_C,C_O,C_O,C_L},	// disp "COOL"
	{C_H,C_E,C_A,C_T},	// disp "HEAT"
	{C_A,C_U,C_T,C_O},	// disp "ATUO"
	{C_X,C_F,C_A,C_N},	// disp "FAN"
	{C_X,C_D,C_R,C_Y},	// disp "DRY"
	{C_X,C_D,C_E,C_F},	// disp "DEF"
	{C_T,C_E,D_5,C_T}	// disp "TEST"
};

/*===============================================================================
	�������ģʽ��
===============================================================================*/
const unsigned char run_outmode_tab[][4] =
{
	{C_N,C_U,C_L,C_L},	// disp "null"
	{C_R,C_E,C_S,C_T},	// disp "REST"
	{C_X,C_C,C_S,C_T},	// disp "CST"
	{C_C,C_O,C_O,C_L},	// disp "COOL"
	{C_X,C_C,C_S,C_P},	// disp "CSP"
	{C_X,C_D,C_S,C_T},	// disp "DST"
	{C_X,C_D,C_E,C_F},	// disp "DEF"
	{C_X,C_D,C_S,C_P},	// disp "DSP"
	{C_X,C_H,C_S,C_T},	// disp "HST"
	{C_H,C_E,C_A,C_T},	// disp "HEAT"
	{C_X,C_H,C_S,C_P},	// disp "HSP"
	{C_E,C_R,C_R,C_o},	// disp "ERRO"
	{C_P,C_R,D_0,C_T},	// disp "PROT"
	{C_T,C_E,D_5,C_T},	// disp "TEST"
	{C_O,C_P,C_E,C_N},	// disp "OPEN"
	{C_O,C_T,C_H,C_E}	// disp "othe"
};


/*===============================================================================
	��ʾ����ģʽ��
===============================================================================*/
const unsigned char opmode_tab[][4] =
{
	{C_O,C_R,C_U,C_N},	// disp "ORUN"	��ʾ����ģʽ
	{C_X,C_O,C_C,C_P},	// disp "OCP"	��ʾʵʱ����
	{C_X,C_O,C_S,C_P},	// disp "OSP"	��ʾ���ò���
	{C_X,C_O,C_C,C_E},	// disp "OCE"	��ǰ�Ĺ��ϴ���
	{C_X,C_O,C_H,C_E},	// disp "OHE"	����Ĺ��ϴ���
	{C_X,C_U,C_C,C_P},	// disp "UCP"	��ʾ�ڻ�����/ʵʱ����
	{C_P,C_A,C_S,C_S},	// disp "DEF"	��ʾ����
	{C_X,C_D,C_S,C_P}	// disp "DSP"	��ʾ����
};


/*===============================================================================
	ADCͨ��ѡ���
===============================================================================*/
#ifndef	NEWPCB
const unsigned char input_CH[] = // INH 0 ��Ч
{	//CBAֵ
	0x25,	// TH1
	0x23,	// TH2
	0x20,	// TH3
	0x21,	// TH4
	0x22,	// TH5
	0x27,	// TH6
	0x26,	// TH7
	0x24,	// TH8

	0x10,	// TH9
	0x11,	// TH10
	0x12,	// TH11
	0x13,	// TH12
	0x14,	// HI_U	 13
	0x15,	// LOW_U 14

	0x00,	// ��ѹ mea_p=15
	0x01,	// ��ѹ mea_p=16
	0x02,	// DIG mea_p=17
	0x03,	// FIX1 mea_p=18
	0x04,	// FIX2 mea_p=19
	0x05	// FIX3 mea_p=20
};
#else//new PCB
const unsigned char input_CH[] = // INH 0 ��Ч
{	//CBAֵ
	0x25,	// TH1
	0x23,	// TH2
	0x10,	// TH3
	0x20,	// TH4
	0x11,	// TH5
	0x12,	// TH6
	0x13,	// TH7
	0x21,	// TH8

	0x22,	// TH9
	0x27,	// TH10
	0x26,	// TH11
	0x24,	// TH12
	0x14,	// ��ѹ�͸�ѹ������ 12 
	0x15,	// ��ѹ�͵�ѹ������ 13 

	0x00,	// ��ѹ mea_p=14
	0x01,	// ��ѹ mea_p=15
	0x02,	// DIG mea_p=16
	0x03,	// FIX1 mea_p=17
	0x04,	// FIX2 mea_p=18
	0x05	// FIX3 mea_p=19

};
#endif
/*===============================================================================
// �����
===============================================================================*/

const unsigned int cap_tab_b[][8] =//MDSB
{
//unit_set		4WV		SV		hicset	hicmax	hicmin	defexv	units
	{SET_B1,	1,		0,		90,	480,	0,	150,	13},//8
	{SET_B1,	1,		0,		90,	480,	0,	150,	16},//10
	{SET_B1,	1,		0,		90,	480,	0,	150,	16},//12 B1
                                    	
	{SET_B2,	1,		0,		90,	480,	0,	150,	20},//15 B2
                                    	
	{SET_B3,	2,		1,		90,	480,	0,	150,	24},//18 B3
                                    	
	{SET_B4,	2,		1,		90,	480,	0,	150,	24},//20
	{SET_B4,	2,		1,		90,	480,	0,	150,	24},//22
	{SET_B4,	2,		1,		90,	480,	0,	150,	24},//24 B4
                                    	
	{SET_B2,	1,		0,		90,	480,	0,	150,	32},//26
	{SET_B2,	1,		0,		90,	480,	0,	150,	32},//28
	{SET_B2,	1,		0,		90,	480,	0,	150,	32},//30
	{SET_B2,	1,		0,		90,	480,	0,	150,	32},//32

	{SET_B2,	1,		0,		180,	480,	150,	150,	32},//34
	{SET_B2,	1,		0,		180,	480,	150,	150,	32},//36
	{SET_B2,	1,		0,		180,	480,	150,	150,	32},//38
	{SET_B2,	1,		0,		180,	480,	150,	150,	32},//40
        {SET_B2,	1,		0,		90,	480,	0,	150,	32},//42
        {SET_B2,	1,		0,		90,	480,	0,	150,	32},//44 
        {SET_B2,	1,		0,		90,	480,	0,	150,	32},//46
        {SET_B2,	1,		0,		90,	480,	0,	150,	32},//48
        {SET_B2,	1,		0,		90,	480,	0,	150,	32},//50
        {SET_B2,	1,		0,		90,	480,	0,	150,	20},//14
        {SET_B2,	1,		0,		90,	480,	0,	150,	20},//16 
        {SET_B1,	1,		0,		90,	480,	0,	150,	 6},//3
        {SET_B1,	1,		0,		90,	480,	0,	150,	 6},//4
        {SET_B1,	1,		0,		90,	480,	0,	150,	 6},//5
        {SET_B1,	1,		0,		90,	480,	0,	150,	 8},//6
        {SET_B1,	1,		0,		90,	480,	0,	150,	 8} //7
        
};

const unsigned int comp_tab_b[][9] =//MDSB
{
//cap_sys	DIG	F1	F2	F3	S1	S2	S3	S4
	{ 9,	5,	4,	0,	0,	0,	0,	0,	0},
	{10,	5,	5,	0,	0,	0,	0,	0,	0},
	{12,	6,	6,	0,	0,	0,	0,	0,	0},//B1

	{15,	5,	5,	5,	0,	0,	0,	0,	0},//B2

	{18,	6,	6,	6,	0,	0,	0,	0,	0},//B3
	{20,	5,	5,	5,	5,	0,	0,	0,	0},//20

//	{23,	5,	6,	6,	6,	0,	0,	0,	0},//20
	{21,	6,	5,	5,	5,	0,	0,	0,	0},//21
	{24,	6,	6,	6,	6,	0,	0,	0,	0},//24 B4

	{27,	6,	6,	0,	0,	5,	5,	5,	0},//
	{30,	5,	5,	5,	0,	5,	5,	5,	0},
	{30,	5,	5,	5,	0,	5,	5,	5,	0},
	{31,	6,	5,	5,	0,	5,	5,	5,	0},

	{34,	6,	6,	6,	0,	5,	5,	5,	0},//340 18+16
	{36,	6,	6,	6,	0,	6,	6,	6,	0},//360 18+18
	{39,	6,	6,	6,	6,	5,	5,	5,	0},//380 24+14
	{40,	6,	6,	6,	6,	5,	5,	5,	0},//400 24+16
	{42,	6,	6,	6,	6,	6,	6,	6,	0},//420 24+18
	{44,	6,	6,	6,	6,	5,	5,	5,	5},//440 24+20
	{48,	6,	6,	6,	6,	6,	6,	6,	6},//460 24+22
	{48,	6,	6,	6,	6,	6,	6,	6,	6},//480 24+24
	{50,	6,	6,	6,	6,	6,	6,	6,	6},//500

	{14,	7,	7,	0,	0,	0,	0,	0,	0},//140
	{16,	6,	5,	5,	0,	0,	0,	0,	0},//160
	{3,	3,	0,	0,	0,	0,	0,	0,	0},//30
	{4,	4,	0,	0,	0,	0,	0,	0,	0},//40
	{5,	5,	0,	0,	0,	0,	0,	0,	0},//50
	{6,	6,	0,	0,	0,	0,	0,	0,	0},//60
	{7,	7,	0,	0,	0,	0,	0,	0,	0} //70
};
const unsigned int comp_tab_b60[][9]	=//MDSB_60hz
{
//cap_sys	DIG	F1	F2	F3	S1	S2	S3	S4
	{11,	6,	5,	0,	0,	0,	0,	0,	0},//080
	{11,	6,	5,	0,	0,	0,	0,	0,	0},//100
	{12,	6,	6,	0,	0,	0,	0,	0,	0},//120
	{15,	5,	5,	5,	0,	0,	0,	0,	0},//150
	{18,	6,	6,	6,	0,	0,	0,	0,	0},//180
	{19,	7,	6,	6,	0,	0,	0,	0,	0},//200
	{21,	7,	7,	7,	0,	0,	0,	0,	0},//220
	{24,	6,	6,	6,	6,	0,	0,	0,	0},//240
	{26,	7,	7,	0,	0,	6,	6,	0,	0},//260 12+15
	{28,	7,	7,	0,	0,	7,	7,	0,	0},//280 15+15
	{29,	7,	7,	0,	0,	5,	5,	5,	0},//300 15+15
	{31,	6,	5,	5,	0,	5,	5,	5,	0},//320 16+15
	
	{34,	6,	6,	6,	0,	5,	5,	5,	0},//340 18+16
	{36,	6,	6,	6,	0,	6,	6,	6,	0},//360 18+18
	{39,	6,	6,	6,	6,	5,	5,	5,	0},//380 24+14
	{40,	6,	6,	6,	6,	5,	5,	5,	0},//400 24+16
	{42,	6,	6,	6,	6,	6,	6,	6,	0},//420 24+18
	{44,	6,	6,	6,	6,	5,	5,	5,	5},//440 24+20
	{48,	6,	6,	6,	6,	6,	6,	6,	6},//460 24+22
	{48,	6,	6,	6,	6,	6,	6,	6,	6},//480 24+24
	{50,	6,	6,	6,	6,	6,	6,	6,	6},//500

	{14,	7,	7,	0,	0,	0,	0,	0,	0},//140
	{16,	6,	5,	5,	0,	0,	0,	0,	0},//160
	{3,	3,	0,	0,	0,	0,	0,	0,	0},//30
	{4,	4,	0,	0,	0,	0,	0,	0,	0},//40
	{5,	5,	0,	0,	0,	0,	0,	0,	0},//50
	{6,	6,	0,	0,	0,	0,	0,	0,	0},//60
	{7,	7,	0,	0,	0,	0,	0,	0,	0} //70	       
};

/*===============================================================================
	���������������Ƿ����
===============================================================================*/
/*
const unsigned char sensor[4][20] =
{
//	T1	T2	T3	T4	T5	T6	T7	T8	T9	T10	T11	T12 HPU LPU HPS	LPS	C1	C2	C3	C4
//	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19
	{1,	1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	0,	0},	//SET_B1;
	{1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0},	//SET_B2;
	{1,	1,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	0},	//SET_B3;
	{1,	1,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1}	//SET_B4;
};
*/
/*===============================================================================
	���������ϱ�����
===============================================================================*/
const unsigned char m_cool[4][12] =
{
//	T1	T2	T3	T4	T5	T6	T7	T8	T9	T10	T11	T12
//	0	1	2	3	4	5	6	7	8	9	10	11
	{1,	0,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1},	//SET_B1;
	{1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1},	//SET_B2;
	{1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1},	//SET_B3;
	{1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1}	//SET_B4;
};

const unsigned char m_heat[4][12] =
{
//	T1	T2	T3	T4	T5	T6	T7	T8	T9	T10	T11	T12
//	0	1	2	3	4	5	6	7	8	9	10	11
	{1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1},	//SET_B1;
	{1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1},	//SET_B2;
	{1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1},	//SET_B3;
	{1,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1}	//SET_B4;
};

const unsigned char s_cool[4][12] =
{
//	T1	T2	T3	T4	T5	T6	T7	T8	T9	T10	T11	T12
//	0	1	2	3	4	5	6	7	8	9	10	11
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1},	//SET_B1;
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1},	//SET_B2;
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1},	//SET_B3;
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1}	//SET_B4;
};

const unsigned char s_heat[4][12] =
{
//	T1	T2	T3	T4	T5	T6	T7	T8	T9	T10	T11	T12
//	0	1	2	3	4	5	6	7	8	9	10	11
	{0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1},	//SET_B1;
	{0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1},	//SET_B2;
	{0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1},	//SET_B3;
	{0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1}	//SET_B4;
};

/*===============================================================================
	��ʾ�����,����
===============================================================================*/
const unsigned char segtab[] =
{
0xC0,/*0*/
0xF9,/*1*/
0xA4,/*2*/
0xB0,/*3*/
0x99,/*4*/
0x92,/*5*/
0x82,/*6*/
0xF8,/*7*/
0x80,/*8*/
0x90,/*9*/
0x88,/*A*/
0x83,/*b*/
0xc6,//A7,/*c*/
0xA1,/*d*/
0x86,/*E*/
0x8E,/*F*/
0x8B,/*h*/
0x89,/*H*/
0xA3,/*o*/
0x8C,/*P*/
0xC7,/*L*/
0xAF,/*r*/
0x91,/*Y*/
0xBF,/*-*/
0xF7/*_*/
};



/*===============================================================================
	ѹ�����Դ��¶ȴ�����
	�ο����裺10K��������VCC
===============================================================================*/

const unsigned int dlt_tab[] =
{
		0x3D1,		//6(��)
		0x3CC,		//8(��)
		0x3C7,		//10(��)
		0x3C2,		//12(��)
		0x3BC,		//14(��)
		0x3B6,		//16(��)
		0x3B0,		//18(��)
		0x3A9,		//20(��)
		0x3A1,		//22(��)
		0x399,		//24(��)
		0x391,		//26(��)
		0x388,		//28(��)
		0x37F,		//30(��)
		0x375,		//32(��)
		0x36B,		//34(��)
		0x360,		//36(��)
		0x35A,		//38(��)
		0x349,		//40(��)
		0x33C,		//42(��)
		0x32F,		//44(��)
		0x322,		//46(��)
		0x314,		//48(��)
		0x306,		//50(��)
		0x2F8,		//52(��)
		0x2E9,		//54(��)
		0x2D9,		//56(��)
		0x2CA,		//58(��)
		0x2BA,		//60(��)
		0x2AA,		//62(��)
		0x299,		//64(��)
		0x289,		//66(��)
		0x278,		//68(��)
		0x267,		//70(��)
		0x257,		//72(��)
		0x246,		//74(��)
		0x235,		//76(��)
		0x224,		//78(��)
		0x214,		//80(��)
		0x203,		//82(��)
		0x1F3,		//84(��)
		0x1E3,		//86(��)
		0x1D3,		//88(��)
		0x1C3,		//90(��)
		0x1B4,		//92(��)
		0x1A5,		//94(��)
		0x196,		//96(��)
		0x188,		//98(��)
		0x17A,		//100(��)
		0x16D,		//102(��)
		0x160,		//104(��)
		0x153,		//106(��)
		0x147,		//108(��)
		0x13B,		//110(��)
		0x12F,		//112(��)
		0x123,		//114(��)
		0x118,		//116(��)
		0x10C,		//118(��)
		0x101,		//120(��)
		0xF7,		//122(��)
		0xED,		//124(��)
		0xE3,		//126(��)
		0xDA,		//128(��)
		0xD2,		//130(��)
		0xCA,		//132(��)
		0xC2,		//134(��)
		0xBA,		//136(��)
		0xB3,		//138(��)
		0xAC,		//140(��)
		0xA6,		//142(��)
		0x9F,		//144(��)
		0x99,		//146(��)
		0x93			//148(��)
};

/*===============================================================================
	�¶ȱ���΢�ṩ��	6~150'C
	�ο����裺10K��������VCC
===============================================================================*/
const unsigned int dlt_tab1[] =
{
	0x2C1,		//6(��)
	0x2AD,		//8(��)
	0x299,		//10(��)
	0x285,		//12(��)
	0x270,		//14(��)
	0x25C,		//16(��)
	0x247,		//18(��)
	0x233,		//20(��)
	0x21E,		//22(��)
	0x20A,		//24(��)
	0x1F6,		//26(��)
	0x1E2,		//28(��)
	0x1CF,		//30(��)
	0x1BC,		//32(��)
	0x1AA,		//34(��)
	0x197,		//36(��)
	0x186,		//38(��)
	0x175,		//40(��)
	0x164,		//42(��)
	0x154,		//44(��)
	0x145,		//46(��)
	0x136,		//48(��)
	0x128,		//50(��)
	0x11A,		//52(��)
	0x10D,		//54(��)
	0x100,		//56(��)
	0xF4,		//58(��)
	0xE9,		//60(��)
	0xDE,		//62(��)
	0xD3,		//64(��)
	0xC9,		//66(��)
	0xC0,		//68(��)
	0xB7,		//70(��)
	0xAE,		//72(��)
	0xA6,		//74(��)
	0x9E,		//76(��)
	0x97,		//78(��)
	0x90,		//80(��)
	0x89,		//82(��)
	0x83,		//84(��)
	0x7D,		//86(��)
	0x77,		//88(��)
	0x71,		//90(��)
	0x6C,		//92(��)
	0x67,		//94(��)
	0x62,		//96(��)
	0x5E,		//98(��)
	0x5A,		//100(��)
	0x56,		//102(��)
	0x52,		//104(��)
	0x4F,		//106(��)
	0x4B,		//108(��)
	0x48,		//110(��)
	0x45,		//112(��)
	0x42,		//114(��)
	0x3F,		//116(��)
	0x3C,		//118(��)
	0x3A,		//120(��)
	0x38,		//122(��)
	0x35,		//124(��)
	0x33,		//126(��)
	0x31,		//128(��)
	0x2F,		//130(��)
	0x2D,		//132(��)
	0x2B,		//134(��)
	0x2A,		//136(��)
	0x28,		//138(��)
	0x27,		//140(��)
	0x25,		//142(��)
	0x24,		//144(��)
	0x22,		//146(��)
	0x21		//148(��)
};

/*===============================================================================
	�¶ȱ�lets��
	�ο����裺10K��������VCC
===============================================================================*/
const unsigned int tmp_tab[] =
{
	0x3B6,		//-30(��)
	0x3AE,		//-28(��)
	0x3A5,		//-26(��)
	0x39C,		//-24(��)
	0x392,		//-22(��)
	0x387,		//-20(��)
	0x37C,		//-18(��)
	0x370,		//-16(��)
	0x363,		//-14(��)
	0x355,		//-12(��)
	0x347,		//-10(��)
	0x338,		//-8(��)
	0x328,		//-6(��)
	0x318,		//-4(��)
	0x307,		//-2(��)
	0x2F5,		//0(��)
	0x2E3,		//2(��)
	0x2D1,		//4(��)
	0x2BD,		//6(��)
	0x2AA,		//8(��)
	0x296,		//10(��)
	0x282,		//12(��)
	0x26E,		//14(��)
	0x25A,		//16(��)
	0x246,		//18(��)
	0x232,		//20(��)
	0x21E,		//22(��)
	0x20A,		//24(��)
	0x1F6,		//26(��)
	0x1E3,		//28(��)
	0x1D0,		//30(��)
	0x1BD,		//32(��)
	0x1AA,		//34(��)
	0x190,		//36(��)
	0x187,		//38(��)
	0x176,		//40(��)
	0x166,		//42(��)
	0x156,		//44(��)
	0x146,		//46(��)
	0x137,		//48(��)
	0x129,		//50(��)
	0x11B,		//52(��)
	0x10E,		//54(��)
	0x101,		//56(��)
	0xF5,		//58(��)
	0xEA,		//60(��)
	0xDE,		//62(��)
	0xD4,		//64(��)
	0xCA,		//66(��)
	0xC0,		//68(��)
	0xB7,		//70(��)
	0xAE,		//72(��)
	0xA6,		//74(��)
	0x9E,		//76(��)
	0x96,		//78(��)
	0x8F,		//80(��)
	0x88,		//82(��)
	0x82,		//84(��)
	0x7C,		//86(��)
	0x76,		//88(��)
	0x70,		//90(��)
	0x6B,		//92(��)
	0x66,		//94(��)
	0x61,		//96(��)
	0x5D,		//98(��)
	0x58,		//100(��)
	0x54,		//102(��)
	0x50,		//104(��)
	0x4C,		//106(��)
	0x49,		//108(��)
	0x46,		//110(��)
	0x43,		//112(��)
	0x40,		//114(��)
	0x3c,		//116(��)
	0x39,		//118(��)
	0x36		//120(��)
};


/*===============================================================================
	��ѹ��
===============================================================================*/

const int lp_tab[] =
{
	-410,		//0
	-390,		//0.1
	-371,		//0.2
	-353,		//0.3
	-336,		//0.4
	-320,		//0.5
	-305,		//0.6
	-291,		//0.7
	-277,		//0.8
	-264,		//0.9
	-251,		//1
	-239,		//1.1
	-227,		//1.2
	-216,		//1.3
	-205,		//1.4
	-195,		//1.5
	-184,		//1.6
	-174,		//1.7
	-165,		//1.8
	-155,		//1.9
	-146,		//2
	-137, 		//2.1
	-128, 		//2.2
	-120, 		//2.3
	-111, 		//2.4
	-103, 		//2.5
	-96,  		//2.6
	-88,  		//2.7
	-80,  		//2.8
	-73,  		//2.9
	-65,  		//3
	-58,  		//3.1
	-51,  		//3.2
	-44,  		//3.3
	-37,  		//3.4
	-30,  		//3.5
	-24,  		//3.6
	-17,  		//3.7
	-11,  		//3.8
	-05,		//3.9
	1, 			//4
	8,    		//4.1
	14,     	//4.2
	20,      	//4.3
	25,			//4.4
	31,			//4.5
	37,			//4.6
	43,			//4.7
	48,			//4.8
	54,			//4.9
	59,			//5
	64,			//5.1
	70,			//5.2
	75,			//5.3
	80,			//5.4
	85,			//5.5
	90,			//5.6
	95,			//5.7
	100,		//5.8
	105,		//5.9
	110,		//6
	114,		//6.1
	120,		//6.2
	124,		//6.3
	128,		//6.4
	133,		//6.5
	137,		//6.6
	142,		//6.7
	146,		//6.8
	151,		//6.9
	155,		//7
	159,		//7.1
	164,		//7.2
	168,		//7.3
	172,		//7.4
	176,		//7.5
	180,		//7.6
	184,		//7.7
	189,		//7.8
	193,		//7.9
	197,		//8
	200,		//8.1
	204,		//8.2
	208,		//8.3
	212,		//8.4
	216,		//8.5
	220,		//8.6
	224,		//8.7
	227,		//8.8
	231,		//8.9
	235,		//9
	238,		//9.1
	242,		//9.2
	246,		//9.3
	249,		//9.4
	253,		//9.5
	256,		//9.6
	260,		//9.7
	263,		//9.8
	267, 		//9.9
	270,		//10
	273,		//10.1
	277,		//10.2
	280,		//10.3
	284,		//10.4
	287,		//10.5
	290,		//10.6
	293,		//10.7
	297,		//10.8
	300, 		//10.9
	303,		//11
	306,		//11.1
	310,		//11.2
	313,		//11.3
	316,		//11.4
	320,		//11.5
	322,		//11.6
	325,		//11.7
	328,		//11.8
	331, 		//11.9
	334,		//12
	337,		//12.1
	340,		//12.2
	343,		//12.3
	346,		//12.4
	349,		//12.5
	352,		//12.6
	355,		//12.7
	358,		//12.8
	361,		//12.9

	363,		//13
	366,		//13.1
	369,		//13.2
	372,		//13.3
	375,		//13.4
	378,		//13.5
	380,		//13.6
	383,		//13.7
	386,		//13.8
	389,		//13.9

	391,		//14
	394,		//14.1
	397,		//14.2
	400,		//14.3
	402,		//14.4
	405,		//14.5
	407,		//14.6
	410,		//14.7
	413,		//14.8
	415			//14.9

};

#endif
/*===============================================================================
// end of file
===============================================================================*/












