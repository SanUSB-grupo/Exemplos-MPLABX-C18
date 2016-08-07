#include "SanUSB48.h"

#define lcd_type 2        // 0=5x7, 1=5x10, 2=2 lines 
#define lcd_line_two 0x40 // LCD RAM address for the 2nd line 

unsigned char i;
/****************PIN DETAILS****************/

#define LCD_DATA LATB
#define LCD_CLEAR 0x01
#define LCD_CURSOR_OFF 0x06
#define FIRST_ROW 0x80
#define SECOND_ROW 0xC0

#define LCD_DB4   PORTBbits.RB0
#define LCD_DB5   PORTBbits.RB1
#define LCD_DB6   PORTBbits.RB2
#define LCD_DB7   PORTBbits.RB3
#define LCD_EN    PORTBbits.RB4
#define LCD_RS    PORTBbits.RB5
/********************************************/

#pragma interrupt interrupcao 
void interrupcao(){}

/******************Function Prototypes*****************/
void lcd_ini(void);
void lcd_envia_byte(unsigned char value);
void Lcd4_Write(unsigned char value);
void Lcd4_Write_Text(unsigned char msg[]);
unsigned char * CopyConstToRAM(unsigned char *dest, const rom unsigned char * src);
void Clear_Destination_Buffer(void);
/***********************************************/

const rom unsigned char text[] = "SanUSB Tool!";
const rom unsigned char love[] = "PIC";
unsigned char ram_msg[16];
unsigned char character[] = {0,10,21,17,17,10,4,0};//O oitavo byte = 0 , pois o padrão é 5x7
unsigned char b1[8] = {4,21,14,4,10,10,10};//Desenha boneco 1
unsigned char b2[8] = {4,14,21,4,10,10,10};//Desenha boneco 2
unsigned char b3[8] = {21,14,4,4,10,10,10};//Desenha boneco 3
unsigned char b4[8] = {21,14,4,4,10,17,0};//Desenha boneco 4

/******************ISR CODE*********************/

void lcd_pos_xy(char x, char y) {
    char address;
    address = (y != 1)? 0x40 : 0;
    address += x-1;
    lcd_envia_byte( 0x80 | address);
}
void
main(void) {
   clock_int_48MHz();
   
   TRISB=0;
    lcd_ini();
    lcd_envia_byte(LCD_CLEAR);
    lcd_envia_byte(LCD_CURSOR_OFF);
    lcd_envia_byte(LCD_CLEAR);
    
    CopyConstToRAM(ram_msg,text);
    Lcd4_Write_Text(ram_msg);
    tempo_ms(10);

    //Store Heart in CGRAM of LCD
    lcd_envia_byte(0x40); ////64 Envia o comando de escrita na CGRAM 4-bit mode, Padrao 5 x 7 
    for (i=0;i<=7;i++)
    {
        Lcd4_Write(character[i]);
    }

    lcd_envia_byte(SECOND_ROW);
    //Lcd4_Write('I');
    //Lcd4_Write(' ');
    
   Lcd4_Write(0);        //Custom Character
    
   //Lcd4_Write(' ');
   
   //CopyConstToRAM(ram_msg,love);
    //Lcd4_Write_Text(ram_msg);

    while(1){
        inverte_saida(pin_b7); inverte_saida(pin_d7);
        tempo_ms(500);
            }
}

/**************Function Definitions*************/
void lcd_envia_byte(unsigned char value)
{
    LCD_RS = 0;
    LCD_DATA = (value & 0xF0);
    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    LCD_DATA = ((value<<4) & 0xF0);
    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    tempo_ms(1);
}
void Lcd4_Write(unsigned char value)
{
    LCD_RS = 1;
    LCD_DATA = (value & 0xF0);
    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    LCD_DATA = ((value<<4) & 0xF0);
    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    tempo_ms(1);
}

void Lcd4_Write_Text(unsigned char msg[])
{
    while(*msg)
    {
        Lcd4_Write(*msg);
        msg++;
    }
}

void lcd_ini(void)
{
    TRISD = 0x00;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;

    LCD_RS = 0;        //Command Register
    LCD_EN = 0;

    LCD_DATA = 0x30;

    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    tempo_ms(1);

    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    tempo_ms(1);

    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    tempo_ms(1);

    tempo_ms(1);
    LCD_DATA = 0x20;    // Four bit mode
    LCD_EN = 1;
    tempo_ms(1);
    LCD_EN = 0;
    tempo_ms(1);

    lcd_envia_byte(0x28);// 4-bit, 2 line, 5x7 mode
    tempo_ms(5);
    lcd_envia_byte(0x0C);// Turn on display
    tempo_ms(5);
    lcd_envia_byte(0x01);// Clear & home display
    tempo_ms(5);
    lcd_envia_byte(0x06);// Left to Right
   tempo_ms(5);
}

unsigned char * CopyConstToRAM(unsigned char *dest, const rom unsigned char * src)
{
    Clear_Destination_Buffer();
    for(;*dest++ = *src++;)
        ;
    return dest;
}
void Clear_Destination_Buffer()  //seht Wichtig
{
    unsigned char i;
    for(i=0;i<16;i++)
    {
        ram_msg[i] = 0;
    }
}









