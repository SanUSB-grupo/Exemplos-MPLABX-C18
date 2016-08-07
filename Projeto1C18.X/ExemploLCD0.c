#include "SanUSB1.h"
#include "lcd.h"

unsigned int i;
unsigned char buffer1[20];
//unsigned char i;
//char buffer1[20];

#pragma interrupt interrupcao 
void interrupcao(){}

void main(void) {
	clock_int_4MHz();

ADCON1 = 15; 
lcd_ini();
Lcd_Cmd(LCD_CLEAR);
Lcd_Cmd(LCD_CURSOR_OFF); 
tempo_ms(100);

lcd_escreve(1, 2, "Contagem:");
tempo_ms(500);

for(i=110; i>0; i--)
{
sprintf(buffer1,"%3d",i);      //Right aligned text
lcd_escreve2(1, 11, buffer1);
tempo_ms(100);
}

Lcd_Cmd(LCD_CLEAR);

tempo_ms(500);

lcd_escreve(2, 4, "By SanUSB");

while(1){}
}
























