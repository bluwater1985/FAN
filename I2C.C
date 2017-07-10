#include "mcu.h"
#include "I2C.h"
extern void delay_ms(unsigned int count_ms);
/********************************************************************************/
/* Filename:	I2C.c															*/
/* Function:	I2C READ AND WRITE												*/
/* Mcu:			PIC16F73														*/
/* Freq:		4MHZ(Cyrstal),Tcy=1us											*/
/* compilier:	HT-PICC and MPLAB IDE 5.70.20									*/
/* Ver:			test															*/
/* CreatDate:	2003-02-26														*/
/********************************************************************************/


/********************************************************************************/
/*	本程序原用于PIC系列单片机，用于MB89F538时要更改部分内容 


/********************************************************************************/
/*	24C0X子程序 																	*/
/********************************************************************************/

/********************************************************************************/
/* When SCK is high, a high to low of SDA generate a start signal.				*/
/*	scl_____
/*			\__
/*	sda__
/*		 \_____
/********************************************************************************/
void I2C_Start(void)						// 50 us
{
	SDA_DIR = 1;
	SCK_DIR = 1;

	NOP();
	I2C_SCK = 1;							//clk=H
	I2C_SDA = 1;							//data=H
	NOP();
	NOP();
	I2C_SDA = 0;
	NOP();
	NOP();
	I2C_SCK = 0;
	NOP();
}

/********************************************************************************/
/* When SCK is high,a low to high of SDA generate a stop signal.				*/
/*    	 	_________
/*	scl ___/
/*			  _______
/*	sda _____/
/********************************************************************************/

void  I2C_Stop(void)						// 40 us
{
	I2C_SDA = 0;
	NOP();
	NOP();
	I2C_SCK = 1;
	NOP();
	NOP();
	I2C_SDA = 1;
}

/********************************************************************************/
/* Send 0 means ack															*/
/* Send 1 means no ack														*/
/********************************************************************************/
void I2C_Ack( unsigned char i )
{
	SDA_DIR = 1;
	NOP();
	if ( i == 0 )
		I2C_SDA = 0;
	else
		I2C_SDA = 1;
	NOP();
	I2C_SCK = 1;
	NOP();
	NOP();
	I2C_SCK=0;
}
char IIC_Wait_Ack(void)
{
	char  ucErrTime=0;
	SDA_DIR = 0;      //SDA设置为输入  
	I2C_SDA=1;
	NOP();
	NOP();	//释放总线
	I2C_SCK=1;
	NOP();
	NOP();	
//	SDA_IN();      //SDA设置为输入 	
/*	while(I2C_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2C_Stop();
			return 1;
		}
	}
	*/
	NOP();
	NOP();		
	I2C_SCK=0;//时钟输出0 	   
	return 0;  
} 
/********************************************************************************/
/* Send 8 bits																	*/
/********************************************************************************/
void I2C_Send_Byte( unsigned char d)		// 280 us
{
	unsigned char i;
	SDA_DIR = 1;
	NOP();									// send a low bit
	for ( i = 0x80; i != 0; i >>= 1 )
	{
		if ( d & i )
			I2C_SDA = 1;
		else
			I2C_SDA = 0;
		NOP();
		I2C_SCK = 1;
		NOP();
		NOP();
		I2C_SCK = 0;
		NOP();	
		NOP();
	}
	I2C_SDA = 0;
	NOP();	
	NOP();									// send a low bit
	I2C_SCK = 1;
	NOP();
	NOP();
	I2C_SCK = 0;
	NOP();
}

/********************************************************************************/
/* receive 8 bits																*/
/********************************************************************************/
unsigned char I2C_Receive_Byte(void)
{
	unsigned char i = 8;
	unsigned char d = 0;
	SDA_DIR = 0;							// input
	I2C_SDA = 1;							// 准双向I/O	
	while ( i-- )
	{
		d = d << 1;
		I2C_SCK = 1;
		NOP();
		NOP();
		if ( I2C_SDA )
			d ++;
		NOP();
		NOP();
		I2C_SCK = 0;
		NOP();
	}
	return d;
}

/********************************************************************************/
/*send data from mcu_address to I2C at begin address of I2C_address.			*/
/********************************************************************************/
void I2C_W( unsigned char device,\
			unsigned char *source,\
			unsigned char address,\
			unsigned char count)
/*
unsigned char device;					//器件地址 0xa0
unsigned char *source;					//数据源地址
unsigned char address;					//目标地址
unsigned char count;					//一次操作字节数
*/
{
	unsigned char pointer;
	I2C_Start();
	I2C_Send_Byte( device );	//send command.
	I2C_Send_Byte(0x02);      //固定高位地址
	I2C_Send_Byte( address );						//send data
	for( pointer = 0; pointer < count; pointer ++ )	//send count bytes
	{
		I2C_Send_Byte( *(source+pointer) );
	}
	I2C_Stop();
}

/********************************************************************************/
/* Read count byte from I2C.address	to I2C.(address+count-1)					*/
/* store it at source[0] to source[count-1]										*/
/********************************************************************************/
void I2C_R( unsigned char writecmd,\
			unsigned char readcmd,\
			unsigned char *source,\
			unsigned char address,\
			unsigned char count)
/*
unsigned char writecmd;					//器件写命令字 0xa0
unsigned char readcmd;					//器件读命令字 0xa1
unsigned char *source;					//数据源地址
unsigned char address;					//目标地址
unsigned char count;					//一次操作字节数
*/    
{
	unsigned char pointer;
	I2C_Start();
	I2C_Send_Byte( writecmd );
	I2C_Send_Byte(0x02);          //固定高位地址
	I2C_Send_Byte( address );
  	I2C_Start();
  	I2C_Send_Byte( readcmd );
	for( pointer = 0; pointer < count; pointer ++ )	//send count bytes
	{
		*(source+pointer) = I2C_Receive_Byte();
		if ( pointer != ( count-1 ) )
		{
			I2C_Ack(0);
		}
	}
	I2C_Ack(1);
	I2C_Stop();
}

void Starting_Measurement(void)
{
	I2C_Start();
	I2C_Send_Byte(0x88);
//    IIC_Wait_Ack();
	I2C_Send_Byte(0x2c);
//	IIC_Wait_Ack();
	I2C_Send_Byte(0x06);
//	IIC_Wait_Ack();
	I2C_Stop();
    delay_ms(100);
}

void Read_Measurement( 	unsigned char *source,\
			unsigned char count)	
{
    unsigned char pointer;
	I2C_Start();
	I2C_Send_Byte(0x89);
//    IIC_Wait_Ack();	
	for(pointer = 0; pointer <count; pointer++)
	{
		*(source+pointer) = I2C_Receive_Byte();
		if ( pointer != ( count-1 ) )
		{
			I2C_Ack(0);
		}
	}
	I2C_Ack(1);
	I2C_Stop();	
}


/********************************************************************************/
/* end of file																	*/
/********************************************************************************/