#include "interrupt_manager.h"

void INTERRUPT_Initialize(void) {
    RCONbits.IPEN = 1; //enable Interrupt Priority mode
    INTCONbits.GIE = 1; //enable high priority interrupt
    INTCONbits.GIEL = 1; //enable low priority interrupt
}
