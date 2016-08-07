#include "SanUSB48.h" //https://youtu.be/cK5bvB26aO4

char setLed0=0, setLed1=0, setLed2=0, setLed3=0, setLed4=0, setLed5=0;
#pragma interrupt interrupcao
void interrupcao(){
    unsigned char c;
    if (serial_interrompeu) {
        serial_interrompeu=0;
        c = le_serial();

        switch (c){
            case '0':
                setLed0=1; //Não imprimir dentro da interrupçção
                break;
            case '1':
                setLed1=1;
                break;
            case '2':
                setLed2=1;
                break;
            case '3':
                setLed3=1;
                break;
             case '4':
                setLed4=4;
                break;
             case '5':
                setLed5=1;
                break;
        }
    }
}



void main(){
    clock_int_48MHz();

    habilita_interrupcao(recep_serial);
    taxa_serial(19200);

    while(1){
        if(!entrada_pin_e3){
            Reset();
        }//pressionar o botão estado para gravação
        if (setLed0){
            nivel_alto(pin_b0);
            tempo_ms(5000);
            nivel_baixo(pin_b0);
            setLed0=0;
          
            //sendrw((rom char *)"A\r\n"); //envia string
        }
        if (setLed1){
            nivel_alto(pin_b1);
            tempo_ms(5000);
            nivel_baixo(pin_b1);
            setLed1=0;
            //sendrw((rom char *)"B\r\n"); //envia string
        }
        if (setLed2){
            nivel_alto(pin_b2);
            tempo_ms(5000);
            nivel_baixo(pin_b2);
            setLed2=0;
            //sendrw((rom char *)"B\r\n"); //envia string
        }
        if (setLed3){
            nivel_alto(pin_b3);
            tempo_ms(5000);
            nivel_baixo(pin_b3);
            setLed3=0;
            //sendrw((rom char *)"B\r\n"); //envia string
        }
        if (setLed4){
            nivel_alto(pin_b4);
            tempo_ms(5000);
            nivel_baixo(pin_b4);
            setLed4=0;
            //sendrw((rom char *)"B\r\n"); //envia string
        }
        if (setLed5){
            nivel_alto(pin_b5);
            tempo_ms(5000);
            nivel_baixo(pin_b5);
            setLed5=0;
            //sendrw((rom char *)"B\r\n"); //envia string
        }

        sendrw((rom char *)"Pic "); //envia string
        tempo_ms(2000);
        sendrw((rom char *)"serial\r\n"); //envia string
        tempo_ms(2000);
    }
    
}