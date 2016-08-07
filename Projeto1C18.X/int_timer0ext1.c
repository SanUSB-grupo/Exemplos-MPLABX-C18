
#include <SanUSB.h>

#pragma interrupt interrupcao
void interrupcao()
{
  if (timer0_interrompeu)          {          //espera o estouro do timer0
timer0_interrompeu=0;         	   //limpa a flag de interrupção
PORTBbits.RB7 =! PORTBbits.RB7;    //Pisca o LED EM B7		
TMR0H=0X0B ; TMR0L=0xDC  ; }//Carrega 3036 = 0x0BDC (65536-3036 -> conta 62500us x 8 = 0,5seg)
			
  if (ext1_interrompeu)      {         //espera a interrupção externa 1 (em B1)
ext1_interrompeu = 0;                  //limpa a flag de interrupção 
PORTBbits.RB6 =! PORTBbits.RB6; }        //altera o LED em B0
while(PORTBbits.RB1==0){};
tempo_ms(100);							//Delay para mascarar o ruido do botão(Bouncing)
 	
} 

void main()         {
clock_int_4MHz();

TRISB = 0b00111111;          //B6 e B7 como Saída

habilita_interrupcao(timer0);    // habilita a interrupção do TMR0
       
multiplica_timer16bits(0,8);     //setup_timer0 - 16 bits com prescaler 1:8 - multiplica o tempo por 8

habilita_interrupcao(ext1);           // habilita a interrupção externa 1 (pino B1)
INTCON2bits.INTEDG1 = 0;     // a interrupção externa 1 ocorre somente na borda de descida

while (1){ if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação
				tempo_ms(100);}
		}               
