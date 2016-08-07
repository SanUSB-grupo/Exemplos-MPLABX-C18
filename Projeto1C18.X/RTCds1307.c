//O Firmware comprova a gravação e leitura na EEPROM interna da placa SanUSB com MPLABX C18
//http://www.youtube.com/watch?v=u1HwZLRcrYQ e http://www.youtube.com/watch?v=zeqS6A5-I08
#include "SanUSB48.h"
#include <i2c.h> 

#pragma interrupt interrupcao
void interrupcao() {}
/**********LCD Pin Configuration**********/
#define LCD_DATA_PINS PORTD
#define RS PORTCbits.RC1
#define RW PORTCbits.RC0
#define EN PORTCbits.RC2
/*****************************************/

/**********Function Prototypes**********/
void DelayMs(unsigned int time);
void LCD_Init(void);
void LCD_Cmd(unsigned char);
void LCD_Data(unsigned char value);
void LCD_Str(const unsigned char *);
void USART_Init(void);
void USART_Write(unsigned char);
void USART_Write_Str(const unsigned char *);
void USART_Write_Str_Line(const unsigned char *);
void USART_Write_Int(int ,unsigned char);
unsigned char USARTReadByte();
void I2C_Init(void);
void I2C_Start(void);
void I2C_Restart(void);
void I2C_Stop(void);
void I2C_Wait(void);
void I2C_Send(unsigned char dat);
unsigned char I2C_Read(void);
unsigned char rtc1307_read(unsigned char address);
unsigned char BCD2UpperCh(unsigned char bcd);
unsigned char BCD2LowerCh(unsigned char bcd);
/************************************/

unsigned char sec,min,hour,date,month,year;
const unsigned char time[] = "TIME:";
const unsigned char date_format[] = "DATE:";
const unsigned char rtc[] = "RTC DS1307";

void main()
{
     clock_int_48MHz();
    TRISC = 0x80;    //Reception Pin as Input Pin, rest all as output Pin
    TRISD = 0x00;    //LCD Data Pins
    LCD_Init();        //Initialize LCD Module    
    USART_Init();    //Initialize USART at 9600 BPS
    LCD_Cmd(0x84);
    LCD_Str(rtc);
    DelayMs(2000);
    I2C_Init();    //To Generate the Clock of 100Khz
    DelayMs(100);
    I2C_Start();
    I2C_Send(0xD0);
    I2C_Send(0x00);
    I2C_Send(0x80);    //CH = 1 Stop oscillator
    I2C_Send(0x53);    //Minute
    I2C_Send(0x08); //Hour
    I2C_Send(0x02);    //Sunday
    I2C_Send(0x29);    //7 December
    I2C_Send(0x10);    //7 December
    I2C_Send(0x12);    //2012
    I2C_Stop();        //Stop the I2C Protocol
    DelayMs(2000);
    //Have to start the Clock again
    I2C_Start();
    I2C_Send(0xD0);
    I2C_Send(0x00);
    I2C_Send(0x00);    //start Clock and set the second hand to Zero
    I2C_Stop();
    DelayMs(2000);
    LCD_Cmd(0x01);
    //Infinite Loop For Reading Time and Date
    while(1)
    {
        sec = rtc1307_read(0x00);
        
        min = rtc1307_read(0x01);
        
        hour = rtc1307_read(0x02);
        
        date = rtc1307_read(0x04);
        
        month = rtc1307_read(0x05);
        
        year = rtc1307_read(0x06);
        
        DelayMs(1);
        LCD_Cmd(0x80);
        LCD_Str(time);
        LCD_Data(BCD2UpperCh(hour));
        LCD_Data(BCD2LowerCh(hour));
        LCD_Data(':');
        LCD_Data(BCD2UpperCh(min));
        LCD_Data(BCD2LowerCh(min));
        LCD_Data(':');
        LCD_Data(BCD2UpperCh(sec));
        LCD_Data(BCD2LowerCh(sec));
        LCD_Cmd(0xC0);
        LCD_Str(date_format);
        LCD_Data(BCD2UpperCh(date));
        LCD_Data(BCD2LowerCh(date));
        LCD_Data('/');
        LCD_Data(BCD2UpperCh(month));
        LCD_Data(BCD2LowerCh(month));
        LCD_Data('/');
        LCD_Data(BCD2UpperCh(year));
        LCD_Data(BCD2LowerCh(year));        
        DelayMs(100);
    }    
}

/*****************Delay Functions*************/
void DelayMs(unsigned int time)
{
    unsigned int i;
    unsigned int t;
    for(i=0;i<time;i++)
    {
        for(t=0;t<650;t++)
            Delay1TCY();
    }    
}
/**********************************************/

/****************RTC FUNCTIONS*****************/
unsigned char BCD2UpperCh(unsigned char bcd)
{
    unsigned char temp;
     temp = bcd >> 4;
     temp = temp | 0x30;
     return(temp);    
}
unsigned char BCD2LowerCh(unsigned char bcd)
{
    unsigned char temp;
     temp = bcd & 0x0F; //Making the Upper 4-bits
     temp = temp | 0x30;
     return(temp);
}

unsigned char rtc1307_read(unsigned char address)
{
    unsigned char temp;
    I2C_Start();
    I2C_Send(0xD0);
    I2C_Send(address);
    I2C_Restart();
    I2C_Send(0xD1);
    temp = I2C_Read();
    I2C_Stop();    //this line is Removed Because it is already included in I2C_read function
    return temp;
}
/**********************************************/

/*****************LCD FUNCTIONS****************/
void LCD_Init()
{
    EN = 0;
    DelayMs(1);
    LCD_Cmd(0x38);
    DelayMs(1);
    LCD_Cmd(0x0E);
    DelayMs(1);
    LCD_Cmd(0x0C);    //Cursor Off
    DelayMs(1);
    LCD_Cmd(0x01);
    DelayMs(1);
    LCD_Cmd(0x06);
    DelayMs(1);
    LCD_Cmd(0x80);    
    DelayMs(1);
}

void LCD_Cmd(unsigned char value)
{
    LCD_DATA_PINS = value;
    RS = 0;
    RW = 0;
    EN = 1;
    DelayMs(1);
    EN = 0;    
}
void LCD_Data(unsigned char value)
{
    LCD_DATA_PINS = value;
    RS = 1;
    RW = 0;
    EN = 1;
    DelayMs(1);
    EN = 0;    
}

void LCD_Str(const unsigned char *str)
{
    while((*str)!='\0')
    {
        LCD_Data(*(str));
        //Next goto char
        str++; //Increment the Pointer
    }
}
/**********************************************/

/***************Serial Port UART***************/
void USART_Init(void)
{
    //Baud Rate = 9600 Bits per Second
    //*** Note: Valid On 48MHz Crystal ONLY ***
    //For other crystal freq calculate new values for SPBRG
    SPBRG = 77;

    //Enable Transmission by setting these Value's
    TXSTAbits.TXEN=1;
    TXSTAbits.BRGH=0;
    
    //Enable Reception by Setting these Value's
    RCSTAbits.SPEN=1;
    RCSTAbits.CREN=1;    //Enable Receiver (RX)
    
    //BAUDCON
    BAUDCONbits.BRG16=0;

}

void USART_Write(unsigned char value)
{
    //Wait for TXREG Buffer to become available
    while(PIR1bits.TXIF == 0);
    TXREG = value;
}

void USART_Write_Str(const unsigned char *str)
{
    while((*str)!='\0')
    {
        //Wait for TXREG Buffer to become available
        while(PIR1bits.TXIF == 0);
        //Write Data
        TXREG = *(str);

        //Next goto char
        str++; //Increment the Pointer
    }
}


void USART_Write_Str_Line(const unsigned char *str)
{
    USART_Write_Str(str);
    //USART_Write_Str("\r\n");
    //Formely I used to write this
    USART_Write(10);
    USART_Write(13);
    
}

void USART_Write_Int(int val,unsigned char field_length)
{
    char str[5]={0,0,0,0,0};
    int i=4,j=0;
    if(val<0) 
    {
        USART_Write('-');    //Write '-' sign for negative numbers.
        val=(val*(-1));                //Make it positive.
    }

    //Convert Number To String and pump over Tx Channel.
    
    while(val)
    {
        str[i]=val%10;
        val=val/10;
        i--;
    }
    if(field_length>5)
        while(str[j]==0) j++;
    else
        j=5-field_length;
    
    for(i=j;i<5;i++)
    {
        USART_Write('0'+str[i]);
    }
}
unsigned char USARTReadByte()
{
    while(!PIR1bits.RCIF);    //Wait for a byte
    
    return RCREG;
}
/**********************************************/