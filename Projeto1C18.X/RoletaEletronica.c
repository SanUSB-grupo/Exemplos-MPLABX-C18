#include "SanUSB1.h" //https://www.youtube.com/watch?v=CnMkaWgM_9A

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){
                  }


unsigned int vetLed[12] = {pin_b0, pin_b1, pin_b2, pin_b3, pin_b4, pin_b5, pin_b6, pin_a0, pin_a1, pin_a2, pin_a3, pin_a4};
int i=0;

//led que inicia o jogo
int ledInicial = 0;

//Funcao para alternar o ledInicial
int acenderLed(){
    if (ledInicial >= 11){
   return 0;
    }
    else{
   return ledInicial + 1;
    }
}

void giroInicial(){
    //velocidadeGiro eh o delay entre as intermitencia dos leds
    //eh constantimente incrementada no loop
    int velocidadeGiro = 50;
    nivel_baixo(vetLed[ledInicial]);
    ledInicial = acenderLed();

    while (velocidadeGiro < 800){
        nivel_alto(vetLed[ledInicial]);
        tempo_ms(velocidadeGiro);
        nivel_baixo(vetLed[ledInicial]);
        ledInicial = acenderLed();
        velocidadeGiro+=20;
    }
}

void main(){
clock_int_4MHz();
nivel_baixo(pin_a3);
    while(1)
    {
        nivel_alto(vetLed[ledInicial]);
        tempo_ms(50);
    
        if (PORTEbits.RE3 == 0){ //botão podes ser em outro pino PORTEbits.RE2

                //velocidadeGiro sera o delay ao final do loop do "giroInicial"
                giroInicial();

                while(PORTEbits.RE2 != 0){
                    //Acende o ledFinal. Neste ponto o ledInicial == ledFinal
                    inverte_saida(vetLed[ledInicial]);
                    tempo_ms(200);
                }
                tempo_ms(3000);
        }

        nivel_baixo(vetLed[ledInicial]);
        ledInicial = acenderLed();
        
        inverte_saida(pin_b7);
        //tempo_ms(500);
    }
}
