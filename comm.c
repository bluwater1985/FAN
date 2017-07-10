#include "mcu.h"
#include "string.h"
#include "stdio.h"
char result_ok;
char result_prop;
char ReaDat;
char Rx_Data_Buffer[34];
char Tx_Data_Buffer[50];
char Rx1_Data1;
char Rx1_Data2[2];
char Rx1_Data3[3];
char Rx1_Data4[4];
char Rx1_Data5[5];
char Rx1_Data6[6];
char Rx1_Data7[7];
char Rx1_Data8[8];
char Rx1_Data9[9];
char Rx1_Data10[10];
char Rx1_Data11[11];
char Rx1_Data12[12];
char Rx1_Data13[13];
char Rx1_Data14[14];

char Rx0_Data9[9];
char Rx0_Data10[10];
char Rx0_Data11[11];
char Rx0_Data14[14];
char Rx0_Data15[15];
char Rx0_Data16[16];
char Rx0_Data17[17];
char Rx0_Data18[18];
char Rx0_Data20[20];
char int_char[5];
char net_tx_queue;
char net_Tx_hum;
char net_Tx_tem;
char Get_Down_Allow;
char Factory_Allow;
char Net_Allow;
char Props_Allow;
char Event_Allow;
char Error_Allow;
char Model_Allow;
char Mcu_version_Allow;
char Rx_Data_Deel;
char Rx_Data_len1;
char Rx_Data_len2;
char Rx_Data_len3;
char Rx_Data_flag;
char Method_No;
char Props_No;
int app_extra;
char move_right;
char move_left;
char device_reboot;
char Rx_data_deel;
char display_blink_time;

unsigned int cal_variable;
/* get_prop  */
const char Rx_Data_Buf26[]={"get_prop "};   //down get_prop        //9   Method NO: 1
const char Rx_Data_prop0[]={"cola"};           //cola              //4   Props  NO: 1

const char Rx_Data_prop1[]={"led_b"};          //led_b             //5   Props  NO: 2
const char Rx_Data_prop2[]={"speed"};          //speed             //5   Props  NO: 3
const char Rx_Data_prop3[]={"angle"};          //angle             //5   Props  NO: 4
const char Rx_Data_prop4[]={"power"};          //power             //5   Props  NO: 5

const char Rx_Data_prop5[]={"buzzer"};         //buzzer            //6   Props  NO: 6
const char Rx_Data_prop6[]={"speed1"};         //speed1            //6   Props  NO: 7
const char Rx_Data_prop7[]={"speed2"};         //speed2            //6   Props  NO: 8
const char Rx_Data_prop8[]={"speed3"};         //speed3            //6   Props  NO: 9
const char Rx_Data_prop9[]={"speed4"};         //speed4            //6   Props  NO: 10

const char Rx_Data_prop10[]={"temp_dec"};       //temp_dec         //8   Props  NO: 11
const char Rx_Data_prop11[]={"humidity"};       //humidity         //8   Props  NO: 12
const char Rx_Data_prop12[]={"use_time"};       //use_time         //8   Props  NO: 13

const char Rx_Data_prop13[]={"app_extra"};      //app_extra        //9   Props  NO: 14
const char Rx_Data_prop14[]={"fan_level"};      //fan_level        //9   Props  NO: 15
 
const char Rx_Data_prop15[]={"child_lock"};     //child_lock      //10  Props  NO: 16
const char Rx_Data_prop16[]={"hw_version"};     //hw_version      //10  Props  NO: 17

const char Rx_Data_prop17[]={"speed_level"};    //speed_level     //11  Props  NO: 18

const char Rx_Data_prop18[]={"angle_enable"};   //angle_enable    //12  Props  NO: 19
const char Rx_Data_prop19[]={"main_channel"};   //main_channel    //12  Props  NO: 20

const char Rx_Data_prop20[]={"poweroff_time"};  //poweroff_time   //13  Props  NO: 21
const char Rx_Data_prop21[]={"natural_level"};  //natural_level   //13  Props  NO: 22
const char Rx_Data_prop22[]={"slave_channel"};  //slave_channel   //13  Props  NO: 23

const char Rx_Data_prop23[]={"button_pressed"}; //button_pressed  //14  Props  NO: 24


/* method    */
const char Rx_Data_Buf27[]={"down"};                      //down                       //4
const char Rx_Data_method0[]={"get_prop "};           //get_prop                       //9   Method NO: 1
const char Rx_Data_method1[]={"set_buzzer "};         //set_buzzer         on/off      //11  Method NO: 2
const char Rx_Data_method2[]={"set_led_b "};          //set_led_b          0/1/2       //10  Method NO: 3
const char Rx_Data_method3[]={"set_speed "};          //set_speed          200--1200   //10  Method NO: 4
const char Rx_Data_method4[]={"set_angle "};          //set_angle          30--120     //10  Method NO: 5
const char Rx_Data_method5[]={"set_angle_enable "};   //set_angle_enable   on/off      //17  Method NO: 6
const char Rx_Data_method6[]={"set_poweroff_time "};  //set_poweroff_time  0--28800    //18  Method NO: 7
const char Rx_Data_method7[]={"set_speed_level "};    //set_speed_level    1--100      //16  Method NO: 8
const char Rx_Data_method8[]={"set_power "};          //set_power          on/off      //10  Method NO: 9 
const char Rx_Data_method9[]={"set_toggle "};         //set_toggle         on/off      //7   Method NO: 10
const char Rx_Data_method10[]={"set_natural_level "}; //set_natural_level  ??          //20  Method NO: 11
const char Rx_Data_method11[]={"set_child_lock "};    //set_child_lock     on/off      //15  Method NO: 12
const char Rx_Data_method12[]={"set_app_extra "};     //set_app_extra      on/off ??   //14  Method NO: 13
const char Rx_Data_method13[]={"*device_reboot "};    //*device_reboot     on/off ??   //15  Method NO: 14
const char Rx_Data_method14[]={"set_cola "};          //set_cola           cola   ??   //9   Method NO: 15
const char Rx_Data_method15[]={"set_move "};          //set_move           left/right  //9   Method NO: 16
const char Rx_Data_method16[]={"set_fan_level "};     //set_fan_level      ??          //14  Method NO: 17
const char Rx_Data_method17[]={"set_button_type "};   //set_button_type    ??          //16  Method NO: 18
const char Rx_Data_method18[]={"down update_fw"};          //mcu_updata         ??          //9  Method NO: 19
const char Rx_Data_Buffer0[]={"on"};
const char Rx_Data_Buffer1[]={"off"};
const char Rx_Data_Buffer2[]={"left"};
const char Rx_Data_Buffer3[]={"right"};

const char Rx_Data_Buffer4[]={"ok"};         //2
const char Rx_Data_Buffer5[]={"error"};      //5

const char Rx_Data_Buffer6[]={"unprov"};     //6 //未配置   
const char Rx_Data_Buffer7[]={"offline"};    //7 //掉线中
const char Rx_Data_Buffer8[]={"local"};      //5 //本地连接
const char Rx_Data_Buffer9[]={"cloud"};      //5 // 云服务
const char Rx_Data_Buffer10[]={"updating"};  //8 //升级中
const char Rx_Data_Buffer11[]={"uap"};       //3 //uap模式等待连接
/*   result "ok"  */
//error "method not found" -5000
//error "invalid arg" -5001
//error "device_busy" -6007
//error "device_poweroff" -6011
//error "device_tumble" -6012

extern char key_onoff;
extern char key_off_flag;
extern char Buzzer_time;
extern char Buzzer_long;
extern char step_motor_first_run;
extern char key_value_timer;
extern char display_value;
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
extern char time_9S;
extern char Buzzer_short;
extern char step_motor_onoff;
extern char step_motor_bit;
extern char step_num;
extern char step_num_bak;
extern char step_motor_clockwise;
extern char step_motor_clockwise_bak;
extern char step_motor_first_run;
extern char Buzzer_onoff_flag;
extern unsigned int  step_motor_mun;
extern unsigned int  step_motor_mun_bak;
extern unsigned int  step_set_mun;
extern unsigned int temp_int;
extern char Lighting_Levels;
extern char tem_data[3];
extern char hum_data[3];
extern unsigned int  Fan_speed;
extern char speed1;
extern char speed2;
extern char speed3;
extern char speed4;
extern char swing_onoff;
extern unsigned int use_time;
extern char button_pressed;
extern unsigned int speed_level;
extern char child_lock;
extern char updata_ready;
extern char step_motor_first_run;
extern __WORD speed_num; 
#define  Buzzer_short   10
#define  Buzzer_long    30
#define NOP()		 __asm(" NOP")

#define ok 1
#define error 20
#define unprov 2
#define offline 3
#define local  4
#define cloud  5
#define updating 6
#define uap      7


#define hw_version  "0001" 
#define main_channel  "80"
#define slave_channel  "20"
//发送采用查询方式
void put_c(unsigned char c) //发送采用查询方式
{
     SMC20_TXE=1;
	 //SMC20_RXE=0;
	//loop_until_bit_is_set(UCSRA,UDRE);
	while (!SSR0_TDRE)
	{
		NOP();
	}
 //   SSR0_TDRE=0;	
    TDR0=c;

}

//发送字符串
void put_s(unsigned char *ptr)
{
    while (*ptr)
    {
        put_c(*ptr++);
    }
    //put_c(0x0D);
    //put_c(0x0A);  //结尾发送回车换行,不需要换行
}

char *int_to_string(int number,char *strnum)
{
    int j=0,i=0,n=0;
    while(number>0)
   {
       *(strnum+j)=number%10+48;
       j++;
       number=number/10;
       n++;
    }
}

int ascii_int(char *strnum)
{
    int j=0;
    while(*strnum>='0'&&*strnum<='9')
   {
       j=10*j;
       j+=*strnum-'0';
       strnum++;
    }
	return j;
}
//接收指定字节数据(带超时控制,Timer0的1ms时基)
//	*ptr		数据缓冲区
//	len			数据长度
//	timeout		超时设定，最长65.536S
//  返回值		已接收字节数目
unsigned char get_data(unsigned char *ptr,unsigned char len,unsigned int timeout)
{
    unsigned count=0;
 	SMC20_TXE=0;
	SMC20_RXE=1;   
	do
    {
        if (SSR0_RDRF)
        {
            *ptr++=RDR0;				//如果接收到数据，读出
            count++;
			SSR0_RDRF=0;
            if (count>=len)
            {
                break;				//够了？退出
            }
        }
        //if(SSR0_PER==1||SSR0_OVE==1||SSR0_FER==1)		//T0溢出 1ms
        //{
            SMC20_RERC=0;
            timeout--;				//倒计时
        //}
    }
    while (timeout);
    return count;
}
void display_Buzzer(void)
{
	time_9S=9;
	display_allow=1;							
	Buzzer_time=Buzzer_short;
    PPGS_PEN10=1; 		
}

void Tx_Wifi_data(void)
{
	            switch (net_tx_queue)
				{
				    case 1:
					    if (Get_Down_Allow==1)
		                {
			                put_s("get_down");
                            put_c(0x0D);			 
                            Get_Down_Allow=0;			 
		                }
					    break;
					case 2:
	                    if (Factory_Allow==1)	
				        {
   				            put_s("factory");
				            put_c(0x0D);								
  				            Factory_Allow=0;	
				        }
						break;
					case 3:					
                        if (Net_Allow==1)
				        {
				            put_s("net");
                            put_c(0x0D);							
                           Net_Allow=0;					
				        }
                        break;
                    case 4:
                        if (Props_Allow==1)
				        {
				            put_s("props temp ");
                            put_s("hum ");				
                            put_c(0x0D);							
                            Props_Allow=0;					
				        }
                        break;
                    case 5:
                        if (Event_Allow==1)
				        {
				            put_s("net");
                            put_c(0x0D);							
                            Event_Allow=0;					
				        }
                        break;
                    case 6:
                        if (Model_Allow==1)
				        {
				            put_s("model zhimi.fan.c2");
                            put_c(0x0D);							
                            Error_Allow=0;					
				        }
                        break;
                    case 7:
                        if (Error_Allow==1)
				        {
				            put_s("net");
                            put_c(0x0D);							
                            Error_Allow=0;					
				        }
                        break;
                    case 8:
                        if (Model_Allow==1)
				        {
				            put_s("model zhimi.fan.c2");
                            put_c(0x0D);							
                            Model_Allow=0;					
				        }
                        break;
                    case 9:
                        if (Mcu_version_Allow==1)
				        {
				            put_s("Mcu_version 0001");
                            put_c(0x0D);							
                            Mcu_version_Allow=0;					
				        }
                        break;													
                    default:
                        break;			                    						
                }	
}				
void Rx_Wifi_data(void)
{
	        char i,j;
			//ReaDat=get_data(&Rx_Data_Buffer,32,5000);
			if (ReaDat==15)
			{
	            strncpy(Rx0_Data14,Rx_Data_Buffer,14);				
				j=strncmp(Rx_Data_method18,Rx0_Data14,14);	
                if(j==0)
				{	
				  	Method_No=19;
                    result_ok=1;
                }					
			}
			if (ReaDat>11)
			{
			  NOP();	
			}
			if (ReaDat<=8)
			{
			    if (ReaDat==3)
					NOP();
				switch(ReaDat)
                {
					case 2:
                        if(Rx_Data_Buffer[0]==0x6b&&Rx_Data_Buffer[1]==0x0d)
						{	
                          	Rx_data_deel=ok;
                            if (updata_ready==1)    //升级程序
                            {
							    
								#pragma asm
	                                JMP 0x12b9       //Bootloader程序的入口地址
	                            #pragma endasm           				
							}								
						}
						break;				    
					case 3:
                        if(Rx_Data_Buffer[0]==0x6f&&Rx_Data_Buffer[1]==0x6b)
						{	
                          	Rx_data_deel=ok;
                            if (updata_ready==1)    //升级程序
                            {
							    
								#pragma asm
	                                JMP 0x12b9       //Bootloader程序的入口地址
	                            #pragma endasm           				
							}								
						}
						break;
					case 4:
                        j=strncmp(Rx_Data_Buffer,Rx_Data_Buffer11,3);
                        if (j==0)
						{
                        	Rx_data_deel=uap;					
				        }
						break;
					case 6:
                        j=strncmp(Rx_Data_Buffer,Rx_Data_Buffer5,5);
                        if (j==0)
						{
                        	Rx_data_deel=error;					
				        }
                        j=strncmp(Rx_Data_Buffer,Rx_Data_Buffer8,5);
                        if (j==0)
						{
                        	Rx_data_deel=local;					
				        }	
                        j=strncmp(Rx_Data_Buffer,Rx_Data_Buffer9,5);
                        if (j==0)
						{
                        	Rx_data_deel=cloud;					
				        }						
						break;						
					case 7:
                        j=strncmp(Rx_Data_Buffer,Rx_Data_Buffer6,6);
                        if (j==0)
						{
                        	Rx_data_deel=unprov;					
				        }
						break;
					case 8:
                        j=strncmp(Rx_Data_Buffer,Rx_Data_Buffer6,7);
                        if (j==0)
						{
                        	Rx_data_deel=offline;					
				        }
						break;
					case 9:
                        j=strncmp(Rx_Data_Buffer,Rx_Data_Buffer6,8);
                        if (j==0)
						{
                        	Rx_data_deel=updating;					
				        }
						break;						
					default:
                        break;						
				}							
			}
			else
			{
				Rx_Data_len1=5;
				Rx_Data_flag=0;
				for (i=0;i<ReaDat;i++)
				{
					Rx_Data_Deel=Rx_Data_Buffer[i];
					if (Rx_Data_Deel==0x22)
					{
						if (Rx_Data_flag==0)
						{
							Rx_Data_len1=i-5;
							switch (Rx_Data_len1)
					    	{
							    case 9:
							        strncpy(Rx0_Data9,Rx_Data_Buffer+5,Rx_Data_len1);
									j=strncmp(Rx_Data_method0,Rx0_Data9,Rx_Data_len1);
									if (j==0)
								       	Method_No=1;		
		                            j=strncmp(Rx_Data_method14,Rx0_Data9,Rx_Data_len1);
									if (j==0)
								       	Method_No=15;										
		                            j=strncmp(Rx_Data_method15,Rx0_Data9,Rx_Data_len1);
									if (j==0)
								       	Method_No=16;
							        break;
							    case 10:
							        strncpy(Rx0_Data10,Rx_Data_Buffer+5,Rx_Data_len1);
									j=strncmp(Rx_Data_method2,Rx0_Data10,Rx_Data_len1);
									if (j==0)
								       	Method_No=3;		
		                            j=strncmp(Rx_Data_method3,Rx0_Data10,Rx_Data_len1);
									if (j==0)
								       	Method_No=4;										
		                            j=strncmp(Rx_Data_method4,Rx0_Data10,Rx_Data_len1);
									if (j==0)
								       	Method_No=5;													
		                            j=strncmp(Rx_Data_method8,Rx0_Data10,Rx_Data_len1);
									if (j==0)
								       	Method_No=9;																	       
								  break;
								   
							    case 11:
							        strncpy(Rx0_Data11,Rx_Data_Buffer+5,Rx_Data_len1);
		                            j=strncmp(Rx_Data_method1,Rx0_Data11,Rx_Data_len1);
									if (j==0)
								       	Method_No=2;
		                            j=strncmp(Rx_Data_method9,Rx0_Data11,Rx_Data_len1);
									if (j==0)
								       	Method_No=10;									
							        break;		
							    case 14:
							        strncpy(Rx0_Data14,Rx_Data_Buffer+5,Rx_Data_len1);
		                            j=strncmp(Rx_Data_method12,Rx0_Data14,Rx_Data_len1);
									if (j==0)
								       	Method_No=13;										
		                            j=strncmp(Rx_Data_method16,Rx0_Data14,Rx_Data_len1);
									if (j==0)
								       	Method_No=17;															
							        break;
							    case 15:
							        strncpy(Rx0_Data15,Rx_Data_Buffer+5,Rx_Data_len1);
		                            j=strncmp(Rx_Data_method13,Rx0_Data15,Rx_Data_len1);
									if (j==0)
								       	Method_No=14;															
							        break;
							    case 16:
							        strncpy(Rx0_Data16,Rx_Data_Buffer+5,Rx_Data_len1);
									j=strncmp(Rx_Data_method7,Rx0_Data16,Rx_Data_len1);
									if (j==0)
								       	Method_No=8;		
		                            j=strncmp(Rx_Data_method17,Rx0_Data16,Rx_Data_len1);
									if (j==0)
								       	Method_No=18;																	
							        break;
							    case 17:
							        strncpy(Rx0_Data17,Rx_Data_Buffer+5,Rx_Data_len1);
		                            j=strncmp(Rx_Data_method5,Rx0_Data17,Rx_Data_len1);
									if (j==0)
								       	Method_No=6;																
							        break;
							    case 18:
							        strncpy(Rx0_Data18,Rx_Data_Buffer+5,Rx_Data_len1);
		                            j=strncmp(Rx_Data_method6,Rx0_Data18,Rx_Data_len1);
									if (j==0)
								       	Method_No=7;																
							        break;
							    case 20:
							        strncpy(Rx0_Data20,Rx_Data_Buffer+5,Rx_Data_len1);
		                            j=strncmp(Rx_Data_method10,Rx0_Data20,Rx_Data_len1);
									if (j==0)
								       	Method_No=11;																				
							        break;
							    default:
                                    break;								 
							}

						}
						if (Method_No>=1)
						    result_ok=1;	
                        if (Rx_Data_flag==1)
						{
							
							Rx_Data_len2=Rx_Data_len1+6;
							Rx_Data_len3=i-Rx_Data_len2;
							switch(Rx_Data_len3)
							{
							    case 1:
                                    Rx1_Data1=Rx_Data_Buffer[Rx_Data_len2];
									if (Method_No==3)  
									{
										Lighting_Levels=Rx1_Data1;										
									}
									if (Method_No==8)
										speed_level=Rx1_Data1-0x30;
                                    if (Method_No==7)                                              //set_poweroff_time									
								        timer_off==Rx1_Data1-0x30;
								case 2:
							        strncpy(Rx1_Data2,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									j=strncmp(Rx_Data_Buffer0,Rx1_Data2,Rx_Data_len3);
									if(j==0)
									{									    
                                        if (Method_No==2)   		                        //buzzer  on							
										{
											Buzzer_onoff_flag=0;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}
                                        if (Method_No==6)                                   //set_angle_enable 		
                                        {
											swing_onoff=1;
				                            display_value=key_value_swing;							   
	                                        display_Buzzer();											
										}										
										if (Method_No==9)                                   //power  on                
					                    {
							                key_onoff=1;	
				                            display_value=key_value_onoff;							   
	                                        display_Buzzer();
					                    }
										if (Method_No==10)                                   //set_toggle  on/off               
					                    {
							                if (key_onoff==1)
                                            {
											    key_onoff=0;	
				                                key_off_flag=1;
				                                Buzzer_time=Buzzer_long;
				                                PPGS_PEN10=1; 		
				                                step_motor_first_run=1;												
											}
                                            else
											{
							                    key_onoff=1;	
				                                display_value=key_value_onoff;							   
	                                            display_Buzzer();												
											}												
					                    }
                                        if (Method_No==12)   		                        //child_lock  on							
										{
											child_lock=1;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}
                                        if (Method_No==13)   		                       //set_app_extra						
										{
											app_extra=1;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}										                
                                        if (Method_No==14)   		                        //*device_reboot					
										{
											device_reboot=1;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}																														 
									}
									if (Method_No==5)                                    //set_angle 
									{
                                        step_set_mun=ascii_int(Rx1_Data2);
										step_set_mun=step_set_mun*13;
									}
                                    if (Method_No==7)                                              //set_poweroff_time									
								        timer_off=ascii_int(Rx1_Data2);									
									if (Method_No==8)
									{
                                        speed_level=ascii_int(Rx1_Data2);
									}											 								
							        break;
							    case 3:
							        strncpy(Rx1_Data3,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									j=strncmp(Rx_Data_Buffer1,Rx1_Data3,Rx_Data_len3);
									if (j==0)
									{
                                        if (Method_No==2)   		                        //buzzer  off							
										{
											Buzzer_onoff_flag=1;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}
                                        if (Method_No==6)                                   //set_angle_enable 		
                                        {
											swing_onoff=0;
				                            display_value=key_value_swing;							   
	                                        display_Buzzer();											
										}										
										if (Method_No==9)                                   //power  off                
					                    {
											key_onoff=0;	
				                            key_off_flag=1;
				                            Buzzer_time=Buzzer_long;
				                            PPGS_PEN10=1; 		
				                            step_motor_first_run=1;					
					                    }
										if (Method_No==10)                                   //set_toggle  on/off               
					                    {
							                if (key_onoff==1)
                                            {
											    key_onoff=0;	
				                                key_off_flag=1;
				                                Buzzer_time=Buzzer_long;
				                                PPGS_PEN10=1; 		
				                                step_motor_first_run=1;												
											}
                                            else
											{
							                    key_onoff=1;	
				                                display_value=key_value_onoff;							   
	                                            display_Buzzer();												
											}												
					                    }
                                        if (Method_No==12)   		                        //child_lock  on							
										{
											child_lock=0;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}
                                        if (Method_No==13)   		                       //set_app_extra						
										{
											app_extra=0;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}										                
                                        if (Method_No==14)   		                        //*device_reboot					
										{
											device_reboot=0;
											Buzzer_time=Buzzer_short;
                                            PPGS_PEN10=1; 		
										}												
									}
									if (Method_No==4)                                     //set_speed
									{
                                        Fan_speed=ascii_int(Rx1_Data3);
										Fan_speed=Fan_speed*16;
										Fan_speed=Fan_speed/100;
										Fan_speed=10000/Fan_speed;
									}
									if (Method_No==5)                                    //set_angle 
									{
                                        step_set_mun=ascii_int(Rx1_Data3);
										step_set_mun=step_set_mun*13;
									}						
                                    if (Method_No==7)                                    //set_poweroff_time									
								        timer_off=ascii_int(Rx1_Data3);									
									if (Method_No==8)
									{
                                        speed_level=100;
									}											 											
							        break;							   
     							case 4:
							        strncpy(Rx1_Data4,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop0,Rx1_Data4,Rx_Data_len3);
										if(j==0)
                                            Props_No=1;											
									}
									if (Method_No==4)                                     //set_speed
									{
                                        Fan_speed=ascii_int(Rx1_Data4);
										Fan_speed=Fan_speed*16;
										Fan_speed=Fan_speed/100;
										Fan_speed=10000/Fan_speed;									
									}							
                                    if (Method_No==7)                                    //set_poweroff_time									
								        timer_off=ascii_int(Rx1_Data4);									
									if(Method_No==16)                                    //set_move
									{
									    j=strncmp(Rx_Data_Buffer2,Rx1_Data4,Rx_Data_len3);
										if(j==0)
  										    move_left=1;										
									}		
							        break;
							    case 5:
							        strncpy(Rx1_Data5,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop1,Rx1_Data5,Rx_Data_len3);
										if(j==0)
                                            Props_No=2;	
									    j=strncmp(Rx_Data_prop2,Rx1_Data5,Rx_Data_len3);
										if(j==0)
                                            Props_No=3;				
									    j=strncmp(Rx_Data_prop3,Rx1_Data5,Rx_Data_len3);
										if(j==0)
                                            Props_No=4;				
									    j=strncmp(Rx_Data_prop4,Rx1_Data5,Rx_Data_len3);
										if(j==0)
                                            Props_No=5;														
									}
									if(Method_No==16)                                    //set_move
									{
									    j=strncmp(Rx_Data_Buffer3,Rx1_Data5,Rx_Data_len3);
										if(j==0)
  										    move_right=1;										
									}									
							        break;							   
							    case 6:
							        strncpy(Rx1_Data6,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);									
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop5,Rx1_Data6,Rx_Data_len3);
										if(j==0)
                                            Props_No=6;	
									    j=strncmp(Rx_Data_prop6,Rx1_Data6,Rx_Data_len3);
										if(j==0)
                                            Props_No=7;				
									    j=strncmp(Rx_Data_prop7,Rx1_Data6,Rx_Data_len3);
										if(j==0)
                                            Props_No=8;				
									    j=strncmp(Rx_Data_prop8,Rx1_Data6,Rx_Data_len3);
										if(j==0)
                                            Props_No=9;														
									    j=strncmp(Rx_Data_prop9,Rx1_Data6,Rx_Data_len3);
										if(j==0)
                                            Props_No=10;																
									}																									
							        break;		
							    case 7:
							        strncpy(Rx1_Data7,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
							        break;
							    case 8:
							        strncpy(Rx1_Data8,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop10,Rx1_Data8,Rx_Data_len3);
										if(j==0)
                                            Props_No=11;	
									    j=strncmp(Rx_Data_prop11,Rx1_Data8,Rx_Data_len3);
										if(j==0)
                                            Props_No=12;				
									    j=strncmp(Rx_Data_prop12,Rx1_Data8,Rx_Data_len3);
										if(j==0)
                                            Props_No=13;										
									}													
							        break;
							    case 9:
							        strncpy(Rx1_Data9,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop13,Rx1_Data9,Rx_Data_len3);
										if(j==0)
                                            Props_No=14;	
									    j=strncmp(Rx_Data_prop14,Rx1_Data9,Rx_Data_len3);
										if(j==0)
                                            Props_No=15;								
									}															
							        break;
							    case 10:
							        strncpy(Rx1_Data10,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop15,Rx1_Data10,Rx_Data_len3);
										if(j==0)
                                            Props_No=16;	
									    j=strncmp(Rx_Data_prop16,Rx1_Data10,Rx_Data_len3);
										if(j==0)
                                            Props_No=17;								
									}													
							        break;
							    case 11:
							        strncpy(Rx1_Data11,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop17,Rx1_Data11,Rx_Data_len3);
										if(j==0)
                                            Props_No=18;			
									}												
							        break;
							    case 12:
							        strncpy(Rx1_Data12,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len3);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop18,Rx1_Data12,Rx_Data_len3);
										if(j==0)
                                            Props_No=19;	
									    j=strncmp(Rx_Data_prop19,Rx1_Data12,Rx_Data_len3);
										if(j==0)
                                            Props_No=20;								
									}																	
							        break;
							    case 13:
							        strncpy(Rx1_Data13,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len2);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop20,Rx1_Data13,Rx_Data_len3);
										if(j==0)
                                            Props_No=21;	
									    j=strncmp(Rx_Data_prop21,Rx1_Data13,Rx_Data_len3);
										if(j==0)
                                            Props_No=22;				
									    j=strncmp(Rx_Data_prop22,Rx1_Data13,Rx_Data_len3);
										if(j==0)
                                            Props_No=23;										
									}															
							        break;
							    case 14:
							        strncpy(Rx1_Data14,Rx_Data_Buffer+Rx_Data_len2,Rx_Data_len2);
									if (Method_No==1)
									{
									    j=strncmp(Rx_Data_prop23,Rx1_Data14,Rx_Data_len3);
										if(j==0)
                                            Props_No=24;	
									}															
							        break;										
							    default:
                                    break;								
							}
						}	
					    Rx_Data_flag++;
					}	
				}
			}	
}
void Result_Wifi_data(void)
{
	if (result_ok==1)
	{     
        if (Method_No==1)
		{
		    put_s("result ");
			switch(Props_No)
			{
                case 1:
				    put_c(0x22);
                    put_s("00000000000000000000000000000000");    							
	                put_c(0x22);
	                put_c(0x0d);
                    break;
                case 2:                               //Light Level
                    put_c(Lighting_Levels);
	                put_c(0x0d);
                    break;								
                case 3:                              //speed
                    int_to_string(Fan_speed,int_char);
					put_s(int_char);
	                put_c(0x0d);
                    break;
                case 4:                              //angle
                    int_to_string(step_set_mun,int_char);
					put_s(int_char);
	                put_c(0x0d);
                    break;                                
                case 5:                              //power
                    put_c(0x22);							 
	                if (key_onoff==1)
		                put_s("on");
				    else
					    put_s("off");
                    put_c(0x22);							
                    put_c(0x0d);
                    break;           
                case 6:                              //buzzer
                    put_c(0x22);							 
					if (Buzzer_onoff_flag==1)
					    put_s("on");
					else
					    put_s("off");
                    put_c(0x22);							
                    put_c(0x0d);
                    break;
                case 7:                              //speed1
                    int_to_string(speed1,int_char);
					put_s(int_char);
				    put_c(0x0d);
                    break;                                
                case 8:                              //speed2
                    int_to_string(speed2,int_char);
				    put_s(int_char);
				    put_c(0x0d);
                    break;                                
                case 9:                              //speed3
                    int_to_string(speed3,int_char);
					put_s(int_char);
				    put_c(0x0d);
                    break;                                
                case 10:                              //speed4
                    int_to_string(speed4,int_char);
				    put_s(int_char);
				    put_c(0x0d);
                    break;                                
                case 11:	                         //tem
				    put_c(tem_data[2]);
				    put_c(tem_data[1]);
				    put_c(tem_data[0]);
                    put_c(0x0d);
                    break;
                case 12:                            //hum
				    put_c(hum_data[2]);
				    put_c(hum_data[1]);
				    put_c(hum_data[0]);
                    put_c(0x0d);
                    break; 
                case 13:                              //use time
                    int_to_string(use_time,int_char);
				    put_s(int_char);
	                put_c(0x0d);
                    break; 
                case 14:                              //app_extra
                    int_to_string(app_extra,int_char);
    				put_s(int_char);
	                put_c(0x0d);
                    break; 
                case 15:                              //fan_level
                    int_to_string(key_value_onoff,int_char);
	    			put_s(int_char);
		            put_c(0x0d);
                    break; 
                case 16:                              //child_lock
                    put_c(0x22);							 
			        if (child_lock==1)              
			            put_s("on");
				    else
					    put_s("off");
                    put_c(0x22);							
                    put_c(0x0d);
                    break;
                case 17:                              //hw_version
                    put_c(0x22);							 
                    put_s(hw_version);
                    put_c(0x22);							
                    put_c(0x0d);
                    break;								
                case 18:                              //speed_level
                    int_to_string(speed_level,int_char);
		    		put_s(int_char);
			        put_c(0x0d);
                    break; 
                case 19:                              //angle_enable
                    put_c(0x22);							 
			        if (key_value_swing==0)              
				        put_s("off");
				    else
			     	    put_s("on");
                    put_c(0x22);							
                    put_c(0x0d);
                    break;								
                case 20:                              //main_channel
                    put_s(main_channel);
				    put_c(0x0d);
                    break; 								
                case 21:                              //poweroff_time
                    int_to_string(timer_off,int_char);
	     			put_s(int_char);
		            put_c(0x0d);
                    break; 								
                case 22:                              //natural_level
                    int_to_string(timer_off,int_char);
					put_s(int_char);
		            put_c(0x0d);
                    break;
                case 23:                              //slave_channel
                    put_s(slave_channel);
		            put_c(0x0d);
                    break; 					
                case 24:                              //button_pressed
                    put_c(0x22);							 
		            if (button_pressed==0)              
			            put_s("null");
				    if (button_pressed==1)              
				        put_s("speed");
				    if (button_pressed==2)              
				        put_s("angle");
					if (button_pressed==3)              
					    put_s("timer");								
                    put_c(0x22);							
                    put_c(0x0d);
                    break;			
			    default:
                    break;			     								
			}
		}
		
		if (Method_No>1&&Method_No<=18)
		{
        	put_s("result ");	
            put_c(0x22);
		    put_s("ok");
		    put_c(0x22);
		    put_c(0x0d);						
		}
		if (Method_No==19)
		{
        	put_s("result ");	
            put_c(0x22);
		    put_s("ready");
		    put_c(0x22);
		    put_c(0x0d);
            updata_ready=1;
		}
		result_ok=0;
		Method_No=0;
		Props_No=0;		
	} 
}			   