#include "SanUSB48.h" // Firmware para configuração e leitura por hardware de EEPROM i2c
#include"i2c_usb.h"//Biblioteca de funcoes I2C com a placa SanUSB, onde RB0(SDA) e RB1(SCL)
//https://dl.dropboxusercontent.com/u/101922388/ProjSanUSB1_MPLABX/Projeto1C18.X.zip
//https://dl.dropboxusercontent.com/u/101922388/ApostilaSanUSB/Apostila_SanUSB_MPLABX.pdf
//Vídeo: https://www.youtube.com/watch?v=3tGow1iWjCc

unsigned char valor,valorbcd, endereco, numquant=0, temp=0;
unsigned char  comando[6], n=0, m=0;
short int flagA4=0, flagA5=0;
unsigned long int resultado, tensao_lida16;

unsigned int i,j,endereco16=0, posicao=0, valorgravado;
unsigned char byte1,byte2; // 2 Partes do valor da tensao_lida16

unsigned int conv_dec_2bytes(unsigned int valor16)
{//Função auxiliar para alocar um valor de 16 bits (até 65535) em 2 bytes
    byte1= valor16%256; byte2 = valor16/256; //o que for resto (%) é menos significativo
    return(byte2,byte1);
}

#pragma interrupt interrupcao
void interrupcao(){
if (serial_interrompeu)  {
     serial_interrompeu=0;
     comando[n] = le_serial();
     if (comando[n]==79) {flagb=1;}

         ++n; if(n>=5){n=0;}
   }
}

void main(){

    clock_int_48MHz();
    habilita_interrupcao(recep_serial);
    habilita_canal_AD(AN0);
    taxa_serial(9600);
    i2c_ini();

    while(1){

        resultado = le_AD10bits(0);
        tensao_lida16 = (resultado * 5000)/1023; //Valor até 16 bits (2 bytes)
        sendnum(tensao_lida16); swputc(' ');

        //***************************************************************************
        conv_dec_2bytes(tensao_lida16);
        posicao=2*endereco16; //endereço é o ponteiro de 16 bits (byte 1 e byte 2)
        escreve_ieeprom( posicao, byte2); //Byte mais significativo do int16
        escreve_ieeprom( posicao+1, byte1 ); //byte menos significativo do int16
        ++endereco16; if (endereco16>=150){endereco16=0;} //Buffer de 300 bytes posicao<300
        //***************************************************************************/

        if(entrada_pin_e3==0){
       send_hex(le_eeprom(5)); swputc(' ');

         //***************LEITURA DO BUFFER DA EEPROM EXTERNA I2C********************
                for(i=0; i<10; ++i) { //150 Valores de 16 bits ou 300 de 8 bits.
                    for(j=0; j<15; ++j) {
                        valorgravado= 256*le_ieeprom((i*30)+2*j) + le_ieeprom((i*30)+2*j+1);
                        sendnum(valorgravado); swputc(' ');
                                        }
                        sendrw((rom char *)"\n\r");
                                    }
                        sendrw((rom char *)"\n\r");
    //***************************************************************************/
                              }
        ++i; if(i>255) {i=0;}
        escreve_eeprom(5, i); //Escreve na posicao 1000 para depurar a leitura da eeprom
        inverte_saida(pin_b7);
        tempo_ms(1000);
             }
}