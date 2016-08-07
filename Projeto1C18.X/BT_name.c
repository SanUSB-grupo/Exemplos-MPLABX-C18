/**********************************************************************************
 Grupo: www.tinyurl.com/SanUSB
 video-aulas: www.youtube.com/SanUSB2

 APKs:  https://play.google.com/store/apps/details?id=appinventor.ai_sandro_juca.BT4SanUSB
 * Nome Versao inicial Android 4.0

 Video-aulas: http://www.youtube.com/watch?v=vtS2rq_sO5M , http://www.youtube.com/watch?v=k2quWQlc-ro ,
 e https://www.youtube.com/watch?v=V65-Vt91rug

 Baixar MPLABX e C18: https://dl.dropbox.com/u/101922388/BaixarMPLABX_C18.pdf
 **********************************************************************************/
#include "SanUSB1.h" //

short int pisca=0, chegou=0, flag=0, s=0;
char comando[30], comand[30], n=0, m=0;

#pragma interrupt interrupcao
void interrupcao()
{
 if (serial_interrompeu) {serial_interrompeu=0;

     comando[n] = le_serial(); m=n; comand[m]=comando[n];
     if (comando[0]==65) {flag=1; pisca=0; chegou=0;}
        ++n;
            switch (comando[0]){
             case  79 : { chegou=1; flag=0; m=0;} //Necessario para gravacao do nome no modem via android com BT4SanUSB.apk
         break;
             case 'L':{ pisca=0; s=1; chegou=0;flag=0; n=0;nivel_alto(pin_b7);}
                        break;
             case 'D': {pisca=0; chegou=0;flag=0; n=0; nivel_baixo(pin_b7);}
                        break;
             case 'P': { pisca=1; chegou=0; flag=0; n=0; }
                        break;

                            }
 }
}

void main(){
    clock_int_4MHz();
    habilita_interrupcao(recep_serial);
    taxa_serial(19200);
    for(k=0;k<=25;k++){comando[k]=32;}
    for(k=0;k<=25;k++){comand[k]=32;}

    while(1){

while (chegou==1){  printf("OK\r\n");
                    inverte_saida(pin_b7);tempo_ms(200); n=0; }
tempo_ms (1000);

if (flag==1 && s==1){
   for(k=0;k<=m;k++){swputc(comand[k]);}
          n=0;m=0;         }

n=0;

while (pisca==1){inverte_saida(pin_b7);tempo_ms(300); n=0;}
tempo_ms (1000);
          }
}
