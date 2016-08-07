#include "SanUSB1.h"// Valor do conversor AD em displays de 7 segmentos multiplexados

#pragma interrupt interrupcao //Vídeo: http://www.youtube.com/watch?v=LRv_lBTU5_c
void interrupcao(){}

void display7(int n){
    switch (n){
        case 0:
            PORTBbits.RB6 = 1;
            PORTBbits.RB5 = 0;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 0;
            PORTBbits.RB1 = 0;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 1:
            PORTBbits.RB6 = 1;
            PORTBbits.RB5 = 1;
            PORTBbits.RB4 = 1;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 1;
            PORTBbits.RB1 = 1;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 2:
            PORTBbits.RB6 = 0;
            PORTBbits.RB5 = 1;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 0;
            PORTBbits.RB1 = 0;
            PORTBbits.RB0 = 1;
            PORTAbits.RA5 = 0;
            break;
        case 3:
            PORTBbits.RB6 = 0;
            PORTBbits.RB5 = 1;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 1;
            PORTBbits.RB1 = 0;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 4:
            PORTBbits.RB6 = 0;
            PORTBbits.RB5 = 0;
            PORTBbits.RB4 = 1;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 1;
            PORTBbits.RB1 = 1;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 5:
            PORTBbits.RB6 = 0;
            PORTBbits.RB5 = 0;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 1;
            PORTBbits.RB2 = 1;
            PORTBbits.RB1 = 0;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 6:
            PORTBbits.RB6 = 0;
            PORTBbits.RB5 = 0;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 1;
            PORTBbits.RB2 = 0;
            PORTBbits.RB1 = 0;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 7:
            PORTBbits.RB6 = 1;
            PORTBbits.RB5 = 1;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 1;
            PORTBbits.RB1 = 1;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 8:
            PORTBbits.RB6 = 0;
            PORTBbits.RB5 = 0;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 0;
            PORTBbits.RB1 = 0;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        case 9:
            PORTBbits.RB6 = 0;
            PORTBbits.RB5 = 0;
            PORTBbits.RB4 = 0;
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 1;
            PORTBbits.RB1 = 0;
            PORTBbits.RB0 = 0;
            PORTAbits.RA5 = 0;
            break;
        default:
            PORTBbits.RB6 = 1;
            PORTBbits.RB5 = 1;
            PORTBbits.RB4 = 1;
            PORTBbits.RB3 = 1;
            PORTBbits.RB2 = 1;
            PORTBbits.RB1 = 1;
            PORTBbits.RB0 = 1;
            PORTAbits.RA5 = 1;
            break;
    }

}

unsigned long int dez, un, resultado, Vresult;

void main(){

    clock_int_4MHz();

    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB0 = 0;
    TRISAbits.TRISA5 = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    
    habilita_canal_AD(AN0);

    //C0 controle unidade e C1 controle dezena;
    while(1){
        resultado = le_AD10bits(0);
        Vresult = (resultado * 50)/1023;

        dez = Vresult/10;
        un = Vresult%10;
        PORTCbits.RC1 = 1;
        display7(dez);
        tempo_ms(5);
        PORTCbits.RC1 = 0;
        PORTCbits.RC0 = 1;
        display7(un);
        tempo_ms(5);
        PORTCbits.RC0 = 0;
    }


}
