#include "mcu.h"
#include "math.h"
#include "main.h"

#define LED1  PDR0_P04
#define ON 1
#define OFF 0

__WORD	speed_num;
__WORD	speed_num_temp;
__WORD speed_num_min;
__WORD speed_num_max;
char speed_increase_flag;
char speed_decrease_flag;
char	Fan_stop_flag;

char temp = 0;

extern char time_5MS;

extern unsigned int  Fan_speed;
extern unsigned int  Fan_speed_temp;
extern char timer_60s;
extern char timer_1s;
extern char key_value_Natural;
extern char time_60s_flag;
extern char time_Nature_flag;

unsigned int  Fan_speed_increase_flag;

char	num_1;
char	speed_num_200[180];
char	speed[180];
char i;
const char speed_100[]={45, 55, 65, 67, 69, 70, 71, 72, 73, 74, 
					    75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 
					    85, 86, 87, 88, 89, 90, 91, 97, 98, 99, 
					    101, 102, 103, 105, 106, 107, 109, 110, 111, 113, 
					    114, 115, 117, 118, 119, 121, 122, 123, 125, 126, 
					    127, 129, 130, 131, 132, 134, 135, 136, 138, 139, 
  					    140, 142, 143, 144, 146, 147, 148, 150, 151, 153, 
  					    155, 158, 160, 163, 165, 168, 170, 171, 172, 173, 
  					    174, 175, 176, 177, 178, 179, 180, 181, 182, 183,
  					    184, 185, 186, 187, 188, 189, 195, 200, 210, 220 
  					};
/*
					  {30, 38, 45, 51, 56, 60, 63, 65, 67, 70, 
					    71, 72, 73, 74, 75, 76, 77, 79, 80, 81, 
					    83, 84, 85, 87, 88, 89, 91, 97, 98, 99, 
					    101, 102, 103, 105, 106, 107, 109, 110, 111, 113, 
					    114, 115, 117, 118, 119, 121, 122, 123, 125, 126, 
					    127, 129, 130, 131, 132, 134, 135, 136, 138, 139, 
  					    140, 142, 143, 144, 146, 147, 148, 150, 151, 152, 
  					    153, 155, 156, 157, 158, 160, 161, 162, 164, 165, 
  					    166, 167, 169, 170, 171, 172, 174, 175, 176, 177, 
  					    179, 180, 181, 182, 183, 189, 192, 195, 200, 210 
  						};
	const char speed_100[]={75, 76, 77, 79, 80, 81, 83, 84, 85, 87,
	                        88, 89, 91, 97, 98, 99, 101, 102, 103, 105,
	                        106, 107, 109, 110, 111, 113, 114, 115, 117, 118,
	                        119, 121, 122, 123, 125, 126, 127, 129, 130, 131,
	                        132, 134, 135, 136, 138, 139, 140, 142, 143, 144,
	                        146, 147, 148, 150, 151, 152, 153, 155, 156, 157,
	                        158, 160, 161, 162, 164, 165, 166, 167, 169, 170,
	                        171, 172, 174, 175, 176, 177, 179, 180, 193, 194,
	                        195, 197, 198, 199, 201, 202, 203, 205, 206, 207,
	                        209, 210, 212, 213, 215, 217, 219, 221, 223, 225};
*/
//Natural_level	    1-27  28-54  55-80  81-100
#define  Natural_level1_low   0 
#define  Natural_level1_high  26 
#define  Natural_level2_low   0 
#define  Natural_level2_high  53 
#define  Natural_level3_low   0 
#define  Natural_level3_high  79 
#define  Natural_level4_low   0 
#define  Natural_level4_high  99 					
Natural_run()
{	
    //if (timer_60s==0)
    if(time_60s_flag == 1)
	{
		time_60s_flag =0;
		Fan_speed_temp = Fan_speed;
		
	        switch (key_value_Natural)
		{
			case 1:
				speed_num_min=Natural_level1_low;
				speed_num_max=Natural_level1_high;
				break;			
			case 2:
			       speed_num_min=Natural_level2_low;
				speed_num_max=Natural_level2_high;
				break;	
			case 3:
				speed_num_min=Natural_level3_low;
				speed_num_max=Natural_level3_high;
				break;			
			case 4:
				speed_num_min=Natural_level4_low;
				speed_num_max=Natural_level4_high;
				break;
			default:
				break;		
		}

		if(Fan_stop_flag == 1)
		{
			if (speed_increase_flag==1)
			{	
				if (speed_num_temp<speed_num_max)
					speed_num_temp++;	
				else
				{
					speed_increase_flag=0;
				}
			}
			else if (speed_increase_flag==0)
			{	
				if (speed_num_temp>speed_num_min)
					speed_num_temp--;	
				else
				{
					speed_increase_flag=1;
				}
			}		
				
			speed_num=speed_num_temp*speed_num_temp;
			speed_num=speed_num*speed_num_temp;
			speed_num=speed_num%speed_num_max;
			//speed_num=speed_num_temp;
			//if(speed_num ==0)
			if(speed_num ==0)
			{
				switch (key_value_Natural)
				{
					case 1:
			        		Fan_speed =160;
						break;
					case 2:
						Fan_speed = 120;
						break;
					case 3:
						Fan_speed = 70;
						break;
					case 4:
						Fan_speed = 45;
						break;		
				}

				return;
			}
			else
				Fan_speed=speed_100[100-speed_num];

			if(Fan_speed<speed_100[100-speed_num_max])
				Fan_stop_flag = 0;
			else
				Fan_stop_flag = 1;
			

			if(Fan_speed <130)
			{
				if(num_1 < 1)
					num_1++;
				else
				{
					num_1 = 0;
					Fan_speed=190+time_5MS;
				}
					
			}
			else
				num_1 = 0;
				/*
				Fan_speed=speed_100[speed_num]*64;
			    	Fan_speed=Fan_speed/100;
			    	Fan_speed=10000/Fan_speed;	*/
			speed_num_200[i] = speed_num;
			speed[i]= Fan_speed;
			if(i<180)
				i++;
			else
				i=0;
		}
		else
		{	
			Fan_speed=190+time_5MS;;
			Fan_stop_flag = 1;
			
			speed_num_200[i] = speed_num;
			speed[i]= Fan_speed;
			if(i<180)
				i++;
			else
				i=0;
			
		}
	}
	
 	if(time_Nature_flag==1)
	{
		time_Nature_flag = 0;
		PDS20=Fan_speed_temp; 
		
		
		if(Fan_speed_temp < Fan_speed)
			Fan_speed_increase_flag = 1;
		else if(Fan_speed_temp > Fan_speed)
			Fan_speed_increase_flag = 0;

		if(Fan_speed_increase_flag == 1)
		{		
			if(Fan_speed_temp <= Fan_speed)
				Fan_speed_temp =Fan_speed_temp+3;	
		}
		else if(Fan_speed_increase_flag == 0)
		{		
		
			if(Fan_speed_temp > Fan_speed)
				Fan_speed_temp --;	
	
		}	
	}
}
