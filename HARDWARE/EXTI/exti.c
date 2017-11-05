#include "exti.h"
#include "delay.h" 
#include "ov7670.h"
//#include "ov7670cfg.h"

u8 ov_sta;
 //�ⲿ�ж�5~9�������
void EXTI9_5_IRQHandler(void)
{		 		
	if(EXTI->PR&(1<<8))//��8�ߵ��ж�
	{     
		if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				OV7670_WRST=0;	 	//��λдָ��	
				delay_us(1);
				OV7670_WRST=1;	
				OV7670_WREN=1;		//����д��FIFO
			}else OV7670_WREN=0;	//��ֹд��FIFO 	 
			ov_sta++;
		}
	}
	EXTI->PR=1<<8;     //���LINE8�ϵ��жϱ�־λ						  
} 
//�ⲿ�ж�9��ʼ��
void EXTI9_Init(void)
{												  
	Ex_NVIC_Config(GPIO_A,8,RTIR); 			//������ش���			  
	MY_NVIC_Init(0,0,EXTI9_5_IRQn,2);		//��ռ0,�����ȼ�0����2	   
}











