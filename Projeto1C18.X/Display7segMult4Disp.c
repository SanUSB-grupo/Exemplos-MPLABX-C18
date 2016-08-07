#include "SanUSB1.h"

#define SEG1 LATAbits.LATA0 // define common pins for each seven segment unit
#define SEG2 LATAbits.LATA1
#define SEG3 LATAbits.LATA2
#define SEG4 LATAbits.LATA3

unsigned char Display(unsigned char);

unsigned int numero=0,temp=0, digit=0,i=0;
unsigned char Desenho;

#pragma interrupt interrupcao
void interrupcao()
{

unsigned char Msd, Lsd;
TMR0L = 100; // Recarrega TMR0 para contar 156 x 32 us
INTCON = 0x20; // Set T0IE and clear T0IF 

switch (digit)
    {
        case 0:
                SEG4=0;// turn off last segment
                SEG1=1;// turn on this segment
                i=numero/1000;  //recebe milhar
                PORTB = Display(i);
                break;
        case 1:
                SEG1=0;// turn off last segment
                SEG2=1;// turn on this segment
                temp=numero%1000;
                i=temp/100;//recebe centena
                PORTB = Display(i);
                break;
        case 2:
                SEG2=0;
                SEG3=1;
                temp=temp%100;
                i=temp/10;   //recebe dezena
                PORTB = Display(i);
                break;
        case 3:
                SEG3=0;
                SEG4=1;
                i=temp%10; //recebe unidade
                PORTB = Display(i);
                break;
    }
++digit;if(digit > 3) {digit = 0;}
}

unsigned char Display(unsigned char i)
{
unsigned char SEGMENT[ ] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
Desenho = SEGMENT[i]; // Pattern to return
return (Desenho);
}


void main()       {
clock_int_4MHz();
//tempo_us(100);
TRISB = 0; // PORT B are outputs
TRISC = 0; // RC0, RC1 are outputs
//
// Configura TMR0 timer interrupt
//
T0CON = 0xC4; // Prescaler = 32
TMR0L = 100; // Load TMR0L with 156 x 32 us
INTCON = 0xA0; // Enable TMR0 interrupt
tempo_ms(100);

while(1)
{
numero++; // Incrementa Cnt
if(numero > 9999) {numero = 0;} // Conta de 0 a 99
tempo_ms(100);

}}

