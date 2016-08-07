//=============================================================================
// Filename: MAIN.C
// Este programa tem implementado um Relogio e um Menu
// Com as bibliotecas do GLCD pode se criar varios aplicativos desde que nao se use os PORTS usados pelo CS1 e CS2 e E do GLCD
// Um Menu que pode ser usada para outras rotinas a serem implementadas
// O menu pode ser manipulado pelas dips SW1 e SW3 entrando na rotina pela SW4 e saido
// da rotina de acerto pela SW2 apertada varias vezes
// O Relogio pode ser acertado entrando na rotina pelo SW4 quando o menu indicar Acerto Relogio
// As Dips Sw1,SW3 alteram hora,min, seg para menos ou para mais ate o limite
// para sair retorne precionando SW2 varias vezes dependendo onde estiver o cursor invisivel

//=============================================================================
#include "SanUSB48.h"

#pragma interrupt interrupcao
void interrupcao(){}
/////////////////////////////////////////////////////////////////////////////
//////// FUNÇOES ////////////////////////////////////////////////////////////
//////// FUNÇOES ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void Acerto_Relogio(void);
void Glcd_Hora(unsigned char lin,unsigned char col);
void Glcd_Limpa_Tela(void);
void Glcd_liga_desl(unsigned char liga_desl);
void Glcd_String(unsigned char *p_str, unsigned char s_tamanho, unsigned char s_linha, unsigned char s_coluna, unsigned char s_fonte);
void Glcd_Byte_3_branco(void);
void Glcd_Inic(void);
void Glcd_Left(void);
void Glcd_Right(void);
void Glcd_Page(unsigned char page);
void Glcd_Pagining(void);
void Glcd_Comand(unsigned char cmd);
void Glcd_Data(unsigned char data);
void Glcd_Pict(const rom unsigned char *pict_);
void Rotina1(void);
void Rotina2(void);
void Rotina3(void);
void Rotina4(void);
void Rotina5(void);
void Rotina6(void);
void Delay_0(unsigned char D);
void InterruptHandlerLow(void);
void InterruptHandlerHigh (void);
void main (void);

/////////////////////////////////////////////////////////////////////////////
//////// DEFINICOES /////////////////////////////////////////////////////////
//////// DEFINICOES /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//definicao de letras
#define L_A 0x41
#define L_B 0x42
#define L_C 0x43
#define L_D 0x44
#define L_E 0x45
#define L_F 0x46
#define L_G 0x47
#define L_H 0x48
#define L_I 0x49
#define L_J 0x4A
#define L_k 0x4B
#define L_L 0x4C
#define L_M 0x4D
#define L_N 0x4E
#define L_O 0x4F
#define L_P 0x50
#define L_Q 0x51
#define L_R 0x52
#define L_S 0x53
#define L_T 0x54
#define L_U 0x55
#define L_V 0x56
#define L_W 0x57
#define L_X 0x58
#define L_Y 0x59
#define L_Z 0x5A
#define L_espa 0x20
#define L_2pts 0x3A
#define L_igua 0x3D

// definicoes numeros

#define N_0 0x30
#define N_1 0x31
#define N_2 0x32
#define N_3 0x33
#define N_4 0x34
#define N_5 0x35
#define N_6 0x36
#define N_7 0x37
#define N_8 0x38
#define N_9 0x39
#define liga 0x01
#define desl 0x00


//definições dos DIPS do Kit Didatico

#define DEF_A1_DIP 0xFC
#define DEF_A2_DIP 0xFB
#define DEF_A3_DIP 0xF7
#define DEF_A4_DIP 0xEF

//definicoes  ACESSO LCD

#define LCD_BIT_E PORTDbits.RD4 //LCD EXECUTA OPERACAO / HABILITA
#define LCD_BIT_RS PORTDbits.RD2 //LCD modo
#define LCD_BIT_RW PORTDbits.RD3 //LCD Escrita-leitura
#define LCD_BIT_CS1 PORTDbits.RD1 //LCD Cs1
#define LCD_BIT_CS2 PORTDbits.RD0 //LCD Cs2
#define LCD_BIT_RST PORTDbits.RD5 //LCD Reset

/* LCD Registers */

#define X_ADRESS	0xB8	/* Adress base for Page 0 */
#define Y_ADRESS	0x40	/* Adress base for Y0	  */
#define START_LINE	0xC0	/* Adress base for line 0 */
#define DISPLAY_ON	0x3F	/* Turn display on	  */
#define DISPLAY_OFF	0x3E	/* Turn display off	  */
//definições acesso Display kit express
#define DISPLAY_1 PORTBbits.RB0 //Liga desliga Q2
#define DISPLAY_2 PORTBbits.RB1 //Liga desliga Q3
#define DISPLAY_3 PORTBbits.RB2 //Liga desliga Q4
#define DISPLAY_4 PORTBbits.RB3 //Liga desliga Q5
//definicoes registros controle de timer0
#define TIMER_0_PRE0 T0CONbits.T0PS0 //PREESCALA BIT0 101 = 64:1
#define TIMER_0_PRE1 T0CONbits.T0PS1 //PREESCALA BIT1
#define TIMER_0_PRE2 T0CONbits.T0PS2 //PREESCALA BIT2
#define TIMER_0_PEN T0CONbits.PSA //PREESCALA HABILITA = 0
#define TIMER_0_EDG T0CONbits.T0SE //EDG DO CLOCK SOMENTE PARA CLOCK EXTERNO
#define TIMER_0_CS T0CONbits.T0CS // FONTE DE CLOCK 0 =  INTERNO
#define TIMER_0_8B T0CONbits.T08BIT //8 OU 16 BITS 1 = 8 BITS
#define TIMER_0_HAB T0CONbits.TMR0ON //HABILITA Timer 0 interupt habilita em 1
// definicoes controle de interrupcao
#define INTER_0_FLG	INTCONbits.TMR0IF //flag do DESABILITA INTERUPT DO TIMER 0 deve ser zerado na rotina de interupcao
#define INTER_0_HAB	INTCONbits.TMR0IE //HABILITA INTERUPT DO TIMER 0 por overflow
#define INTER_H_HAB INTCONbits.GIEH //HABILITA INTERUPT HIGHT PRIORIT
#define INTER_L_HAB INTCONbits.GIEL //HABILITA INTERUPT LOW PRIORIT
#define INTER_0_LPR INTCON2bits.TMR0IP //p/ LOW PRIORIT de TIME 0 = 0
//definicoes display tabela de caracteres vamos ver como ta

#define DIG_0	0xEE, 	//0
#define DIG_1	0x28, 	//1
#define DIG_2	0xCD,	//2
#define DIG_3	0x6D,	//3
#define DIG_4	0x2B,	//4
#define DIG_5	0x67,	//5
#define DIG_6	0xE7,	//6
#define DIG_7	0x2C,	//7
#define DIG_8	0xEF,	//8
#define DIG_9	0x6F,	//9
#define DIG_A	0xAF,	//A
#define DIG_B	0xE3,	//b
#define DIG_C	0xC6,	//C
#define DIG_D	0xE9,	//D
#define DIG_E	0xC7,	//E
#define DIG_F	0x87,	//F
#define DIG_PONTO	0x10,	//PONTO
#define DIG_GRAU	0x0F,	//GRAU
//definicoes LCD (alterar para o disp gráfico
#define DEF_MODE_SET_INC	0x06
#define DEF_MODE_DISP_ON	0x0C
#define DEF_MODE_SET_ADDR	0x80


#define DEF_TRISA 	0b00011111
#define DEF_TRISB 	0xF0
#define DEF_TRISC 	0b11111111
#define DEF_TRISD 	0b00000000
#define DEF_TRISE 	0b11111111

//definições dos LEDS do Kit Didatico

#define DEF_LED1 0x02 //=0000 0010
#define DEF_LED2 0x08 //=0000 1000
#define DEF_LED3 0x10 //=0001 0000
#define DEF_LED4 0x80 //=1000 0000
#define DEF_LED5 0x01 //=0000 0001
#define DEF_LED6 0x40 //=0100 0000
#define DEF_LED7 0x04 //=0000 0100
#define DEF_LED8 0x20 //=0010 0000
// DEFINICOES MATRIX DE LEITURA PORTA B
#define DEF_1_7 0x01 //=0000 0001
#define DEF_2_8 0x02 //=0000 0010
#define DEF_3_9 0x04 //=0000 0100
#define DEF_4__ 0X08 //=0000 1000
#define DEF_5_0 0x10 //=0001 0000
#define DEF_6__ 0x20 //=0010 0000
#define DEF_T2
#define Seg_0	0b11101110	;// 00 - RETORNA  0
#define Seg_1	0b00101000	; //01 - RETORNA 1
#define Seg_2	0b11001101	; //02 - RETORNA 2
#define Seg_3	0b01101101	; //03 - RETORNA 3
#define Seg_4	0b00101011	; //04 - RETORNA 4
#define Seg_5	0b01100111	; //05 - RETORNA 5
#define Seg_6	0b11100111	; //06 - RETORNA 6
#define Seg_7	0b00101100	; //07 - RETORNA 7
#define Seg_8	0b11101111	; //08 - RETORNA 8
#define Seg_9	0b01101111	; //09 - RETORNA 9
#define Seg_A	0b10101111	; //10 - RETORNA A
#define Seg_B	0b11100011	; //11 - RETORNA b
#define Seg_C	0b11000110	; //12 - RETORNA C
#define Seg_D	0b11101001	; //13 - RETORNA d
#define Seg_E	0b11000111	; //14 - RETORNA E
#define Seg_F	0b10000111	; //15 - RETORNA F
/////////////////////////////////////////////////////////////////////////////
//////// CONSTANTES ARRAYS  /////////////////////////////////////////////////
//////// CONSTANTES ARRAYS  /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
const rom unsigned char TAB_7_SEG[] =
{
	0xEE, 	//0
	0x28, 	//1
	0xCD, 	//2
	0x6D,	//3
	0x2B,	//4
	0x67,	//5
	0xE7,	//6
	0x2C,	//7
	0xEF,	//8
	0x6F,	//9
	0xAF,	//A
	0xE3,	//b
	0xC6,	//C
	0xE9,	//D
	0xC7,	//E
	0x87 //F
};
//definicoes caracter numérico
const rom unsigned char Tab_numero[] =
{
	0x30,//0
	0x31,
	0x32,
	0x33,
	0x34,
	0x35,
	0x36,
	0x37,
	0x38,
	0x39//9
};
// ------------------------------------------------------
// GLCD Picture name: fonte numerica grande
// GLCD Model: KS0108 128x64
// ------------------------------------------------------
const rom unsigned char fonte_16x8[] = {
0xFC,0xFE,0x86,0x46,0x26,0xFE,0xFC,0x00,
0x18,0x1C,0x0E,0xFE,0xFE,0x00,0x00,0x00,
0x0C,0x0E,0xC6,0xF6,0x7E,0x3E,0x0C,0x00,
0x0C,0x0E,0xC6,0xC6,0xE6,0x3C,0x18,0x00,
0xE0,0xF0,0xB8,0x9C,0xFE,0xFE,0xC0,0x00,
0x3C,0x7E,0xE6,0xC6,0xC6,0xC6,0x86,0x00,
0xFC,0xFE,0x06,0xC6,0xC6,0xC6,0x80,0x00,
0x0E,0xC6,0xE6,0xF6,0x7E,0x3E,0x1E,0x00,
0xBC,0xFE,0x66,0x66,0x66,0xFE,0xBC,0x00,
0x00,0x7C,0xFE,0xC6,0xC6,0xC6,0xFE,0xFC,
0x00,0x00,0x00,0x98,0x98,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
//
// Bmp nao implementado bandeira do sao paulo pode ser usado no lugar
//  do bmp do PIC_expert basta trocar na Funcao Main()
//
/*const rom unsigned char sao_paulo_bmp[1024] = {
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,247,251,243,243,241,225, 33,  1,  0,  0,128,192,192,192,192,
 128,132,158,191,255,255,255,255,255,255,255,255,255,127,127, 63,
  63, 63, 49, 56, 60,158,159,159,207,207,207,199,207,231,231,230,
 227,243,243,113,121,113, 57, 57, 57, 56, 60, 60, 30, 30, 30, 14,
  14, 15, 15,  7, 15,  7,135,135,131,131,195,193,193,  1,  1,  1,
   1,  1,255,255,255,255,  0,  0,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 127,127,127,127,127, 63, 57,152,156,158,159,143,207,207,199,231,
 227,231, 99,115,115,113, 57, 56, 60, 56, 28, 28, 28, 30, 14, 14,
  15,143,135,135,131,131,135,195,195,195,193,225, 97, 96, 96, 96,
  96,112, 48,  0,  0,  0,  0,  0,  0,252,252,252,252,252, 14, 14,
   6,  7,  7,  7,  3,  7,  3,  3, 31, 31, 31, 31, 15,  0,  0,  0,
   0,  0,255,255,255,255,  0,  0,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,127,127,127, 63, 63, 63, 63,159,
 159,143,207,207,207,199,231,227,243,243,113,115,113, 57, 60, 60,
  60, 30, 28, 14, 14, 15, 15,135,135,195,195,195,195,225, 97,112,
  48, 48, 48, 48, 56, 24,252,252,252,252,  0,  0,  0,  0,  0,  1,
 127,255,255,255,225,225, 97,113,113, 48, 48, 48, 48, 48,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  7,255,255,255,255,128,192,
 192,192,192,192,192,192,224,224,224,254,126,126,126,  0,  0,  0,
   0,  0,255,255,255,255,  0,  0,255,255,255,255,255,255,255,255,
 255,255,  1,  1, 24,249,248,252,252,254, 30, 30, 30, 15, 15,  7,
 135,  7,131,131,195,193,193,224,224,112,112, 48, 56, 24, 24, 28,
  28, 12,  0,  0,  0,  0,  0, 15,255,255,255,253,240, 48, 56, 24,
  24, 28, 28, 12, 14,  6,  7,  7,  7,  3,  2,  0,  0,  0,  0,  0,
   0, 15, 63, 63, 63, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
 128,  0,  0,  0,128,128,128,128,128,192,195,195,195,227,225,225,
 225,225,225,224,224,241,240,240,240,240,240,248,120,248,120,120,
 248,252,255,255,127, 63,  0,128,255,255,255,255,255,255,255,255,
 255,255,255,240,128,  0, 63,255,255,255,224,  0,  0,  0,  1, 15,
 255,255,255,251,225,225, 96,112,112, 56, 56, 28, 28, 12, 12,126,
 254,255,252,192,  0,  0,  0,  0,  0, 15, 63, 31, 31, 24,  0,  0,
   0,  0,128,128,192,192,192,192,224,224,224,240,240,240,240,248,
 248,248,248,252,252,252,252,252, 28, 30, 30, 14, 15, 15, 15, 15,
  15, 15, 15, 15, 15,  7,  7,  7,  7,  7,  7,  3,  3,  3,  3,  3,
   3,  3,  3,  1,  1,  1,  1,  0,  0,  0,  0,128,192,240,252,126,
  63, 15,  3,  1,  0, 12,  7,  7,255,255,255,255,255,255,255,255,
 255,255,255,255,255,248,  0,  7, 63,255,255,255,240,  0,  0,  0,
   0,  1,193,225, 96,112, 48, 56, 24, 28, 28, 14, 14,  6,135,135,
 195,195,193,225,224,240,240,248,120,120, 60, 60, 30, 30, 14, 14,
  15,  7,  7,  7,  3,  3,  3,  1,  1, 63,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,240,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,192,224,248,252, 63, 31,  7,  3,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,252,192,  0,  7,255,255,255,254,192,192,
 224,224,224,240,240,120,120,124, 60, 62, 30, 31, 15, 15,  7,  7,
   3,  3,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,240,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
 128,192,240,248,252, 63, 31,  7,  3,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,
 255,255,255,255,255,127,127,127,120,  0, 39,  7, 15, 31, 31, 63,
  63,125,121,248,240,240,224,192,192,192,128,128,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,254,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,248,252, 62,
  31, 15,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255
};
*/
//**************************************************************
// ------------------------------------------------------
// GLCD Fonte Caracteres Numericos
// GLCD Model: KS0108 128x64
// ------------------------------------------------------
/* System 5x8 (char #32 to #128) */
const rom unsigned char fonte_Nun[] = {
0x3e,0x51,0x49,0x45,0x3e,0x00, /* 0	*/
0x00,0x42,0x7f,0x40,0x00,0x00, /* 1 */
0x42,0x61,0x51,0x49,0x46,0x00, /* 2 */
0x21,0x41,0x45,0x4b,0x31,0x00, /* 3 */
0x18,0x14,0x12,0x7f,0x10,0x00, /* 4 */
0x27,0x45,0x45,0x45,0x39,0x00, /* 5 */
0x3c,0x4a,0x49,0x49,0x30,0x00, /* 6 */
0x01,0x71,0x09,0x05,0x03,0x00, /* 7 */
0x36,0x49,0x49,0x49,0x36,0x00, /* 8 */
0x06,0x49,0x49,0x29,0x1e,0x00, /* 9 */
0x00,0x60,0x60,0x00,0x00,0x00, /* . */
};
//**************************************************************
// ------------------------------------------------------
// GLCD Fonte Caracteres 8x6
// GLCD Model: KS0108 128x64
// ------------------------------------------------------
/* System 5x8 (char #32 to #128) */
const rom unsigned char fonte_8x6[] = {
0x00,0x00,0x00,0x00,0x00,0x00, /* Espace	0x20 */
0x00,0x00,0x4f,0x00,0x00,0x00, /* ! */
0x00,0x07,0x00,0x07,0x00,0x00, /* " */
0x14,0x7f,0x14,0x7f,0x14,0x00, /* # */
0x24,0x2a,0x7f,0x2a,0x12,0x00, /* 0x */
0x23,0x13,0x08,0x64,0x62,0x00, /* % */
0x36,0x49,0x55,0x22,0x20,0x00, /* & */
0x00,0x05,0x03,0x00,0x00,0x00, /* ' */
0x00,0x1c,0x22,0x41,0x00,0x00, /* ( */
0x00,0x41,0x22,0x1c,0x00,0x00, /* ) */
0x14,0x08,0x3e,0x08,0x14,0x00, /* // */
0x08,0x08,0x3e,0x08,0x08,0x00, /* + */
0x50,0x30,0x00,0x00,0x00,0x00, /* , */
0x08,0x08,0x08,0x08,0x08,0x00, /* - */
0x00,0x60,0x60,0x00,0x00,0x00, /* . */
0x20,0x10,0x08,0x04,0x02,0x00, /* / */
0x3e,0x51,0x49,0x45,0x3e,0x00, /* 0		0x30 */
0x00,0x42,0x7f,0x40,0x00,0x00, /* 1 */
0x42,0x61,0x51,0x49,0x46,0x00, /* 2 */
0x21,0x41,0x45,0x4b,0x31,0x00, /* 3 */
0x18,0x14,0x12,0x7f,0x10,0x00, /* 4 */
0x27,0x45,0x45,0x45,0x39,0x00, /* 5 */
0x3c,0x4a,0x49,0x49,0x30,0x00, /* 6 */
0x01,0x71,0x09,0x05,0x03,0x00, /* 7 */
0x36,0x49,0x49,0x49,0x36,0x00, /* 8 */
0x06,0x49,0x49,0x29,0x1e,0x00, /* 9 */
0x00,0x36,0x36,0x00,0x00,0x00, /* : */
0x00,0x56,0x36,0x00,0x00,0x00, /* ; */
0x08,0x14,0x22,0x41,0x00,0x00, /* < */
0x14,0x14,0x14,0x14,0x14,0x00, /* = */
0x00,0x41,0x22,0x14,0x08,0x00, /* > */
0x02,0x01,0x51,0x09,0x06,0x00, /* ? */
0x3e,0x41,0x5d,0x55,0x1e,0x00, /* @		0x40 */
0x7e,0x11,0x11,0x11,0x7e,0x00, /* A */
0x7f,0x49,0x49,0x49,0x36,0x00, /* B */
0x3e,0x41,0x41,0x41,0x22,0x00, /* C */
0x7f,0x41,0x41,0x22,0x1c,0x00, /* D */
0x7f,0x49,0x49,0x49,0x41,0x00, /* E */
0x7f,0x09,0x09,0x09,0x01,0x00, /* F */
0x3e,0x41,0x49,0x49,0x7a,0x00, /* G */
0x7f,0x08,0x08,0x08,0x7f,0x00, /* H */
0x00,0x41,0x7f,0x41,0x00,0x00, /* I */
0x20,0x40,0x41,0x3f,0x01,0x00, /* J */
0x7f,0x08,0x14,0x22,0x41,0x00, /* K */
0x7f,0x40,0x40,0x40,0x40,0x00, /* L */
0x7f,0x02,0x0c,0x02,0x7f,0x00, /* M */
0x7f,0x04,0x08,0x10,0x7f,0x00, /* N */
0x3e,0x41,0x41,0x41,0x3e,0x00, /* O */
0x7f,0x09,0x09,0x09,0x06,0x00, /* P		0x50 */
0x3e,0x41,0x51,0x21,0x5e,0x00, /* Q */
0x7f,0x09,0x19,0x29,0x46,0x00, /* R */
0x26,0x49,0x49,0x49,0x32,0x00, /* S */
0x01,0x01,0x7f,0x01,0x01,0x00, /* T */
0x3f,0x40,0x40,0x40,0x3f,0x00, /* U */
0x1f,0x20,0x40,0x20,0x1f,0x00, /* V */
0x3f,0x40,0x38,0x40,0x3f,0x00, /* W */
0x63,0x14,0x08,0x14,0x63,0x00, /* X */
0x07,0x08,0x70,0x08,0x07,0x00, /* Y */
0x61,0x51,0x49,0x45,0x43,0x00, /* Z */
0x00,0x7f,0x41,0x41,0x00,0x00, /* [ */
0x02,0x04,0x08,0x10,0x20,0x00, /* \ */
0x00,0x41,0x41,0x7f,0x00,0x00, /* ] */
0x04,0x02,0x01,0x02,0x04,0x00, /* ^ */
0x40,0x40,0x40,0x40,0x40,0x00, /* _ */
0x00,0x00,0x03,0x05,0x00,0x00, /* `		0x60 */
0x20,0x54,0x54,0x54,0x78,0x00, /* a */
0x7F,0x44,0x44,0x44,0x38,0x00, /* b */
0x38,0x44,0x44,0x44,0x44,0x00, /* c */
0x38,0x44,0x44,0x44,0x7f,0x00, /* d */
0x38,0x54,0x54,0x54,0x18,0x00, /* e */
0x04,0x04,0x7e,0x05,0x05,0x00, /* f */
0x08,0x54,0x54,0x54,0x3c,0x00, /* g */
0x7f,0x08,0x04,0x04,0x78,0x00, /* h */
0x00,0x44,0x7d,0x40,0x00,0x00, /* i */
0x20,0x40,0x44,0x3d,0x00,0x00, /* j */
0x7f,0x10,0x28,0x44,0x00,0x00, /* k */
0x00,0x41,0x7f,0x40,0x00,0x00, /* l */
0x7c,0x04,0x7c,0x04,0x78,0x00, /* m */
0x7c,0x08,0x04,0x04,0x78,0x00, /* n */
0x38,0x44,0x44,0x44,0x38,0x00, /* o */
0x7c,0x14,0x14,0x14,0x08,0x00, /* p		0x70 */
0x08,0x14,0x14,0x14,0x7c,0x00, /* q */
0x7c,0x08,0x04,0x04,0x00,0x00, /* r */
0x48,0x54,0x54,0x54,0x24,0x00, /* s */
0x04,0x04,0x3f,0x44,0x44,0x00, /* t */
0x3c,0x40,0x40,0x20,0x7c,0x00, /* u */
0x1c,0x20,0x40,0x20,0x1c,0x00, /* v */
0x3c,0x40,0x30,0x40,0x3c,0x00, /* w */
0x44,0x28,0x10,0x28,0x44,0x00, /* x */
0x0c,0x50,0x50,0x50,0x3c,0x00, /* y */
0x44,0x64,0x54,0x4c,0x44,0x00, /* z */
0x08,0x36,0x41,0x41,0x00,0x00, /* { */
0x00,0x00,0x77,0x00,0x00,0x00, /* | */
0x00,0x41,0x41,0x36,0x08,0x00, /* } */
0x08,0x08,0x2a,0x1c,0x08,0x00, /* <- */
0x08,0x1c,0x2a,0x08,0x08,0x00, /* -> */
0xff,0xff,0xff,0xff,0xff,0x00, /* 	 	0x80 */
};
// ------------------------------------------------------
// GLCD Picture name: P I C expert.bmp
// GLCD Model: KS0108 128x64
// ------------------------------------------------------

const rom unsigned char PIC_expert_bmp[1024] = {
 253,  1,  3,231,239,207,207,143, 31, 63,127,255,255,255,255,255,
 127, 63, 63,127,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255, 31, 31,255,255,255,255,255,
 255,  0,  0, 63, 63,127,127,127, 63,  0,  0,129,255,255,255,127,
 126, 60, 61,254,255,255,255,255,255,255,255,127,127,127,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,249,249,  1,
  13,  1,249,249,249,249,249,241,193,131, 31,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,127,127,127,127,127,255,255,255,255,255,255, 63, 63,159, 31,
  63, 31, 15, 47,143,255,255,231,  3,  8,  0,241,253,255,255,255,
  63,  0,  0,127,255,254,254,254,254,254,255,255,255,255,255,255,
 254,  0,  0,255,255,255,255, 15,  3,  0,252,254,254,252,240,228,
 225,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  0,
   0, 68,199,199,199,215, 16,  0,255,255,255,255,255,255,255,249,
 249,228,129,  9, 29, 63,141,193,241,249,253,255,255,255,251,241,
   4,  0,248,252,252,248,240,  1,  3, 31,255,255,255,255,  7,  1,
  48,188,158,158,158,152,128,129,223,255,255,255,255,  0,  0,  0,
 252,255,255,255,255,255,255,255,  0,  0,  0,127, 31,255,255,255,
 255,254,252,248,249,255,255,255,255,255,255,255,255,255,255,207,
 207,192,192,207,223,255,255,252,224,192,135, 31, 31, 63,159,143,
 231,255,255,255,255,255,255,255,255,255,255,255,255,127, 63,  0,
 192,  0,127,127,127,127, 62, 62,223,  7,131,247,255,255,255,127,
  63, 31,  7, 96,248,240, 65,  3, 15, 63,127,127,255,255,255,255,
   0,  0, 31, 63, 63, 63, 15,128,192,248,255,255,255,255,240,192,
 131, 15, 31, 31,159,143,199,227,251,255,255,255,207,192,208,192,
 231,255,255,255,255,255,255,255,254,252,249,252,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,254,
 254,254,254,254,254,254,254,254,254,254,255,255,255,255,255,254,
 254,254,254,254,255,255,254,254,254,254,254,255,255,255,231,227,
 224,224,227,247,255,255,255,255,255,255,255,255,255,255,255,255,
 255,127, 63, 63, 63,127,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
   7, 67, 17,252,252,252,248,241,  1,  3,191,255,255,255,255, 15,
   3,129,249,252,252,248,241,  3,  7, 63,255,255,255,255,255,251,
 243,251,241,  4,  0,255,255,255,255,255,255,255,255,127,  7,  1,
 240,252,254,255,254,252,  0,  1, 15,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 254,254,254, 63, 31, 15,135,192,224,248,255,255,255,255,  1,  0,
   0,255,255,255,255,255,255,254,  0,  0,255,255,255,255,255,255,
 255,255,255,  0,  0,255,255,255,255,255,255,255,255,128,  0,  0,
 255,255,255,255,255,255, 15,  0,  0,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 63,
  15, 67, 80, 92, 94, 95, 95, 95, 71,  1,241,255,255,255,255,224,
 192,  3, 31, 63,127, 63, 15,128,192,248,255,255,255,255,255,255,
  63, 63, 31, 32, 32, 31, 31,159,191,255,255,255,255,255,248,224,
 195,143,159,159,207,195,224,248,254,255,255,255,255,255,255,255,
 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
};

// declaracao de variaveis globais
/////////////////////////////////////////////////////////////////////////////
//////// VARIAVEIS GLOBAIS  /////////////////////////////////////////////////
//////// VARIAVEIS GLOBAIS  /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

unsigned char portd_ant = 0;
unsigned int k,j;
unsigned int k1;
unsigned char x,y;
unsigned char T_mili = 0;
unsigned char T_inc = 0;
unsigned int T_int = 0;
unsigned char T_seg0 = 0;
unsigned char T_seg1 = 0;
unsigned char T_min0 = 0;
unsigned char T_min1 = 0;
unsigned char T_hor0 = 0;
unsigned char T_hor1 = 0;
unsigned char T_acerto = 0;
unsigned char timer_seg[20];
unsigned char T = 0;
unsigned char M_portA,T_pos;
unsigned char P_hora[9];
unsigned char Palavra1[21] = "                    ";


void main (void);
void Inic_PIC_Register(void); //Inicialisa registradores do PIC


//INICIO MAIN ===============================######################## I N I C I O ##################################=============================== INICIO MAIN
//INICIO MAIN ===============================######################## I N I C I O ##################################=============================== INICIO MAIN
//INICIO MAIN ===============================######################## I N I C I O ##################################=============================== INICIO MAIN
//INICIO MAIN ===============================######################## I N I C I O ##################################=============================== INICIO MAIN

void main(void)
{
    //clock_int_48MHz();
	unsigned char col,lin,len,font,u,M_portA;
	unsigned char Menu_p[] = "<< PIC EXPERT MENU >>Rotina 1  Rotina 2  Rotina 3  Rotina 4  Rotina 5  Acerto Relogio  ";
	unsigned char Aponta[] = ">> ";
	Inic_PIC_Register();
	Glcd_Inic();
	Glcd_Pict(&PIC_expert_bmp[0]);
	for(u=0;u<100;u++)Delay_0(250);
	Glcd_liga_desl(desl);
	Glcd_Limpa_Tela();
	len = 21;//quantos caracteres 1-21 para fonte 6x8
	lin = 0;// pagina de impressao 0-7
	col = 0;//0-127 posicao horizontal da impressao (em pontos na tela)
	font = 0;//por enquanto so fonte 0
	Glcd_String(&Menu_p[0],len,lin,col,font);
	Glcd_String(&Menu_p[21],10,2,8,0);
	Glcd_String(&Menu_p[31],10,3,8,0);
	Glcd_String(&Menu_p[41],10,4,8,0);
	Glcd_String(&Menu_p[51],10,5,8,0);
	Glcd_String(&Menu_p[61],10,6,8,0);
	Glcd_String(&Menu_p[71],15,7,8,0);
	Glcd_liga_desl(liga);
	T_seg0 = 0;
	T_seg1 = 3;
	T_min0 = 7;
	T_min1 = 5;
	T_hor0 = 2;
	T_hor1 = 2;
	T_pos = 2;
	INTER_0_HAB = 0;
	Glcd_String(&Aponta[0],1,T_pos,1,0);
	TIMER_0_HAB =1;
	INTER_0_HAB = 1;
	INTER_L_HAB = 1;
	while(1)
	{
		if(T_acerto == 1)
		{
			Glcd_Hora(1,35);
			T_acerto = 0;
		}
		if((PORTA | 0xE1)!= 0xFF)
		{
			INTER_L_HAB = 0;
			M_portA = PORTA;
			if((M_portA | DEF_A4_DIP) != 0xFF)
			{
				if(T_pos > 2)
				{
					Glcd_String(&Aponta[2],1,T_pos,1,0);
					T_pos--;
					Glcd_String(&Aponta[0],1,T_pos,1,0);
				}
			}
			if((M_portA | DEF_A2_DIP) != 0xFF)
			{
				if(T_pos < 7)
				{
					Glcd_String(&Aponta[2],1,T_pos,1,0);
					T_pos++;
					Glcd_String(&Aponta[0],1,T_pos,1,0);
				}
			}
			if((M_portA | DEF_A1_DIP) != 0xFF)
			{
				switch(T_pos-1)
				{
					case 1:
						Rotina1();
						break;
					case 2:
						Rotina2();
						break;
					case 3:
						Rotina3();
						break;
					case 4:
						Rotina4();
						break;
					case 5:
						Rotina5();
						break;
					case 6:
						Acerto_Relogio();
						break;
				}

			}
			if((M_portA | DEF_A3_DIP) != 0xFF)
			{
				Nop();
			}
			Delay_0(250);
			while((PORTA | 0xE1)!= 0xFF)Nop();
			Delay_0(250);
			while((PORTA | 0xE1)!= 0xFF)Nop();
			Delay_0(250);
			while((PORTA | 0xE1)!= 0xFF)Nop();
			INTER_0_HAB = 1;
		}
	}
}
//FIM MAIN ================================#######################################################################============================== FIM MAIN
//FIM MAIN ================================#######################################################################============================== FIM MAIN
//FIM MAIN ================================#######################################################################============================== FIM MAIN
//FIM MAIN ================================#######################################################################============================== FIM MAIN
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////
// Esta rotina e responsavel pelo acerto do relogio usando as dips de direcao
// seta para direita (sw4)segue para os digitos da direta
// seta para esquerda(sw2) segue para os digitos da esquerda e sai da rotina
// seta para cima (sw1)incremenda o digito
// seta para baixo (sw3)
//////////////////////////////////////////////////////////////////////////////////////////
//
void Acerto_Relogio(void)
{
	unsigned char T_dig = 10;
	unsigned char Mporta = 0;
	INTER_L_HAB = 0;
	Delay_0(250);
	while((PORTA | 0xE1)!= 0xFF)Nop();
	Delay_0(250);
	while((PORTA | 0xE1)!= 0xFF)Nop();
	Delay_0(250);
	INTER_L_HAB = 0;
	while(T_dig != 0)
	{
		if(T_dig == 10)T_dig = 1;
		if((PORTA | 0xE1)!= 0xFF)
		{
			Mporta = PORTA;
			if((Mporta | DEF_A4_DIP) != 0xFF)
			{
				switch(T_dig)
				{
					case 1:
						if(T_hor1 < 2)T_hor1++;
						break;
					case 2:
						if(T_hor1 < 2)
						{
							if(T_hor0 < 9)T_hor0++;
						}
						else
						{
							if(T_hor0 < 3)T_hor0++;
						}
						break;
					case 3:
						if(T_min1 < 5)
							T_min1++;
						break;
					case 4:
						if(T_min0 < 9)
							T_min0++;
						break;
					case 5:
						if(T_seg1 < 5)
							T_seg1++;
						break;
				}
				Glcd_Hora(1,35);
			}
			if((Mporta | DEF_A2_DIP) != 0xFF)
			{
				switch(T_dig)
				{
					case 1:
						if(T_hor1 > 0)
							T_hor1--;
						break;
					case 2:
						if(T_hor0 > 0)
							T_hor0--;
						break;
					case 3:
						if(T_min1 > 0)
							T_min1 --;
						break;
					case 4:
						if(T_min0 > 0)
							T_min0--;
						break;
					case 5:
						if(T_seg1 > 0)
							T_seg1--;
						break;
				}
				Glcd_Hora(1,35);
			}
			if((Mporta | DEF_A3_DIP) != 0xFF)
			{
				if(T_dig > 0)
					T_dig--;
			}
			if((Mporta | DEF_A1_DIP) != 0xFF)
			{
				if(T_dig < 5)
					T_dig++;
			}
			Delay_0(250);
			while((PORTA | 0xE1)!= 0xFF)Nop();
			Delay_0(250);
			while((PORTA | 0xE1)!= 0xFF)Nop();
			Delay_0(250);
		}
	}
	INTER_L_HAB = 1;
}
//////////////////////////////////////////////////////////////////////////////////////////
// Rotinas a serem codificadas
//
//////////////////////////////////////////////////////////////////////////////////////////
//

void Rotina1(void)
{
	unsigned char Menu_p[] = "Rotina 1";
	Glcd_String(&Menu_p[0],8,4,65,0);
}
void Rotina2(void)
{
	unsigned char Menu_p[] = "Rotina 2";
	Glcd_String(&Menu_p[0],8,4,65,0);
}
void Rotina3(void)
{
	unsigned char Menu_p[] = "Rotina 3";
	Glcd_String(&Menu_p[0],8,4,65,0);
}
void Rotina4(void)
{
	unsigned char Menu_p[] = "Rotina 4";
	Glcd_String(&Menu_p[0],8,4,65,0);
}
void Rotina5(void)
{
	unsigned char Menu_p[] = "Rotina 5";
	Glcd_String(&Menu_p[0],8,4,65,0);
}
void Rotina6(void)
{
	unsigned char Menu_p[] = "Rotina 6";
	Glcd_String(&Menu_p[0],8,4,65,0);
}
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
// Mostra hora no Glcd em  Lin =  linha do LCD de 0 a 7     col = coluna em doc pict de 0 a 127//
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Glcd_Hora(unsigned char lin,unsigned char col)
{
	INTER_L_HAB = 0;
	Delay_0(250);
	P_hora[0] = Tab_numero[T_hor1];
	P_hora[1] = Tab_numero[T_hor0];
	P_hora[2] = L_2pts;
	P_hora[3] = Tab_numero[T_min1];
	P_hora[4] = Tab_numero[T_min0];
	P_hora[5] = L_2pts;
	P_hora[6] = Tab_numero[T_seg1];
	P_hora[7] = Tab_numero[T_seg0];
	Glcd_String(&P_hora[0],8,lin,col,0);
	INTER_L_HAB = 1;
}
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
// Limpa tela do GLCD//
//////////////////////////////////////////////////////////////////////////////////////////////
//

void Glcd_Limpa_Tela()
{
	unsigned char lado,page,col;
	INTER_L_HAB = 0;
	Glcd_liga_desl(desl);
	for(lado=1;lado<3;lado++)
	{
		if(lado == 1)Glcd_Left();
		if(lado == 2)Glcd_Right();
		for(page=0;page<8;page++)
		{
			Glcd_Page(page);
			LCD_BIT_RW = 0; // Escrita
			LCD_BIT_RS = 1;// modo Dados
			for(col=0;col<64;col++)
			{
					PORTB = 0x00;
					Delay_0(5);
					LCD_BIT_E = 1;
					Delay_0(5);
					LCD_BIT_E = 0;
					Delay_0(5);
			}
		}
	}
	Glcd_liga_desl(liga);
	INTER_L_HAB = 1;
}
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
// Mostra Palavra no GLCD cujo endereco e passado como ponterio do primeiro caracter da array" [0] , tamanho em
// numero de caracteres (max 21), linha (0-7), coluna (0-127), fonte nao implementado //
//////////////////////////////////////////////////////////////////////////////////////////////
//

void Glcd_String(unsigned char *p_str, unsigned char s_tamanho, unsigned char s_linha, unsigned char s_coluna, unsigned char s_fonte)
{
	unsigned char l,f_coluna,c_coluna;
	int add_car,cod_car;
	INTER_H_HAB = 0;
	INTER_L_HAB = 0;
	s_tamanho = s_tamanho * 6;
	if(s_linha > 7) s_linha = 7;
	if(s_coluna > 127)s_coluna = 127;
	Glcd_Page(s_linha);
	if(s_tamanho > (128 - s_coluna))
	{
		s_tamanho = (128 - s_coluna);
	}
	if(s_coluna < 64)
	{
		Glcd_Left();
		Glcd_Comand(Y_ADRESS | s_coluna);
	}
	else
	{
		Glcd_Right();
		Glcd_Comand(Y_ADRESS | (s_coluna - 64));
	}

	LCD_BIT_RW = 0; // Escrita
	LCD_BIT_RS = 1;// modo Dados
	f_coluna = s_tamanho+s_coluna;
	while(s_coluna < f_coluna)
	{
		cod_car = *p_str;//carrega o codigo do caracter desejado
		add_car = (cod_car * 6) - 0xC0;//encontra o indice na tabela de fontes da letra desejada e coloca em add_car
		if(add_car < 0)add_car = 0;
		for(c_coluna=0;c_coluna<6;c_coluna++)
		{
			if(s_coluna == 64)
			{
				Glcd_Right();
				Glcd_Page(s_linha);
			}
			LCD_BIT_RW = 0; // Escrita
			LCD_BIT_RS = 1;// modo Dados
			PORTB = fonte_8x6[add_car];//imprime a fonte com indice add_car
			Delay_0(5);
			LCD_BIT_E = 1;
			Delay_0(5);
			LCD_BIT_E = 0;
			Delay_0(5);
			add_car++;
			s_coluna++;
		}
		p_str++;
		if(s_coluna == f_coluna)Glcd_liga_desl(liga);
	}
	INTER_L_HAB = 1;
	INTER_H_HAB = 1;
}
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mostra uma figura BMP no GLCD deve ser passado como argumento
// do endereco do primeiro elemento da constant array[0] que ja tenha sido definida com 1024 bytes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void Glcd_Pict(const rom unsigned char *pict_)
{
	const rom unsigned char *p_pict;
	unsigned char CS,x,i;
	INTER_L_HAB = 0;
	k = 0;
	CS = 0;
	Glcd_liga_desl(desl);
	while(1)
	{
			Glcd_Left();
			p_pict = pict_;
			for(x=0;x<8;x++)
			{
				Glcd_Page(x);
				LCD_BIT_RW = 0; // Escrita
				LCD_BIT_RS = 1;// modo Dados
				for(y=0;y<64;y++)
				{
					PORTB = *p_pict;
					p_pict++;
					Delay_0(5);
					LCD_BIT_E = 1;
					Delay_0(5);
					LCD_BIT_E = 0;
					Delay_0(5);
				}
				p_pict += 64;
			}
			Glcd_Right();
			p_pict = pict_;
			for(x=0;x<8;x++)
			{
				p_pict += 64;
				Glcd_Page(x);
				LCD_BIT_RW = 0; // Escrita
				LCD_BIT_RS = 1;// modo Dados
				for(y=0;y<64;y++)
				{
					PORTB = *p_pict;
					p_pict++;
					Delay_0(5);
					LCD_BIT_E = 1;
					Delay_0(5);
					LCD_BIT_E = 0;
					Delay_0(5);
				}
			}
			break;
	}
	Glcd_liga_desl(liga);
	INTER_L_HAB = 1;
}
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
// liga GLCD 1 liga 0 desliga isso e feito um lado por vez
// portanto o lado deve estar previamente selecionado
//////////////////////////////////////////////////////////////////////////////////////////////
//

void Glcd_liga_desl(unsigned char lig_desl)
{
	INTER_L_HAB = 0;
	Glcd_Left();
	if(lig_desl == 1)
	{
		PORTB = DISPLAY_ON;
	}
	else
	{
		PORTB = DISPLAY_OFF;
	}
	Delay_0(10);
	LCD_BIT_E = 1;
	Delay_0(10);
	LCD_BIT_E = 0;
	Delay_0(10);
	Glcd_Right();
	if(lig_desl == 1)
	{
		PORTB = DISPLAY_ON;
	}
	else
	{
		PORTB = DISPLAY_OFF;
	}
	Delay_0(10);
	LCD_BIT_E = 1;
	Delay_0(10);
	LCD_BIT_E = 0;
	Delay_0(10);
	INTER_L_HAB = 1;
}
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
// qualquer comando conhecido (byte) pode ser passado ao glcd por essa funcao//
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Glcd_Comand(unsigned char cmd)
{
	INTER_L_HAB = 0;
	LCD_BIT_RS = 0;// modo comando
	LCD_BIT_RW = 0; // Escrita
	PORTB = cmd;//desliga display
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	INTER_L_HAB = 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// qualquer Dado (byte) pode ser passado ao glcd por essa funcao o Lado do glcd deve estar previamente selecionado //
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Glcd_Data(unsigned char data)
{
	INTER_L_HAB = 0;
	LCD_BIT_RS = 1;// modo comando
	LCD_BIT_RW = 0; // Escrita
	PORTB = data;//desliga display
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	INTER_L_HAB = 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// muda selecao de lado para esquerdo
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Glcd_Left(void)
{
	INTER_L_HAB = 0;
	LCD_BIT_RS = 0;// modo comando
	LCD_BIT_RW = 0; // Escrita
	LCD_BIT_CS1 = 1;
	LCD_BIT_CS2 = 0;
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	PORTB = START_LINE;//inicia no primeiro endereco DDRAM
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	PORTB = Y_ADRESS;//inicia na primeira coord y (COLUNA 0)
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	INTER_L_HAB = 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// muda selecao de lado para direto
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Glcd_Right(void)
{
	INTER_L_HAB = 0;
	LCD_BIT_RS = 0;// modo comando
	LCD_BIT_RW = 0; // Escrita
	LCD_BIT_CS1 = 0;
	LCD_BIT_CS2 = 1;
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	PORTB = START_LINE;//inicia no primeiro endereco DDRAM
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	PORTB = Y_ADRESS;//inicia na primeira coord y (COLUNA 0)
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
	INTER_L_HAB = 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// muda pagina 1-7 Sao 7 linhas de 1 byte de altura onde os caracteres vao aparecer
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Glcd_Page(unsigned char page)
{
	LCD_BIT_RS = 0;// modo comando
	LCD_BIT_RW = 0; // Escrita
	if(page > 7)page = 7;
	PORTB = ( page | X_ADRESS);//paginacao conforme valor de x
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// rotinha de atraso //
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Delay_0(unsigned char D)
{
	unsigned char n, n1;
	for(n = 0; n < D; n++)
	{
		for(n1 = 0; n1 < 40; n1++)
		{
			Nop();
			ClrWdt();
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Rotina de interupcao de baixa prioridade
// onde esta implementado o relogio baseado no iterupt 0 overflow
// tambem pode ser usado para temporizadore colocando um valor nas variaveis timer_seg[x]
// essa rotina zera constantemente essas variaveis podendo ser usado para contar tempo
// testando se a variavel timer_seg chegou a 0.
// A precisao do relogio pode ser melhorada alterando o valor de Acerto para mais ou para menos
//////////////////////////////////////////////////////////////////////////////////////////////
//

#pragma interruptlow InterruptHandlerLow
void InterruptHandlerLow(void)
{
	unsigned char TM1,TM2;
	unsigned int Acerto;
	Acerto = 1500;
	T_int++;
	if(T_mili > 0)T_mili--;
	if(INTER_0_FLG)
	{
		T_int++;
		if(T_int > Acerto)
		{
			T_int = 0;
			T_inc = 1;
			T_seg0++;
			for(TM1=1;TM1 < 20;TM1++)
			{
				if(timer_seg[TM1] > 0)
					timer_seg[TM1]--;
			}
			T_acerto = 1;
			if(T_seg0 > 9)
			{
				T_seg0 = 0;
				T_seg1++;
			}
			if(T_seg1 > 5)
			{
				T_seg1 = 0;
				T_seg0 = 0;
				T_min0++;
			}
 			if(T_min0 > 9)
			{
				T_min0 = 0;
				T_min1++;
			}
 			if(T_min1 > 5)
			{
				T_min1 = 0;
				T_min0 = 0;
				T_seg0 = 0;
				T_seg1 = 0;
				T_hor0++;
			}
 			if(T_hor0 > 4)
			{
				if(T_hor1 == 2)
				{
					T_hor0 = 0;
					T_hor1 = 0;
					T_min1 = 0;
					T_min0 = 0;
					T_seg0 = 0;
					T_seg1 = 0;
				}
			}
			if(T_hor0 > 9)
			{
	 			if(T_hor1 == 1)
				{
					T_hor1++;
					T_hor0 = 0;
					T_min1 = 0;
					T_min0 = 0;
					T_seg0 = 0;
					T_seg1 = 0;
				}
			}
		}
	}
	INTER_0_FLG = 0;
}

//*****************************************************************************
// Alta prioridade interrupt routine
//*****************************************************************************
//#pragma code
#pragma interrupt InterruptHandlerHigh
void InterruptHandlerHigh(void)
{
	Nop();
}
//////////////////////////////////////////////////////////////////////////////////////////////
// inicializa o GLCD
//////////////////////////////////////////////////////////////////////////////////////////////
//

void Glcd_Inic(void)
{
	LCD_BIT_E = 0;
	LCD_BIT_RS = 0;// modo comando
	LCD_BIT_RW = 0; // Escrita
	LCD_BIT_CS1 = 0; // Seleciona LEFT SIDE
	LCD_BIT_CS2 = 0; // Seleciona RIGHT SIDE
	LCD_BIT_RST = 1; //Reset (nao)
	Delay_0(5);
	LCD_BIT_RST = 0; //Reset (nao)
	Delay_0(5);
	LCD_BIT_RST = 1; //Reset (nao)
	Delay_0(5);
	PORTB = DISPLAY_OFF;//desliga display
	Delay_0(5);
	LCD_BIT_E = 1;
	Delay_0(5);
	LCD_BIT_E = 0;
	Delay_0(5);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// inicializa o PIC
// conforme configuracao da placa PIC_Expert, interupt  e timer 0 implementado
//////////////////////////////////////////////////////////////////////////////////////////////
//
void Inic_PIC_Register(void)
{
	RCON = 0X80;// LIMPA REGISTRO DE RESET
	ADCON1 = 0xF;// CONFIGURA TODAS AS PORTAS ANALOGICAS COMO I/O
	CMCON = 0x0F;//( DESABILITAR COMPARADOR)
	LATA = 0;
	TRISA = 0b11111111;
    T0CON = 0b11000101;// timer ativo, 8 bits,clock interno, preescale 1:64
	LATB = 0;//LIMPA O LATCH DA PORTA B
	TRISB = 0;// tudo Saida
	LATD = 0;
	TRISD = 0x00;//PORTA D TUDO SAIDA
	// enderecando
	INTER_L_HAB = 1;//Interup LOW habilitada
	INTER_H_HAB = 1;//Interup HIGHT habilitada
	INTER_0_HAB = 1;//Interup LOW habilitada
	TIMER_0_HAB = 1;//Interupt 0 habilitada POR OVERFLOW
	INTER_0_LPR = 0;//TIME 0 INT LOW PRIORIT
}
