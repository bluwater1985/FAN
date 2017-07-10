/********************************************************************************/
/* Filename:	I2C.h															*/
/* Function:	I2C READ AND WRITE												*/
/* Mcu:			PIC16F73														*/
/* Freq:		4MHZ(Cyrstal),Tcy=1us											*/
/* compilier:	HT-PICC and MPLAB IDE 5.70.20									*/
/* Ver:			test															*/
/* CreatDate:	2003-02-26														*/
/********************************************************************************/

#ifndef __def_i2c
#define	__def_i2c

#define	I2C_SDA		PDR6_P60
#define	I2C_SCK		PDR6_P61
#define	SDA_DIR		DDR6_P60
#define	SCK_DIR		DDR6_P61

#define NOP()		 __asm(" NOP")


void I2C_Start(void);						// 50 us
void  I2C_Stop(void);						// 40 us
void I2C_Ack( unsigned char i );
void I2C_Send_Byte( unsigned char d);		// 280 us
unsigned char I2C_Receive_Byte(void);
void I2C_W(	unsigned char device,\
			unsigned char *source,\
			unsigned char address,\
			unsigned char count);	//һ�β����ֽ���
/*
unsigned char device,\//;			
unsigned char *source,\//;					//����Դ��ַ
unsigned char address,\//;					//Ŀ���ַ
unsigned char count);					//һ�β����ֽ���
*/
void I2C_R(	unsigned char writecmd,\
			unsigned char readcmd,\
			unsigned char *source,\
			unsigned char address,\
			unsigned char count);//һ�β����ֽ���
/*
unsigned char writecmd,\//;					//����д������ 0xa0
unsigned char readcmd,\//;					//������������ 0xa1
unsigned char *source\,//;					//����Դ��ַ
unsigned char address\,//;					//Ŀ���ַ
unsigned char count);					//һ�β����ֽ���
*/
#endif

/********************************************************************************/
/* end of file																	*/
/********************************************************************************/