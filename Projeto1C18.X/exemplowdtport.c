//Programa que utiliza o wdt, reseta em 16 seg. se a limpaflag_wdt(); não for limpa
#include <SanUSB.h>

void main(){
clock_int_4MHz();
habilita_wdt(); // Se a flag wdt não foor limpa (limpaflag_wdt();) dentro de while(1), reseta em 16 segundos.

nivel_alto(pin_b0);
nivel_alto(pin_b7); 
tempo_ms(3000);

	while (1)
	{
	//limpaflag_wdt();
	nivel_alto(pin_b0); // Pisca Led na função principal
	nivel_baixo(pin_b7);
	tempo_ms(500);
	nivel_baixo(pin_b0);
	nivel_alto(pin_b7); 
	tempo_ms(500);
    }
	}
