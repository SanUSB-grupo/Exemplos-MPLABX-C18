#include "SanUSB48.h"// Video: https://www.youtube.com/watch?v=6-3FN1Lq9qc
//Aplicativo Android em https://play.google.com/store/apps/details?id=appinventor.ai_sandro_juca.BluetimeRelay

int set_segA[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67}; //DISPLAY ANODO COMUM
int set_segC[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; //DISPLAY CATODO COMUM
int set_theend[6]={0x21,0x2B,0x06,0x06,0x0B,0x07};

unsigned char comando[9];
short int flag = 0;
int n=0;
int dia=-1, hora=-1, minuto=-1, segundo=-1;
int i,j,w,x,y,dezhora,undhora,dezmin,undmin,dezseg,undseg;
int time=0;
int a,b,c;

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c

void interrupcao(){
    if (serial_interrompeu){
        serial_interrompeu=0;
        comando[n] = le_serial();
        if (comando[n]== 'D'){
            flag = 1;
        }
        if(n==8){
            if(comando[0] == 'L'){
                if(comando[8]=='y'){
                    dia = comando[1]-0x30;
                    hora = (10*(comando[2]-0x30))+(comando[3]-0x30);
                    minuto = (10*(comando[4]-0x30))+(comando[5]-0x30);
                    segundo = (10*(comando[6]-0x30))+(comando[7]-0x30);
                }
            }
        }
        if(n==8){
            n=0;
        }else{
            ++n;
        }
    }
}

void main(){
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    PORTB = 0x7F;
    clock_int_48MHz();
    habilita_interrupcao(recep_serial);
    taxa_serial(19200);
    //T0CON BITS = TMR0ON , T08BIT(0=16bits OR 1=8bits), T0CS , T0SE , PSA , T0PS2 T0PS1 T0PS0.
    //Defaull 1 in all bits.
    T0CON =0B11000001; //TMR0ON, 8 bits, Prescaler 1:4 (001 - see datasheet)
    TMR0L = 6; //conta 250us antes de estourar x 4 = 1ms
    nivel_baixo(pin_c1);
    nivel_baixo(pin_c2);
    while(1){
        if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação
        inverte_saida(pin_b7);
        tempo_ms(500);
        n=0;
        flag = 0;
        if(dia >=0 && dia <=9 && hora >=0 && hora <=23 && minuto >=0 && minuto <=59 && segundo >=0 && segundo <=59){
            nivel_baixo(pin_b7);
            if(dia!=0 || hora!=0 || minuto!=0 || segundo!=0){
                nivel_alto(pin_c1);
                nivel_alto(pin_c2);
                for(i=dia;i>=0;i--){
                    for(j=hora;j>=0;j--){
                        dezhora=j/10;
                        undhora=j%10;
                        for(w=minuto;w>=0;w--){
                            dezmin=w/10;
                            undmin=w%10;
                            for(x=segundo;x>=0;x--){
                                if(flag != 1){
                                    dezseg=x/10;
                                    undseg=x%10;
                                    for(y=0;y<71;y++){           //71 * 14 = 994 ms
                                        TMR0L = 0;
                                        nivel_alto(pin_c0);
                                        nivel_baixo(pin_a5);
                                        nivel_baixo(pin_a4);
                                        nivel_baixo(pin_a3);
                                        nivel_baixo(pin_a2);
                                        nivel_baixo(pin_a1);
                                        nivel_baixo(pin_a0);
                                        PORTB=set_segC[i];
                                        timer0_ms(2);

                                        nivel_baixo(pin_c0);
                                        nivel_alto(pin_a5);
                                        PORTB=set_segC[dezhora];
                                        timer0_ms(2);

                                        nivel_baixo(pin_a5);
                                        nivel_alto(pin_a4);
                                        PORTB=set_segC[undhora];
                                        timer0_ms(2);

                                        nivel_baixo(pin_a4);
                                        nivel_alto(pin_a3);
                                        PORTB=set_segC[dezmin];
                                        timer0_ms(2);

                                        nivel_baixo(pin_a3);
                                        nivel_alto(pin_a2);
                                        PORTB=set_segC[undmin];
                                        timer0_ms(2);

                                        nivel_baixo(pin_a2);
                                        nivel_alto(pin_a1);
                                        PORTB=set_segC[dezseg];
                                        timer0_ms(2);

                                        nivel_baixo(pin_a1);
                                        nivel_alto(pin_a0);
                                        PORTB=set_segC[undseg];
                                        timer0_ms(2);
                                    }
                                    if (flag == 1){
                                        nivel_baixo(pin_a0);
                                    }
                                }
                            }segundo=59;
                        }minuto=59;
                    }hora=23;
                }
                nivel_baixo(pin_a0);
                nivel_baixo(pin_c1);
                nivel_baixo(pin_c2);
                flag = 0;
            }
            for(a=0;a<2;a++){
                for(b=0;b<3;b++){
                    for(c=0;c<50;c++){
                        nivel_alto(pin_c0);
                        nivel_baixo(pin_a5);
                        nivel_baixo(pin_a4);
                        nivel_baixo(pin_a3);
                        nivel_baixo(pin_a2);
                        nivel_baixo(pin_a1);
                        nivel_baixo(pin_a0);
                        PORTB=set_theend[5];
                        tempo_ms(3);

                        nivel_baixo(pin_c0);
                        nivel_alto(pin_a5);
                        PORTB=set_theend[4];
                        tempo_ms(3);

                        nivel_baixo(pin_a5);
                        nivel_alto(pin_a4);
                        PORTB=set_theend[3];
                        tempo_ms(3);

                        nivel_baixo(pin_a4);
                        nivel_alto(pin_a2);
                        PORTB=set_theend[2];
                        tempo_ms(3);

                        nivel_baixo(pin_a2);
                        nivel_alto(pin_a1);
                        PORTB=set_theend[1];
                        tempo_ms(3);

                        nivel_baixo(pin_a1);
                        nivel_alto(pin_a0);
                        PORTB=set_theend[0];
                        tempo_ms(3);
                    }
                    PORTB=0x7F;
                    tempo_ms(time);
                }
                time=900;
            }
            PORTB = 0x7F;
            dia = -1;
            hora = -1;
            minuto = -1;
            segundo = -1;
        }
    }
}
