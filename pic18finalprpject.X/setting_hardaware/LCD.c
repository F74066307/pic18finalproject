/*
 * File:   LCD.c
 * Author: 70136
 *
 * Created on 2019?12?15?, ?? 3:17
 */


#include <xc.h>
#include <pic18f4520.h>
#include "LCD.h"



void Cmd(int Value)
{
 PORTD = Value;               /* Write the command to data lines         */
 RC0   = 0;                   /* RS-0(command register)                  */
 RC1   = 1;                   /* E-1(enable)                             */
 __delay_us(25);                
 RC1   = 0;                   /* E-0(enable)                             */
}
 
void Data(int Value)
{
 PORTD = Value;               /* Write the character to data lines       */
 RC0   = 1;                   /* RS-1(data register)                     */
 RC1   = 1;                   /* E-1(enable)                             */
 __delay_us(25);                
 RC1   = 0;                   /* E-0(enable)                             */
}

void Send2Lcd(const char Adr, const char *Lcd)
{
 Cmd(Adr);                    /* Address of location to display string   */
 while(*Lcd!='\0')            /* Check for termination character         */
 {    
  Data(*Lcd);                 /* Display the character on LCD            */    
  Lcd++;                      /* Increment the pointer                   */
 }
}

void LCD_init(){
    Cmd(0X30);                   /* LCD Specification Commands              */
    Cmd(0X38);                   /* Double Line Display Command             */
    Cmd(0X06);                   /* Auto Increment Location Address Command */
    Cmd(0X0C);                   /* Display ON Command                      */
    Cmd(0X01);                   /* Clear Display Command                   */
    
    Send2Lcd(0x84,"monitor");  /* Displays string in the first line       */
    Send2Lcd(0xc5,"start");     /* Displays string in the second line      */
}