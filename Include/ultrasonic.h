#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

extern uint16_t Ult_Data;
void Ultrasonic_Init(void);
uint16_t Ultrasonic_Get(void);
void ADC_PWM(uint16_t v);
void Ultrasonic_Exit(void);
#endif
