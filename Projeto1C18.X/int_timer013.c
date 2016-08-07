#include "SanUSB1.h"

#pragma interrupt interrupcao
void interrupcao()
{
    if (timer3_interrompeu){             //espera o estouro do timer3
        timer3_interrompeu = 0;          //limpa a flag de interrupção
        PORTBbits.RB7 =! PORTBbits.RB7;  //Pisca o LED em B7
        tempo_timer16bits(3,62500);
    } //Carrega 3036 = 0x0BDC (65536-3036 -> conta 62500us x 8 = 0,5seg)

    if (timer1_interrompeu){
        timer1_interrompeu = 0;
        PORTBbits.RB6 =! PORTBbits.RB6;
        tempo_timer16bits(1,62500);
    }

    if (timer0_interrompeu){
        timer0_interrompeu = 0;
        PORTBbits.RB5 =! PORTBbits.RB5;
        tempo_timer16bits(0, 62500);
    }
} 


void main(){
    clock_int_4MHz();

    TRISB = 0b00011111;          //B6, B7 E B5 como Saída

    habilita_interrupcao(timer0);
    habilita_interrupcao(timer1);
    habilita_interrupcao(timer3);

    multiplica_timer16bits(0,32); //B5
    tempo_timer16bits(0,62500); //OK

    multiplica_timer16bits(1,2); //B6
    tempo_timer16bits(1,62500); //OK

    multiplica_timer16bits(3,8); //B7
    tempo_timer16bits(3,62500); //OK

    while (1)
    {
        if(!entrada_pin_e3)
        {
            Reset();
        }//pressionar o botão para gravação
        tempo_ms(100);
    }
}
