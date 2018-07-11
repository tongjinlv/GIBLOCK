#include "include.h"
code IR_NumberCode[]={103,207,231,133,239,199,165,189,181,173};
xdata int RecordData[15];
int MValue=0;
extern uint8_t Mode;
void App_Add()
{
    MValue++;
}
void App_Sub()
{
    MValue--;
}
void App_Init()
{
    MValue=RecordData[Mode];
    switch(Mode)
    {
        case 0:HD_Init();ADC_Init();UART0_InitTimer3();break;
        case 1:ADC_Init();UART0_UInit();break;
        case 2:ADC_Init();break;
        case 3:HD_Init();PWM_Set(0);ADC_Init();break;
        case 4:HD_Init();ADC_GPIO();break;
        case 5:HD_Init();PWM_Set(0);ADC_GPIO();break;
        case 6:ADC_UPWM();Ultrasonic_Exit();break;
        case 7:HD_Init();UART0_UInit();ADC_UPWM();Ultrasonic_Init();break;
        case 8:HD_Init();UART0_UInit();ADC_UPWM();Ultrasonic_Init();break;
        case 9:ADC_UPWM();Ultrasonic_Exit();BitLed_Init();break;
    }
}
int App_GetInt(int V,int Max,int Min)
{
    char z=0;
    char e=1;
    char i;
   if(R_Data!=29)return V;
    Delayms(100);
    R_Data=0;
    while(1)
    {
        Delayms(100);
        if(e)if(z==0)HD_Clear(0);
        if(z>=2)HD_Float(V);
        if(z++>5)z=0;
        if(R_Data==29)break;
         for(i=0;i<10;i++)
            {
                if(R_Data==IR_NumberCode[i]){if((V*10+i)<Max){V=V*10;V+=i;}else e=0; R_Data=0;HD_Float(V);}
            }
        if(R_Data==157){V++;R_Data=0;}
        if(R_Data==87){if(V>Min)V--;R_Data=0;}
        if(R_Data==79){V=0;R_Data=0;e=1;}
        if(R_Data==111)RecordData[Mode]=V;
    }
    Delayms(200);
   R_Data=0;
    return V;
}
void NumMode()
{
    char i;
    for(i=0;i<10;i++)
    {
    if(R_Data==IR_NumberCode[i]){Mode=i;R_Data=0;HD_Lesson(Mode);JQ_PLay(2);App_Init();Delayms(200);JQ_PLay(0); break;}
    }
    
    
}
void App_Run(uint16_t t)
{
  // Mode=4;
    static bit a;
    switch(Mode)
    {
          case 0:ADC_Start();if(t%2000==0)HD_Float(ADC_Value);NumMode(); PWM_Set((2048-(int)ADC_Value)>>4);break;//ADC直接控制PWM
          case 1:ADC_Start();if(t%2000==0)HD_Float(ADC_Value);if(t%ADC_Value==0)a=!a; if(a)PWM_Set(255);else PWM_Set(-255); break;//ADC直接控制PWM
          case 2:MValue=App_GetInt(MValue,4069,0);ADC_Start();if(t%2000==0)HD_Float(ADC_Value);if(ADC_Value>MValue)PWM_Set(255);else PWM_Set(-255);break;//ADC通过设置阈值控制PWM
          case 3:MValue=App_GetInt(MValue,4069,0);ADC_Start();if(t%2000==0)HD_Float(ADC_Value);if(t%20000==0){if(ADC_Value>MValue)JQ_PLay(4);}break;//ADC通过设置阈值控制PWM
          case 4:if(t%2000==0){HD_Float((char)ADCP);if(ADCP)PWM_Set(255);else PWM_Set(-255);}break;
          case 5:if(t%2000==0){HD_Float((char)ADCP);if(t%20000==0)if(!ADCP)JQ_PLay(4);}break;
          case 6:HD_Float(MValue);MValue=App_GetInt(MValue,1000,0);if(t%500==0)ADC_Beep(MValue);break;
          case 7:MValue=App_GetInt(MValue,4069,0);HD_Float(ADC_Value);ADC_Value=Ultrasonic_Get();if(ADC_Value>MValue)PWM_Set(255);else PWM_Set(-255);break;
          case 8:MValue=App_GetInt(MValue,4069,0);HD_Float(ADC_Value);ADC_Value=Ultrasonic_Get();if(t%5==0){if(ADC_Value>MValue)JQ_PLay(4);}break;
          case 9:BitLed();break;
//         case 1:HD_Float(MValue);MValue=App_GetInt(MValue,255,0);ADC_PWM(MValue);break;
//        case 2:HD_Float(MValue);MValue=App_GetInt(MValue,255,0);PWM_Set(MValue);break;
//        case 3:ADC_Start();if(t%2000==0)HD_Float(ADC_Value); PWM_Set((2048-(int)ADC_Value)>>4);break;
//        case 4:HD_Float(MValue);MValue=App_GetInt(MValue,4069,0);break;
//        case 5:MValue=App_GetInt(MValue,4069,0);ADC_Start();if(t%2000==0)HD_Float(ADC_Value);if(ADC_Value>MValue)PWM_Set(255);else PWM_Set(-255);break;
//        case 6:HD_Float((char)ADCP);if(ADCP)PWM_Set(255);else PWM_Set(-255);break;
//        case 7:HD_Float(ADC_Value);ADC_Value=Ultrasonic_Get();break;
//        case 8:HD_Float(MValue);MValue=App_GetInt(MValue,1000,0);if(t%500==0)ADC_Beep(MValue);break;
//        case 10:HD_Float(R_Data);break;
//        case 11:HD_Float(R_Data);break;
//        case 12:HD_Float(R_Data);break;
//        case 13:HD_Float(R_Data);break;
//        case 14:HD_Float(R_Data);break;
//        case 15:HD_Float(R_Data);break;
    }
}