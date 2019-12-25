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
char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
char Checksum;

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
            
            DHT11_Start();
            DHT11_CheckResponse();
            /* read 40-bit data from DHT11 module */
            RH_Integral = DHT11_ReadData();  /* read Relative Humidity's integral value */
            RH_Decimal = DHT11_ReadData();   /* read Relative Humidity's decimal value */
            T_Integral = DHT11_ReadData();   /* read Temperature's integral value */
            T_Decimal = DHT11_ReadData();    /* read Relative Temperature's decimal value */
            Checksum = DHT11_ReadData();     /* read 8-bit checksum value */
            
            sprintf(r,"%d.%1d C  %d.%1d H",T_Integral,T_Decimal,RH_Integral,RH_Decimal);
            LCD_clear();
            Send2Lcd(0x80,r);  //* Displays string in the first line       
            
            MQ_Read(value);
            memset(r,'\0',sizeof(r));
            sprintf(r,"%d %d %d",(int)value[0],(int)value[1],(int)value[2]);
            Send2Lcd(0xc0,r);     // Displays string in the second line
            
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