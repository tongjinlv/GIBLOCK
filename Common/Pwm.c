#include "include.h"


sbit PWM1=P1^1;
sbit PWM2=P1^2;

void PWM_Set(int v)
{
    PWM1_P11_OUTPUT_ENABLE;
    PWM0_P12_OUTPUT_ENABLE;
    PWM_IMDEPENDENT_MODE;
    PWM_CLOCK_DIV_128;
    PWMPH = 0x00;
    PWMPL = 0xff;
    PWM0H = 0;					
    PWM1H = 0;					
    if(v>=0){PWM0L =v;PWM1L =0;}
    if(v<=0){PWM0L =0;PWM1L =0-v;}
    set_LOAD;
    set_PWMRUN;
}
