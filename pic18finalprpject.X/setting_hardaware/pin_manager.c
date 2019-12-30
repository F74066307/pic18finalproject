#include "pin_manager.h"

void PIN_MANAGER_Initialize() {
    ADCON1 = 0x0D; //AN0,AN1->analog,other->digital

    //lcd
    TRISC = 0X00; // RC(control lines) output
    TRISD = 0X00; // RD(data lines) output

    //buzzer
    TRISBbits.RB0 = 0; //RB0 output

    //sensor
    TRISA = 0b00000101; //RA0,RA2 input
}
