/******************************************************************************
O Firmware comprova a gravação e leitura na EEPROM interna da placa SanUSB com MPLABX C18
Durante o teste, lê a posicao 0 da EEPROM interna e escreve o valor binário lido nas portas B e D
Ao resetar, os leds mostram, em binário, o último valor armazenado na eeprom interna antes do último reset. Vídeo: http://www.youtube.com/watch?v=SJIQAB4XUv8
Projeto completo disponível em: https://dl.dropboxusercontent.com/u/101922388/ProjSanUSB1_MPLABX/Projeto1C18.X.zip
Instruções para baixar o MPLABX C18: https://dl.dropboxusercontent.com/u/101922388/BaixarMPLABX_C18.pdf
 *****************************************************************************/
#include "SanUSB48.h"	    

unsigned char i=0; //i<=255

#pragma interrupt interrupcao
void interrupcao() {}

void main (void)
{
 clock_int_48MHz();
 TRISB = 0;//Portas B e D como saída
 TRISD = 0;

  /* Apaga os LEDs */
  PORTB = 0;
  PORTB = 0;
  i=le_eeprom(0); //resgata valor anterior antes do reset
/* Incrementa os LEDs com o valor de i armazenado na EEPROM interna*/
  while (1)
	{
	
	PORTB = le_eeprom(0);//Para teste, lê a posicao 0 da EEPROM interna e escreve o valor binário lido nas portas B e D
        PORTD = le_eeprom(0);//No início, após um reset, mostra o último valor armazenado na EEPROM antes do reset.
        tempo_ms(200);      //Vídeo: http://www.youtube.com/watch?v=SJIQAB4XUv8

        ++i; //incrementa i -> i=i+1;
        if (i>255){i=0;}

        escreve_eeprom(0,i); //escreve o valor de i na posicao 0 da EEPROM interna
        tempo_ms(200);
	}
    
}


