#include "SanUSB48.h"

#pragma interrupt interrupcao
void interrupcao(){//se houver interrupção inserir função aqui
                   }
                   
void main (void)
{
clock_int_48MHz();

while (1)
{
//while(PORTBbits.RB3){nivel_alto(pin_b6)};
nivel_alto(pin_b7); nivel_alto(pin_d7);
tempo_ms(300);
nivel_baixo(pin_b7); nivel_alto(pin_d7);
tempo_ms(300);
}
}
