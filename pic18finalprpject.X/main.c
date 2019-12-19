#include "setting_hardaware/setting.h"
#include "setting_hardaware/LCD.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include <pic18f4520.h>

char r[100];
int count=0;
int cycle=4;
double value[3];

void main(void) 
{
    SYSTEM_Initialize() ;
    while(1);
    return;
    
}


void __interrupt(high_priority) Hi_ISR(void)
{
    if(PIR1bits.TMR1IF&&PIE1bits.TMR1IE) {
        if(count<cycle){
            count++;
        }
        else{
            count=0;
            memset(r,'\0',sizeof(r));
            __delay_us(100);
            sprintf(r,"%s%.2f C",r,ADC_Read(0));
            __delay_us(100);
            MQ_Read(value);
            memset(r,'\0',sizeof(r));
            sprintf(r,"%s lpg=%.1f ppm CO=%.1f ppm smoke=%.1f ppm",r,value[0],value[1],value[2]);
            
            //see whether out of limit and bep buzzer
            /*
             if(...){
             * speak();
             * __delay_ms(40);
             * speak();
             * }
             */
            
            //change cycle if in need
            //........
        }
        PIR1bits.TMR1IF=0;
        TMR1=timer_val;
    }

    return ;
}