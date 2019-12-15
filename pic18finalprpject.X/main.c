#include "setting_hardaware/setting.h"
#include "setting_hardaware/LCD.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include <pic18f4520.h>

char r[15];

void main(void) 
{
    SYSTEM_Initialize() ;
    while(1);
    return;
    
}


void __interrupt(high_priority) Hi_ISR(void)
{
    if(PIR1bits.TMR1IF&&PIE1bits.TMR1IE) {
        memset(r,'\0',sizeof(r));
        sprintf(r,"%.2f",ADC_Read(0));
        __delay_us(200);
        
        memset(r,'\0',sizeof(r));
        sprintf(r,"%.1f",ADC_Read(1));
        PIR1bits.TMR1IF=0;
        TMR1=65535-(1000000/4)/4;
    }

    return ;
}