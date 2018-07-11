#include "include.h"

sbit DIN=P0^6;				   //定义DIN数据端口
sbit CLK=P0^7;				   //定义CLK数据端口
unsigned char code CODE[16]={0xBB,0x81,0xEA,0xE3,0xD1,0x73,0x7B,0xA1,0xFB,0xF3,0xF9,0x5B,0x3A,0xCB,0x7A,0x78,};  //共阴数码管0~F字型码，需根据硬件接法定义		
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
 I2CWritebyte(0x40);	//数据命令设置：普通模式，地址自动加一
 I2CStop();

 I2CStart();
 I2CWritebyte(0xc0);	//地址命令设置：初始地址00H
 for(i=0;i<16;i++)	//发送16位显示数据
 {
   I2CWritebyte(0xff);
 }
 I2CStop();

 I2CStart();
 I2CWritebyte(0x8c);	//显示控制：显示开，脉冲宽度设为11/16
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