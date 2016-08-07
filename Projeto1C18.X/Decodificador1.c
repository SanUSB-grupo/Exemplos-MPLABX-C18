#include "SanUSB1.h" // Emulação de decodificador para display de 7 segmentos - palavra Usb2

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){
        }

short int X, Y;  //Entradas
short int a, b, c, d, e, f, g;  //saídas

void decodificador(short int X, short int Y) //Função auxiliar do decodificador fixo para USb2
{
a=!Y;		saida_pino(pin_b0,a);   //Anodo comum
b=X^Y;		saida_pino(pin_b1,b);
c=X&Y;		saida_pino(pin_b2,c);
d=0;		saida_pino(pin_b3,d);
e=!X&Y;	        saida_pino(pin_b4,e);
f=X&Y;		saida_pino(pin_b5,f);
g=!X&!Y;	saida_pino(pin_b6,g);
}
void main(){
clock_int_4MHz();
while (1)
{
decodificador(0,0); // Insere as entradas X=0 e Y=0 no decodiicador fixo ? Saída letra S
tempo_ms(1000);

decodificador(0,1); // Saída letra t
tempo_ms(1000);

decodificador(1,0); // Saída letra o
tempo_ms(1000);

decodificador(1,1); // Saída letra P
tempo_ms(1000);
}}

