#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "lcd.h"
#include "ov7670.h"
//#include "ov7670cfg.h"
#include "timer.h"	  		 
#include "sccb.h"	
#include "exti.h"
#include "Pic_Process.h"



extern  double fx,fy;
extern u8 ov_sta;	//在exit.c里面定义
extern u8 ov_frame;	//在timer.c里面定义		

/*---图像处理需要的外部变量---*/
extern u8 Pic_Buff[120][120];
extern u8 Search_Cnt; 

u16 l=0,h=0;
u16 row,col;

 //更新LCD显示
void camera_refresh(void)
{
 	u16 color;	
  u16 LCD_color;	
	u16 color_r;
  u16 color_g;
  u16 color_b;
	u8 x,y;
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_R2L);		//从上到下,从右到左
		LCD_Set_Window((lcddev.width-120)/2,(lcddev.height-120)/2,120,120);
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1;  
		h=0;
		for(col=0;col<240;col++)
		{ 	
			if((col%2)==0)h++;
			for(row=0;row<240;row++)
			{ 	
						OV7670_RCK=0;	
						color = Get_Color();	//读数据
						OV7670_RCK=1;
						OV7670_RCK=0;
						OV7670_RCK=1;
						LCD_color = color;	
					if(((col%2)==0)&&((row%2)==0)) 
					{							    
						Pic_Buff[h-1][l]=(u8)color;
					    l++;
					}		 
	
		    }
		l=0;
		}   
		h=0;
		EXTI->PR=1<<9;     			//清除LINE9上的中断标志位
		ov_sta=0;					//开始下一次采集
		Image_Binaryzation();   /*-----	图像二值化函数-----*/
			for(y=0;y<120;y++)
		{
		  for(x=0;x<120;x++)
			{
				LCD_color = Pic_Buff[y][x];
				LCD_color<<=8;
			    color_r = LCD_color&0xf800;
			    color_b = LCD_color>>11;
			    LCD_color >>=5;
			    color_g =LCD_color&0x07e0; 
		  	    LCD_color=color_r+color_b+color_g;
				LCD->LCD_RAM=LCD_color; 
			}
		}
		LCD_Scan_Dir(D2U_R2L);	//恢复默认扫描方向 
		} 
	
}	
	
int main(void)
{   
	int lox,loy;
	
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化  
	uart1_init(84,115200);		//初始化串口波特率为115200 
	
 	LCD_Init();
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"OV7670 TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2012/9/14");  
	LCD_ShowString(60,130,200,16,16,"KEY0:Light Mode");
	LCD_ShowString(60,150,200,16,16,"KEY1:Saturation");
	LCD_ShowString(60,170,200,16,16,"KEY2:Brightness");
	LCD_ShowString(60,190,200,16,16,"KEY_UP:Contrast");
	LCD_ShowString(60,210,200,16,16,"TPAD:Effects");	 
  LCD_ShowString(60,230,200,16,16,"OV7670 Init...");	  
	while(OV7670_Init())//初始化OV7670
	{
		LCD_ShowString(60,230,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,230,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 
	
	OV7670_Light_Mode(0);
	EXTI9_Init();						//使能定时器捕获
	OV7670_Window_Set(10,174,240,240);	//设置窗口	  
  	OV7670_CS=0;	
	LCD_Clear(BLACK);
	PAout (13)=1;
  while(1) 
	{	
		camera_refresh();         //更新显示

		lox=get_horizontal();
		loy=get_row();
		printf("%d %d\n",lox,loy);
		
	}
}

