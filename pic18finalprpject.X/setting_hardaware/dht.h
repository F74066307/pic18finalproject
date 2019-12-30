#include <pic18f4520.h>
#include <xc.h>
#define _XTAL_FREQ 4000000

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();
