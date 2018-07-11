#ifndef _SEG_H_
#define _SEG_H_


void HD_595_Write(uint8_t dat);
void HD_Init(void);
extern xdata uint8_t SEGBuf[];
void HD_Set(uint8_t i,uint8_t dat,uint8_t Bit);
void HD_Number(uint16_t dat);
void HD_Float(float dat);
void HD_Lesson(uint8_t v);
void HD_Clear(uint8_t f);
#endif

