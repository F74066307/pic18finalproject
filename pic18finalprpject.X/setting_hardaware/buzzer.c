/*
 * File:   buzzer.c
 * Author: 70136
 *
 * Created on 2019?12?19?, ?? 8:39
 */


#include <xc.h>
#include <pic18f4520.h>
#include "buzzer.h"

void speak(){
    LATBbits.LATB0=1;
    __delay_ms(40);
    LATBbits.LATB0=0;
}

void buzzer_init(){
    speak();
}
