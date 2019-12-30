#include <pic18f4520.h>
#include <xc.h>
#define _XTAL_FREQ 4000000
#define FIRST_LINE 0x80
#define SECOND_LINE 0xc0

void Data(int Value);           
void Cmd(int Value);            
void Send2Lcd(const char Adr, const char *Lcd);
void LCD_init(void);
void LCD_clear(void);

