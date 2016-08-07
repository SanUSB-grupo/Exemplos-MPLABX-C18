#include "SanUSB1.h"//http://www.electro-tech-online.com/microcontrollers/94288-development-driving-vga-monitors.html

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c
void interrupcao(){
                  }
//hardware configuration
#define R		PORTDbits.RD2				//red on GPIO0
#define G		PORTDbits.RD1				//green on gpio1
#define B		PORTDbits.RD0				//blue on gpio2
#define HSync           PORTDbits.RD6				//hsync on gpio4
#define VSync           PORTDbits.RD7				//vsync on gpio5
//end hardware configuration

//global variables
//1-bit colors for now
#define RED		0b00000001		//red is 0th bit
#define GREEN		0b00000010		//green is the 1st bit
#define BLUE		0b00000100		//BLUE is the 2nd bit
#define CLR_MASK	RED|GREEN|BLUE	//port mask used to set the output, value depends on hardware configuration. only the bits set to 1 will be changed.
#define BLACK		0b00000000		//black is nothing
#define H_Res		8		//horizontal resolution
#define V_Res		1		//vertical resolution, set at 1 for now.
const rom unsigned char Vid_RAM[V_Res][H_Res] = {
		{RED, GREEN, BLUE, RED|GREEN, RED|BLUE, GREEN|BLUE, RED|GREEN|BLUE, BLACK}
		};
int h_index, v_index;		//horizontal and vertical indexes;
char GPIO_VandH;			//GPIO's VSync and HSync bits;
//VSync=0;					//Vsync is normally low;
//HSync=0;

void main(){
clock_int_4MHz();
			//Hsync is normally low;
	while (1){
		//TODO Auto-generated main function
		for (v_index=0; v_index<V_Res*0+200; v_index++){		//one line at a time, v_index should reach V_res but for now, we will try to just repeat the same line
			for (h_index=0; h_index<H_Res; h_index++) {			//now, generate each line
				GPIO_VandH = Vid_RAM[0][h_index];						//output video ram's content
			}
			HSync=1;			//send the hsync signal;
			Nop();
			Nop();
			Nop();
			HSync=0;			//reset the hsync signal;
		}
		VSync=1;				//send the VSync signal;
		Nop();					//may need more nop;
		VSync=0;				//reset the Vsync signal;
	}
}
