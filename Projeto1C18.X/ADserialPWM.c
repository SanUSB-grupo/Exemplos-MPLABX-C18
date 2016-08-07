/*******************************************************************************
Software: Firmware abaixo compilado com o MPLABX + C18 Lite (https://dl.dropboxusercontent.com/u/101922388/BaixarMPLABX_C18.pdf)
Hardware: Placa SanUSB com um resistor de 1K ligado entre os pinos
C2(PWM1) e A0(AN0) e um capacitor de 10uF entre o pino  A0 e o Gnd.
Mais detalhes em: http://www.youtube.com/watch?v=lB21b3zA4Ac
 ******************************************************************************/
#include "SanUSB1.h"

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c

void interrupcao() {

}

unsigned long int resultado, Vresult; //16 bits
unsigned char i = 0;
const char Tensao[] = "Tensao Result= ";
const char Rn[] = "\r\n";
const char TextoAD[] = "Valor AD= ";

void main() {
    clock_int_4MHz(); //Função necessari para o dual clock
    taxa_serial(19200);
    habilita_canal_AD(AN0);

    while (1) {
        for (i = 0; i < 100; i = i + 5) {
            SetaPWM1(10000, i);
            SetaPWM2(10000, i); //frequência em Hz

            resultado = le_AD10bits(0); //Lê canal  0 da entrada analógica com  resolução de 10 bits (ADRES)
            Vresult = (resultado * 5000) / 1023;

            //printf("Tensao Result= %lu mV\r\n", Vresult); //evitar  o printf o uso do printf e imprimir com sendsw e sendnum
            sendsw((char *) Tensao);
            sendnum(Vresult);
            sendsw((char *) Rn);

            inverte_saida(pin_b7);
            tempo_ms(500);
        }

        for (i = 100; i > 0; i = i - 5) {
            SetaPWM1(1200, i);
            SetaPWM2(1200, i);

            resultado = le_AD10bits(0); //Lê canal  0 da entrada analógica com  resolução de 10 bits (ADRES)
            //printf("Valor AD= %lu\r\n", resultado); //evitar  o printf o uso do printf e imprimir com sendsw e sendnum

            sendsw((char *) TextoAD);
            sendnum(resultado);
            sendsw((char *) Rn);

            inverte_saida(pin_b7);
            tempo_ms(500);
        }


    }
}
