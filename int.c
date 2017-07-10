
/********************************************************************************/
/* Filename:	intout.c							 							*/
/* Function:	������������������жϷ������										*/
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
/*	����Ϊ�жϷ������
/********************************************************************************/


/********************************************************************************/
/*	��ʱ�ж�
/********************************************************************************/
__interrupt void time_1ms(void)				// ��ʱ�ж�
{
	if ( IO_TMCR.bit.TCEF )					// 1ms ��ʱ
	{
		IO_TMCR.bit.TCEF = 0;
		IO_TCR = tm1ms;						// 1ms timer
		time_byte_pc ++;
		time_exv ++;
		if ( time_byte_in ++ > 250 )		// �������ֽ�ʱ����
			time_byte_in = 251;

		if ( COMMIN == txd )
		{
			if ( (txd_in[1] == 5) || (txd_in[1] == 6) || (txd_in[1] == 7) )
			{								// ��3��������ҪӦ��
				if( time_byte_in >= 3 && txd_loop < frame_loop ) 
				{ 							// ���ͺ���ʱ3ms�Ž�RS485��Ϊ����״̬��
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
//	��UNITͨѶ
//================================================================================
__interrupt void uart_sio(void)
{
	unsigned char i;
	i = IO_SSD2.byte & 0xe0;
	if ( i )
	{
		IO_SMC22.bit.RERC = 0;				// clr error flag
		i = IO_SIDR2;						// clear���յ�������
	}
	else if ( IO_SSD2.bit.RDRF )			// �����ж�
	{
		rxd_in[byte_rxd_in] = IO_SIDR2;		// �����յ�������
		byte_rxd_in ++;
		if ( byte_rxd_in >= len_rxd_in )
			byte_rxd_in = len_rxd_in;
			
		IO_SMC22.bit.RERC = 0;				// clr errors flag
		time_byte_in = 0;
	}
	else if ( IO_SSD2.bit.TDRE )			// �����ж�
	{
		i = txd_in[2] + 5;
		if (byte_txd_in < i )				// δ������
		{
			IO_SIDR2 = txd_in[byte_txd_in];	// ������һ�ֽ�
			byte_txd_in ++;
			time_byte_in = 0;
		}
		else								// �������
		{
			IO_SMC22.bit.TIE = 0;			// �ر�UART TXD �ж�
			IO_SMC22.bit.TXE = 0;			//
		}
	}
	else
	{
		i = IO_SIDR2;						// clear���յ�������
		COMMIN = txd;
		IO_SMC22.byte = txd1mode;
	}
}

//================================================================================
//	IRQB ��PCͨѶ����
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
//	IRQC ��PCͨѶ����
//================================================================================
__interrupt void txd_int(void)
{
	unsigned char i;
	if ( byte_txd_pc < txd_pc[2] + 5 )		// δ������ϣ�����
	{
		i = IO_SSD1.byte;					// ����IO_SSD1֮��Ž�IO_SIDR1�е�����
		IO_SIDR1 = txd_pc[byte_txd_pc];
		byte_txd_pc ++;						// �͵���λ�Ĵ�����
		time_byte_pc = 0;
	}
	else if ( time_byte_pc > 2 )			// ������ϣ��л�������ģʽ
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
/*	������ʱ�ж�1/150s
/********************************************************************************/

__interrupt void timebase_int(void)
{
	if ( IO_TBTC.bit.TBOF )					// 1/150s ��ʱ
	{
		IO_TBTC.bit.TBOF = 0;
		time_150();
		if ( config[2] & 0x80 )				        // ����
		{
			if ( queue == q_cool || queue == q_heat )
				ctrl_dcomp();				// ��������ѹ����
		}							// time count of system
	}
}

//================================================================================
// end of file
//================================================================================
