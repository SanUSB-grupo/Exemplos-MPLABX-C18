#ifndef __LCD1_H
#define __LCD1_H
/** D E F I N E S ************************************************************/
#define D4       PORTBbits.RB0
#define D5       PORTBbits.RB1
#define D6	 PORTBbits.RB2
#define D7       PORTBbits.RB3

#define TRIS_D4  TRISBbits.TRISB0
#define TRIS_D5  TRISBbits.TRISB1
#define TRIS_D6  TRISBbits.TRISB2
#define TRIS_D7  TRISBbits.TRISB3

#define RS_PIN   PORTBbits.RB5
#define E_PIN    PORTBbits.RB4
//não usado // #define RW_PIN   PORTBbits.RB2

#define TRIS_RS  TRISBbits.TRISB5
#define TRIS_E   TRISBbits.TRISB4
//não usado // #define TRIS_RW  TRISBbits.TRISB2

// Define o valor dos delays baseado no clock da CPU de 48 MHz
#define DELAY_SINC()	Delay1KTCYx(12)		// Delay de 1ms para Fosc=48MHz

#define DELAY_5ms()	Delay10KTCYx(6)		// Delay de 5ms para Fosc=48MHz

/*** D E F I N E S D E C O N F I G U R A C A O *******************************/
/******************************************************************************
 * Define:	LimpaDisplay()
 * Descrição: 	Remove todos os caracteres do display e retorna a posição do
 *		cursor para a linha 1 e coluna 1
 *****************************************************************************/
#define LimpaDisplay()  	EscreveComandoLCD(0b0000000001)
/******************************************************************************
 * Define:	LimpaDisplay()
 * Descrição: 	Liga o display de LCD e retira o cursor do visor.
 *****************************************************************************/
#define LigaDisplay()  		EscreveComandoLCD(0b0000001000)
/******************************************************************************
 * Define:	LimpaDisplay()
 * Descrição: 	Desliga o display. (Não apaga o backlight)
 *****************************************************************************/
#define DesligaDisplay()  	EscreveComandoLCD(0b0000001100)
/******************************************************************************
 * Define:	LigaCursor()
 * Descrição: 	Faz com que o cursor apareça no LCD caso este esteja ligado
 *		e liga a tela com o cursor caso este esteja desligado.
 *****************************************************************************/
#define LigaCursor()		EscreveComandoLCD(0b0000001110)
/******************************************************************************
 * Define:	DesligaCursor()
 * Descrição: 	Faz com o cursor suma do LCD caso este esteja ligada e com que
 *		ligue o LCD sem o cursor caso este esteja desligado
 *****************************************************************************/
#define DesligaCursor()		EscreveComandoLCD(0b0000001100)
/******************************************************************************
 * Define:	PiscaCursor()
 * Descrição: 	Faz com que o cursor apareça no LCD e fique piscando caso este
 *              esteja ligado e liga a tela com o cursor piscando caso este
 *              esteja desligado.
 *****************************************************************************/
#define PiscaCursor()		EscreveComandoLCD(0b0000001111)


 extern void ConfiguraLCD(void);


 extern void EscreveComandoLCD(unsigned char cmd);

 extern void EscreveByteLCD(char data);

 extern void EnderecoCursor(unsigned char endereco);

extern void PosicaoCursorLCD(unsigned char linha, unsigned char coluna);

 extern void EscreveCaractereLCD(char data);

extern void EscreveInteiroLCD(int valor);

 extern void EscreveFraseRamLCD(char *buffer);

 extern void EscreveFraseRomLCD(const rom char *buffer);

#endif

 void ConfiguraLCD(void)
{int i;
	ADCON1 |= 0x0F;
	TRIS_RS = 0;
	TRIS_E = 0;
	TRIS_D4=0;
	TRIS_D5=0;
	TRIS_D6=0;
	TRIS_D7=0;
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	D7=0;
	D6=0;
	D5=1;
	D4=1;

//Passo 1: Envio do comando de inicialização 0b0011

	// Delay inicial de 15ms após alimentar o LCD: Vdd > 4,5V
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
	DELAY_5ms();
	DELAY_5ms();
	DELAY_5ms();

	//Habilita leitura do comando pelo LCD, através do pino de enable, para tanto,
	//um pulso de 1ms com borda de descida é efetuado
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

	// Delay de pelo menos 4.1ms
	DELAY_5ms();

	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();


	// Delay de pelo menos 100us
	DELAY_5ms();

	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

//Passo 4: Envio da Configuração 0b0010 no Nibble-High
	D7=0;
	D6=0;
	D5=1;
	D4=0;

	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
/*//Adaptação für CGRAM
    E_PIN  = 1;
    RS_PIN = 0;            // command mode

    tempo_ms(15);        // Wait 15ms to ensure powered up

    // send "Display Settings" 3 times (Only top nibble of 0x30 for 4-bit bus)
    for (i=0; i<3; i++) {
        EscreveByteLCD(0x3);
        tempo_ms(2);//wait(0.00164);  // this command takes 1.64ms, so wait for it
    }//*/


//Envio dos comandos de Configuração do LCD
	EscreveComandoLCD(0x28);	// 0x28 Function Set: 4bit interface, 2 lines, Font 5x7 //5x8 0x38
        //EscreveComandoLCD(0x0c); //Display Control: Display ON, Cursor ON, Blink OFF
	EscreveComandoLCD(0x06);	// 0x6Entry mode set: Increment, Shift OFF //ok
	EscreveComandoLCD(0b00001110);	// 0x0c Display Control: Display ON, Cursor ON, Blink OFF
	EscreveComandoLCD(0x01);	// 0x01 Clear display
}

void EscreveComandoLCD(unsigned char cmd)
{
	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;	// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	//Seleciona pinos de Dados: Nibble-High
	if(cmd&0b00010000){D4=1;}
	else {D4=0;}
	if(cmd&0b00100000){D5=1;}
	else {D5=0;}
	if(cmd&0b01000000){D6=1;}
	else {D6=0;}
	if(cmd&0b10000000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

	//Seleciona pinos de Dados: Nibble-Low
	if(cmd&0b00000001){D4=1;}
	else {D4=0;}
	if(cmd&0b00000010){D5=1;}
	else {D5=0;}
	if(cmd&0b00000100){D6=1;}
	else {D6=0;}
	if(cmd&0b00001000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
}

void EnderecoCursor(unsigned char endereco)
{
	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 0;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	//Seleciona pinos de Dados: Nibble-High
	D7 = 1;
	if(endereco&0b00010000){D4=1;}
	else {D4=0;}
	if(endereco&0b00100000){D5=1;}
	else {D5=0;}
	if(endereco&0b01000000){D6=1;}
	else {D6=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();

	//Seleciona pinos de Dados: Nibble-Low
	if(endereco&0b00000001){D4=1;}
	else {D4=0;}
	if(endereco&0b00000010){D5=1;}
	else {D5=0;}
	if(endereco&0b00000100){D6=1;}
	else {D6=0;}
	if(endereco&0b00001000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
}

void PosicaoCursorLCD(unsigned char linha, unsigned char coluna)
{
	#define linha1	0x00
	#define	linha2	0x40

	unsigned char endereco = 0x00;

	coluna--;

	if (coluna >= 0)
	{
		switch (linha)
		{
			case 1: // 	linha1Desliga ambos pontos decimais
				endereco = linha1 + coluna;
				EnderecoCursor(endereco);
			break;

			case 2: // 	linha1Desliga ambos pontos decimais
				endereco = linha2 + coluna;
				EnderecoCursor(endereco);
			break;

			default:
				endereco = linha1;
			break;
		}
	}
	else
	{
		endereco = linha1;
	}
}


void EscreveCaractereLCD(char data)
{
	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	RS_PIN = 1;		// comando=0, dados=1
	E_PIN =  0; 	// desabilita=0, habilita=1

	//Seleciona pinos de Dados: Nibble-High
	if(data&0b00010000){D4=1;}
	else {D4=0;}
	if(data&0b00100000){D5=1;}
	else {D5=0;}
	if(data&0b01000000){D6=1;}
	else {D6=0;}
	if(data&0b10000000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();


	//Seleciona pinos de Dados: Nibble-Low
	if(data&0b00000001){D4=1;}
	else {D4=0;}
	if(data&0b00000010){D5=1;}
	else {D5=0;}
	if(data&0b00000100){D6=1;}
	else {D6=0;}
	if(data&0b00001000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
}

void EscreveByteLCD(char data)
{
	//Seleciona pinos de Controle para escrita do comando
	//não usado // 	RW_PIN = 0;	//escrita=0, leitura=1
	//RS_PIN = 1;		// comando=0, dados=1
	//E_PIN =  0; 	// desabilita=0, habilita=1

	//Seleciona pinos de Dados: Nibble-High
	if(data&0b00010000){D4=1;}
	else {D4=0;}
	if(data&0b00100000){D5=1;}
	else {D5=0;}
	if(data&0b01000000){D6=1;}
	else {D6=0;}
	if(data&0b10000000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();


	//Seleciona pinos de Dados: Nibble-Low
	if(data&0b00000001){D4=1;}
	else {D4=0;}
	if(data&0b00000010){D5=1;}
	else {D5=0;}
	if(data&0b00000100){D6=1;}
	else {D6=0;}
	if(data&0b00001000){D7=1;}
	else {D7=0;}

	//Pulso no pino de Enable para habilitar leitura do LCD na borda de descida
	E_PIN = 1;
        DELAY_SINC();
	E_PIN = 0;
	DELAY_SINC();
}

void EscreveInteiroLCD(int valor)
{
	char texto[7] = " ";
	itoa( valor, texto);
	EscreveFraseRamLCD(texto);
}

void EscreveFraseRamLCD(char *buffer)
{
	while(*buffer)                  // escreve dados no LCD ate achar caracter nulo
	{
	        EscreveCaractereLCD(*buffer); // escreve caracter no LCD
	        buffer++;               // incrementa apontador
	}
}

void EscreveFraseRomLCD(const rom char *buffer)
{
	while(*buffer)                  // escreve dados no LCD ate achar caracter nulo
	{
	        EscreveCaractereLCD(*buffer); // escreve caracter no LCD
	        buffer++;               // incrementa apontador
	}
}
