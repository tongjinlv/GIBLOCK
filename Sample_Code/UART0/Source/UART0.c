#include "include.h"
uint8_t Mode=0;


void Test()
{
    Delayms(200);
    HD_Clear(0xff);
    PWM_Set(100);
    while(1)
    {
        Delayms(1);
        if(R_Data==29)break;
    }
    PWM_Set(0);
}
void PowerOFF()
{
    Delayms(200);
    HD_Clear(0);
    R_Data=0;
    while(1)
    {
        if(R_Data==93)break;
    }
    Delayms(100);
    R_Data=0;
}
void Pause()
{
    Delayms(200);
    R_Data=0;
    while(1)
    {
        if(R_Data==253)break;
    }
    Delayms(100);
    R_Data=0;
}
void Menu()
{
    uint8_t k=0;
    k=Key();
    if(R_Data==61||k==0x01){if(Mode<15)Mode++;else Mode=0;HD_Lesson(Mode);JQ_PLay(2);App_Init();Delayms(200);JQ_PLay(0);R_Data=0;}
    if(R_Data==221||k==0x02){if(Mode>0)Mode--;else Mode=15;HD_Lesson(Mode);JQ_PLay(2);App_Init();Delayms(200);JQ_PLay(0);R_Data=0;}
    //if(R_Data==157||k==0x01){App_Add();R_Data=0;}
    //if(R_Data==87||k==0x02){App_Sub();R_Data=0;}
  //  if(R_Data==29){Test();HD_Lesson(Mode);R_Data=0;}
    //if(R_Data==93){PowerOFF();HD_Lesson(Mode);R_Data=0;}
    if(R_Data==93){HD_Lesson(Mode);Delayms(1000);R_Data=0; SW_Boot();}
    if(R_Data==253)Pause();
}
void main (void)
{
    xdata uint16_t TC;
    UART0_InitTimer3();			
    Set_All_GPIO_Quasi_Mode;
    EA=1;
    HD_Init();
    Ext_Init();
    HD_Number(R_Data);
    PWM_Set(0);
   // App_Init();
    JQ_PLay(4);Delayms(1000);JQ_PLay(0);
    while(1)
    {
     
     Menu();
     App_Run(TC);
       Send_Data_To_UART0(0xaa);
     TC++;
    }
             
}
