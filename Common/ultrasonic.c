#include "include.h"
sbit Trig=P0^6;
sbit Echo=P0^7;
xdata uint8_t Level_Trig;  //测量成功标志
void Ultrasonic_Init()
{
    
    P07_Input_Mode;
    set_P0S_7;
    Enable_BIT7_HighLevel_Trig;
    P06_PushPull_Mode;
  //  TMOD = 0XFF;
    TIMER0_MODE1_ENABLE;
}
void Ultrasonic_Exit()
{
   P06_Quasi_Mode;
   P07_Quasi_Mode;
}
void PinInterrupt_ISR (void) interrupt 7
{
    PIF = 0x00;
    switch(Level_Trig)
    {
        case 0:
        TL0=0;
        TH0=0;
        set_TR0;
        Enable_BIT7_LowLevel_Trig;
        Level_Trig=1;
        break;
        case 1:
        clr_TR0; 
        clr_EPI;
        Level_Trig=2;
        break;
    }
}

void delay_20us()
 {  
     uint8_t bt ;
    for(bt=0;bt<100;bt++);
 }
uint16_t Ultrasonic_Get()
{
    xdata uint16_t R;
    Trig=1;
    delay_20us();
    Trig=0;
    Level_Trig=0;
    Enable_BIT7_HighLevel_Trig;
    set_EPI;
    Delayms(100);
    if(Level_Trig==2)
    {
       R=TH0;
       R<<=8;
       R|=TL1; 
       R/=58;
    }
    return R;
}