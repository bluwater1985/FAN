/********************************************************************************/
/* Filename:	initout.c														*/
/* Function:	数码涡旋室外机控器硬件初始化程序								*/
/* Mcu:			MB89F538														*/
/* Freq:		8MHZ(Cyrstal),Tcy=0.5us											*/
/* compilier:	Softune workbench												*/
/* Ver:			test															*/
/* CreatDate:	2003-07-31														*/
/********************************************************************************/


/********************************************************************************/
/*

	有UNION的要引用时在后面加.byte
	内部特殊功能寄存器初始化
	IO_PURRx，上拉电阻，1：NO，0：YES
	IO_DDRx，方向寄存器，0：INPUT，1：OUTPUT

	Description about the program:

/********************************************************************************/
/*	内部寄存器初始化
/********************************************************************************/
void init(void)
{
	unsigned char i;

	IO_PDR0.byte = 0x00;					// stop all
	IO_PDR1.byte = 0x07;					// stop all
	IO_PDR2.byte = 0x02;					// stop all
	IO_PDR3.byte = 0x08;
	IO_PDR4.byte = 0x00;
	IO_PDR5.byte = 0x07;					// P50~P52 use as ADC

	IO_DDR0 = 0xff;							// output for perpheral control
	IO_DDR1 = 0xff;							// output
	IO_DDR2.byte = 0xff;					// output
	IO_DDR3.byte = 0xf7;
	IO_DDR4.byte = 0x3b;					// 

	IO_PURR0.byte = 0xff;					// no pull up
	IO_PURR1.byte = 0xff;					// no pull up
	IO_PURR2.byte = 0xff;					// no pull up
	IO_PURR3.byte = 0xff;
	IO_PURR4.byte = 0xff;
	
	IO_DDCR.byte = 1;						// raising edge

	IO_PDR6.byte = 0x00;					// 
	IO_PURR6.byte = 0xff;

	IO_SYCC.byte = 0xff;					// 0.5us
//	IO_STBC.byte = 0;						// see p83
	IO_WDTC = 0x05;							// see p159 0x85
	IO_TBTC.bit.TBOF = 0;
	IO_TBTC.bit.TBIE = 0;					// disable int
	IO_TBTC.byte = 0x42;					// see p148, 2^15/4915200=6.666ms
	IO_WPCR.byte = 0;

//	About PWM timer
	IO_CNTR1.byte = 0;
	IO_CNTR2.byte = 0x80;//000000;
	IO_CNTR3.byte = 0;						// normal mode
	IO_COMR1 = 1;							// 19200bps，OK！
	IO_COMR2 = 250;

//	HIGH SPEED UART，接PC
	IO_SRC1.byte = 0x08;					// 19200,PWM1
	IO_SMC11.byte = 0x54;//0x56;			// P400,mode2,async,1stop bit,high uart
	IO_SMC12.byte = 0x21;					// P402
	i = IO_SIDR1;							// Clr  OFRE flag
	i = IO_SSD1.byte;
	IO_SSD1.byte = 0;
	IO_SSD1.bit.RIE = 1;					// enable rec int

//	About PWC
	IO_PCR1.byte = 0;
	IO_PCR2.byte = 0;						// See P236
	IO_RLBR = 0;							// See P237

// 	COMMON UART，接UNIT
// 19200bps,异步，1个停止位，
	i = IO_SIDR2;							// clear RDRF flag
	IO_SMC21.byte = 0x0b;//00001011;		// see p368
	IO_SRC2 = 4;							// 19200bps
	IO_SMC22.byte = 0;						// see p370
	i = IO_SSD2.byte;

	IO_PPGC2.byte = 0;
	IO_PRL22.byte = 0;
	IO_PRL21.byte = 0;
	IO_PRL23.byte = 0;

//	IO_TMCR.byte = 0x03;					// enable interrupt
	IO_TMCR.byte = 0x01;					// disable interrupt

	IO_TCR = tm1ms;							// 63535,1ms timer
	IO_EIC1.byte = 0x22;//b00100010;		// fall edge, disable int
	IO_EIC2.byte = 0x22;//b00100010;		// fall edge, disable int
	IO_PPGC1.byte = 0;
	IO_PRL12.byte = 0;						// disable PPG1
	IO_PRL11.byte = 0;
	IO_PRL13.byte = 0;

//	About I2C
//	IO_ICCR.byte = 0x69;					// clock control register
//	IO_ICCR.bit.EN = 1;
//	IO_ICCR.byte = 0x69;					// clock control register
	IO_ICCR.byte = 0x00;
	IO_IBCR.byte = 0x00;					// slave mode
//	IO_IACR.byte = 7;						// See P454 address control register
//	IO_IBSR.byte = b01100000;				// bus status register
//	IO_IBCR.byte = b00110000;				// bus control register
//	IO_IADR.byte =							// address register
//	IO_IDAR =								// data register

	IO_EIE2.byte = 0;						// disable external int2 input
	IO_EIF2.byte = 0;
	IO_RCR1.byte = 0;
	IO_RCR2.byte = 0;						// disable 6bit PPG timer

//	clock output function
	IO_CKR.byte = 0;						// See P496
	IO_SMR.byte = 0;
	IO_SDR = 0;
	IO_WREN.byte = 0;
	IO_WROR.byte = 0;

//	Int level set
	IO_ILR1 = 0;
	IO_ILR2 = 0;
	IO_ILR3 = 0;
	IO_ILR4 = 0;
}

/********************************************************************************/
/*	系统参数初始化
/********************************************************************************/
void init_para(void)
{
	unsigned char i,j,buf[5];
//	flags.oil_ban = 0;
	flags.fend = 0;
	flags.ob = 0;
	flags.delrom = 0;
	flags.dir = 1;
	flags.inc = 0;
	flags.incstop = 0;
	flags.dec	= 0;
	flags.decstop = 0;
	flags.anyerr = 0;
	flags.run_heat = 1;
	flags.fleshwin = 0;
	flags.no1 = 1;
	flags.dlt_eng = 0;
	flags.deg = 0;
	cnt_500ms = 0;
	comprunflag = 0;
	flags.cnt_cap1 = 0;
	flags.cnt_cap2 = 0;
	cnt_th1 = 0;
	cnt_hi = 0;
	eng_inv = 0;
	menddef = 0;
	senddef = 0;
	
	for ( i=0;i<6;i++ )
	{
		unit_run[i] = 0;
		comm_in_en[i] = 0xff;				// 通讯允许
	}
	for ( i=0;i<10;i++ )
	{
		err[i] = 0;
	}
	dispmode = 0;
	time_compall_off = 1800;
	for ( i=0;i<4;i++ )
	{
		time_comp_on[i] = 0;
		time_comp_off[i] = m3;
		time_cov[i] = 0;
	}
	for ( i=0;i<8;i++ )
	{
		hp_buf[i] = 0;
		lp_buf[i] = 0;
	}
	cnt_hipre = 0;
	cnt_lowpre = 0;

	I2C_R(0xa0, 0xa1, buf, 0, 2);
	nop;

	if ( (buf[0] == 0x33) && (buf[1] == 0x66) )	// 标记判断，确认是否写默认数据
	{
		for ( i=0;i<4;i++ )						// 读设置参数
		{
			delay(20);
			j = i<<2;
			I2C_R(0xa0, 0xa1, err_rec+j, j+0x40, 4);
			delay(20);
			I2C_R(0xa0, 0xa1, buf, 0x70+i*4, 4);
			time_comp_run_h[i] = buf[0];
			time_comp_run_l[i] = buf[1];
			time_comp_run_m[i] = buf[2];
		}
		for ( i=0;i<5;i++ )
		{
			delay(20);	
			j = i<<2;
			I2C_R(0xa0, 0xa1, config+j+4, j+0x10,4);			
		}		
	        Tsct=config[20];
	}
	else	// new or error
	{
		buf[0] = 0x33;
		buf[1] = 0x66;
		delay(10);
		I2C_W( 0xa0,buf,0,2);					// 标记
		delay(10);
		buf[0] = 0;
		buf[1] = 0;
		I2C_R(0xa0, 0xa1, buf, 0, 2);
		if ( (buf[0] == 0x33) && (buf[1] == 0x66) )	// 标记判断，确认是否写默认数据
		{
			clr_bit(&err[6],bit_err_rom);		// ROM ERR
		}
		else
		{
			set_bit(&err[6],bit_err_rom);		// ROM ERR
		}
		for ( i = 0; i < 17; i++ )				// 16个可调参数
		{
			config[i+4] = para_defalt[i];		// 读缺省参数
		}
		for ( i=0;i<5;i++ )
		{
			delay(20);
			j = i<<2;
			I2C_W( 0xa0,config+j+4,j+0x10,4);
			buf[i] = 0xff;
		}
		clrwdt();

		for ( i=0;i<4;i++ )
		{
			delay(20);
			I2C_W( 0xa0,buf,4*i+0x40,4);
		}
		clrwdt();

		for ( i=0;i<4;i++ )
		{
			buf[i] = 0;
		}

		for ( i=0;i<4;i++ )
		{
			delay(20);
			I2C_W( 0xa0,buf,4*i+0x70,4);
		}

		for ( i=0; i<4; i++ )
		{
			time_comp_run_h[i] = 0;
			time_comp_run_l[i] = 0;
			time_comp_run_m[i] = 0;
		}
	}

	for ( i = 0; i < 17; i++ )
	{
		if ( config[i+4] < para_min[i] || config[i+4] > para_max[i] )
		{ 									// 数据校验错，或超出可能范围
			config[i+4] = para_defalt[i];
		}
		err_rec[i] = 0xff;
	}
        Tsct=config[20];
	RTC.week = 0;
	RTC.hour = 0;
	RTC.min = 0;
	RTC.sec = 0;
	
	time_rec_in = 0;
	time_th8_over = 0;
	time_ddsm = 0;							// 除霜检测计时,unit:min
	time_ddss = 0;							// 除霜检测计时,unit:ms
	time_drm = 0;							// 除霜运行时间,unit:min
	time_drs = 0;							// 除霜运行时间,unit:s
	time_reset = 0;
	time_cmp_dlt = 0;
	time_disp = 0;
	time_ctrl = 0;
	time_adc = 0;
	time_base = 0;
	time_input_det = 0;
	time_exv = 0;
	time_lpress = 0;
	time_hpress = 0;
	time_chg_queue = 0;
	time_dig_onbak = 0;
//	time_eng_hi_limit = 80;
	time_dig_on = 0;
	time_dig_off = 20000;					// no eng output of dig comp
	time_comm_slave = 0;
	time_tscafail = 0;
	time_TH12fail = 0;
	time_eadd = 0;
	time_adjexv = 240;
	time_dlt_high = 0;
	time_invdef	= 600;
	eng_bc = 0;								// 能力补偿部分
	cnt_eadd = 0;							// 能力补偿次数
	
	time_fan_th1=0;
	time_keepstub = 0;
	time_oilb = 0;	
	
	flag_comprun = 0;
	Tsct = 50;								// 目标过热度
	Tsca = 0;								// 实际过热度
	hi_pressure = 0;
	low_pressure = 0;
	cnt_addexv_ls = 0;
	cnt_addexv_th1 = 0;
	cnt_openexv = 0;
	crunning = 0;
	for ( i = 0; i < 6; i++ )
	{
		err_cnt[i] = 0;
		for ( j = 0; j < 2; j ++ )
		{
			time_err[i][j] = 0;
		}
	}

         ini_hicset[1]=0;
         ini_hicset[2]=0;
         ini_hicset[3]=0;
         ini_hicset[4]=0;
         ini_hicset[5]=0;
         ini_hicset[6]=0;         

	time_mea_dlt = 3;
	time_byte_in = 120;
	time_byte_pc = 0;
	byte_txd_in = 0;
	byte_rxd_in = 0;
	byte_txd_pc = 0;
	byte_rxd_pc = 0;
	byte_rxd_pcbak = 0;
	
	count_yellow = 0;
	target_superheat = 15;					// 初始目标过热度为1.5度
	dpoint = 0;//0xff
	fan_spd = 0;							// stop fan
	time_fan = 0;
	mea_p = 0;

	dig_pwm_bak = 0;
	dig_pwm = 0;
	cap_all = 0;
	cap_all_bak = 0;

	queuebak = q_null;
	err_det = 0;
	err_point = 1;
	err_rec_cur = 0;
	err_rec_end = 0;
	out_stu[0] = 0;
	out_stu[1] = 0;
	out_stu[2] = 0;
	FAN_EV_OUT = 0;
	disp_5s = 0;
//	op_grade = 1;			//按键操作级
	pa_input = 0;			//输入参数位数
	for ( i = 0;i < max_unit; i ++ )		// CLR indoor backup data
	{
		for ( j = 0;j < 19; j++ )
		{
			rxd_inbak[i][j] = 0;
		}
		data_slave[i] = 0;
	}
	
	for ( i = 0; i < 20; i++ )
	{
		rxd_in[i] = 0;
	}

	for ( i = 0; i < 53; i++ )
	{
		txd_in[i] = 0;
	}

	for ( i = 0; i < 3; i++ )
	{
		for ( j=0; j < max_unit+2; j++ )
		{
			rxd_pcbak[i][j] = 0;			// 接收到的计算机命令备份
		}	
	}
	cur_pcbak = 0;							// 从 rxd_pcbak[i][4] 开始为内机地址
}

/********************************************************************************/
/* end of file																	*/
/********************************************************************************/