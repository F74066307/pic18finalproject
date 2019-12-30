#include "buzzer.h"

/*
 *beep the buzzer for 40 ms
 */
void speak() {
    LATBbits.LATB0 = 1;
    __delay_ms(40);
    LATBbits.LATB0 = 0;
}

/*
 * init the buzzer
 */
void buzzer_init() {
    speak();
}
