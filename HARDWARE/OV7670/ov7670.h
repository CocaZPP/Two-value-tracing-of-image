#ifndef _OV7670_H
#define _OV7670_H
#include "sys.h"
#include "sccb.h"


#define OV7670_VSYNC  	PAin(8)			//ͬ���źż��IO
#define OV7670_WRST		PBout(7)		//дָ�븴λ
#define OV7670_WREN		PGout(9)		//д��FIFOʹ��
#define OV7670_RCK		PAout(6)		//������ʱ��
#define OV7670_RRST		PAout(4)  		//��ָ�븴λ
#define OV7670_CS		PGout(15)  		//Ƭѡ�ź�(OE)
															  					 
#define OV7670_DATA   GPIOF->IDR&0x00FF  					//��������˿�
/////////////////////////////////////////									
	    				 
u8   OV7670_Init(void);		  	   		 
void OV7670_Light_Mode(u8 mode);
void OV7670_Color_Saturation(u8 sat);
void OV7670_Brightness(u8 bright);
void OV7670_Contrast(u8 contrast);
void OV7670_Special_Effects(u8 eft);
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height);
u16 Get_Color(void);


#endif





















