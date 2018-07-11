#include "include.h"

sbit HD_595_CLK=P1^7;
sbit HD_595_LCK=P1^5;
sbit HD_595_DAT=P1^6;
xdata uint8_t SEGBuf[4];
code SEGNUMCode[]={0xee,0x0a,0xe9,0xab,0x0f,0xa7,0xe7,0x8a,0xef,0xaf};

/*
------7--------
2-------------3
------0--------
6-------------1
------5--------
4--------------
*/
void HD_595_Write(uint8_t dat)
{
	uint8_t i;
	HD_595_LCK=0;
	for(i=0;i<8;i++)
	{
		if(dat&0x01)HD_595_DAT=1;else HD_595_DAT=0;
		HD_595_CLK=0;
		dat>>=1;
		HD_595_CLK=1;
	}
	HD_595_LCK=1;
}

void Timer1_ISR (void) interrupt 3             
{           
   
  static uint8_t i;
	P00=1;P01=1;P03=1;P04=1;
	switch(i)
	{
		case 0:HD_595_Write(SEGBuf[i]);P00=0;i=1;break;
		case 1:HD_595_Write(SEGBuf[i]);P01=0;i=2;break;
		case 2:HD_595_Write(SEGBuf[i]);P03=0;i=3;break;
		case 3:HD_595_Write(SEGBuf[i]);P04=0;i=0;break;
		default:break;
	}
    
}
void HD_Init()
{
	TIMER1_MODE2_ENABLE; 
	TH1=0x00;
	TL1=0x00;
	set_ET1; 
	set_TR1;  
}
void HD_Set(uint8_t i,uint8_t dat,uint8_t Bit)
{
	SEGBuf[i]=SEGNUMCode[dat]|Bit;
}
void HD_Number(uint16_t dat)
{
    char i;
    for(i=0;i<4;i++)
    {
        HD_Set(3-i,dat%10,0x00);
        dat/=10;
    }
}
void HD_Float(float dat)//1245
{
    char i,s=0,c=0,va=4,vb=-1;
    uint32_t temp;
    if(dat<0)
    {
        va=3;vb=0;
        dat=0-dat;
        SEGBuf[0]=0x01;
    }
    temp=dat;
    if(temp==0)c=1;else 
    for(c=0;c<10;c++)
    {
        if(!temp)break;
        temp/=10;
    }
    temp=1;
    for(i=0;i<(va-c);i++)temp*=10;//(乘3次10与一次乘1000结果是不一样的)
    dat*=temp;
    temp=dat;
    for(i=3;i>vb;i--)
    {
        if((c+vb)==(i))HD_Set(i,temp%10,0x10);
        else HD_Set(i,temp%10,0x00);
        temp/=10;
    }
}
void HD_Lesson(uint8_t v)
{
    SEGBuf[0]=0x64;
    SEGBuf[1]=0x01;
    SEGBuf[2]=SEGNUMCode[v/10];
    SEGBuf[3]=SEGNUMCode[v%10];
}
void HD_Clear(uint8_t f)
{
    SEGBuf[0]=f;
    SEGBuf[1]=f;
    SEGBuf[2]=f;
    SEGBuf[3]=f;
}