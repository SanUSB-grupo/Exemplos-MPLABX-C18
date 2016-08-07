#include "SanUSB1.h"

#pragma interrupt interrupcao
void interrupcao(){//se houver interrupção inserir função aqui
                   }

//Colar o SanUSB.h dentro da pasta /Microchip/MCC18/3.40/h
//Após abri o projeto, ir em Run e setar como projeto principal
//inserir os caminhos da pasta em Run - Set project - Customize
//Arquivo compilado: Projeto1C18.X\dist\default\production\Projeto1C18.X.production.hex
//clicar só em build, se clicar em build and clean, limpa o ./sanusb do mesmo diretório no Mac OSX
//Se mudar de SO clicar em Build and Clean
//Se necessário, ir em Tools - options e verificar o compilador padrão

long int i;

void delay (void)
{
  for (i = 0; i <10000; i++)
    ;
}

void main (void)
{
clock_int_4MHz();

  TRISB = 0;
  TRISD = 0;

  while (1)
    {
if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação
      /* Zera a porta B */
      PORTB = 0; PORTD = 0;

      /* Delay para ver o Led */
      tempo_ms(300);

      /* Liga os LEDs */
      PORTB = 0xff; PORTD = 0xff;

     /* Delay para ver o Led */
      delay ();
    }
}

