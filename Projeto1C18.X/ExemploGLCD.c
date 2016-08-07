/************************************************
* Compilador Multiplataforma MPLABX C18:
* https://dl.dropboxusercontent.com/u/101922388/BaixarMPLABX_C18.pdf*/

#include "SanUSB48.h" //Vídeo: http://www.youtube.com/watch?v=9inU3HIoy7o
#include "GLCD.h"
#include "imagem.h"

#pragma interrupt interrupcao
void interrupcao(){}

const rom unsigned char imagem[];

void main (void){
    unsigned char i;
        clock_int_48MHz();
	Init_GLCD();
        
        SetPos(1,1);  
	SanDraw((rom char*)imagem);
        tempo_ms(4000);
        ClearScreen();

///*    //box(1,1,126,62);//plota caixa entre os 4 pontos x1,y1,x2,y2 (máx 126 e 62)
	//ASCII 22 (x16) is set position followed by x,y
	PutMessage((rom char*)"\x16\x26\x08 Grupo\x16\x20\x10  SanUSB\n Titulo:\n Autor:\n Compilador:");
	PutMessage((rom char*)"\x16\x32\x18LcdGrafico C18");
	PutMessage((rom char*)"\x16\x32\x20Grupo SanUSB");
	PutMessage((rom char*)"\x16\x40\x28MPLABX C18");
        tempo_ms(1000);
        //ClearScreen(); //*/
   
	while (1){inverte_saida(pin_b7); inverte_saida(pin_d7); tempo_ms(500);
                  if(!entrada_pin_e3){Reset();} //Estado de gravação via USB
                 }
}

