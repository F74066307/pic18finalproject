#include "setting_hardaware/setting.h"
#include "setting_hardaware/LCD.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include <pic18f4520.h>

//lcd showing buffer
char r[100];

//control detect freq
int count = 0;
int cycle = 4;

//array to store mq2 read
double value[3];

//for dht11 result
char RH_Decimal, RH_Integral, T_Decimal, T_Integral;
char Checksum;

/*
 * program entry point
 */
void main(void) {
    SYSTEM_Initialize();
    while (1);
    return;
}

/*
 * handle high priority interrupt
 */
void __interrupt(high_priority) Hi_ISR(void) {
    //timer1 interrupt
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        if (count < cycle) { //count for cycle*0.25s
            count++;
        } else { //reach cycle*0.25s
            count = 0;

            // read 40-bit data from DHT11
            DHT11_Start();
            DHT11_CheckResponse();
            RH_Integral = DHT11_ReadData(); // read relative humidity int value
            RH_Decimal = DHT11_ReadData(); // read relative humidity digit value
            T_Integral = DHT11_ReadData(); // read temperature int value
            T_Decimal = DHT11_ReadData(); // read relative temperature digit value
            Checksum = DHT11_ReadData(); // read 8-bit checksum value
            // Displays DHT11 result in the first line
            memset(r, '\0', sizeof (r));
            sprintf(r, "%d.%1d C  %d.%1d H", T_Integral, T_Decimal, RH_Integral, RH_Decimal);
            LCD_clear();
            Send2Lcd(FIRST_LINE, r);

            // read lpg,co,smoke in ppm from mq2
            MQ_Read(value);
            memset(r, '\0', sizeof (r));
            sprintf(r, "%d %d %d", (int) value[0], (int) value[1], (int) value[2]);
            // Displays lpg,co,smoke in the second line
            Send2Lcd(SECOND_LINE, r);

            //see whether out of limit and beep buzzer
            //and change cycle if in need
            if (value[0] >= 500 || value[1] >= 500 || value[2] >= 500 || T_Integral >= 40 || RH_Integral >= 80) {
                speak();
                speak();
                cycle = 2; // reduce to 0.5s to detect once
            } else {
                cycle = 4; // restore to 1s to detect once
            }
        }

        //clear flag bit and reset timer1 value
        PIR1bits.TMR1IF = 0;
        TMR1 = timer_val;
    }

    return;
}