/* 
 * File:   LCD.h
 * Author: 70136
 *
 * Created on 2019?12?15?, ?? 3:16
 */
#ifndef LCD_H
#define	LCD_H

#define _XTAL_FREQ 250000

void Data(int Value);           
void Cmd(int Value);            
void Send2Lcd(const char Adr, const char *Lcd);
void LCD_init(void);
void LCD_clear(void);

#endif	/* LCD_H */

