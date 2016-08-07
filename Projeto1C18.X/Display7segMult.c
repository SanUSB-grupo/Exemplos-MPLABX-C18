#include "SanUSB1.h"

#define DIGIT1 PORTCbits.RC0
#define DIGIT2 PORTCbits.RC1
unsigned char Cnt = 0;
unsigned char Flag = 0;
unsigned char Display(unsigned char);

#pragma interrupt interrupcao
void interrupcao()
{

unsigned char Msd, Lsd;
TMR0L = 100; // Recarrega TMR0 para contar 156 x 32 us
INTCON = 0x20; // Set T0IE and clear T0IF
Flag = ~ Flag; // Inverte a Flag
if(Flag == 0) // Do digit 1
        {
            DIGIT2 = 0;
            Msd = Cnt / 10; // MSD digit
            //*/if(Msd != 0) // blank MSD
            //{
            PORTB = Display(Msd); // Send to PORT C
            DIGIT1 = 1; // Enable digit 1
            //}
        }
else
{ // Faz o digito 2
            DIGIT1 = 0; // Disable digit 1
            Lsd = Cnt % 10; // LSD digit
            PORTB = Display(Lsd); // Send to PORT C
            DIGIT2 = 1; // Enable digit
}
}

unsigned char Display(unsigned char i)
{
unsigned char Pattern;
unsigned char SEGMENT[ ] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07, 0x7F,0x6F};
Pattern = SEGMENT[i]; // Pattern to return
return (Pattern);
}


void main()       {
clock_int_4MHz();
//tempo_us(100);
TRISB = 0; // PORT B are outputs
TRISC = 0; // RC0, RC1 are outputs
DIGIT1 = 0;
//
// Configura TMR0 timer interrupt
//
T0CON = 0xC4; // Prescaler = 32
TMR0L = 100; // Load TMR0L with 156 x 32 us
INTCON = 0xA0; // Enable TMR0 interrupt
tempo_ms(1000);

while(1)
{
Cnt++; // Incrementa Cnt
if(Cnt == 100) Cnt = 0; // Conta de 0 a 99
tempo_ms(1000);

}}

