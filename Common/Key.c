#include <stdio.h>
#include "N76E003.h"
#include "Common.h"
#include "Function_Define.h"

sbit Key1=P2^0;
sbit Key2=P1^0;

uint8_t Key_Get()
{
	uint8_t Value=0x00;
	P2S|=SET_BIT7;
	Key1=1;
	if(Key1)Value|=0x01;
	Key1=0;
	Key2=1;
	if(Key2)Value|=0x02;
	Key2=0;
	return Value;
}
uint8_t Key()
{
    uint32_t count=0;
    uint8_t v;
    v=Key_Get();
    if(v!=3)while(Key_Get()!=3&count++<10000);
    if(count>=10000)v|=0x80;
   return v;
}