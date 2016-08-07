#include "SanUSB1.h" //Princípio dos RTOS com estouro do timer 1, com prescaler maximo de 8
unsigned long int  i, flag;

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){

    if (timer1_interrompeu)     {          //espera o estouro do timer1
    timer1_interrompeu = 0;           	   //limpa a flag de interrupção
        tempo_timer16bits(1,1000);  //Carrega 64536 = 0xFC18 (65536-1000)
        flag = 1;
                                }
                   }
void  main(void)
{
clock_int_4MHz();//Função que garante 1 Cm = 1us
habilita_interrupcao(timer1);
tempo_timer16bits(1,1000);  //Carrega 64536 = 0xFC18 (65536-1000)
multiplica_timer16bits(1,4);     //liga timer1 com prescaler (multiplicador) = 4

    while(1)
    {
    if(!entrada_pin_e3){Reset();}//pressionar o botão para gravação
        if (flag)
        {flag = 0;
    
            ++i; //sempre que o resto % da divisao for exatamente zero
   //Tarefa 1 - As tarefas ocorrem em multiplos de 4 ms
   if ((i%2) == 0 ) // Ocorre a cada 4 x 1000us x 2 = 8ms
                {inverte_saida(pin_b4);} //Escrever as funções concorrentes aqui
   //Tarefa 2
   if ((i%10) == 0) //Ocorre a cada 4 x 1000us x 10 = 40ms
                {inverte_saida(pin_b5);}
   //Tarefa 3
   if ((i%20) == 0) //Ocorre a cada 4 x 1000us x 20 = 80ms
                {inverte_saida(pin_b6);}
    //Tarefa 4
   if ((i%100) == 0) //Ocorre a cada 4 x 1000us x 100 = 400ms
                 {inverte_saida(pin_b7);}//B4 ocorre 50 vezes menos qie o B7
                                        
        }
    }
}
