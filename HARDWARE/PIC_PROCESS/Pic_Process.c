#include "Pic_Process.h"
#include "lcd.h"
#include "math.h"
#include "stdio.h"
#include "usart.h"  
 
u8 Pic_Buff[120][120];


/*-----	ͼ���ֵ������-----*/
void Image_Binaryzation(void)
{   
    int i,j;
	  int a=0,b=0,c=0;


    for(i=0;i<H;i++)
      {
        for(j=0;j<V;j++)
        {
   					if(Pic_Buff[j][i]<THRESHOLD)
						{
						  Pic_Buff[j][i]=0x00;    //��ɫ
							a++;	b++;c++;
						}
          
          else
            Pic_Buff[j][i]=0xfe;   //��ɫ

         }
       }
//			
//			printf("%d %d\n",a,b);
}

/*-----	ͼ����ֵ�˲�������1*3��-----*/
void Image_Filter(void)
{
  int i,j,last_break;

  for(i=0;i<120;i++)
	{
	 for(j=0;j<120-2;j++)
	  {
	   if(Pic_Buff[j][i]==0x00&&Pic_Buff[j+1][i]==0&&Pic_Buff[j+2][i]==0x00)
		 {			 
		   Pic_Buff[j][i]=0x00;
			 last_break = j+2;
		 }
	   else      
		   Pic_Buff[j][i]=0xfe;
     }
		 Pic_Buff[last_break-1][i] = Pic_Buff[last_break][i] = 0x00;//���������ڵ�
   }
}

/*-----	Ѱ��ˮƽ�������λ��-----*/

u8 get_horizontal(void)
{
		int count[4];        //��¼����
    int i,j,x;
	  u8 tiaobian=0;               //2����
	for( i=0;i<119;i++)
	{
			for( j=0;j<119;j++)
		 {
			 if(Pic_Buff[i][j] != Pic_Buff[i][j+1]  )//�ҵ�����
			 {
				 if(tiaobian >2)
				   break ;
			  count[tiaobian]=j;
        tiaobian++;			 
			 }
	   }
		 if(tiaobian==2)
		 {
		  x=(count[0]+count[1])/2;
		 }
	
	}
	   return x;
}

/*-----	Ѱ�Ҵ�ֱ�������λ��-----*/
u8 get_row(void)
{
		int count[4];        //��¼����
	  int i,j,y;
	 u8 tiaobian=0;               //2����
	for( j=0;j<119;j++)
	{
			for( i=0;i<119;i++)
		 {
			 if(Pic_Buff[i][j] != Pic_Buff[i+1][j]  )//�ҵ�����
			 {
				 if(tiaobian >2)
				   break ;
			  count[tiaobian]=i;
        tiaobian++;			 
			 }
	   }
		 if(tiaobian==2)
		 {
		  y=(count[0]+count[1])/2;
		 }
	 }
	return y;
	
}



