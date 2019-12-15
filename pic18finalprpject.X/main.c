#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#define _XTAL_FREQ 4000000
char r[15];
void main(void) 
{
    SYSTEM_Initialize() ;
    while(1) {
        memset(r,'\0',sizeof(r));
        sprintf(r,"%.2f",ADC_Read(0));
        //UART_Write_Text(r);
        __delay_us(200);
        memset(r,'\0',sizeof(r));
        sprintf(r,"%.1f",ADC_Read(1));
        //UART_Write_Text(r);
        __delay_us(200);
    }
    return;
    
}


void __interrupt(high_priority) Hi_ISR(void)
{
    if(PIR1bits.CCP1IF == 1) {
        RC2 ^= 1;
        PIR1bits.CCP1IF = 0;
        TMR3 = 0;
    }

    return ;
}