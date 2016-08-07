#include "SanUSB48.h" //https://www.youtube.com/watch?v=-9Gf5K0SZ2Y

#pragma interrupt interrupcao
void interrupcao()
{
  unsigned char c;

 if (serial_interrompeu)  {            
     serial_interrompeu=0;
     c = le_serial();
     {
         switch (c){
             case 'L':
             nivel_alto(pin_b7);
                 break;
             case 'D':
           nivel_baixo(pin_b7);
                 break;
        
        }
     } 
   }
} 

void main(){
    clock_int_48MHz();

    habilita_interrupcao(recep_serial);
    taxa_serial(19200);

    while(1){
        
        swputc('L');
        tempo_ms(500);

        swputc('D');
        tempo_ms(500);
        inverte_saida(pin_b7);
 
            }
}

