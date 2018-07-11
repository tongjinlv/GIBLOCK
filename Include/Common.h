#ifndef _COMMON_H_
#define _COMMON_H_

typedef bit                   BIT;
typedef unsigned long         uint32_t;
typedef unsigned char         uint8_t;
typedef unsigned int          uint16_t;

void  UART0_InitTimer3(void);
void UART0_UInit(void);
void  Send_Data_To_UART0(uint8_t c);
extern bit BIT_TMP;
void SW_Boot(void);

#endif
