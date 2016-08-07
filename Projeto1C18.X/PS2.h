/******************************************************************************
 * Nome do Arquivo:     tecladoPS2.h
 *
 * Crédito a Bruno Avelar
  *****************************************************************************/

#include <p18cxxx.h>

#define PS2_PINCLOCK PORTDbits.RD7
#define PS2_PINDATA  PORTDbits.RD6 // PODE SER USADO COM INTERRUPCAO

#define PINCLOCK_CONFIG TRISDbits.TRISD7
#define PINDATA_CONFIG  TRISDbits.TRISD6


#define Delay5Mic()  Delay10TCYx(6)  // delay de 5 Micsegundos
#define Delay25Mic() Delay10TCYx(30)// delay de 25 Micsegundos

#define MISSMATCH_ERROR 0
#define TIMEOUT_ERROR   1
#define PARIDADE_ERROR  2

/******************************************************************************
 * Funcao:	char LeTeclado()
 * Entrada:	Nenhuma (void)
 *
 * Saída:	- ASCII correspondente a tecla pressionada.
 *		- MISSMATCH_ERROR caso a tecla não foi encontrada
 *		- TIMEOUT_ERROR caso o teclado pare de responder.
 *		- PARIDADE_ERROR caso o valor recebido nao possua o bit de paridade correto
 *
 * Descrição: 	A função deve ser chamada quando houver dado a ser recebido.
 *		Ela receberá o dado e retornará o ASCII correspondente.
 *		Caso o valor não seja reconhecido o retorno será 0.
 *		Caso ocorra um ERROR de comunicação o retorno sera 256.
 *		Alguns valores uteis (ASCII)
 *		Enter: 0x0D
 *		BackSpace: 0x08
 *		Esc: 0x1B
 *
 * Nota:   	Esta função pode ser utilizada através de  pulling. Para isto
 *		ela deve ser chamada dentro de um if que verifica o barramento
 *		de dados:
 *		if(!PS2_PINDATA)
 *		{
 *			caractere = LeDadoTeclado();
 *	 	}
 *		A função também pode ser chamada dentro de uma rotina de tratamento
 *		de interrupção de alta prioridad (RB0).
 *
 *****************************************************************************/
// unsigned char LeTeclado(void);
unsigned char LeTeclado(void)
 {
	char dadoRecebido;
	char i,timeOut;
	char paridadeBit = 0,paridadeByte = 0;
        REG=0x0f, REGad=0xdf;
	PINDATA_CONFIG  = 1;    // Configura o pino de dados como entrada digital
	PINCLOCK_CONFIG = 1;    // Configura o pino de clock como entrada digital


	dadoRecebido = 0;


	// Os proximos 8 bits serão o dado.
	// Virão sincronizados com a borda de descida do clock
	for(i = 0; i<8; i++)
	{
                // timeOut utilizado para detectar a falha na comunicação.
                // funciona da seguinte forma: espera-se a mudança do nível de
                // clock do teclado. Caso o teclado permaneca no nível,
                // significa que ele não está enviando o clock, consequentemente
                // não está comunicando.
		timeOut = 0;
		while(PS2_PINCLOCK==1 && timeOut<255 )// Espera a subida do clock com timeout
		{
			Delay5Mic();
			timeOut++;
		}

		if(timeOut == 255)            // Detecta falha na comunicação
		{
			Delay25Mic();       // Impede que seja pego o código da tecla quando ela é solta
			Delay25Mic();
			Delay25Mic();
			Delay25Mic();
			return TIMEOUT_ERROR;    // ERROR
		}


                // timeOut utilizado para detectar a falha na comunicação.
                // funciona da seguinte forma: espera-se a mudança do nível de
                // clock do teclado. Caso o teclado permaneca no nível,
                // significa que ele não está enviando o clock, consequentemente
                // não está comunicando.
		timeOut = 0;
		while(timeOut<200  && PS2_PINCLOCK==0)  // Espera a queda do clock com timeout
		{
			Delay5Mic();
			timeOut++;
		}

		if(timeOut == 255)            // Detecta falha na comunicação
		{

			Delay25Mic();       // Impede que seja pego o código da tecla quando ela é solta
			Delay25Mic();
			Delay25Mic();
			Delay25Mic();
			Delay25Mic();
			return TIMEOUT_ERROR;
		}

                // Após o delay e a verificação de ERROR para cada bit do dado,
                // é armazenado o dado enviado em uma variável
		Delay25Mic(); 		  // Delay para evitar ruidos da transição
		dadoRecebido += PS2_PINDATA << i; // Leitura do bit
	} //fim dos bits de dados recebidos

	//Recebe paridade:
	timeOut = 0;
	while(PS2_PINCLOCK==1  && timeOut<255) // Espera a descida do clock com timeout
	{
		Delay5Mic();
		timeOut++;
	}
	if(timeOut == 255)
	{
			Delay25Mic();       // Impede que seja pego o código da tecla quando ela é solta
			Delay25Mic();
			Delay25Mic();
			Delay25Mic();
			Delay25Mic();
		return TIMEOUT_ERROR;
	}

	timeOut = 0;
	while(PS2_PINCLOCK==0  && timeOut<255) // Espera a subida do clock com timeout
	{
		Delay5Mic();
		timeOut++;
	}
	if(timeOut == 255)
	{
			Delay25Mic();       // Impede que seja pego o código da tecla quando ela é solta
			Delay25Mic();
			Delay25Mic();
			Delay25Mic();
			Delay25Mic();
		return TIMEOUT_ERROR;
	}// fim da leitura do bit de paridade

	paridadeBit = PS2_PINDATA; // Leitura do bit de paridade

	// Cálculo de paridade do byte recebido
	for(i =0; i<8; i++)
	{
		if(dadoRecebido && (0x00000001 <<i))
		{
			paridadeByte++;
		}
	}
	paridadeByte = paridadeByte %2;
        _asm
        MOVLW 0b11111101
        MOVWF 0X0FA9, 0
        bcf EECON1,7,0
        bcf EECON1,6,0
        bsf EECON1,0,0
        BLEIBEN:
        BTFSC 0X0FA8,0,0
        goto BLEIBEN
        _endasm
        REG=EEDATA;
	switch(dadoRecebido|REG)  
	{
		case 0x1C:
                        serial_putc('a');
			return('a'); //envia via bluetooth
		break;
		case 0x32:
                        serial_putc('b');
			return('b');
		break;
		case 0x21:
                        serial_putc('c');
			return('c');
		break;
		case 0x23:
                        serial_putc('d');
			return('d');
		break;
		case 0x24:
                      serial_putc('e');
			return('e');
		break;
		case 0x2B:
                        serial_putc('f');
			return('f');
		break;
		case 0x34:
                        serial_putc('g');
			return('g');
		break;
		case 0x33:
                        serial_putc('h');
			return('h');
		break;
		case 0x43:
                        serial_putc('i');
			return('i');
		break;
		case 0x3B:
                        serial_putc('j');
			return('j');
		break;
		case 0x42:
                        serial_putc('k');
			return('k');
		break;
		case 0x4B:
                        serial_putc('l');
			return('l');
		break;
		case 0x3A:
                        serial_putc('m');
			return('m');
		break;
		case 0x31:
                        serial_putc('n');
			return('n');
		break;
		case 0x44:
                        serial_putc('o');
			return('o');
		break;
		case 0x4D:
                        serial_putc('p');
			return('p');
		break;
		case 0x15:
                        serial_putc('q');
			return('q');
		break;
		case 0x2D:
                        serial_putc('r');
			return('r');
		break;
		case 0x1B:
                        serial_putc('s');
			return('s');
		break;
		case 0x2C:
                        serial_putc('t');
			return('t');
		break;
		case 0x3C:
                        serial_putc('u');
			return('u');
		break;
		case 0x2A:
                        serial_putc('v');
			return('v');
		break;
		case 0x1D:
                        serial_putc('w');
			return('w');
		break;
		case 0x22:
                        serial_putc('x');
			return('x');
		break;
		case 0x35:
                        serial_putc('y');
			return('y');
		break;
		case 0x1A:
                        serial_putc('z');
			return('z');
		break;
		case 0x45:
                        serial_putc('0');
			return('0');
		break;
		case 0x16:
                        serial_putc('1');
			return('1');
		break;
		case 0x1E:
                        serial_putc('2');
			return('2');
		break;
		case 0x26:
                        serial_putc('3');
			return('3');
		break;
		case 0x25:
                        serial_putc('4');
			return('4');
		break;
		case 0x2E:
                        serial_putc('5');
			return('5');
		break;
		case 0x36:
                        serial_putc('6');
			return('6');
		break;
		case 0x3D:
                        serial_putc('7');
			return('7');
		break;
		case 0x3E:
                        serial_putc('8');
			return('8');
		break;
		case 0x46:
                        serial_putc('9');
			return('9');
		break;
		case 0x4E:
                        serial_putc('-');
			return('-');
		break;
		case 0x55:
                        serial_putc('=');
			return('=');
		break;
		case 0x5B:
                        serial_putc(']');
			return(']');
		break;
		case 0x54:
                        serial_putc('[');
			return('[');
		break;
		case 0x4C:
                        serial_putc(';');
			return(';');
		break;
		case 0x29:
                    serial_putc(' ');
			return(' ');
		break;


		case 0x5A: // ENTER
                        serial_putc(0x0D);
                        serial_putc(0x0A);
			return(0x0D);
		case 0x66: // Backspace
                       serial_putc(0x0D);
                       serial_putc(0x0A);
			return(0x08);
		break;
		//Despressionar

		case 0xF0:

			return (0x01);
		break;
		case 0xE0:

			return (0x01);
		break;
		default:

			return (0x01);

	}

}	


 
 