
#include "SanUSB1.h"

 short int ledXOR, ledpisca;

 #pragma interrupt interrupcao
void interrupcao(){}

void main(void){
clock_int_4MHz();

while(1)
{
ledXOR = PORTBbits.RB1^PORTBbits.RB2;  //OU exclusivo entre os pinos b1 e b2 ->input

saida_pino(pin_b7,ledXOR); 		   //O LedXOR mostra o resultado do OU exclusivo

ledpisca=!ledpisca;  		   // ledpisca é igual ao inverso de ledpisca
saida_pino(pin_b0,ledpisca);		   // b0 recebe o valor de ledpisca
tempo_ms(500);
}
}