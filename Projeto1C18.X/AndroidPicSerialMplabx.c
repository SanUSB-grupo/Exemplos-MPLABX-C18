//Utiliza interrupcao serial para receber comandos enviados via bluetooth ou zigbee para configuracao do PWM
#include "SanUSB48.h" //

const char Teste[] = "Teste\r\n";

#pragma interrupt interrupcao
void interrupcao()
{
  unsigned char c;
 if (serial_interrompeu)  {            
     serial_interrompeu=0;
     c = le_serial();
    // if (c >= '0' && c<= '9')
     {
         switch (c){
             case 'F':
             nivel_alto(pin_b7);
                 break;
             case 'B':
           nivel_baixo(pin_b7);
                 break;
        
        }
     } 
   }
} 

//unsigned long int resultado, Vresult; //16 bits
void main(){
    clock_int_48MHz();

    habilita_interrupcao(recep_serial);
    taxa_serial(9600);

    while(1){
        sendsw((char *)Teste);
        
        nivel_alto(pin_b7);nivel_alto(pin_d7);
        tempo_ms(5000);
        nivel_baixo(pin_b7);nivel_alto(pin_d7);
        tempo_ms(5000);

        
    }
}

