#include "SanUSB1.h"
#include "lcd.h"
#include"i2c_usb.h"//Biblioteca de funcoes I2C com a placa SanUSB, onde RB0(SDA) e RB1(SCL)

unsigned int i;
unsigned char buffer1[20];
unsigned char sino[8]= {0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};

#pragma interrupt interrupcao 
void interrupcao(){}

//******************************************************************************
//VARIAVEIS GLOBAIS ************************************************************
unsigned char buffer[16]; //Define o tipo de matriz para escrever no LCD.

void main(void) {
	clock_int_4MHz();
	habilita_canal_AD(AN0);

    taxa_serial(9600);
    i2c_ini();
	
	lcd_ini();
	//Lcd_Cmd(LCD_CLEAR);
	Lcd_Cmd(LCD_CURSOR_OFF);
	tempo_ms(100);

        CGRAM_SanUSB(1,sino);//CGRAM_build(monta posicao do caractere especial,vetor do desenho);
        tempo_ms(300);
        Lcd_Chr(1, 2, 1); //Lcd_Chr(linha, coluna, posicao do caractere especial);
        
	tempo_ms(500);

        lcd_escreve(1, 3, "Microcontrol");
	tempo_ms(500);
	
	lcd_escreve(2, 1, "Converte");
	tempo_ms(500);
	
    while(1)
    {
		i= le_AD10bits(0);
                inverte_saida(pin_b7);inverte_saida(pin_d7);
		sprintf(buffer,"%d  ",i);
		lcd_escreve2(2, 12, buffer); //com buffer
		tempo_ms(500);

sprintf(buffer, "%02X ", le_ieeprom(hora));
lcd_escreve2(2,1, buffer); //com buffer
sprintf(buffer, "%02X ", le_ieeprom(min));
lcd_escreve2(2,4, buffer); //com buffer
sprintf(buffer, "%02X ", le_ieeprom(seg));
lcd_escreve2(2,7, buffer); //com buffer

               
       	}
}
























