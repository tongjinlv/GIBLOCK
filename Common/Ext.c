#include "include.h"

xdata uint8_t R_Data=0;
xdata uint8_t R_Even=0;
void Ext_Init()
{
    P30_Input_Mode;
    Enable_INT_Port0;
    P30 =1;
    IT1= 0;
    set_EX0;
}
uint16_t Ext_GetTime(uint8_t h)
{
    uint16_t i=0;
    while(P30==h&i++<2000);
    return i;
}
void GetCode()
{
    uint8_t dat[4],x,y;
    xdata uint8_t value;
    uint16_t temp;
    temp=Ext_GetTime(0);
    if(temp<1000)return;else R_Data=value;
    temp=Ext_GetTime(1);//700;
    if(temp<600){R_Data=value;R_Even=1;return ;}
    for(x=0;x<4;x++)
    {
        dat[x]=0;
        for(y=0;y<8;y++)
        {
        dat[x]<<=1;
        temp=Ext_GetTime(0);//76
        temp=Ext_GetTime(1);//102
        if(temp>150)dat[x]|=0x01;
        }
    }
    if(dat[0]==~dat[1]&dat[2]==~dat[3])
    value=dat[3];
    R_Data=value;
    R_Even=0;
    if(R_Data==93)SW_Boot();
}

void EXT_INT0(void) interrupt 0
{
    uint16_t count=0;
    EA=0;
    GetCode();
    EA=1;
}
