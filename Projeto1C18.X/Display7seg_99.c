#include "SanUSB1.h"
#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){                  }
int setseg[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; //Vetor com 10 //elementos que desenham de 0 a 9
int i, z, dezena, unidade;  //índice dezena,unidade (ponteiro)

void main ()
{
clock_int_4MHz();
PORTB= 0b00000000;
TRISB=0x00;   // porta B como saída.
while(1)
{
for (i=0;i<99;i++)
{
for(z=0;z<20;z++){

dezena=i/10;  //dezena recebe o número inteiro da divisão por 10
unidade=i%10; //unidade recebe o resto  da divisão por 10 

nivel_alto(pin_a0);  //pin_a0 aciona transistor do comum das dezenas
nivel_baixo(pin_a1);    //pin_a3 aciona transistor do comum das unidades
PORTB = setseg[dezena]; //A porta B recebe o desenho do número das dezenas apontado pela //variável dezena
tempo_ms(10);             

nivel_alto(pin_a1);  //selecionei a unidade
nivel_baixo(pin_a0);   
PORTB = setseg[unidade]; //A porta B recebe o desenho do número das unidades apontado //pela variável unidade
tempo_ms(10);
}}
}
}