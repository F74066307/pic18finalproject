#include "dht.h"

/*
 * check and wait dht11 sensor until free
 */
void DHT11_CheckResponse() {
    while (PORTAbits.RA2 & 1); /* wait till bus is High */
    while (!(PORTAbits.RA2 & 1)); /* wait till bus is Low */
    while (PORTAbits.RA2 & 1); /* wait till bus is High */
}

/*
 * init and send start command to dht11 sensor
 */
void DHT11_Start() {
    TRISAbits.RA2 = 0; // set as output port
    LATAbits.LATA2 = 0; // send low pulse of min 18 ms width
    __delay_ms(18);
    LATAbits.LATA2 = 1; // pull data bus high
    __delay_us(20);
    TRISAbits.RA2 = 1; // set as input port    
}

/*
 * read a byte from dht11 sensor
 */
char DHT11_ReadData() {
    char i, data = 0;
    for (i = 0; i < 8; i++) {
        while (!(PORTAbits.RA2 & 1)); // wait till 0 pulse, this is start of data pulse
        __delay_us(30);
        if (PORTAbits.RA2 & 1) // check whether data is 1 or 0    
            data = ((data << 1) | 1);
        else
            data = (data << 1);
        while (PORTAbits.RA2 & 1);
    }
    return data;
}

