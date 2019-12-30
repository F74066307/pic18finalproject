#include <xc.h>
#include <pic18f4520.h>
#include "adc.h"
#include "interrupt_manager.h"
#include "pin_manager.h"
#include "LCD.h"
#include "buzzer.h"
#include "dht.h"

#define _XTAL_FREQ 4000000

void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
int timer_val;
