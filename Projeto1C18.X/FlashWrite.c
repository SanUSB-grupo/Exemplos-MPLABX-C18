#include "SanUSB48.h" // Firmware para configuração e leitura por hardware de EEPROM i2c

char mem1[8],x; //buffer de 8 bytes
unsigned char cont_mem_dados=0;
unsigned short cont_mem_prog=0, count=0;
 char mem[64];
 char i;

#pragma interrupt interrupcao
void interrupcao(){}

unsigned short read_FLASH(unsigned endereco)
{
 union
 	{
 	struct
 	{
        unsigned short low:8;
 	unsigned short high:8;
 	} ;
 struct
 	{
 	unsigned short all;
 	} ;
 	}dado;
 TBLPTR = endereco; //carrega endereço
 _asm //lê posição apontada pelo TBLPTR, envia
 	TBLRDPOSTINC //dado para TABLAT e incrementa TBLPTR
 	_endasm
 	dado.low = TABLAT; //salva dado em dado.low

 	_asm //lê posição apontada pelo TBLPTR, envia
 	TBLRDPOSTINC //dado para TABLAT e incrementa TBLPTR
 	_endasm
 	dado.high = TABLAT; //salva dado em dado.high

 	return(dado.all); //retorna dado disponível em dado.all
}

void memcpyram2flash(unsigned addr, char * mem) {
 int chunkSize = 64;
 unsigned char i;
 TBLPTR = addr;
 EECON1bits.EEPGD = 1;
 EECON1bits.CFGS = 0;
 EECON1bits.WREN = 1;
 EECON1bits.FREE = 1;
 INTCONbits.GIE = 0;
 EECON2 = 0x55;
 EECON2 = 0xAA;
 EECON1bits.WR = 1;
 Nop();
 INTCONbits.GIE = 1;
 EECON1bits.WREN = 0;

 //*********************************************************
 for(i = 0;i < 64;i++){
    TABLAT = mem[i];        // put a char into the table latch register
    _asm
      TBLWTPOSTINC          // write to holding register and post-increment
    _endasm

   if(((i + 1) % chunkSize) == 0){ // write to flash after each chunkSize bytes
      TBLPTR --;    //put TBLPTR in holding register address range
      EECON1bits.EEPGD = 1; // ...write the holding registers to flash
      EECON1bits.CFGS = 0;
      EECON1bits.WREN = 1;
      EECON1bits.FREE = 0;
      INTCONbits.GIE = 0;
      EECON2 = 0x55;
      EECON2 = 0xAA;
      EECON1bits.WR = 1;
      Nop();
      INTCONbits.GIE = 1;
      EECON1bits.WREN = 0;
      TBLPTR ++;
 }
 }}

 void main(void) {
     clock_int_48MHz();
    habilita_interrupcao(recep_serial);
    taxa_serial(19200);



 // write test string to address 0x5000 in program memory
 for (i = 0; i < 64; i++)
                          { mem[i] = i;
                            memcpyram2flash(0x5000, mem);
                            Nop();}

    while(1){
    ++count; ++ cont_mem_dados; ++ cont_mem_prog;
inverte_saida(pin_b7);
tempo_ms(500);

    if(!entrada_pin_e3)//Se apertar o botão...
 	  {
            for(x=0;x<8;x++) {mem[x]=0;} //ZERA BUFFER mem PARA GRAVAÇÃO DA MEMÓRIA FLASH
            escreve_eeprom(0x10, cont_mem_dados); // cont_mem_dados GRAVA NA EEPROM INTERNA ATÉ 0XFF
            mem1[0] = cont_mem_prog;
            mem1[1] = cont_mem_prog >> 8;             // cont_mem_prog - mem[1] byte mais significativo
            //sendsw((char *)"A\r\n");
             swputc('A');swputc(' '); //
            //write_FLASH(0x3000, &mem1); //colocar &mem depois; grava 4 words na FLASH (bytes 0x5000 a 0x5007),
             tempo_ms(500);
	    tempo_ms(1000);
            sendrw((rom char *)"M\r\n");
            sendnum(le_eeprom(0x10)); sendrw((rom char *)" ");
            sendnum(read_FLASH(0x5000+count)); sendrw((rom char *)" "); //mostra a primeira word (0x5000 e 0x5001); valor até 0X3FFF
    }}
 }
