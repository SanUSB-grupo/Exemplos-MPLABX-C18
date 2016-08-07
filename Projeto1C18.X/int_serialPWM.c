//Utiliza interrupcao serial para receber comandos enviados via bluetooth ou zigbee para configuracao do PWM
#include "SanUSB1.h" //

#pragma interrupt interrupcao
void interrupcao()
{
  unsigned char c;

 if (serial_interrompeu)  {            
     serial_interrompeu=0;
     c = le_serial();
     if (c >= '0' && c<= '9')
     {
         switch (c){
             case '1':
                 SetaPWM1(10000,10); //SetaPWM1(frequencia,porcento);
                 SetaPWM2(10000,10);
                 break;
             case '2':
                 SetaPWM1(10000,20);
                 SetaPWM2(10000,20);
                 break;
             case '3':
                 SetaPWM1(10000,30);
                 SetaPWM2(10000,30);
                 break;
             case '4':
                 SetaPWM1(10000,40);
                 SetaPWM2(10000,40);
                 break;
             case '5':
                 SetaPWM1(10000,50);
                 SetaPWM2(10000,50);
                 break;
             case '6':
                 SetaPWM1(10000,60);
                 SetaPWM2(10000,60);
                 break;
             case '7':
                 SetaPWM1(10000,70);
                 SetaPWM2(10000,70);
                 break;
             case '8':
                 SetaPWM1(10000,80);
                 SetaPWM2(10000,80);
                 break;
             case '9':
                 SetaPWM1(10000,90);
                 SetaPWM2(10000,90);
                 break;
             case '0':
                 SetaPWM1(10000,100);
                 SetaPWM2(10000,100);
                 break;
         }
     } 
   }
} 

unsigned long int resultado, Vresult; //16 bits
void main(){
    clock_int_4MHz();


    habilita_interrupcao(recep_serial);
    taxa_serial(19200);

    while(1){
        nivel_alto(pin_b7);
        tempo_ms(500);
        nivel_baixo(pin_b7);
        tempo_ms(500);

        resultado = le_AD10bits(0);//Lê canal  0 da entrada analógica com  resolução de 10 bits (ADRES)
        Vresult= (resultado * 5000)/1023;
        printf("Valor AD= %lu\r\n", resultado);
       // printf("Tensao Result= %lu mV\r\n", Vresult);
    }
}

