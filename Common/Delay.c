#include "include.h"


void Delay10us(uint16_t u16CNT)
{
    uint32_t i;
    for(i=0;i<u16CNT;i++);
}
void Delayms(uint16_t u16CNT)
{
    uint32_t i;
    for(i=0;i<u16CNT;i++)Delay10us(100);
}