#include "SanUSB1.h"

#define RELE1 pin_b6 // Conectado ao fio branco do módulo Relé(Figura4)


unsigned char tecla = 0;
unsigned char bit01 = 0, bit02 = 0, bit03 = 0, bit04 = 0, bitStd= 0;

short int RELE1_STATE = 0; // Estado do Relé LOW (Desligado)

#pragma interrupt interrupcao
void interrupcao()
{
 if (timer0_interrompeu)     {          //espera o estouro do timer0
timer0_interrompeu = 0;           	   //limpa a flag de interrupção
PORTBbits.RB7 =! PORTBbits.RB7;    //Pisca o LED em B7
tempo_timer16bits(0,62500); }//Carrega 3036 = 0x0BDC (65536-3036 -> conta 62500us x 8 = 0,5seg)
 	
} 


void main()         {
clock_int_4MHz();

TRISB = 0b00000011;          //B0 a B5 como entrada e B6-B7 como Saída

//habilita_interrupcao(timer0);
INTCONbits.TMR0IE = 1; T0CONbits.TMR0ON = 1;
multiplica_timer16bits(0,16);           //liga timer0 - 16 bits com multiplicador (prescaler) 8
tempo_timer16bits(0,62500);       //Conta 16 x 62500us = 1 seg.

taxa_serial(19200);
printf("Aguardando tecla de comando..."); // Exibimos a mensagem no terminal...

while (1){ if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação
		
bitStd = entrada_pin_b0; //Lê o estado do pino STD e armazena em 'bitStd'
  if (bitStd == 1) {//Se estiver em nível alto fará as leituras
                       //dos bits dos pinos Q3, Q2, Q1 e Q0

    bit01 = entrada_pin_b1;
    bit02 = entrada_pin_b2;
    bit03 = entrada_pin_b3;
    bit04 = entrada_pin_b4;

    tecla = (bit04 * 8) + (bit03 * 4) + (bit02 * 2) + (bit01 * 1);//Conversão binária para

                                                                  //decimal (ver Vídeo1)

    printf("Recebido: "); // Exibe a mensagem

    switch (tecla){ // Seleciona a tecla pressionada

    case 1: // Tecla 1
      printf("1 ");
      /* COMANDO PARA RELE1 */
      RELE1_STATE = !RELE1_STATE; // Guarda o estado INVERTIDO do Relé.
      break;

    case 2: // Tecla 2
      printf("2 ");
      break;

    case 3: // Tecla 3
      printf("3 ");
      break;

    case 4: // Tecla 4
      printf("4 ");
      break;

    case 5: // Tecla 5
      printf("5 ");
      break;

    case 6: // Tecla 6
      printf("6 ");
      break;

    case 7: // Tecla 7
      printf("7 ");
      break;

    case 8: // Tecla 8
      printf("8 ");
      break;

    case 9: // Tecla 9
      printf("9 ");
      break;

    case 10: // Tecla 0
      printf("0 ");
      break;

    case 11: // Tecla *
      printf("* ");
      break;

    case 12: // Tecla #
      printf("# ");
      break;
    }

    saida_pino(RELE1, RELE1_STATE);//Liga ou desliga o Relé1 conforme o estado (HIGH/ LOW)

    // Zeram-se todas as variáveis
    tecla = 0;
    bit01 = 0;
    bit02 = 0;
    bit03 = 0;
    bit04 = 0;
    bitStd= 0;
    tempo_ms(500); // Aguarda 500 milissegundos
  }
} 


}
