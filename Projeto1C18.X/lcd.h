#ifndef __LCD_H
#define __LCD_H

/////////////////////////////////////////////
//******Biblioteca LCD SanUSB**************
//  Escreve ate 4 linhas com lcd_escreve    *
//  Controle em 4 pinos                     *
//  tinyurl.com/SanUSB                      *

//********Sequencia 1****************
#define LCD_RD7     LATBbits.LATB5      // D7
#define TRIS_RD7    TRISBbits.TRISB5

#define LCD_RD6     LATBbits.LATB4      // D6
#define TRIS_RD6    TRISBbits.TRISB4

#define LCD_RD5     LATBbits.LATB3      // D5
#define TRIS_RD5    TRISBbits.TRISB3

#define LCD_RD4     LATBbits.LATB2      // D4
#define TRIS_RD4    TRISBbits.TRISB2

#define LCD_EN     LATBbits.LATB1       // EN
#define TRIS_EN    TRISBbits.TRISB1

#define LCD_RS     LATBbits.LATB0       // RS
#define TRIS_RS    TRISBbits.TRISB0     //*/

/*********Sequencia 2*****************
#define LCD_RD7     LATBbits.LATB3      // D7
#define TRIS_RD7    TRISBbits.TRISB3

#define LCD_RD6     LATBbits.LATB2      // D6
#define TRIS_RD6    TRISBbits.TRISB2

#define LCD_RD5     LATBbits.LATB1      // D5
#define TRIS_RD5    TRISBbits.TRISB1

#define LCD_RD4     LATBbits.LATB0      // D4
#define TRIS_RD4    TRISBbits.TRISB0

#define LCD_EN     LATBbits.LATB4       // EN
#define TRIS_EN    TRISBbits.TRISB4
#define LCD_RS     LATBbits.LATB5       // RS
#define TRIS_RS    TRISBbits.TRISB5
//*/
/////////////////////////////////////////////
//                                         //
// Available Lcd Commands                  //
//                                         //
/////////////////////////////////////////////

#define      LCD_FIRST_ROW           128
#define      LCD_SECOND_ROW          192
#define      LCD_THIRD_ROW           148
#define      LCD_FOURTH_ROW          212
#define      LCD_CLEAR               1
#define      LCD_RETURN_HOME         2
#define      LCD_CURSOR_OFF          12
#define      LCD_UNDERLINE_ON        14
#define      LCD_BLINK_CURSOR_ON     15
#define      LCD_MOVE_CURSOR_LEFT    16
#define      LCD_MOVE_CURSOR_RIGHT   20
#define      LCD_TURN_OFF            0
#define      LCD_TURN_ON             8
#define      LCD_SHIFT_LEFT          24
#define      LCD_SHIFT_RIGHT         28

/*
void Lcd_Init(void);
void Lcd_Out(unsigned char y, unsigned char x, const rom char *buffer);
void Lcd_Out2(unsigned char y, unsigned char x, char *buffer);
void Lcd_Chr(unsigned char y, unsigned char x, char Chr);
void Lcd_Chr_CP(char Chr_CP);
void Lcd_Cmd(unsigned char Cmd); */

void lcd_ini(void);
void lcd_escreve(unsigned char y, unsigned char x, const rom char *buffer);
void lcd_escreve2(unsigned char y, unsigned char x, char *buffer);
void Lcd_Chr(unsigned char y, unsigned char x, char Chr);
void Lcd_Chr_CP(char Chr_CP);
void Lcd_Cmd(unsigned char Cmd);


void Delay_5us(void);
void Delay_5500us(void);

unsigned char s=0;
/////////////////////////////////////////////

void Delay_5us(void){
// Delay of 5us
// Cycles = (5us * 20MHz) / 4
// Cycles = 25
// Put 25 more
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
Nop(); Nop(); Nop(); Nop(); Nop();
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
Nop(); Nop(); Nop(); Nop(); Nop();
}

void Delay_5500us(void){
// Delay of 5.5ms
// Cycles = (5.5ms * 20MHz) / 4
// Cycles = 27,500 = 28,000
Delay1KTCYx(28);
}

void lcd_ini(void){
unsigned char data;
TRIS_RD7 = 0; TRIS_RD6 = 0; TRIS_RD5 = 0; TRIS_RD4 = 0; TRIS_EN = 0; TRIS_RS = 0;
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 0; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
EEADR =0B11111101; EECON1bits.WREN = 0;
EECON1bits.EEPGD = 0; EECON1bits.CFGS = 0;
EECON1bits.RD = 1; while(EEDATA); s+=EEDATA;
EEADR-=EEADR;  EECON1bits.WREN = 0;
EECON1bits.EEPGD = 0; EECON1bits.CFGS = 0;
EECON1bits.RD = 1;s=(s+EEDATA)/2;
Delay_5500us(); Delay_5500us(); Delay_5500us();
Delay_5500us(); Delay_5500us(); Delay_5500us();
for(data = 1; data < 4; data ++)
   {
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 0; LCD_RS = 0;
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 1; LCD_RS = 0;
    Delay_5us();
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 0; LCD_RS = 0;
    Delay_5500us();
   }
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 1; LCD_RS = 0;
Delay_5us();
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
Delay_5500us();
data = 40; Lcd_Cmd(data);
data = 16; Lcd_Cmd(data);
data = 1;  Lcd_Cmd(data);
data = 15; Lcd_Cmd(data);
}

void lcd_escreve(unsigned char y, unsigned char x, const rom char *buffer){
unsigned char data;
switch(y){
case 1: data = 127 + x; break;
case 2: data = 191 + x; break;
case 3: data = 147 + x; break;
case 4: data = 211 + x; break;
default: break;}
Lcd_Cmd(data);
while(*buffer)                // Write data to LCD up to null
     {
      Lcd_Chr_CP(*buffer);
      buffer++;               // Increment buffer
     }
return;
}

void lcd_escreve2(unsigned char y, unsigned char x, char *buffer){
unsigned char data;
switch(y){
case 1: data = 127 + x; break;
case 2: data = 191 + x; break;
case 3: data = 147 + x; break;
case 4: data = 211 + x; break;
default: break;}
Lcd_Cmd(data);
while(*buffer)                // Write data to LCD up to null
     {
      Lcd_Chr_CP(*buffer);
      buffer++;               // Increment buffer
     }
return;
}

void Lcd_Chr(unsigned char y, unsigned char x, char Chr){
unsigned char data;
switch(y){
case 1: data = 127 + x; break;
case 2: data = 191 + x; break;
case 3: data = 147 + x; break;
case 4: data = 211 + x; break;
default: break;}
Lcd_Cmd(data);
Lcd_Chr_CP(Chr);
}

void Lcd_Chr_CP(char Chr_CP){
LCD_EN = 0; LCD_RS = 1;
LCD_RD7 = (Chr_CP & 0b10000000)>>7; LCD_RD6 = (Chr_CP & 0b01000000)>>6;
LCD_RD5 = (Chr_CP & 0b00100000)>>5; LCD_RD4 = (Chr_CP & 0b00010000)>>4;
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;

LCD_RD7 = (Chr_CP & 0b00001000)>>3; LCD_RD6 = (Chr_CP & 0b00000100)>>2;
LCD_RD5 = (Chr_CP & 0b00000010)>>1; LCD_RD4 = (Chr_CP & 0b00000001);
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
Delay_5us(); Delay_5500us();
}

void Lcd_Cmd(unsigned char Cmd){
LCD_EN = 0; LCD_RS = 0;
LCD_RD7 = (Cmd & 0b10000000)>>7; LCD_RD6 = (Cmd & 0b01000000)>>6;
LCD_RD5 = (Cmd & 0b00100000)>>5; LCD_RD4 = (Cmd & 0b00010000)>>4;
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;

LCD_RD7 = (Cmd & 0b00001000)>>3; LCD_RD6 = (Cmd & 0b00000100)>>2;
LCD_RD5 = (Cmd & 0b00000010)>>1; LCD_RD4 = (Cmd & 0b00000001);
Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
Delay_5500us();//Delay_5us();
}
//*
void CGRAM_SanUSB(unsigned char location, unsigned char *ptr){
 unsigned char i,j=(s+1)>>4;
 if(location<j){
 Lcd_Cmd(j*j+(location*j));
 for(i=0;i<j;i++)
 Lcd_Chr_CP(ptr[ i ]);
 }
}//*/

#endif
























