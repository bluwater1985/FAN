/*===============================================================================
// Filename:	defineout.h
// Function:	数码涡旋室外机控器头文件
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
//	硬件的定义
//	对于两个压缩机的系统，使用A板
//	两个压缩机以上的系统，使用B板
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
//	只使用A板时的输出定义
//=============================================================================*/

	#define	cfg1_4WV		RLY6			// 4WVa
	#define	cfg1_FANH		RLY5			// 高速
	#define	cfg1_FANL		RLY4			// 低速
	#define	cfg1_EV1		RLY3			// 电磁阀1
	#define	cfg1_EV2		RLY2			// 电磁阀2

/*===============================================================================
//	使用A板和B板时的输出定义
//==============================================================================*/

	#define	cfg2_COMP4		RLY6			// 定速3
	#define	cfg2_4WVA		RLY5			// 4WVa
	#define	cfg2_4WVB		RLY4			// 4WVb

	#define	cfg2_FANH1		0x80			// B板 高速
	#define	cfg2_FANL1		0x40			// B板 低速
	#define	cfg2_FANH2		0x20			// B板 高速
	#define	cfg2_FANL2		0x10			// B板 低速
	#define	cfg2_FANH3		0x08			// B板 高速
	#define	cfg2_FANL3		0x04			// B板 低速
	#define	cfg2_EV1		0x02			// B板 电磁阀1
	#define	cfg2_EV2		0x01			// B板 电磁阀2

/*===============================================================================
//	公共信息定义
//==============================================================================*/
	#define	cfg_COMP1		RLY9			// 数码压缩机
	#define	cfg_COMP2		RLY8			// 定速1
	#define	cfg_COMP3		RLY7			// 定速2

	#define	PWM_V		IO_PDR0.bit.P00		// PWM输出

	#define	COMMIN		IO_PDR3.bit.P31		// 与室内机通讯RS485控制，1/0：发送/接收

	#define	I2C_SDA		IO_PDR4.bit.P42
	#define	I2C_SCK		IO_PDR4.bit.P43
	#define	COMMPC		IO_PDR4.bit.P44		// 联网通讯RS485控制，1/0：发送/接收

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

	#define	HI_PRE		0x01				// 高压检测端口
	#define	LO_PRE		0x02				// 低压检测端口
	#define	DIG_OVER	0x04				// 数码压缩机过载检测
	#define	FIX_OVER1	0x08				// 定容压缩机1过载检测
	#define	FIX_OVER2	0x10				// 定容压缩机2过载检测
	#define	FIX_OVER3	0x20				// 定容压缩机3过载检测


	#define	CS_14094	IO_PDR5.bit.P54		// 14094.CS
	#define	CLK_14094	IO_PDR5.bit.P57		// 14094.CLK
	#define	CLK_164		IO_PDR5.bit.P56		// 164.Clk

	#define	PIN_ERR		        IO_PDR6.bit.P60	// 故障检测，正常为0，故障为1
	#define	K1			IO_PDR6.bit.P61	//
	#define	K2			IO_PDR6.bit.P62	//
	#define	K3			IO_PDR6.bit.P63	//
	#define	K4			IO_PDR6.bit.P64	//

	#define	PORT_EXV1	IO_PDR1.byte
	#define	PORT_EXV2	IO_PDR3.byte
	#define	PORT_EXV3	IO_PDR2.byte
	#define	PORT_EXV4	IO_PDR0.byte

/*===============================================================================
	数据的定义
===============================================================================*/
	#define	max_unit		32//48		// 最大内机支持数量
	#define	len_rxd_in		82			// 接收内机数据长度
	#define	len_rxd_pc		72			// 接收内机数据长度

	#define	CH_HI			2			// ADC1 高压传感器
	#define	CH_LOW			1			// ADC2 低压传感器

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
	#define	offmode			0			// 关机
	#define	coolmode		1			// 制冷
	#define	heatmode		2			// 制热
	#define	automode		3			// 自动
	#define	fanmode			4			// 送风
	#define	drymode			5			// 除湿
	#define	defmode			6			// 除霜
	#define	testmode		7			// 抽真空

/* 系统运行队列*/
	#define	q_null		 	0			// 关机状态
	#define	q_reset		 	1			// 系统复位流程
	#define	q_cool_start 	2			// 制冷开机流程
	#define	q_cool		 	3			// 制冷正常运行
	#define	q_cool_stop	 	4			// 制冷关机流程
	#define	q_def_start	 	5			// 除霜开始流程
	#define	q_def		 	6			// 除霜正常运行
	#define	q_def_stop		7			// 除霜结束流程
	#define	q_heat_start 	8			// 制热开机流程
	#define	q_heat 		 	9			// 制热正常运行
	#define	q_heat_stop  	10			// 制热关机流程
	#define	q_err		 	11			// 压缩机高低压保护流程
	#define	q_err_protect	12			// 恶性故障死机保护
	#define	q_test			13			// 测试流程
	#define	q_openexv		14			// 开阀

//在 err_cnt表种的位置
//	#define	edov			0			// 数码过载
//	#define	efov1			1			// 定速1过载
//	#define	efov2			2			// 定速2过载
//	#define	efov3			3			// 定速3过载
	#define	ehi				4			// 0:高压
	#define	elo				5			// 1:低压

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
	#define	ms32			32			// 32ms，for exv drive

	#define	d_time_hex		5			// 热交器切换时间间隔，单位为S
	#define	d_time_fan		30			// 风机切换时间间隔，单位为S
	#define	d_time_comp_off	5			// 压缩机关闭切换间隔
	#define	d_time_comp_on	40			// 压缩机启动切换间隔

	#define	d_time_recwait	10			// 接收等待时间10ms

	#define	d_time_ctrl		40			// 40s
	#define	d_time_adc		150		// 0.5s

	#define	dms5000			750			// 5s(显示计算周期为1/150s)
	#define	dms2000			300			// 2s(显示计算周期为1/150s)
	#define	dms1500			225			// 1.5s(显示计算周期为1/150s)
	#define	dms1000			150			// 1s(显示计算周期为1/150s)
	#define	dms500			75			// 0.5s(显示计算周期为1/150s)

	#define	sp_i			0			// 电流型压力传感器
	#define	sp_u			1			// 电压型压力传感器

	#define	output			1
	#define	input			0

	#define	frame_loop		5			// 通讯查询帧

	#define	target_superheat_max	20	// 最大目标过热度，扩大10倍
	#define	target_superheat_min	-20	// 最小目标过热度，扩大10倍

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

	#define	TH1				0			// 排气温度传感器
	#define	TH2				1			// 1#进盘温度传感器
	#define	TH3				2			// 1#中盘温度传感器
	#define	TH4				3			// 2#进盘温度传感器
	#define	TH5				4			// 2#中盘温度传感器
	#define	TH6				5			// 3#进盘温度传感器
	#define	TH7				6			// 3#中盘温度传感器
	#define	TH8				7			// 环境温度传感器
	#define	TH9				8			// 出盘温度传感器
	#define	TH10			        9			// 过冷进温度传感器
	#define	TH11			        10			// 过冷出温度传感器
	#define	TH12			        11			// 回气温度传感器

	#define	dir_exv1		0x01		// 电子膨胀阀1运动方向
	#define	dir_exv2		0x02		// 电子膨胀阀2运动方向
	#define	dir_exv3		0x04		// 电子膨胀阀3运动方向
	#define	dir_exv4		0x08		// 电子膨胀阀4运动方向
	#define	dir_exv1bak		0x10		// 电子膨胀阀1上次运动方向
	#define	dir_exv2bak		0x20		// 电子膨胀阀2上次运动方向
	#define	dir_exv3bak		0x40		// 电子膨胀阀3上次运动方向
	#define	dir_exv4bak		0x80		// 电子膨胀阀4上次运动方向

	#define	psw_openexv		0x3366		// 开阀
	#define	psw_def			0xe001		// 手动除霜
	#define	psw_clrerr		0xe002		// 清故障记录
	#define	psw_serve		0x0755		// 服务密码
	#define	psw_factory		0xeb00		// 工厂密码

	#define	dm_run_mode		0			//显示工作模式
	#define	dm_curr_para	        1			//显示实时参数
	#define	dm_set_para		2			//显示设置参数
	#define	dm_curr_err		3			//当前的故障代码
	#define	dm_his_err		4			//记忆的故障代码
	#define	dm_unit_para	        5			//显示内机配置/实时参数
	#define	dm_operate		6			//显示密码
	#define	dm_modify_para	        7			//显示密码

	#define	max_dispmode	8			//最大显示模式数
	#define	max_curr_para	23			//显示实时参数
	#define	max_set_para	23			//显示设置参数
	#define	max_scan_para	3			//显示查询的设置参数
	#define	max_curr_err	4			//当前的故障代码
	#define	max_his_err	16			//记忆的故障代码
	#define	max_unit_para	18			//显示内机配置/实时参数
	#define	max_modify_para	16			//显示内机配置/实时参数
	#define	max_psw			7			//显示密码

	#define	keyspd		7				// 按键速度控制
	#define	key1		1
	#define	key2		2
	#define	key3		3
	#define	key4		4

	#define	addr_para	2	// 设置参数在EEPROM中的起始地址
        #define HZ50            0
        #define HZ60            1
        #define EIC1            90
        #define EIC2            90
        #define EIC3            90 
        #define EIC4            90  
        #define EIC5            90        
        #define EIC6            90
// 以下参数在config中的位置
//	version				0
//	sw1					1
//	sw2					2
//	sw3					3
//	以上4个程序固化或拨码设置，以下16个软件设置
	#define	DefA		4	//除霜检测线A点（-15~-2℃，默认为-6℃，变化量为1℃），带符号表示
	#define	DefB		5	//除霜检测线B点（-30~-15℃，默认为-24℃，变化量为1℃），带符号表示
	#define	DefTemp		6	//除霜结束温度（5~20℃,默认为12℃，变化量为1℃），实际值
	#define	DefIT		7	//除霜间隔时间（25~90min，默认为45min，变化量为1min），实际值        
	#define	DefRT		8	//除霜运行时间（5~15min，默认为10min，变化量为1min），实际值         
	#define	NT			9	//降噪延时时间（3~9hour，默认为6hour，变化量为1hour），实际值
	#define	nStep1		10	//制热时阀动作系数step1（0.1~5，默认为1，变化量为0.1），放大10倍处理
	#define	nStep2		11	//制热时阀动作系数step2（0~5，默认为0.5，变化量为0.1），放大10倍处理
	#define	TscA1		12	//过热度温度1（0~TscA2℃,默认为32℃，变化量为1℃），实际值                      
	#define	TscA2		13	//过热度温度2（TscA1~50℃,默认为40℃，变化量为1℃），实际值                     
	#define	TscT1		14	//过冷度目标温度1（0~TscT2,默认为3℃，变化量为1℃），实际值                         
	#define	TscT2		15	//过冷度目标温度1（TscT1~TscT3,默认为8℃，变化量为1℃），实际值                     
	#define	TscT3		16	//过冷度目标温度1（TscT2~50℃,默认为12℃，变化量为1℃），实际值                     
	#define	factor_j	17	//制热补偿倍数限制
	#define	factor_m	18	//制冷能力衰减系数
	#define	umid		19	//内机中盘温度

// 1，显示外机实时参数 代码：0PXX 共22个
/*
00：电子膨胀阀1开读
01：电子膨胀阀2开读
02：电子膨胀阀3开读
03：电子膨胀阀4开读
04：总能力需求
05：数码压缩机PWM百分比
06：TH1
07：TH2
08：TH3
09：TH4
10：TH5
11：TH6
12：TH7
13：TH8
14：TH9
15：TH10
16：TH11
17：TH12
18：高压
19：低压
20：外机当前实际过热度
21：外机当前目标过热度
22：内机中盘平均温度
*/

// 2，显示外机硬件信息/配置参数 代码：0CXX 共30个
/*
00：外机程序版本
01：外机地址号
02：机型A/B
03：单冷/热泵C/H
04：连接内机数量
05：设置阀初始开度
06：设置能力
07：DefA
08：DefB
09：DefTemp
10：DefIT
11：DefRT
12：NT
13：nStep1
14：nStep2
15：TscA1
16：TscA2
17：TscT1
18：TscT2
19：TscT3
20：factor_j
21：factor_m
22：pip3
*/

// 3，显示当前恶性故障 代码：ECXX 不限
// 4，记忆的故障代码 代码：ESXX 共16个
// 5，显示密码 代码：----
// 6，显示内机实时参数 代码：UPXX 共
/*
01：内机程序版本
02：能力
03：机型0：MCC；1：MCK；2：MCM；3：MWM；4：MDB；
04：线控器设置温度
05：线控器设置模式，STOP：停机；COOL：制冷；HEAT：制热；FAN：送风；DRY：除湿；
06：线控器设置风速，F0：停；F1：低速；F2：中速；F3：高速：F4：自动；
07：内机运行模式，STOP：停机；COOL：制冷；HEAT：制热；FAN：送风；DRY：除湿；DEF：除霜；TEST：调试
08：内机电子膨胀阀开度
09：内机能力需求百分比
10：内机进盘温度
11：内机中盘温度
12：内机出盘温度
13：内机回风温度
14：故障查询
*/

/*===============================================================================
	位数据定义
================================================================================*/
//err[6]
	#define	bit_err_sys		7	// 系统故障
	#define	bit_err_rom		6	// 存贮器故障
	#define	bit_err_low		5	// 低压开关
	#define	bit_err_hi		4	// 高压开关
	#define	bit_err_f3ov	3	// FIX3过载
	#define	bit_err_f2ov	2	// FIX2过载
	#define	bit_err_f1ov	1	// FIX1过载
	#define	bit_err_dov		0	// DIG过载

//err[7]
	#define	bit_err_scom	        7	// 从机通讯
	#define	bit_err_r407	        6	// 冷媒泄漏
	#define	bit_err_tsca	        5	// 过热度太小
	#define	bit_err_urg		4	// 紧急运行
	#define	bit_err_out		3	// 环境温度过高过低保护
	#define	bit_err_4wv		2	// 4WV故障
	#define	bit_err_comm	        1	// 通讯故障
	#define	bit_err_dhi		0	// 排气温度过高

//err[8]
	#define	bit_err_th8		7	// TH8开路/短路
	#define	bit_err_th7		6	// TH7开路/短路
	#define	bit_err_th6		5	// TH6开路/短路
	#define	bit_err_th5		4	// TH5开路/短路
	#define	bit_err_th4		3	// TH4开路/短路
	#define	bit_err_th3		2	// TH3开路/短路
	#define	bit_err_th2		1	// TH2开路/短路
	#define	bit_err_th1		0	// TH1开路/短路

//err[9]
	#define	bit_err_nocom	        6	// 内外机通讯全断
	#define	bit_err_ls		5	// 低压传感器开路/短路
	#define	bit_err_hs		4	// 高压传感器开路/短路
	#define	bit_err_th12	        3	// TH12开路/短路
	#define	bit_err_th11	        2	// TH11开路/短路
	#define	bit_err_th10	        1	// TH10开路/短路
	#define	bit_err_th9		0	// TH9开路/短路


	#define	comp1_on		0	// 开定速压缩机1允许
	#define	comp2_on		1	// 开定速压缩机2允许
	#define	comp3_on		2	// 开定速压缩机3允许
	#define	comp4_on		3	// 开定速压缩机4允许
	#define	comp1_off		4	// 关定速压缩机1允许
	#define	comp2_off		5	// 关定速压缩机2允许
	#define	comp3_off		6	// 关定速压缩机3允许
	#define	comp4_off		7	// 关定速压缩机4允许

	#define	m_u				1
	#define	s_u				0

#define		toilb		5400
//#define		toilb		300		//cuimin20071022 test
#define		toilr		5400	// 1.5hour
//#define		toilr		300		//cuimin20071022 test

unsigned char comprunflag;		// 压缩机on/off requare flag
unsigned char compstu;
unsigned char crunning;
/*===============================================================================
	标志位定义
================================================================================*/

struct flag
{
	unsigned char USE_A			:1;	// 仅使用了A板SET_A1 SET_A2 SET_B1
	unsigned char delrom		:1;	// 0/1,清除外部存贮器
	unsigned char anyerr		:1;	// 0/1,外机有故障
	unsigned char fleshwin		:1;	// 0/1,标准/新风机型
//	unsigned char oil_ban		:1;	// 0/1,no/油平衡
//	unsigned char oil_rec		:1;	// 0/1,no/油恢复
	unsigned char fend			:1;	// 0/1
	unsigned char run_heat		:1;	// 0/1,首次运行制热
	unsigned char dir			:1;	// 0/1,补偿dec/inc
	unsigned char chgpara		:1;	// 0/1,修改配置参数
	unsigned char inc			:1;	// 0/1,增加
	unsigned char dec			:1;	// 0/1,减载
	unsigned char incstop		:1;	// 0/1,增加停止
	unsigned char decstop		:1;	// 0/1,减载停止
	unsigned char slave			:1;	// 0/1,无/有从机
//	unsigned char fdef			:1;	// 0/1,开机除霜
	unsigned char sort_sp		:1;	// 0/1,current/voltage
	unsigned char no1			:1;	// 0/1,首次开机制热
	unsigned char dlt_eng		:1;	// 0/1,排温过高减载能力
	unsigned char deg			:1; // 0/1,无件载
	unsigned char or		:3;	// 0/1,油
	unsigned char ob			:1;	// 0/1,油平衡
	unsigned char cd		:1;	// 0/1,压力过高时能力减载
	//unsigned char aa		:1;
        unsigned char cnt_cap1           :1;				// 补偿能力0.7~1.0减半用计数器
        unsigned char cnt_cap2		:1;		// 补偿能力1.0~1.2减半用计数器
        unsigned char sh_out_hig        :1;   //回气过热度过高过冷阀调节标志
        unsigned char first_sh_out_hig  :1;    //首次回气过热度过高过冷阀调节标志
        unsigned char d_def_hi		:1;		//除霜时高压开关 cuimin20071025
}flags;

/*===============================================================================
//	全局变量定义
===============================================================================*/

unsigned char flag_comprun;			// 记录压缩机运行标记
//D0:COMP1
//D1:COMP2
//D2:COMP3
//D3:COMP4

unsigned char Tsct;				// 目标过热度(放大10倍)
int Tsca;					// 实际过热度(放大10倍)
int step1;					// 根据实际过热度和目标过热度计算的开度变化(放大10倍)
int step2[3];					// 根据进盘和回气温度计算的开度变化(放大10倍)
unsigned char R22_HZ;                           //50HZ和60HZ的区别
unsigned char num_in;				// 内机数量
unsigned char cap_sys;				// 系统总功率，100X
unsigned int  cap_all_bak;			// 上一周期室内机能力总需求
unsigned int  cap_all;				// 本周期室内机能力总需求扩大1000倍
unsigned int  cap_act;				// 实际能力需求倍份
unsigned int  cap_all_temp;                     //
unsigned int  eng_bc;				// 能力补偿量
unsigned char cnt_th1;				// 补偿能力减半用计数器(TH1过高)
unsigned char cnt_hi;				// 补偿能力减半用计数器(高压过高)
unsigned char eng_inv;				// 补偿能力减半用计时器
unsigned char menddef;				// 主机结束除霜
unsigned char senddef;				// 从机结束除霜
//unsigned char time_eng_hi_limit;                 //排气压力过高时每周期减载数码的15%，计时
unsigned char key;				// 按键
unsigned char keybak;				// 按键
unsigned char keycnt;				// 按键计时
unsigned char psw[4];				// 口令
unsigned char pswcnt;				// 口令计数
signed   char pa_input;				//输入参数位数
signed   char mod_point;	 		//修改参数的指针
unsigned char op_grade;				//按键操作级
unsigned char out_stu2_bak;                     //上一次压缩机状态
unsigned char dir_exv;				// 电子膨胀阀运行方向，1/0：增加/减少
/*
//	D7		D6		D5		D4		D3		D2		D1		D0
//	exvbak4	exv3bak	exv2bak	exv1bak	exv4	exv3	exv2	exv1
*/

signed 	 char exv_pos[4];			// 阀的位置 -128 ~ +127
unsigned int  chg_step[4];			// 电子膨胀阀改变步数
unsigned int  chg_stepbak[4];		        // 电子膨胀阀改变步数备份
int step[4];					// 电子膨胀阀实际步数
int init_step[4];				// 设置的膨胀阀初始开度

unsigned char FAN_EV_OUT;			// 风机和电磁阀输出寄存器
unsigned char FAN_EV_OUTBAK;		        // 风机和电磁阀输出寄存器备份

unsigned char cnt_eadd;				// 能力补偿次数
unsigned char p_eadd;				// 能力补偿倍数

unsigned char time_input_det;		        // 输入信号检测

unsigned int  time_reset;			// 复位时间，用于制热时计算目标过热度,unit:s
unsigned int  time_cmp_dlt;			// 计算过热度用，两次比较DLT的时间间隔 320S

unsigned char time_ddsm;			// 除霜检测计时,unit:min
unsigned char time_ddss;			// 除霜检测计时,unit:ms
unsigned char time_drm;				// 除霜运行时间,unit:min
unsigned char time_drs;				// 除霜运行时间,unit:s

unsigned char time_hpress;			// 高压检测时间>320ms认为是故障
unsigned char time_lpress;			// 低压检测时间>320ms认为是故障
unsigned char time_cov[4];			// 压缩机过流检测时间

unsigned int  time_compall_off;		// 所有压缩机全部停止时开始计时，用于四通阀换相,unit:s
unsigned int  time_comp_on[4];		// 压缩机启动时开始计时，用于最小运行时间保护,unit:s
unsigned char time_comp_off[4];		// 压缩机停止时开始计时，用于停机保护,unit:s
unsigned char time_mea_dlt;		// 数码压缩机排气温度检测时间间隔，unit:s
unsigned char time_dlt_high;		// 数码压缩机排气温度过高检测时间，unit:s
unsigned char time_base;		// 1s基本计时
unsigned char time_adc;			// 测量温度时间间隔

unsigned int  time_chg_queue;		// 流程切换时计时，单位为S
unsigned char time_hex;			// 热交器切换时间间隔，单位为S
unsigned char time_fan;			// 风机切换时间间隔，单位为S
unsigned char time_comp;		// 压缩机启动间隔

unsigned char time_exv_stop[4];		// 电子膨胀阀驱动停止延时500ms稳定
unsigned char time_exv;			// 电子膨胀阀驱动延时150ms每步
unsigned char time_adjexv;		// 制热运行前3分钟不可调阀
unsigned char time_eadd;		// 能力补偿周期
unsigned char time_disp;		// display for 1s and off for 0.5s,cycle

unsigned int  time_dig_onbak;		// 数码压缩机有能力输出时的时间宽度,unit:ms
unsigned int  time_dig_offbak;		// 数码压缩机无能力输出时的时间宽度,unit:ms
unsigned int  time_dig_on;		// 数码压缩机有能力输出时的时间宽度,unit:ms
unsigned int  time_dig_off;		// 数码压缩机无能力输出时的时间宽度,unit:ms
unsigned char time_ctrl;		// 控制时间，与d_time_ctrl对应

unsigned int  time_err[6][2];
// 0:数码过载,1:定速1过载,2:定速2过载,3:定速3过载,4:高压,5:低压
unsigned char err_cnt[6];			// 故障计数
// 0:数码过载,1:定速1过载,2:定速2过载,3:定速3过载,4:高压,5:低压
/*
unsigned int  time_oil_rec_det;		// 油恢复检测时间，unit:sec
unsigned int  time_oil_rec_run;		// 油恢复运行时间，unit:sec

unsigned char time_balance_run;		// 油平衡运行时间
		 long time_balance_det;		// 油平衡检测积分
*/
unsigned char time_comp_run_h[4];	// 运行小时高字节
unsigned char time_comp_run_l[4];	// 运行小时低字节
unsigned char time_comp_run_m[4];	// 运行分钟
unsigned char time_comp_run_s[4];	// 运行秒钟

unsigned char time_fan_th1;		// 根据排温调整风机
unsigned char time_defrost;		// 除霜检测时间S
unsigned int  time_invdef;		// 两次除霜间隔
unsigned char time_heat_sec;		// 制热运行时间秒钟
unsigned char time_heat_min;		// 制热运行时间分钟

unsigned int  time_th8_over;		// 超过环境温度范围的保护运行

unsigned int  time_tscafail;		// 制冷时实际过热度小于2运行时间S
unsigned int  time_TH12fail;		// TH12故障保护运行时间S
unsigned int  time_LSfail;			// LS故障保护运行时间S
unsigned char flag_inn_com;		//至少有一太内机通信故障标志

unsigned int  time_keepstub;		//
unsigned int  time_oilb;
unsigned int  time_keepstur;		//
unsigned int  time_oilr;


unsigned char rxd_in[len_rxd_in];     // 接收室内机数据缓冲区
unsigned char rxd_inbak[max_unit][19];// 接收的室内机组参数备份
//[0]：程序版本
//[1]：拨码1，高四位为机型；低四位为能力
//[2]：拨码2，保留/保留/水泵/步进摆风/普通摆风/新风/电加热2/电加热1
//[3]：拨码3，保留
//[4]：线控器模式字1
//[5]：线控器模式字2
//[6]：内机运行模式
//[7]：保留
//[8]：线控器故障
//[9]：内机阀开度100
//[10]：内机阀开度10
//[11]：能力需求
//[12]：inlet temp
//[13]：midlet temp
//[14]：outlet temp
//[15]：indoor temp
//[16]：in+mid
//[17]：out+indoor
//[18]：保留

unsigned char txd_in[60];				// 发送到室内机数据缓冲区
unsigned char rxd_pc[len_rxd_pc];		// 主机接收计算机数据缓冲区
unsigned char rxd_pcbak[3][max_unit+4];	// 接收计算机数据缓冲区备份3级缓冲校验参数不备份,处理完毕清除
// 数据存贮格式：
// 1：[0]:cmd:7/8
// 当CMD为7时：
//	[1]：内机数N
//	[2]：线控器模式字1
//	[3]：线控器模式字2
//	[4]~[N+3]为内机地址号
// 当CMD为8时：
//	[1]：线控器模式字1
//	[2]：线控器模式字2

unsigned char hic_state;                        //当前过冷阀状态
unsigned char hic_state_bak;                    //上一次过冷阀状态
unsigned char sh_out_time;                     //调节过冷阀60S计时
unsigned char ini_sh_out_time;                  //调节过冷阀初始计时
unsigned char ini_hicset[8];                    //过冷阀在不同能力下的初始开度
unsigned char txd_pc[250];			// 发送到计算机机数据缓冲区，1+1+1+10+1+9*16+1+1
unsigned char txd_loop;				// 每次最大连续发送次数（发送时初始化）
unsigned char rxd_count;			// 发送次数计数，被4整除时发送广播数据，其他发查询命令
unsigned char byte_rxd_in;			// 接收的室内机字节数
unsigned char byte_txd_in;			// 发送的室内机字节数
unsigned char byte_rxd_pc;			// 接收的上位机字节数
unsigned char byte_txd_pc;			// 发送的上位机字节数
unsigned char byte_rxd_pcbak;		        // 接收数据长度备份
unsigned char temp_bak1;
unsigned char comm_in_en[6];		        // 与内机通讯允许标志位
unsigned char unit_run[6];			// 室内机运行标志位，1/0运行/停止，存方排列参见10.4

unsigned int time_rec_in;			// 连续接收室内机数据累计时间
unsigned char time_byte_in;			// 接收室内机两个数据字节时间间隔
unsigned char time_byte_pc;			// 接收上位机两个数据时间间隔
unsigned char time_comm_slave;		        // 从机通讯保护

unsigned char uchCRCHi;
unsigned char uchCRCLo;

unsigned char cnt_500ms;			// 显示用


unsigned char count_yellow;			// 数码压缩机排气温度进入黄色区域定时检测次数
unsigned char fan_spd;				// 风速控制，0/1/2/3：停/低/种/高
unsigned char unit_addr;			// 查询的室内机编号
unsigned char cur_pcbak;			// 检索计算机接收缓冲区，内机开关控制用

int	TH8BAK;							// 环境温度（放大10倍后取整，有符号）
int	temp_buf[12];					// 温度（放大10倍后取整，有符号）
int     dig_pwm;				// 数码压缩机的PWM占空比,放大10倍取整
int     dig_pwm_bak;				// 数码压缩机的PWM占空比备份,放大10倍取整
signed char target_superheat;		        // 外机目标过热度，用于制热时电子膨胀阀的控制
unsigned char mea_p;				// 分时测量温度指针

unsigned int  hi_pressure;			// 高压值,40s周期内的平均值，放大10X
unsigned int  low_pressure;			// 低压值,40s周期内的平均值，放大10X
unsigned char cnt_hipre;			// 压力测试次数
unsigned char cnt_lowpre;			// 压力测试次数
unsigned int  hp_buf[8];			// 高压
unsigned int  lp_buf[8];			// 高压

signed char dpoint_row;				// 行选择
signed char dpoint;					// 数值选择
unsigned char dbufcnt;				// 显示缓冲区计数器
unsigned char dbuf[4];				// 显示缓冲区，左为dbuf[3]，右为dbuf[0]
unsigned char dispmode;				// 显示模式
unsigned int  disp_5s;				// 显示刷新5S保持
unsigned char updata_f;				//数字刷新标记

unsigned char err_det;				//
//D7	D6		D5		D4		D3   	D2		D1		D0
//				COMP4	COMP3	COMP2	COMP1	LOW		HI
unsigned char err_point_row;		// 故障检索用
unsigned char err_point;			// 故障检索用
//unsigned char err_com_point;		// 通讯故障检索用
unsigned char err_rec[16];			// 保存在EEPROM里的故障记录
unsigned char err_rec_end;			// 当前的故障表尾
unsigned char err_rec_cur;			// 检索故障的指针位置
unsigned char err[10];				// 故障
/*
//0:	D7		D6		D5		D4		D3   	D2		D1		D0
//		7#		6#		5#	 	4#		3#		2#		1#		0#
//1:	D7		D6		D5		D4		D3   	D2		D1		D0
//		15#		14#		13#	 	12#		11#		10#		9#		8#
//2:	D7		D6		D5		D4		D3   	D2		D1		D0
//		23#		22#		21#	 	20#		19#		18#		17#		16#
//...
//6:	D7		D6		D5		D4		D3   	D2		D1		D0
//		SYSTEM	EEPROM	低压开关	高压开关	F3_OV	F2_OV	F1_OV	D_OV
//7:	D7		D6		D5		D4		D3		D2		D1		D0
//		从机通讯	冷媒泄漏	Tsca<2	紧急运行	超温保护	4WV		COMM	DLT_HI
//8:	D7		D6		D5		D4		D3   	D2		D1		D0
//		TH8		TH7 	TH6		TH5		TH4		TH3		TH2		TH1
//9:	D7		D6		D5	 	D4	  	D3   	D2		D1		D0
//				通讯全断 低压探头 高压探头	TH12	TH11	TH10	TH9
*/

signed   char paraadj;				// 调整参数时备份用
signed   char parabak;				// 调整参数时备份用
unsigned char queue;				// 运行队列，queue[0] 为当前运行模式，queue[0] 为即将运行模式
unsigned char queuebak;				// 发生故障时保护当前运行模式

unsigned char num_comp;				// 压缩机台数
unsigned char num_sv;				// 电磁阀个数
unsigned char num_4wv;				// 4通阀个数
//unsigned int  exv_init_open[4];		// 电子膨胀阀校验后的初始开度
unsigned char COMP[4];				// 定速压缩机能力表
unsigned char self_addr;			// 本机地址
signed char config[22];				// 室外机配置，详见通讯协议10.1
//[0]： 程序版本
//[1]： 拨码1
//[2]： 拨码2
//[3]： 拨码3
//[4]： Byte5	DefA除霜检测线A点（-15~-2℃，默认为-6℃，变化量为1℃），带符号表示
//[5]： Byte6	DefB除霜检测线B点（-30~-15℃，默认为-24℃，变化量为1℃），带符号表示
//[6]： Byte7   DefTemp除霜结束温度（5~20℃,默认为12℃，变化量为1℃），实际值
//[7]： Byte8	DefIT除霜间隔时间（25~90min，默认为45min，变化量为1min），实际值
//[8]： Byte9	DefRT除霜运行时间（5~15min，默认为10min，变化量为1min），实际值
//[9]： Byte10	NT降噪延时时间（3~9hour，默认为6hour，变化量为1hour），实际值
//[10]：Byte11	nStep1制热时阀动作系数step1（0.1~5，默认为2，变化量为0.1），放大10倍处理
//[11]：Byte12	nStep2制热时阀动作系数step2（0~5，默认为0.5，变化量为0.1），放大10倍处理
//[12]：Byte13	TscA1（0~TscA2℃,默认为32℃，变化量为1℃），实际值
//[13]：Byte14	TscA2（TscA1~50℃,默认为40℃，变化量为1℃），实际值
//[14]：Byte15	TscT1（0~TscT2,默认为3℃，变化量为1℃），实际值
//[15]：Byte16	TscT2（TscT1~TscT3,默认为8℃，变化量为1℃），实际值
//[16]：Byte17	TscT3（TscT2~50℃,默认为12℃，变化量为1℃），实际值
//[17]：Byte18	factor_j
//[18]：Byte19	factor_m
//[19]：Byte20	连管参数3
//[20]: Byte21  Tsct目标过热度（1~10℃默认值为5℃）
unsigned char out_stu[3];			// 见协议10.3 byte2,3,4
//[0]：模式
//[1]：风机+电磁阀状态
//[2]：四通阀+定速压缩机状态

unsigned char unit_set;				// 拨码设置类型

unsigned char data_out[33];			// 外机数据乾坤大挪移用的

unsigned char cnt_addexv_ls;		// 压力过低时开阀
unsigned char cnt_addexv_th1;		// 排温过高保护开阀

unsigned char cnt_openexv;			// 低压过低保护开阀

unsigned char hicset;				// 过冷阀设置初始开度
unsigned int  hicmax;				// 过冷阀最大开度
unsigned char hicmin;				// 过冷阀最小开度
unsigned char defexv;				// 除霜后阀恢复开度
unsigned char tab[4];
struct rt
{
	unsigned char week;				//
	unsigned char hour;				//
	unsigned char min;				//
	unsigned char sec;				//
}RTC;								// Real time clock

unsigned char SCOMP[4];				// 从机COMP
unsigned char eng_slave;			// 分配给内机的能力

unsigned char data_slave[72];		// 从机数据

unsigned char flag_frist_dlt;		//第一次排气过高
unsigned char frist_hi;			//第一次压力高压26
/*===============================================================================
	参数表 设置的缺省参数
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

const unsigned int init_open[4] =		// 初始开度
	{ 150,200,250,300 };

/*===============================================================================
	K2/K3调整时显示内容和范围
===============================================================================*/
const unsigned char disp_zone[] =
{
	26,				// 显示外机实时参数
	30,				// 显示外机硬件信息/配置参数
	30,				// 显示外机设置参数
	60,				// 显示当前恶性故障
	16,				// 记忆的故障代码
	14,				// 显示内机实时参数
	15				// 显示密码0-f
};

/*===============================================================================
	内机能力表，单位：HP 扩大了10倍
===============================================================================*/
const unsigned char cap_tab[] =
	{8,10,15,18,23,25,30,40,50,60,9,11,28,32,35,45,80,100,120,180,220,65,240};
//	{8,10,15,18,23,25,30,40,50,60,70,80,90,100,110,120};
    //8
/*===============================================================================
	内机运行模式表
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
	外机运行模式表
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
	显示操作模式表
===============================================================================*/
const unsigned char opmode_tab[][4] =
{
	{C_O,C_R,C_U,C_N},	// disp "ORUN"	显示工作模式
	{C_X,C_O,C_C,C_P},	// disp "OCP"	显示实时参数
	{C_X,C_O,C_S,C_P},	// disp "OSP"	显示设置参数
	{C_X,C_O,C_C,C_E},	// disp "OCE"	当前的故障代码
	{C_X,C_O,C_H,C_E},	// disp "OHE"	记忆的故障代码
	{C_X,C_U,C_C,C_P},	// disp "UCP"	显示内机配置/实时参数
	{C_P,C_A,C_S,C_S},	// disp "DEF"	显示密码
	{C_X,C_D,C_S,C_P}	// disp "DSP"	显示密码
};


/*===============================================================================
	ADC通道选择表
===============================================================================*/
#ifndef	NEWPCB
const unsigned char input_CH[] = // INH 0 有效
{	//CBA值
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

	0x00,	// 高压 mea_p=15
	0x01,	// 低压 mea_p=16
	0x02,	// DIG mea_p=17
	0x03,	// FIX1 mea_p=18
	0x04,	// FIX2 mea_p=19
	0x05	// FIX3 mea_p=20
};
#else//new PCB
const unsigned char input_CH[] = // INH 0 有效
{	//CBA值
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
	0x14,	// 电压型高压传感器 12 
	0x15,	// 电压型低压传感器 13 

	0x00,	// 高压 mea_p=14
	0x01,	// 低压 mea_p=15
	0x02,	// DIG mea_p=16
	0x03,	// FIX1 mea_p=17
	0x04,	// FIX2 mea_p=18
	0x05	// FIX3 mea_p=19

};
#endif
/*===============================================================================
// 拨码表
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
	传感器或检测输入是否存在
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
	传感器故障报警表
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
	显示段码表,共阳
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
	压缩机自带温度传感器
	参考电阻：10K，上拉至VCC
===============================================================================*/

const unsigned int dlt_tab[] =
{
		0x3D1,		//6(℃)
		0x3CC,		//8(℃)
		0x3C7,		//10(℃)
		0x3C2,		//12(℃)
		0x3BC,		//14(℃)
		0x3B6,		//16(℃)
		0x3B0,		//18(℃)
		0x3A9,		//20(℃)
		0x3A1,		//22(℃)
		0x399,		//24(℃)
		0x391,		//26(℃)
		0x388,		//28(℃)
		0x37F,		//30(℃)
		0x375,		//32(℃)
		0x36B,		//34(℃)
		0x360,		//36(℃)
		0x35A,		//38(℃)
		0x349,		//40(℃)
		0x33C,		//42(℃)
		0x32F,		//44(℃)
		0x322,		//46(℃)
		0x314,		//48(℃)
		0x306,		//50(℃)
		0x2F8,		//52(℃)
		0x2E9,		//54(℃)
		0x2D9,		//56(℃)
		0x2CA,		//58(℃)
		0x2BA,		//60(℃)
		0x2AA,		//62(℃)
		0x299,		//64(℃)
		0x289,		//66(℃)
		0x278,		//68(℃)
		0x267,		//70(℃)
		0x257,		//72(℃)
		0x246,		//74(℃)
		0x235,		//76(℃)
		0x224,		//78(℃)
		0x214,		//80(℃)
		0x203,		//82(℃)
		0x1F3,		//84(℃)
		0x1E3,		//86(℃)
		0x1D3,		//88(℃)
		0x1C3,		//90(℃)
		0x1B4,		//92(℃)
		0x1A5,		//94(℃)
		0x196,		//96(℃)
		0x188,		//98(℃)
		0x17A,		//100(℃)
		0x16D,		//102(℃)
		0x160,		//104(℃)
		0x153,		//106(℃)
		0x147,		//108(℃)
		0x13B,		//110(℃)
		0x12F,		//112(℃)
		0x123,		//114(℃)
		0x118,		//116(℃)
		0x10C,		//118(℃)
		0x101,		//120(℃)
		0xF7,		//122(℃)
		0xED,		//124(℃)
		0xE3,		//126(℃)
		0xDA,		//128(℃)
		0xD2,		//130(℃)
		0xCA,		//132(℃)
		0xC2,		//134(℃)
		0xBA,		//136(℃)
		0xB3,		//138(℃)
		0xAC,		//140(℃)
		0xA6,		//142(℃)
		0x9F,		//144(℃)
		0x99,		//146(℃)
		0x93			//148(℃)
};

/*===============================================================================
	温度表（奥微提供）	6~150'C
	参考电阻：10K，上拉至VCC
===============================================================================*/
const unsigned int dlt_tab1[] =
{
	0x2C1,		//6(℃)
	0x2AD,		//8(℃)
	0x299,		//10(℃)
	0x285,		//12(℃)
	0x270,		//14(℃)
	0x25C,		//16(℃)
	0x247,		//18(℃)
	0x233,		//20(℃)
	0x21E,		//22(℃)
	0x20A,		//24(℃)
	0x1F6,		//26(℃)
	0x1E2,		//28(℃)
	0x1CF,		//30(℃)
	0x1BC,		//32(℃)
	0x1AA,		//34(℃)
	0x197,		//36(℃)
	0x186,		//38(℃)
	0x175,		//40(℃)
	0x164,		//42(℃)
	0x154,		//44(℃)
	0x145,		//46(℃)
	0x136,		//48(℃)
	0x128,		//50(℃)
	0x11A,		//52(℃)
	0x10D,		//54(℃)
	0x100,		//56(℃)
	0xF4,		//58(℃)
	0xE9,		//60(℃)
	0xDE,		//62(℃)
	0xD3,		//64(℃)
	0xC9,		//66(℃)
	0xC0,		//68(℃)
	0xB7,		//70(℃)
	0xAE,		//72(℃)
	0xA6,		//74(℃)
	0x9E,		//76(℃)
	0x97,		//78(℃)
	0x90,		//80(℃)
	0x89,		//82(℃)
	0x83,		//84(℃)
	0x7D,		//86(℃)
	0x77,		//88(℃)
	0x71,		//90(℃)
	0x6C,		//92(℃)
	0x67,		//94(℃)
	0x62,		//96(℃)
	0x5E,		//98(℃)
	0x5A,		//100(℃)
	0x56,		//102(℃)
	0x52,		//104(℃)
	0x4F,		//106(℃)
	0x4B,		//108(℃)
	0x48,		//110(℃)
	0x45,		//112(℃)
	0x42,		//114(℃)
	0x3F,		//116(℃)
	0x3C,		//118(℃)
	0x3A,		//120(℃)
	0x38,		//122(℃)
	0x35,		//124(℃)
	0x33,		//126(℃)
	0x31,		//128(℃)
	0x2F,		//130(℃)
	0x2D,		//132(℃)
	0x2B,		//134(℃)
	0x2A,		//136(℃)
	0x28,		//138(℃)
	0x27,		//140(℃)
	0x25,		//142(℃)
	0x24,		//144(℃)
	0x22,		//146(℃)
	0x21		//148(℃)
};

/*===============================================================================
	温度表lets用
	参考电阻：10K，上拉至VCC
===============================================================================*/
const unsigned int tmp_tab[] =
{
	0x3B6,		//-30(℃)
	0x3AE,		//-28(℃)
	0x3A5,		//-26(℃)
	0x39C,		//-24(℃)
	0x392,		//-22(℃)
	0x387,		//-20(℃)
	0x37C,		//-18(℃)
	0x370,		//-16(℃)
	0x363,		//-14(℃)
	0x355,		//-12(℃)
	0x347,		//-10(℃)
	0x338,		//-8(℃)
	0x328,		//-6(℃)
	0x318,		//-4(℃)
	0x307,		//-2(℃)
	0x2F5,		//0(℃)
	0x2E3,		//2(℃)
	0x2D1,		//4(℃)
	0x2BD,		//6(℃)
	0x2AA,		//8(℃)
	0x296,		//10(℃)
	0x282,		//12(℃)
	0x26E,		//14(℃)
	0x25A,		//16(℃)
	0x246,		//18(℃)
	0x232,		//20(℃)
	0x21E,		//22(℃)
	0x20A,		//24(℃)
	0x1F6,		//26(℃)
	0x1E3,		//28(℃)
	0x1D0,		//30(℃)
	0x1BD,		//32(℃)
	0x1AA,		//34(℃)
	0x190,		//36(℃)
	0x187,		//38(℃)
	0x176,		//40(℃)
	0x166,		//42(℃)
	0x156,		//44(℃)
	0x146,		//46(℃)
	0x137,		//48(℃)
	0x129,		//50(℃)
	0x11B,		//52(℃)
	0x10E,		//54(℃)
	0x101,		//56(℃)
	0xF5,		//58(℃)
	0xEA,		//60(℃)
	0xDE,		//62(℃)
	0xD4,		//64(℃)
	0xCA,		//66(℃)
	0xC0,		//68(℃)
	0xB7,		//70(℃)
	0xAE,		//72(℃)
	0xA6,		//74(℃)
	0x9E,		//76(℃)
	0x96,		//78(℃)
	0x8F,		//80(℃)
	0x88,		//82(℃)
	0x82,		//84(℃)
	0x7C,		//86(℃)
	0x76,		//88(℃)
	0x70,		//90(℃)
	0x6B,		//92(℃)
	0x66,		//94(℃)
	0x61,		//96(℃)
	0x5D,		//98(℃)
	0x58,		//100(℃)
	0x54,		//102(℃)
	0x50,		//104(℃)
	0x4C,		//106(℃)
	0x49,		//108(℃)
	0x46,		//110(℃)
	0x43,		//112(℃)
	0x40,		//114(℃)
	0x3c,		//116(℃)
	0x39,		//118(℃)
	0x36		//120(℃)
};


/*===============================================================================
	低压表
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












