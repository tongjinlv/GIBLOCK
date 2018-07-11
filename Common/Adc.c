#include "include.h"


xdata uint16_t ADC_Value;
void ADC_ISR (void) interrupt 11
{
    clr_ADCF;                       
    ADC_Value=ADCRH;
    ADC_Value<<=4;
    ADC_Value|=ADCRL;
}
void ADC_Init()
{
    P05_Input_Mode;
   	Enable_ADC_AIN4;													
    set_EADC;		
    EA = 1;	
}
void ADC_Start()
{
    set_ADCS;
}
uint16_t ADC_Read()
{
    return ADC_Value;
}
void ADC_GPIO()
{
    P05_Quasi_Mode;
    ADCCON0&=0xF0;AINDIDS=0x00;
    clr_EADC;
    ADCP=1;
}
void ADC_PWM(uint16_t v)
{
    P05_PushPull_Mode;
    PWM2_P05_OUTPUT_ENABLE;
    PWM_IMDEPENDENT_MODE;
    PWM_CLOCK_DIV_128;
    PWMPH = 0x00;
    PWMPL = 0xff;
    PWM2L = v&0xff;					
    PWM2H = v>>8;					
    set_LOAD;
    set_PWMRUN;
}
void ADC_Beep(uint16_t v)
{
    P05_PushPull_Mode;
    PWM2_P05_OUTPUT_ENABLE;
    PWM_IMDEPENDENT_MODE;
    PWM_CLOCK_DIV_128;
    PWMPL =v&0xff;
    PWMPH =v>>8;
    v/=2;
    PWM2L = v&0xff;					
    PWM2H = v>>8;					
    set_LOAD;
    set_PWMRUN;
}
void ADC_UPWM()
{
    PWM2_P05_OUTPUT_DISABLE;
    P05_Quasi_Mode;
}