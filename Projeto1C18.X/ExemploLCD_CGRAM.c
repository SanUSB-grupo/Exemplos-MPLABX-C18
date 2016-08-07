#include "SanUSB48.h"
#include "lcd.h"

unsigned int i=0,z=1;
unsigned char buffer1[20];
//unsigned char sino[]= {0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};

char abre1[] = {0x0E,0x1C,0x18,0x10,0x18,0x1C,0x0E,0x00};
char fecha1[] = {0x00,0x1E,0x1F,0x10,0x1F,0x1E,0x00,0x00};

char abre2[] = {0x0E,0x07,0x03,0x01,0x03,0x07,0x0E,0x00};
char fecha2[] = {0x00,0x0F,0x1F,0x01,0x1F,0x0F,0x00,0x00};

char vazio[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char b1[] = {4,21,14,4,10,10,10};//Desenha boneco 1

#pragma interrupt interrupcao 
void interrupcao(){}

void main(void) {
	clock_int_48MHz();
	habilita_canal_AD(AN0);
	
	lcd_ini();
	//Lcd_Cmd(LCD_CLEAR);
	Lcd_Cmd(LCD_CURSOR_OFF);
	tempo_ms(100);

        CGRAM_SanUSB(1,abre1);//CGRAM_build(monta posicao do caractere especial,vetor do desenho);
        tempo_ms(100);
        CGRAM_SanUSB(2,fecha1);
        tempo_ms(100);
        CGRAM_SanUSB(3,abre2);
        tempo_ms(100);
        CGRAM_SanUSB(4,fecha2);
        tempo_ms(100);
        CGRAM_SanUSB(5,vazio);
        tempo_ms(100);
        CGRAM_SanUSB(6,b1);
        tempo_ms(100);

 while(1){
    lcd_escreve(1,1,"SanUSB pisca o");
    tempo_ms(500);
    lcd_escreve(2,1,"Led pra voce ");
    tempo_ms(500);

    Lcd_Chr(2, 14, 6); //Lcd_Chr(linha, coluna, posicao do caractere especial);
    tempo_ms(500);
    
    for (z = 1; z < 16; z++) {
    Lcd_Chr(1, z, 2);
    tempo_ms(300);
    Lcd_Chr(1, z, 1);
    tempo_ms(300);
    Lcd_Chr(1, z, 5);
    tempo_ms(100);
    inverte_saida(pin_b7);
    inverte_saida(pin_d7);
          }
    //*
    z=16;
    for (z = 16; z > 0; z--) {
    Lcd_Chr(2, z, 4);
    tempo_ms(300);
    Lcd_Chr(2, z, 3);
    tempo_ms(300);
    Lcd_Chr(2, z, 5);
    tempo_ms(100);
    inverte_saida(pin_b7);
    inverte_saida(pin_d7);
                            }//*/
 }

}

























