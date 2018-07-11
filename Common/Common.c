#include "include.h"

bit BIT_TMP;

//---------------------------------------------------------------
void UART0_InitTimer3() //use timer3 as Baudrate generator
{
    uint32_t u32Baudrate=115200;
	P06_Quasi_Mode;
	P07_Quasi_Mode;	
	SCON = 0x52;     //UART0 Mode1,REN=1,TI=1
	set_SMOD;        //UART0 Double Rate Enable
	T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
	set_BRCK;        //UART0 baud rate clock source = Timer3
	RH3    = HIBYTE(65536 - (1000000/u32Baudrate)-1);  		/*16 MHz */
	RL3    = LOBYTE(65536 - (1000000/u32Baudrate)-1);			/*16 MHz */
	set_TR3; 
	TI = 1;   
	ES = 1;	
	EA=1;
}
void UART0_UInit()
{
    SCON=0x00;
    clr_SMOD;
    TI = 0; 
    clr_TR3;
}
uint8_t Receive_Data_From_UART0(void)
{
    uint8_t c;
    while (!RI);
    c = SBUF;
    RI = 0;
    return (c);
}

void Send_Data_To_UART0 (uint8_t c)
{
    TI = 0;
    SBUF = c;
    while(TI==0);
}


void debug(const char *fmt,...)
{
	printf(fmt);
}

void SW_Boot(void)
{
    TA = 0xAA;
    TA = 0x55;
    CHPCON |=0x02; 
    TA = 0xAA;
    TA = 0x55;
    set_SWRST;
}
void serial_IT(void) interrupt 4 
{
	static xdata uint8_t dat=0;
	uint8_t a;
	if (RI) 
	{          
        SW_Boot();        
		clr_RI;                             
		a=SBUF;
		if((a==0xa4)|(a==0xae))
		{ 	
          if(dat==0x02)SW_Boot();
		  dat=0;
		}else dat+=a;
	}
	if(TI)
	{
			clr_TI;                    
	}
}