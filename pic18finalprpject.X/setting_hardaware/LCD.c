#include "LCD.h"

/*
 * send a command to lcd
 * 
 * param: int Value - the command
 */
void Cmd(int Value) {
    LATD = Value; //Write the command to data lines
    LATCbits.LC4 = 0; // RS-0(command register)

    //create a positive pluse to send a command
    LATCbits.LC6 = 0; // E-0(enable)
    __delay_us(25);
    LATCbits.LC6 = 1; // E-1(enable)
    __delay_us(25);
    LATCbits.LC6 = 0; // E-0(enable)
    __delay_ms(3);
}

/*
 * send data(byte) to lcd
 * 
 * param: int Value - the data
 */
void Data(int Value) {
    LATD = Value; /* Write the character to data lines       */
    LATCbits.LC4 = 1; /* RS-0(command register)                  */

    //create a positive pluse to send a data
    LATCbits.LC6 = 0; /* E-0(enable)                             */
    __delay_us(25);
    LATCbits.LC6 = 1; /* E-1(enable)                             */
    __delay_us(25);
    LATCbits.LC6 = 0; /* E-0(enable)                             */
    __delay_ms(3);
}

/*
 * send a string to lcd with certain location
 * 
 * param: const char Adr - Address of location to display string
 * param: const char *Lcd - the string to send
 */
void Send2Lcd(const char Adr, const char *Lcd) {
    Cmd(Adr); // Address of location to display string
    while (*Lcd != '\0') // Check for termination character
    {
        Data(*Lcd); // Display the character on LCD
        Lcd++; // Increment the pointer
    }
}

/*
 *clear the lcd window
 */
void LCD_clear() {
    Cmd(0X01); // Clear Display Command
}

/*
 * init lcd and show greeting msg on lcd
 */
void LCD_init() {
    //wait setup time
    __delay_ms(15);

    // LCD Specification Commands 2*16 8-bit mode
    Cmd(0X38);
    __delay_us(125);

    LCD_clear();
    Cmd(0X06); // Auto Increment Location Address Command
    Cmd(0X0C); // Display ON Command
    __delay_us(125);

    Send2Lcd(FIRST_LINE, "monitor"); // Displays string in the first line
    Send2Lcd(SECOND_LINE, "start"); // Displays string in the second line
}