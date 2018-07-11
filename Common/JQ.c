#include "include.h"

sbit JQ_IO=P1^4;
sbit JQ_OK=P1^3;

void JQ_PLay(uint16_t z)
{

    P13_PushPull_Mode;
    P14_PushPull_Mode;
    JQ_OK=1;
    Delay10us(1000);
    JQ_OK=0;
	Delay10us(1000);
	while(z--)
	{
	JQ_IO=1;
	Delay10us(1000);
	JQ_IO=0;
	Delay10us(1000);
	}
}