//Utiliza interrupcao serial para receber comandos enviados via bluetooth ou zigbee para configuracao do PWM
#include "SanUSB1.h" 

#define Rede "RedeSanUSB" //Nome da rede WiFi que o modem vai se conectar
#define Senha "keki"   // Senha da rede WiFi
//#define IP "192.168.1.201"     //IP gerado pelo DHCP
//#define Porta "2000" //Senha da rede que deseja se conectar

const char Teste[] = "Teste\r\n";

#pragma interrupt interrupcao

void interrupcao() {
    unsigned char c;

    if (serial_interrompeu) {
        serial_interrompeu = 0;
        c = le_serial();
        // if (c >= '0' && c<= '9')
        {
            switch (c) {
                case 'L':
                    nivel_alto(pin_d7);
                    break;
                case 'B':
                    nivel_baixo(pin_d7);
                    break;

            }
        }
    }
}

//unsigned long int resultado, Vresult; //16 bits

void main() {
    clock_int_4MHz();

    habilita_interrupcao(recep_serial);
    taxa_serial(19200);

    while (1) {

        sendsw((char *) Teste); // const char Teste[] = "Teste\r\n ";

        inverte_saida(pin_b7);
        //inverte_saida(pin_d6);
        tempo_ms(3000);

    }
}

