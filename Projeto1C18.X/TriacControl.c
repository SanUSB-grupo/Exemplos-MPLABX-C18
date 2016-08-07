//O Firmware comprova a gravação e leitura na EEPROM interna da placa SanUSB com MPLABX C18
//http://www.youtube.com/watch?v=u1HwZLRcrYQ e http://www.youtube.com/watch?v=zeqS6A5-I08
#include "SanUSB48.h"	    

#define RB0 PORTBbits.RB0  //entrada default
#define TRIAC PORTBbits.RB7 //saída
#define UP  entrada_pin_e3 //entrada
#define DWN entrada_pin_a2 //entrada

#define MAX_TIME 7000 //Verificar o tempo máximo com teste prático real
#define MIN_TIME 1

int atraso=0;

#pragma interrupt interrupcao
void interrupcao() 
{
    if(ext0_interrompeu) //interrupção externa 0 no pino B0
    { TRIAC = 0; //desliga o triac para o próximo meio-período, que também desliga passando pelo zero anterior
    ext0_interrompeu=0;
    while(RB0); //enquanto o pino de interrupção B0 estiver alto fique parado
    atraso=k;
    while(atraso--);

    TRIAC=1; //Liga triac e conduz a tensão de entrada para saída
    }
}

void main (void){
  clock_int_48MHz();
 
 TRISB=0x01;//somente B0 (externa 0) como entrada
 k=600;//inicia com 600
 habilita_interrupcao(ext0);
 INTCON2bits.INTEDG0 = 1; //interrompe com borda de subida

while(1)
{
if(!UP)
    {
    tempo_ms(5);
    if(!UP)
    {
    ++k; if(k>=MAX_TIME) {k=MAX_TIME;}
    atraso=k;
    }
    }
 else if(!DWN)
    {
    tempo_ms(5);
    if(!DWN)
    {
     --k; if(k<=MIN_TIME) {k=MIN_TIME;}
    atraso=k;
    }
} 
 }
}

