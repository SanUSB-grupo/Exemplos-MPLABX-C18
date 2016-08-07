#include "SanUSB1.h"

#pragma interrupt interrupcao
void interrupcao(){//se houver interrupção inserir função aqui
                   }

void main (void)
{
clock_int_4MHz();

while (1)
{
   nivel_alto(pin_b6); 
   tempo_ms(500);
   nivel_baixo(pin_b6);
   tempo_ms(500);
   nivel_alto(pin_b7); 
   tempo_ms(500);
   nivel_baixo(pin_b7);
   tempo_ms(500);
}
}
