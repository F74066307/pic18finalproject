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
 LATD = Value;               /* Write the command to data lines         */
 LATCbits.LC4=0;                   /* RS-0(command register)                  */
    
 LATCbits.LC6=0;                  /* E-0(enable)                             */
 __delay_us(25);  
 LATCbits.LC6=1;                  /* E-1(enable)                             */
 __delay_us(25);                  
 LATCbits.LC6=0;                  /* E-0(enable)                             */
 __delay_ms(3);
}
 
void Data(int Value)
{
 LATD = Value;               /* Write the character to data lines       */
 LATCbits.LC4=1;                   /* RS-0(command register)                  */
     
 LATCbits.LC6=0;                  /* E-0(enable)                             */
 __delay_us(25); 
 LATCbits.LC6=1;                  /* E-1(enable)                             */
 __delay_us(25);               
 LATCbits.LC6=0;                  /* E-0(enable)                             */
 __delay_ms(3);
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

void LCD_clear(){
    Cmd(0X01);                   /* Clear Display Command                   */
}

void LCD_init(){
    
    __delay_ms(15);              
    Cmd(0X38);                   /* LCD Specification Commands              */
    __delay_us(125);   
    
    Cmd(0X01);                   /* Clear Display Command                   */
    Cmd(0X06);                   /* Auto Increment Location Address Command */
    Cmd(0X0C);                   /* Display ON Command                      */
    __delay_us(125);
    Send2Lcd(0x80,"monitor");  /* Displays string in the first line       */
    Send2Lcd(0xc0,"start");     /* Displays string in the second line      */
}