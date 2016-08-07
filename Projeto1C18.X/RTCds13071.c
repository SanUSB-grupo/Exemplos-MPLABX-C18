//O Firmware comprova a gravação e leitura na EEPROM interna da placa SanUSB com MPLABX C18
//http://www.youtube.com/watch?v=u1HwZLRcrYQ e http://www.youtube.com/watch?v=zeqS6A5-I08
#include "SanUSB48.h"
#include<i2c.h>//Biblioteca de funções I2C.
#include"biblioteca_lcd_2x16.h"//Biblioteca LCD do Noboru.

#pragma interrupt interrupcao
void interrupcao() {}

#define ledverde PORTAbits.RA5//Pino 35 do PIC18F4550.
#define ledvermelho PORTAbits.RA4//Pino 35 do PIC18F4550.
//******************************************************************************
//VARIAVEIS GLOBAIS ************************************************************
unsigned char ucHora; // Armazena Hora.
unsigned char ucMinuto; // Armazena Minuto.
unsigned char leitura; // Armazena Segundo.
unsigned char ucDia; // Armazena Dia.
unsigned char ucMes; // Armazena Mes.
unsigned char ucAno; // Armazena Ano.
unsigned char ucDia_Semana; // Armazena Dia da Semana.
unsigned char buffer[16]; //Define o tipo de matriz para escrever no LCD.
//PROTÓTIPOS DA FUNÇÕES ********************************************************
void write_RTC_I2c(void);
void read_RTC_I2c(unsigned int pos_memoria);
//******************************************************************************
void write_RTC_I2c() {
StartI2C(); // Inicializa a comunicação I2c
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0xD0); // End. fixo para DS1307: 1101000X, onde x = 0 é para gravação.
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x00); // End. onde começa a programação do relógio, end. dos segundos.
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x00); // Inicializa com 00 segundos.
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x08); // Inicializa com 8 minutos.
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x08); // Inicializa com 08:00hs (formato 24 horas).
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x04); // Inicializa com terça
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x17); // Inicializa com dia 17
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x04); // Inicializa com mês 04
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0x13); // Inicializa com ano 13
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
StopI2C(); // Finaliza a comunicação I2c
}
void read_RTC_I2c(unsigned int pos_memoria) {
StartI2C();
WriteI2C(0xD0); //address of DS1307.
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(pos_memoria); // Position the address pointer to 0.
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
RestartI2C();
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
WriteI2C(0XD1); // Direction bit set to read.
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
leitura = ReadI2C();
IdleI2C(); //Verifica e aguarda até o barramento I2C estar disponível.
while (SSPCON2bits.PEN);
StopI2C();
}
void main(void) {
//ADCON1 = 0b00000111; //Todas as portas A do PIC como digital(desliga os conversores a/d).
TRISA = 0b00001111; //RA0 a RA4 - Entrada e RA5 a RA6 - Saída.
TRISB = 0b11100111; //RB0, RB1,RB2,RB5,RB6 e RB7 Entradas e RB3 a RB4 - Saidas.
TRISC = 0b10111111; //RC0 a RC5 e RC7 - Entradas e RC6 - Saída.
TRISD = 0b00000000; //RD0 a RD7 = Saídas.
//TRISE = 0b00000000; //RE0 a RE2 - Saídas.
ledvermelho = 1; //Estado "1" é led apagado.
DDRBbits.RB1 = 1; // Set SCL (PORTB,1) pin to input
DDRBbits.RB0 = 1; // Set SDA (PORTB,0) pin to input
OpenI2C(MASTER, SLEW_OFF); //Modo master com velocidade de 100Khz.
SSPADD = 49; //Taxa de comunicação de 100khz.
//write_RTC_I2c();//Apenas qdo não tem nada no RTC e está sem Bateria.

//LCD***********************************************************************
lcd_inicia(0x28, 0x0F, 0x06); //Inicializa o display LCD an com 4 linhas de dados
lcd_LD_cursor(0); //Desliga o cursor.
lcd_limpa_tela();
lcd_posicao(1, 1); //Posicina Linha 1, Coluna 1.
imprime_string_lcd("EEPROM - DS-1307"); //Imprime uma string.

//**************************************************************************

while (1) {//Loop infinito
//Leitura de Posição da Hora no DS-1307.
read_RTC_I2c(0x02);
lcd_posicao(2, 1);
sprintf(buffer, "%02X ", leitura);
imprime_buffer_lcd(buffer, 16);
//Leitura de Posição de Minuto no DS-1307.
read_RTC_I2c(0x01);
lcd_posicao(2, 3);
sprintf(buffer, ":%02X ", leitura);
imprime_buffer_lcd(buffer, 16);
//Leitura de Posição de Segundo no DS-1307.
read_RTC_I2c(0x00);
lcd_posicao(2, 6);
sprintf(buffer, ":%02X ", leitura);
imprime_buffer_lcd(buffer, 16);
//**********************************************************************
ledverde = 1;
Delay10KTCYx(250);
ledverde = 0;
Delay10KTCYx(250);
}
}