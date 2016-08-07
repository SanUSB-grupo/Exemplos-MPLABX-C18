#include "SanUSB1.h" //Emulação de uma softserial (porta serial) nos pinos B4 e B5 via software
#include <sw_uart.h> //Pino B4 (Tx) e Pino B5 (Rx) //http://www.youtube.com/watch?v=6HBbMR2a2I0

#pragma interrupt interrupcao 
void interrupcao(){

                  }

void DelayTXBitUART (void) // Para cálculo dos tempos
{
Delay10TCYx  (4);// 40,58 - 4MHz - 19200
}

void DelayRXBitUART (void)
{
      Delay10TCYx  (3); // 38,58 - 4MHz - 19200
        Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
}
void DelayRXHalfBitUART (void)
{
        Delay10TCYx  (1); // 17,54 - 4MHz - 19200
        Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
}

void main( void )
{
char data;
char mens [] = {" SanUSB "};
unsigned int m = 0;

OpenUART(); //Configure I/O pins B4 and B5 for use as a UART.
clock_int_4MHz();

  while( 1 )					// loop: fica sempre aqui:
  {
        if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação

//    data = ReadUART();   			// Espera chegar um byte e pára o firmware (getchar());
//    WriteUART( data );                        // ... ecoa ele de volta

while (m<9)				// teste de envio mensagem
	{ WriteUART(mens [m]); m++;
	} m=0;

inverte_saida(pin_b7);
tempo_ms(500);
  }
}


