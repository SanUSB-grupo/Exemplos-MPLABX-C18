
#include "SanUSB1.h"

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){

                  }

#define LEDPin  LATBbits.LATB7   //Define LEDPin as PORT B Pin 6
#define LEDTris TRISBbits.TRISB7 //Define LEDTris as TRISB Pin 6

void main()
{
clock_int_4MHz();
	LEDTris = 0;//Set LED Pin data direction to OUTPUT
	LEDPin = 1;//Set LED Pin
	
	while(1)
	{
if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação
		LEDPin =~LEDPin;//Toggle LED Pin
	
	tempo_ms(500);//Delay 250K cycles (1 second at 1MHz since each instruction takes 4 cycles)
	}

}
