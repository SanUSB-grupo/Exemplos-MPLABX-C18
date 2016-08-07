#include "SanUSB1.h"

// inserir o desvio _asm goto interrupcao _endasm  na função void _high_ISR (void){   } em SanUSB.h
#pragma interrupt interrupcao
void interrupcao()
{
  if (timer1_interrompeu)     {          //espera o estouro do timer0
timer1_interrompeu=0;           	   //limpa a flag de interrupção
PORTBbits.RB7 =! PORTBbits.RB7;    //Pisca o LED em B7		
tempo_timer16bits(1,50000); }	//Conta 8 x 50000us = 0,4 seg.



 if (timer0_interrompeu)     {          //espera o estouro do timer0
timer0_interrompeu = 0;           	   //limpa a flag de interrupção
PORTBbits.RB7 =! PORTBbits.RB7;    //Pisca o LED em B7		
tempo_timer16bits(0,62500); }

			
  if (ext1_interrompeu)      {         //espera a interrupção externa 1 (em B1)
ext1_interrompeu = 0;                  //limpa a flag de interrupção 
PORTBbits.RB7 =! PORTBbits.RB7;  //altera o LED em B0
tempo_ms(100);		}       //Delay para mascarar o ruido do botão(Bouncing)
  } //*/
 
void main()       {
clock_int_4MHz();
TRISB = 0b01111110;          //B0 e B7 como Saída

habilita_interrupcao(timer0);
multiplica_timer16bits(0,16);           //liga timer0 - 16 bits com multiplicador (prescaler) 8 
tempo_timer16bits(0,62500);       //Conta 16 x 62500us = 1 seg.

//habilita_interrupcao(timer1);
multiplica_timer16bits(1,8);           //liga timer3 - 16 bits com multiplicador (prescaler) 8
tempo_timer16bits(1,50000);		//Conta 8 x 50000us = 0,4 seg.

//habilita_interrupcao(ext1);     // habilita a interrupção externa 1 com borda de descida          


while(1){if(!entrada_pin_e3) {Reset(); 
									tempo_ms(100);}}
}
