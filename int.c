
/********************************************************************************/
/* Filename:	intout.c							 							*/
/* Function:	数码涡旋室外机控器中断服务程序										*/
/* Mcu:			MB89F538														*/
/* Freq:		8MHZ(Cyrstal),Tcy=0.5us											*/
/* compilier:	Softune workbench												*/
/* Ver:			test															*/
/* CreatDate:	2003-07-31														*/
/********************************************************************************/

#pragma intvect time_1ms			0x08// 16bit timer
#pragma intvect uart_sio			0x0a// uart/sio
#pragma intvect rxd_int				0x0b// recept
#pragma intvect txd_int				0x0c// transmite
#pragma intvect timebase_int		        0x0e// time base int

/********************************************************************************/
/*	以下为中断服务程序
/********************************************************************************/


/********************************************************************************/
/*	定时中断
/********************************************************************************/
__interrupt void time_1ms(void)				// 定时中断
{
	if ( IO_TMCR.bit.TCEF )					// 1ms 定时
	{
		IO_TMCR.bit.TCEF = 0;
		IO_TCR = tm1ms;						// 1ms timer
		time_byte_pc ++;
		time_exv ++;
		if ( time_byte_in ++ > 250 )		// 接收两字节时间间隔
			time_byte_in = 251;

		if ( COMMIN == txd )
		{
			if ( (txd_in[1] == 5) || (txd_in[1] == 6) || (txd_in[1] == 7) )
			{								// 这3个命令需要应答
				if( time_byte_in >= 3 && txd_loop < frame_loop ) 
				{ 							// 发送后延时3ms才将RS485置为输入状态。
				     byte_rxd_in = 0;
				     IO_SMC22.byte = rxd1mode;
	    	    	             COMMIN = rxd;
				}
			}
			time_rec_in = 0;
		}
		else
		{
			time_rec_in ++;
			if ( time_rec_in >= 3000 )
				time_rec_in = 3000;
		}
		
	}
}

//================================================================================
//	与UNIT通讯
//================================================================================
__interrupt void uart_sio(void)
{
	unsigned char i;
	i = IO_SSD2.byte & 0xe0;
	if ( i )
	{
		IO_SMC22.bit.RERC = 0;				// clr error flag
		i = IO_SIDR2;						// clear接收到的数据
	}
	else if ( IO_SSD2.bit.RDRF )			// 接收中断
	{
		rxd_in[byte_rxd_in] = IO_SIDR2;		// 读接收到的数据
		byte_rxd_in ++;
		if ( byte_rxd_in >= len_rxd_in )
			byte_rxd_in = len_rxd_in;
			
		IO_SMC22.bit.RERC = 0;				// clr errors flag
		time_byte_in = 0;
	}
	else if ( IO_SSD2.bit.TDRE )			// 发送中断
	{
		i = txd_in[2] + 5;
		if (byte_txd_in < i )				// 未发送完
		{
			IO_SIDR2 = txd_in[byte_txd_in];	// 发送下一字节
			byte_txd_in ++;
			time_byte_in = 0;
		}
		else								// 发送完毕
		{
			IO_SMC22.bit.TIE = 0;			// 关闭UART TXD 中断
			IO_SMC22.bit.TXE = 0;			//
		}
	}
	else
	{
		i = IO_SIDR2;						// clear接收到的数据
		COMMIN = txd;
		IO_SMC22.byte = txd1mode;
	}
}

//================================================================================
//	IRQB 与PC通讯接收
//	read IO_SSD1 and IO_SIDR1, then clear RDRF flag
//================================================================================
__interrupt void rxd_int(void)
{
	unsigned char i,j;
	j = IO_SIDR1;							// Clr  OFRE flag
	i = IO_SSD1.byte & 0xc0;
	nop;
	nop;
	if (i == 0x80)							// normal data
	{
		rxd_pc[byte_rxd_pc] = j;			// read and clear RDRF flag
		byte_rxd_pc ++;						// next byte
		if (byte_rxd_pc >= len_rxd_pc )
			byte_rxd_pc = 0;//len_rxd_pc;
		time_byte_pc = 0;
	}
	else
	{										// overrun errors
		j = IO_SIDR1;						// Clr  OFRE flag
		i = IO_SSD1.byte;
	}
}

//================================================================================
//	IRQC 与PC通讯发送
//================================================================================
__interrupt void txd_int(void)
{
	unsigned char i;
	if ( byte_txd_pc < txd_pc[2] + 5 )		// 未发送完毕，继续
	{
		i = IO_SSD1.byte;					// 读了IO_SSD1之后才将IO_SIDR1中的数据
		IO_SIDR1 = txd_pc[byte_txd_pc];
		byte_txd_pc ++;						// 送到移位寄存器中
		time_byte_pc = 0;
	}
	else if ( time_byte_pc > 2 )			// 发送完毕，切换到接收模式
	{
		COMMPC = rxd;						// MAX485 turn to input mode
		byte_rxd_pc = 0;					// next byte
		byte_rxd_pcbak = 0;					// next byte
		i = IO_SIDR1;						// Clr  OFRE flag
		IO_SSD1.bit.TIE = 0;				// disable txd int
		IO_SSD1.bit.RIE = 1;				// enable rec int
	}
}

/********************************************************************************/
/*	基本定时中断1/150s
/********************************************************************************/

__interrupt void timebase_int(void)
{
	if ( IO_TBTC.bit.TBOF )					// 1/150s 定时
	{
		IO_TBTC.bit.TBOF = 0;
		time_150();
		if ( config[2] & 0x80 )				        // 主机
		{
			if ( queue == q_cool || queue == q_heat )
				ctrl_dcomp();				// 控制数码压缩机
		}							// time count of system
	}
}

//================================================================================
// end of file
//================================================================================
