#include "mcu.h"
#include "main.h"

#define Key_On_off        PDRG_PG1//PDR0_P00
#define Key_Swing         PDR1_P14//PDR1_P17
#define Key_Timer         PDR1_P17//PDR1_P14
#define Key_Natural       PDR0_P00

#define LED1  PDR0_P04
#define LED2  PDR0_P05
#define LED3  PDR0_P06
#define LED4  PDR0_P07
#define WiFi_LED  PDR1_P01

char Buzzer_time;
char key_value_onoff;
char key_value_swing;
char key_value_timer;
char key_display_onoff;
char key_display_swing;
char key_display_timer;
char key_status_onoff1;
char key_status_swing1;
char key_status_timer1;
char key_status_onoff2;
char key_status_swing2;
char key_status_timer2;
char key_status_Natural1;
char key_status_Natural2;
char key_value_Natural;
char key_display_Natural;
char key_off_flag;
char key_timer_onoff;     //0表示定时禁止   1表示定时关机开启
char key_swing_onoff;     //0表示摆风禁止   1表示摆风开启
char key_onoff; 		//���ػ�״ָ̬ʾ,	1:����״̬��0:�ػ�״̬
char swing_onoff;		//ҡͷ״ָ̬ʾ,		1:��ʼҡͷ��0:ֹͣҡͷ
char Natural_Mode;     
unsigned int timer_off;  //定时时间，分钟表示
char timer_off_status;  //0 无定时，1定时半小时，2定时1小时 3定时4小时 4定时8小时
char display_allow;
char display_value;
char button_pressed;

char Fan_speed_temp2;	//�ڽ�����Ȼ��״̬ʱ���洢��ǰת��

extern char count_10ms;
extern char step_motor_clockwise;
extern int step_motor_mun;
extern int step_set_mun;
extern char step_motor_first_run;
extern char step_num;
extern char step_motor_clockwise_bak;
extern int step_motor_mun_bak;
extern char step_num_bak;
extern char time_9S;
extern char Factory_Allow;
extern char net_tx_queue;
extern char Model_Allow;
extern unsigned int  Fan_speed;
extern char display_blink_time;
extern char speed_increase_flag;
extern __WORD speed_num;
void Key_scan(void);
extern void put_c(unsigned char c);
extern void put_s(unsigned char *ptr);
void Key_scan()   
{
	char key_io_flag = 0;
	if(count_10ms>=2)                //scan key per 10ms
	{
		count_10ms=0;
		if(Key_On_off==0)
		{	
			if ( key_status_onoff1<250)
		        key_status_onoff1=key_status_onoff1+1; 
			key_status_onoff2=0;
		}
		if(Key_Swing==0)
		{	
			if ( key_status_swing1<250)
		         key_status_swing1=key_status_swing1+1;
			 key_status_swing2=0;
		}	 
		if(Key_Timer==0)
		{	
			if ( key_status_timer1<250)
		         key_status_timer1=key_status_timer1+1;
			key_status_timer2=0;
		}
		if (Key_Natural==0)
		{
			if ( key_status_Natural1<250)
		         key_status_Natural1=key_status_Natural1+1;
			key_status_Natural2=0;			
		}
  		if(Key_On_off==1)
		{	
			if ( key_status_onoff2<250)
		        key_status_onoff2=key_status_onoff2+1; 
		}
		if(Key_Swing==1)
		{	
			if ( key_status_swing2<250)
		         key_status_swing2=key_status_swing2+1;
		}	 
		if(Key_Timer==1)
		{	
			if ( key_status_timer2<250)
		         key_status_timer2=key_status_timer2+1;
		}
		if (Key_Natural==1)
		{
			if ( key_status_Natural2<250)
		         key_status_Natural2=key_status_Natural2+1;		
		}

		//�ػ�
		if (key_onoff==1)
		{	
			if (key_status_onoff1>=100)
			{	
				key_onoff=0;
				key_off_flag=1;
				Buzzer_time=Buzzer_long;
				PPGS_PEN10=1; 		
				step_motor_first_run=1;
				if (step_motor_clockwise==0)
					step_motor_clockwise=1;
				else
					step_motor_clockwise=0;
			}
		}		
		
		if (key_status_onoff1>=5&&key_status_onoff2>=2)
		{
		 
			if (key_off_flag==0)
			{	   
				if (key_onoff==0)
				{
					key_onoff=1;
					switch (key_value_onoff)
					{
						case 1:
							Fan_speed=L_speed_fan;
							break;
	      		            		case 2:
							Fan_speed=M_speed_fan;
							break;					
						case 3:
							Fan_speed=H_speed_fan;
							break;
						case 4:
							Fan_speed=Th_speed_fan;
							break;					
						default: 
							break;					   
					}
					Fan_speed_temp2 = Fan_speed;
				}
				else
			       {
					if (time_9S>0&&key_display_onoff==1)
					{
						Natural_Mode=0;
						if (key_value_onoff<4) 
							key_value_onoff=key_value_onoff+1;
						else
							key_value_onoff=1;
		
						switch (key_value_onoff)
						{
							case 1:
				                    		Fan_speed=L_speed_fan;
				                     	break;
	      		                		case 2:
				                   		Fan_speed=M_speed_fan;
				                    		break;					
				               	case 3:
				                    		Fan_speed=H_speed_fan;
				                    		break;
				                	case 4:
				                    		Fan_speed=Th_speed_fan;
				                    		break;					
				                	default: 
				                     	break;					   
		            	    		}
						
					}

					Fan_speed_temp2 = Fan_speed;
				}

				//ֻҪ���ػ��������¾��˳���Ȼ��
				Natural_Mode=0;
				Fan_speed = Fan_speed_temp2;//�˳���Ȼ��ʱ���ָ�֮ǰ��ת��
				
				key_display_onoff=1;
				key_display_swing=0;
				key_display_timer=0;
				key_display_Natural=0;
				time_9S=9;
				display_value=key_value_onoff;
				display_allow=1;
                		Buzzer_time=Buzzer_short;
                		PPGS_PEN10=1;
			}				
            		key_status_onoff1=0;
			key_status_onoff2=0;
			key_off_flag=0;			
		}
		
		if (key_status_Natural1&&key_status_Natural2)
		{
			if (key_onoff==1)
			{
                		if (time_9S>0&&key_display_Natural==1)
				{	
					//������Ȼ�磬�洢����ת��
					if((key_value_Natural == 0)&&(Natural_Mode==0))
					{
						Fan_speed_temp2 = Fan_speed;
					}
					
					if(key_value_Natural<4)
					{
						key_value_Natural++;
						Natural_Mode=1;
					}
					else
					{	
                        			key_value_Natural=0;
					    	Natural_Mode=0;
						Fan_speed = Fan_speed_temp2;//�˳���Ȼ��ʱ���ָ�֮ǰ��ת��
                    			}
                		}
				speed_increase_flag=1;
				speed_num=0;				
				key_display_Natural=1;
				key_display_swing=0;
				key_display_timer=0;
				key_display_onoff=0;
				time_9S=9;
				display_value=key_value_Natural;
				display_allow=1;
				Buzzer_time=Buzzer_short;
				PPGS_PEN10=1; 
			}
			key_status_Natural1=0;
			key_status_Natural2=0;			
		}
		if (key_status_swing1>=5&&key_status_swing2>=2)
		{
			if (key_onoff==1)
			{	
				if (time_9S>0&&key_display_swing==1)
				{
					if (key_value_swing<4)
					{
						key_value_swing++;
					}
					else
						key_value_swing=0;							
	                    		switch(key_value_swing)
	                  		{
						case 1:
							step_set_mun=swing_30;
							break;
						case 2:
							step_set_mun=swing_60;
							break;					
						case 3:
					              step_set_mun=swing_90;
					              break;
						case 4:
							step_set_mun=swing_120;
							break;					
						default: 
							break;		
					}						
				}					
				if (step_motor_first_run==1)
				{
					step_motor_mun=step_set_mun>>1;
		            		step_motor_clockwise=1;	
					step_num=0;
					step_motor_first_run=0;
				}
				else
				{
					step_num=step_num_bak;
					step_motor_clockwise=step_motor_clockwise_bak;
					step_motor_mun=step_motor_mun_bak;
				}
					key_display_swing=1;
					key_display_timer=0;
					key_display_onoff=0;
					key_display_Natural=0;
					time_9S=9;
					display_value=key_value_swing;
					display_allow=1;
				    	Buzzer_time=Buzzer_short;
		            		PPGS_PEN10=1; 						
			}
            		key_status_swing1=0;
			key_status_swing2=0;
       	 }
		if (key_status_timer1>=5&&key_status_timer2>=2)
		{
			if (key_onoff==1)
			{
				if (time_9S>0&&key_display_timer==1)   
				{					   
					if(key_value_timer<4)
						key_value_timer++;	
					else
						key_value_timer=0;
			  	}
				switch(key_value_timer)
				{
					case 0:
						break;
		                    case 1:
						timer_off=30;
						break;						
		                    case 2:
						timer_off=60;
						break;
		                    case 3:
						timer_off=240;
						break;						
		                    case 4:
						timer_off=480;
						break;
					default: 
						timer_off=0;
						break;
						
				}
				key_display_timer=1;
				key_display_onoff=0;
				key_display_swing=0;
				key_display_Natural=0;
				time_9S=9;
				display_value=key_value_timer;
				display_allow=1;
				Buzzer_time=Buzzer_short;
 				PPGS_PEN10=1; 						  
			}
            		key_status_timer1=0;
            		key_status_timer2=0;			

		}	

	}
	
	if (key_onoff==1)
	{
		if (time_9S>0)
		{	
			if (display_blink_time<55)
			{	
				if (display_allow==1)
				{				    
			        	switch (display_value)
		            		{
						case 0:
							LED1=OFF;
							LED2=OFF;
							LED3=OFF;
							LED4=OFF;	
							break;			
						case 1:
							LED1=ON;
							LED2=OFF;
							LED3=OFF;
							LED4=OFF;	
							break;
						case 2:
							LED1=ON;
							LED2=ON;
							LED3=OFF;
							LED4=OFF;
							break;					
						case 3:
							LED1=ON;
							LED2=ON;
							LED3=ON;
							LED4=OFF;
							break;
						case 4:
							LED1=ON;
							LED2=ON;
							LED3=ON;
							LED4=ON;
							break;					
						default: 
							break;					   
					}	
				}
			}
			else
			{
				LED1=OFF;
				LED2=OFF;
				LED3=OFF;
				LED4=OFF;				
			}								
		}
		else
		{
		    LED1=OFF;
		    LED2=OFF;
		    LED3=OFF;
		    LED4=OFF;
            display_allow=0; 			
		} 
	}
    else
    {
		LED1=OFF;
		LED2=OFF;
		LED3=OFF;
		LED4=OFF;
        key_display_onoff=0;
        key_display_timer=0;
        key_display_swing=0;
        key_display_Natural=0;		
	}			    	
}


						







