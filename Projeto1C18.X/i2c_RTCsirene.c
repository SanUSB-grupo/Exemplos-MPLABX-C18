#include "SanUSB48.h" // Firmware para configuração e leitura por hardware de EEPROM i2c e de relógio DS1307 (BCD)
#include"i2c_usb.h"//Biblioteca de funcoes I2C com a placa SanUSB, onde RB0(SDA) e RB1(SCL)
//Vídeo: http://youtu.be/xNZVVRcdpIU

//Endereco Hora e Minuto do Alarme
#define horaAlarme 0x07
#define minAlarme  0x08

unsigned char endereco, numquant=0, numquant1=0;
unsigned char  comando[6], n=0;
short int flagA4=0, flagA5=0, flagA6=0, flagA7=0, flagAlarme=0;

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
     //////////FUNCAO 4: CONFIGURA RELÓGIO////////////////////Ex: Digitar A4H09 (Hora = 09) , A4D15 (Dia = 15).
     if (comando[n]=='A'){n=0;comando[0] = 'A';} //UTILIZAR VALORES DECIMAIS EM DOIS DIGITOS. ex:06, 23, 15, etc.
         if ( comando[1]== '4' && comando[2]== 'H' && n==2) { endereco=2;} //Escreve o endereco das horas
         if ( comando[1]== '4' && comando[2]== 'M' && n==2) { endereco=1;} //Escreve o endereco dos minutos
         if ( comando[1]== '4' && comando[2]== 'S' && n==2) { endereco=0;} //Escreve o endereco dos segundos
         if ( comando[1]== '4' && comando[2]== 'D' && n==2) { endereco=4;} //Escreve o endereco do dia
         if ( comando[1]== '4' && comando[2]== 'N' && n==2) { endereco=5;} //Escreve o endereco do mes
         if ( comando[1]== '4' && comando[2]== 'Y' && n==2) { endereco=6;} //Escreve o endereco do ano

         if ( comando[1]== '4' && comando[3]>='0'&&comando[3]<='9'&& n==3) {numquant=(comando[3]-0x30);}
         if ( comando[1]== '4' && comando[4]>='0'&&comando[4]<='9'&& n==4) {numquant=numquant*10+(comando[4]-0x30);
                                                                         flagA4=1;
                                                                            }
     //////////////*////////FUNCAO 5: LÊ RELÓGIO////////////////////////////Ex: A5- Lê o relógio e o calendário
         if (comando[1]== '5' && n==1){flagA5=1;}

      //CONFIGURANDO HORA DO ALARME
         if ( comando[1]== '6' && comando[2]== 'H' && n==2) { endereco=7;} //Escreve o endereco das horas do alarme
         if ( comando[1]== '6' && comando[2]== 'M' && n==2) { endereco=8;} //Escreve o endereco dos minutos do alarme
         if ( comando[1]== '6' && comando[3]>='0'&&comando[3]<='9'&& n==3) {numquant1=(comando[3]-0x30);}
         if ( comando[1]== '6' && comando[4]>='0'&&comando[4]<='9'&& n==4) {numquant1=numquant1*10+(comando[4]-0x30);
                                                                        flagA6=1;
                                                                        flagAlarme=1;
                                                                      }
         if (comando[1]== '7' && n==1){flagA7=1;}
         ++n; if(n>=7){n=0;}
   }
}

toca_sirene(){
    if (flagAlarme){

            nivel_alto(pin_c0);
            tempo_ms(5000);
            nivel_baixo(pin_c0);
            flagAlarme=0;
    }
}

void main(){

    clock_int_48MHz();
    habilita_interrupcao(recep_serial);
    habilita_canal_AD(AN0);
    taxa_serial(9600);
    i2c_ini();
    TRISC = 0;

    while(1){

        if (le_rtc(hora) == le_rtc(horaAlarme) && le_rtc(min) == le_rtc(minAlarme)){
            toca_sirene();

        }

        if (flagA4){ flagA4=0; //Comandos A4 para Configurar o RTC
                escreve_rtc(endereco, dec_para_bcd(numquant)); //Escrever em BCD no RTC
                send_hex(le_rtc(hora)); swputc (':');     //Envia resultado via serial por bluetooth ou qualquer outro modem.
                send_hex(le_rtc(min));  swputc (':');     //Exemplo de resposta: 18:49:37 19/04/14
                send_hex(le_rtc(seg));  swputc (' ');
                send_hex(le_rtc(dia));  swputc ('/');
                send_hex(le_rtc(mes));  swputc ('/');
                send_hex(le_rtc(ano));  swputc(' ');
                    }

        if (flagA5){ flagA5=0; //BCD em hexadecimal representa o decimal
                send_hex(le_rtc(hora)); swputc (':');
                send_hex(le_rtc(min));  swputc (':');
                send_hex(le_rtc(seg));  swputc (' ');
                send_hex(le_rtc(dia));  swputc ('/');
                send_hex(le_rtc(mes));  swputc ('/');
                send_hex(le_rtc(ano));  swputc(' ');
                      }

        //Escreve hora e minuto alarme
         if (flagA6){ flagA6=0; //Comandos A0 para Configurar o Alarme
                escreve_rtc(endereco, dec_para_bcd(numquant1)); //Escrever em BCD no RTC
                send_hex(le_rtc(horaAlarme)); swputc (':');     //Envia resultado via serial por bluetooth ou qualquer outro modem.
                send_hex(le_rtc(minAlarme));  swputc(' ');     //Exemplo de resposta: 18:49:37 19/04/14
         }

        //imprime hora e minuto do alarme
         if (flagA7){ flagA7=0; //BCD em hexadecimal representa o decimal
                send_hex(le_rtc(horaAlarme)); swputc (':');
                send_hex(le_rtc(minAlarme)); swputc(' ');
         }

        inverte_saida(pin_b7);
        tempo_ms(1000);            }
}
