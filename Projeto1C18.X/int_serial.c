#include "SanUSB1.h"


unsigned int result;

short int pisca=0,avisa_interrompeu;

    unsigned int d=10, e=15;
    char str[7];
    unsigned char Txdata[] = "TESTE_USART\r\n";

char inputstr[30];
char str_pos = 0;

#pragma interrupt interrupcao
void interrupcao()
{
if (serial_interrompeu)  {  serial_interrompeu=0; avisa_interrompeu=1;

    inputstr[str_pos] = getcUSART(); //ou le_serial - vai buscar a inputstr à porta série caracter a caracter (em cada iterada)
    str_pos++;//incrementa a posição de escrita na string de destino
    if(str_pos == 30){str_pos = 0;}  //verifica se a string de 80 caracteres
   //está cheia e caso o esteja faz reset da posição de escrita na string a 0
 
//comando = le_serial();//apenas um byte

    switch (inputstr[0]) //teste da comunicacao serial no Terminal
      {
case 'L' : {pisca=0; nivel_alto(pin_b7);putrsUSART ( (const far rom char *) " Ligado\r\n");while (envia_byte());} //Recebe A e Transmite byte B para teste
break;
case 'D' : {pisca=0; nivel_baixo(pin_b7);putrsUSART ( (const far rom char *) " Desligado");while (envia_byte());}
break;
case 'P' : {pisca=1;  printf_text(Txdata); printf_data(10);
           }
break;
     }

                            }
}

void main()       {
clock_int_4MHz();

habilita_interrupcao(recep_serial);
taxa_serial(9600);

  while (1) {
  if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação

    nivel_alto(pin_b7);
    tempo_ms(1000);
    nivel_baixo(pin_b7);
    tempo_ms(1000);
    
    //tempo_ms(2000);
     ultoa(d,str); // convert to string and print d - importante para sensores
     putsUSART(str);
     tempo_ms(200);// o tempo para envio de mais de um caractere

    // escreve_serial('A'); //while (envia_byte());// escreve só um byte
     
   //------------Transmissão Serial ----------------------------------------------------------------
    putsUSART((char *) Txdata); // transmite the string   

    if (avisa_interrompeu == 1)  //foi inserido um caracter?
    {
        if(inputstr[str_pos - 1] == 'K') //0x0D o último caracter foi o ENTER?
        {avisa_interrompeu = 0;
 //   printf("Comando digitado %s\r", inputstr);
    str_pos = 0; //reset da posição na string de buffer
    
        }
    } 
     
  }
}

