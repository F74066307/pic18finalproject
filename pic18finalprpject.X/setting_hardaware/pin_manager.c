/*
 * File:   pin_manager.c
 * Author: 70136
 *
 * Created on 2019?12?15?, ?? 3:04
 */


#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(){
    ADCON1 = 0x0D; //AN0,AN1->analog,other->digital
    
    //lcd
    TRISC=0X00;                  /* PORTC(control lines) configured as o/p  */
    TRISD=0X00;                  /* PORTD(data lines) configured as o/p     */
    
    //buzzer
    
    //sensor
    TRISA = 0x03;//RA0,RA1 input
}
