#include "SanUSB1.h"
#include "lcd.h"

unsigned int i;
unsigned char buffer1[20];
unsigned char sino[8]= {0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};

#pragma interrupt interrupcao 
void interrupcao(){}

void main(void) {
	clock_int_4MHz();
	habilita_canal_AD(AN0);
	
	lcd_ini();
	//Lcd_Cmd(LCD_CLEAR);
	Lcd_Cmd(LCD_CURSOR_OFF);
	tempo_ms(100);

        CGRAM_SanUSB(1,sino);//CGRAM_build(monta posicao do caractere especial,vetor do desenho);
        tempo_ms(300);
        Lcd_Chr(1, 2, 1); //Lcd_Chr(linha, coluna, posicao do caractere especial);
        
	tempo_ms(500);

        lcd_escreve(1, 3, "Amanda Kildary");
	tempo_ms(500);
	
	lcd_escreve(2, 1, "Converte");
	tempo_ms(500);
	
    while(1)
    {
		i= le_AD10bits(0);
                inverte_saida(pin_b7);inverte_saida(pin_d7);
		sprintf(buffer1,"%d  ",i);
		lcd_escreve2(2, 12, buffer1); //com buffer
		tempo_ms(300);

                //printf("a ");
       	}
}
























