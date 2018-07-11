#ifndef _ADC_H_
#define _ADC_H_

sbit ADCP=P0^5;
extern xdata uint16_t ADC_Value;
void ADC_Init(void);
void ADC_Start(void);
uint16_t ADC_Read(void);
void ADC_GPIO(void);
void ADC_Beep(uint16_t v);
void ADC_PWM(uint16_t v);
void ADC_UPWM(void);
#endif
