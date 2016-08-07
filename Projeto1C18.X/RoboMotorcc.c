/*
	https://www.youtube.com/watch?v=_lPOhQd2C3I&feature=youtu.be
*/
#include "SanUSB48.h"
#define rodaDireitaFrente pin_b0
#define rodaDireitaTras pin_b1
#define rodaEsquerdaFrente pin_b2
#define rodaEsquerdaTras pin_b3
#define piscaDir pin_b6
#define piscaEsq pin_b7
// c1 = SetaPWM2 , led vermelho
// c2 = setaPWM1, leds azuis e verde

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
char comando = 'P';
int setAlarme =0;
char setPisca= 'X';


// ----------------- motor do carro -------------------
void para(){
    nivel_baixo(rodaDireitaFrente);
    nivel_baixo(rodaEsquerdaFrente);

    nivel_baixo(rodaDireitaTras);
    nivel_baixo(rodaEsquerdaTras);
}

void esquerda(){
    nivel_alto(rodaDireitaFrente);


    /*
        nivel_alto(rodaDireitaFrente);
        tempo_ms(20);
        nivel_alto(rodaEsquerdaFrente);
        tempo_ms(20);
        nivel_baixo(rodaEsquerdaFrente);
     */
}


void direita(){
    nivel_alto(rodaEsquerdaFrente);
    /*
        int i;
        nivel_alto(rodaEsquerdaFrente);
        //tempo_ms(20);
        for(i=0;i<5;i++){
             nivel_alto(rodaDireitaFrente);
             tempo_ms(2000);
             nivel_baixo(rodaDireitaFrente);
             tempo_ms(2000);
        }
        nivel_baixo(rodaEsquerdaFrente);
        */
}

void frente(){
    nivel_alto(rodaDireitaFrente);
    nivel_alto(rodaEsquerdaFrente);

//

}

void tras(){
    nivel_alto(rodaDireitaTras);
    nivel_alto(rodaEsquerdaTras);

}
// ----------------- motor do carro -------------------
// ----------------- buzina e alarme ------------------
void buzina(){
    int i;
    for(i=0;i<2;i++){
        nivel_alto(pin_b4);
        tempo_ms(300);
        nivel_baixo(pin_b4);
        tempo_ms(100);
    }
}
//-----------------buzina e alarme --------------------
// ----------- LEDs para pisca , farol e ré  -------------
paraPisca(unsigned int pinoE, unsigned int pinoD){
    nivel_baixo(pinoD);
    nivel_baixo(pinoE);
}
pisca(unsigned int pino){
    nivel_alto(pino);
    tempo_ms(300);
    nivel_baixo(pino);
    tempo_ms(300);
}
pisca2(unsigned int pinoD, unsigned int pinoE){
    nivel_alto(pinoD);
    nivel_alto(pinoE);
    tempo_ms(300);
    nivel_baixo(pinoD);
    nivel_baixo(pinoE);
    tempo_ms(300);
}
void resetPWD(){
    SetaPWM2(10000, 100);
    SetaPWM1(10000, 100);
}
void setaPWDvermelhoForte(){  // carro parado
    SetaPWM2(10000, 1);
}

void setaPWDvermelhoFraco(){ // carro andando pra frente, lado, outro lado
    SetaPWM2(10000, 90);
}

void setaPWDbranco(){ // carro de ré
    SetaPWM2(10000, 1);
    SetaPWM1(10000,1);

}
// -----------LEDs para pisca , farol e ré  -------------

void interrupcao(){
    if (serial_interrompeu)  {
     serial_interrompeu=0;
     comando = le_serial();
     switch(comando){
         case 'F':
             
             //nivel_alto(pin_b7);
             para();
             paraPisca(piscaDir,piscaEsq);
             setPisca ='X'; // QUALQUER CARACTERE DIFERENTE DE D , E e  A
             frente();

             resetPWD();
             setaPWDvermelhoFraco();
         break;

         case 'D':
             para(); // executa apenas uma vez
             paraPisca(piscaDir,piscaEsq);

             direita();

             setPisca = 'D';

             resetPWD();
             setaPWDvermelhoFraco();
         break;

         case 'E':
             para();
             paraPisca(piscaDir,piscaEsq);
             esquerda();

             setPisca = 'E';

             resetPWD();
             setaPWDvermelhoFraco();
         break;

         case 'P':
             para();
             paraPisca(piscaDir,piscaEsq);
             setPisca ='X';// QUALQUER CARACTERE DIFERENTE DE D , E e  A

             resetPWD();
             setaPWDvermelhoForte();
             
             setAlarme = 0;//FUNÇAO DE ALARME
         break;
         
         case 'T':
             para();
             paraPisca(piscaDir,piscaEsq);
             setPisca ='X';// QUALQUER CARACTERE DIFERENTE DE D , E e  A
             tras();
            

             resetPWD();
             setaPWDbranco();
         break;
         case 'A':
             paraPisca(piscaDir,piscaEsq);
             setAlarme = 1;
             setPisca = 'A';
         break;
         case 'B':
             buzina();
         break;
     }
    }
}

void main(){
    clock_int_48MHz(); //Funcao necessaria para o dual clock
    habilita_interrupcao(recep_serial);
    taxa_serial(19200);
    setaPWDvermelhoForte();

    while(1){
            if (!entrada_pin_e3){
                Reset();
            }
            if(setAlarme){
                    buzina();
                    setaPWDbranco();
                    tempo_ms(150);
                    resetPWD();
                    tempo_ms(150);
            }
             if(setPisca == 'A'){
                pisca2(piscaDir,piscaEsq);
            }
            if(setPisca == 'D'){
                pisca(piscaDir);
            }
            if(setPisca == 'E'){
                pisca(piscaEsq);
            }

    }
}
