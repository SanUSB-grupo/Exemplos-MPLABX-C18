/******************************************************************************
 * Descrição:   	Firmware capaz de prover a comunicação entre um teclado
 *                      PS/2 e o microcontrolador
 * Vídeo: http://www.youtube.com/watch?v=yV6MWybpB3w
 *
 * Créditos a Bruno A. Dayrell
 * 
 * 			H A R D W A R E:
 *
 *  			Conector Femea:		Pinos | Porta | Função
 *                                        1      RD6    Teclado Data
 *      	6 [] 5			  3       - 	GND
 *             4      3                   4       -	VCC
 *                                        5      RD7	Teclado Clock
 *            	 2  1                     
 *		Comunicação Teclado -> PIC
 *
 *		1 start bit.  Sempre 0 (Pode ser usado para ativar interrupção).
 *		8 data bits, Menos significante primeiro.
 *		1 bit de paridade (paridade ímpar)
 *		1 stop bit.  Sempre 1.
 *****************************************************************************/

#include "SanUSB48.h"	
#include "PS2.h"     
#include "lcd1.h"    

    char letra;
    int i;

#pragma interrupt interrupcao
void interrupcao() {}

void main(void)
{   clock_int_48MHz();
    taxa_serial(19200);

    ConfiguraLCD();     

    while(1)
    {    
        // aguarda o pino de start bit (start bit = 0)
        while(PS2_PINDATA){if(!entrada_pin_e3){Reset();}}//Estado de gravação via USB, se o botão for pressionado

        // Verificação da condição de permitir leitura do teclado
        if(!PS2_PINDATA)
                    {
                            letra = LeTeclado();
                    }
        Delay10KTCYx(30);
                    // Tratamento do caractere que verifica se não é nenhum
                    // caractere de ERRO e também se não é alguma tecla especial
                    // como exemplo, backspace ou enter.
		if(letra!= MISSMATCH_ERROR && letra!= TIMEOUT_ERROR && letra!= PARIDADE_ERROR ) //0, 1 e 2
     		{
			if(letra == 0x0D)//Enter
			{
                                // Início da 2ª Linha
				PosicaoCursorLCD(2,1);
			}
			else
			{
				if(letra == 0x08) // Backspace - limpa todo o display
				{
                                        LimpaDisplay();
				}
				else
				{
                                        EscreveCaractereLCD(letra);
				}
			}
		} 

    } 


}

