#include "SanUSB48.h" //Exemplo com 4 tarefas (task) concorrentes (paralelas)
#include <osa.h> //Vídeo-aula: https://www.youtube.com/watch?v=s6BG8ZN0aDk
//Evitar uso de outros laços dentro das tasks (como for, do - while, etc.!)


#pragma interrupt interrupcao 
void interrupcao(){

    if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        TMR1H           = 0xD8;     
        TMR1L           = 0xF0;
        OS_Timer();
    }
}

void PIC_Init(void)
{
    LATB            = 0x00;
    TRISB           = 0x00;

    T1CON           = 0x80;     // modo 16 bits
    TMR1H           = 0xD8;     // 1ms
    TMR1L           = 0xF0;

    INTCON = 0;
    INTCONbits.PEIE = 1;
    PIR1bits.TMR1IF = 0;        // Flag interrupcao Timer1
    PIE1bits.TMR1IE = 1;        // Habilita interrupcao Timer1
    T1CONbits.TMR1ON= 1;        // Liga Timer1
}

void Task_1(void)
{
    while(1)
    {
        inverte_saida(pin_b7);
        OS_Delay(1000);       
    }
}

void Task_2(void)
{
    while(1)
    {
        OS_Delay(200);
        LATBbits.LATB6^=1;
    }
}

void Task_3(void)
{
    while(1)
    {
        OS_Delay(300);
        LATBbits.LATB5^=1;
    }
}
/* // OSAcf.h configurado com 4 tasks
void Task_4(void)
{
    while(1)
    {
        OS_Delay(400);
        LATBbits.LATB4^=1;
    }
} */

void main(void)
{
    clock_int_48MHz();

    PIC_Init();                     // Configurações gerais do PIC
   
    OS_Init();                      

    OS_Task_Create(1,Task_1);       // Criando uma tarefa,  prioridade 1
    OS_Task_Create(2,Task_2);       // Criando uma tarefa,  prioridade 2
    OS_Task_Create(3,Task_3);       // Criando uma tarefa,  prioridade 3
    //OS_Task_Create(4,Task_4);       // Criando uma tarefa,  prioridade 4

    OS_EI();                        // Habilita interrupcoes
    OS_Run();                       // Executa o RTOS
}


