#include "include.h"

sbit DIN=P0^6;				   //����DIN���ݶ˿�
sbit CLK=P0^7;				   //����CLK���ݶ˿�
unsigned char code CODE[16]={0xBB,0x81,0xEA,0xE3,0xD1,0x73,0x7B,0xA1,0xFB,0xF3,0xF9,0x5B,0x3A,0xCB,0x7A,0x78,};  //���������0~F�����룬�����Ӳ���ӷ�����		
void delay_nms(unsigned int n)
{
    unsigned int i;
    while(n--)
    for(i=0;i<550;i++);
}
void I2CStart()
{
    DIN=1;
    CLK=1;
	_nop_();
	_nop_();
	DIN=1; 
	_nop_();
	_nop_();
	DIN=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLK=0;
	_nop_();
	_nop_();
}
void I2CStop()
{
	CLK=1;
	_nop_();
	_nop_();
	DIN=0;
	_nop_();
	_nop_();
	DIN=1;
	_nop_();
	_nop_();
	CLK=0;
	DIN=0;

}
void I2CWritebyte(unsigned char oneByte)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    CLK=0;
	if(oneByte&0x01) 
	  DIN=1;
	else 
	  DIN=0;
	_nop_();
	_nop_();
	_nop_();
	CLK=1;
	oneByte=oneByte>>1;
	}
	CLK=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	DIN=0;
	_nop_();
	_nop_();
}
void disp()
{
 unsigned char i;

 I2CStart();
 I2CWritebyte(0x40);	//�����������ã���ͨģʽ����ַ�Զ���һ
 I2CStop();

 I2CStart();
 I2CWritebyte(0xc0);	//��ַ�������ã���ʼ��ַ00H
 for(i=0;i<16;i++)	//����16λ��ʾ����
 {
   I2CWritebyte(0xff);
 }
 I2CStop();

 I2CStart();
 I2CWritebyte(0x8c);	//��ʾ���ƣ���ʾ������������Ϊ11/16
 I2CStop();
}
void BitLed_Init()
{
    P06_OpenDrain_Mode;
    P07_OpenDrain_Mode;
}
void BitLed()
{   
    disp();	
    delay_nms(1000);
}