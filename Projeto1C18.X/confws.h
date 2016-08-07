#ifndef CONFWS_H
#define CONFWS_H

     //Funciona quando somente o led verde estiver piscando

void iniws(void){
     unsigned char i=17;
     SPBRGH =0x02; SPBRG = 0x70;
     tempo_ms(2000);

     sputc(56+i);sputc(72);sputc(72);inverte_saida(pin_b7);tempo_ms (500);
     inverte_saida(pin_b7);
     while (AT1==0){ SPBRGH=0x04; SPBRG=0xE1;
     tempo_ms (4000);sputc(56+i);sputc(72);sputc(72);
     inverte_saida(pin_b7);}
     AT1=0;--i;

     sputc(189+i);sputc(194);sputc(198);sputc(232);sputc(222);sputc(228);
     sputc(242);sputc(64);sputc(164);sputc(26);
     tempo_ms (1000);inverte_saida(pin_b7);
     while (AT1==0){ tempo_ms (2000);
     sputc(189+i);sputc(194);sputc(198);sputc(232);sputc(222);sputc(228);
     sputc(242);sputc(64);sputc(164);sputc(26);
     inverte_saida(pin_b7);}
     AT1=0;--i;

     sputc(216+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(194);
     swputc(32);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
     swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
     swputc(ip[9]);swputc(ip[10]);swputc(ip[11]);swputc(ip[12]);swputc(ip[13]);sputc(26);
     tempo_ms(1000); inverte_saida(pin_b7);
     while (AT1==0){ tempo_ms (2000);
     sputc(216+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(194);
     swputc(32);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
     swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
     swputc(ip[9]);swputc(ip[10]);swputc(ip[11]);swputc(ip[12]);swputc(ip[13]);sputc(26);
     inverte_saida(pin_b7);}
     AT1=0;--i;

     sputc(217+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(206);
     sputc(64);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
     swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
     swputc(ip[9]);if(ip[9]==46){swputc(ip[10]);} else {swputc(ip[10]);swputc(ip[11]);} sputc(26);
     tempo_ms(1000); inverte_saida(pin_b7);
     while (AT1==0){ tempo_ms (2000);
     sputc(217+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(206);
     sputc(64);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
     swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
     swputc(ip[9]);if(ip[9]==46){swputc(ip[10]);} else {swputc(ip[10]);swputc(ip[11]);} sputc(26);
     inverte_saida(pin_b7);}
     AT1=0;--i;

     sputc(218+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);
     sputc(200);sputc(64);sputc(96);sputc(26);
     tempo_ms(500);inverte_saida(pin_b7);
     while (AT1==0){ tempo_ms (1000);
     sputc(218+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);
     sputc(200);sputc(64);sputc(96);sputc(26);
     inverte_saida(pin_b7);}
     AT1=0;--i;

    sputc(219+i);sputc(202);sputc(232);sputc(64);sputc(234);sputc(64);
    sputc(196);sputc(64);sputc(98);sputc(114);sputc(100);sputc(96);
    sputc(96);sputc(26); inverte_saida(pin_b7);
    tempo_ms(1000); inverte_saida(pin_b7);
    sputc(219+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(224);
    sputc(64);sputc(224);sputc(228);sputc(222);sputc(232);sputc(222);
    sputc(64);sputc(98);sputc(112);sputc(26);
    tempo_ms(1000);  inverte_saida(pin_b7); 
    sputc(219+i);sputc(202);sputc(232);sputc(64);sputc(222);sputc(64);
    sputc(200);sputc(64);sputc(166);sputc(194);sputc(220);sputc(170);
    sputc(166);sputc(132);sputc(90);sputc(204);sputc(216);sputc(242);sputc(26);
    tempo_ms(500); inverte_saida(pin_b7);
    sputc(219+i);sputc(194);sputc(236);sputc(202);sputc(26);
    tempo_ms (1000); inverte_saida(pin_b7);
    while (AT1==0){ tempo_ms (2000);
    sputc(219+i);sputc(194);sputc(236);sputc(202);sputc(26);
    tempo_ms(1000); 
    inverte_saida(pin_b7);}
    AT1=0;--i;

     sputc(218+i);sputc(202);sputc(196);sputc(222);sputc(222);sputc(232);
     sputc(26);
     tempo_ms (1000); inverte_saida(pin_b7);
     while (AT1==0){ tempo_ms (4000);
     inverte_saida(pin_b7);}
     sputc(218+i);sputc(202);sputc(196);sputc(222);sputc(222);sputc(232);
     sputc(26);
     AT1=0;--i;

    SPBRGH =0x02; SPBRG = 0x70; tempo_ms (100);
    sputc(63+i);sputc(72);sputc(72);inverte_saida(pin_b7);tempo_ms (500);
    inverte_saida(pin_b7);
    while (AT1==0){ tempo_ms (4000);sputc(63+i);sputc(72);sputc(72);
    inverte_saida(pin_b7); tempo_ms (500);}
    AT1=0;--i;

   sputc(222+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
   sputc(230);sputc(64);swputc(rede[0]);swputc(rede[1]);swputc(rede[2]);
   swputc(rede[3]);swputc(rede[4]);swputc(rede[5]);swputc(rede[6]);
   swputc(rede[7]);swputc(rede[8]);swputc(rede[9]);swputc(rede[10]);
   swputc(rede[11]);swputc(rede[12]);swputc(rede[13]);swputc(rede[14]);
   swputc(rede[15]);swputc(rede[16]);sputc(26);tempo_ms (500); inverte_saida(pin_b7);
   while (AT1==0){ tempo_ms (2000);
   sputc(222+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
   sputc(230);sputc(64);swputc(rede[0]);swputc(rede[1]);swputc(rede[2]);
   swputc(rede[3]);swputc(rede[4]);swputc(rede[5]);swputc(rede[6]);
   swputc(rede[7]);swputc(rede[8]);swputc(rede[9]);swputc(rede[10]);
   swputc(rede[11]);swputc(rede[12]);swputc(rede[13]);swputc(rede[14]);
   swputc(rede[15]);swputc(rede[16]);sputc(26);tempo_ms (500); inverte_saida(pin_b7);
                 }
    AT1=0;--i;

    sputc(223+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
    sputc(224);sputc(64);swputc(senha[0]);swputc(senha[1]);swputc(senha[2]);
    swputc(senha[3]);swputc(senha[4]);swputc(senha[5]);swputc(senha[6]);
    swputc(senha[7]);swputc(senha[8]);swputc(senha[9]);swputc(senha[10]);
    swputc(senha[11]);swputc(senha[12]);swputc(senha[13]);swputc(senha[14]);
    swputc(senha[15]);swputc(senha[16]);sputc(26);tempo_ms (500); inverte_saida(pin_b7);
    while (AT1==0){ tempo_ms (2000);
    sputc(223+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
    sputc(224);sputc(64);swputc(senha[0]);swputc(senha[1]);swputc(senha[2]);
    swputc(senha[3]);swputc(senha[4]);swputc(senha[5]);swputc(senha[6]);
    swputc(senha[7]);swputc(senha[8]);swputc(senha[9]);swputc(senha[10]);
    swputc(senha[11]);swputc(senha[12]);swputc(senha[13]);swputc(senha[14]);
    swputc(senha[15]);swputc(senha[16]);sputc(26);tempo_ms(500); inverte_saida(pin_b7);
                  }
    AT1=0;--i;

    sputc(224+i);sputc(202);sputc(232);sputc(64);sputc(198);sputc(222);
    sputc(218);sputc(218);sputc(64);sputc(222);sputc(224);sputc(202);
    sputc(220);sputc(64);sputc(84);sputc(166);sputc(194);sputc(220);
    sputc(170);sputc(166);sputc(132);sputc(84);sputc(26);
    tempo_ms (500); inverte_saida(pin_b7);
    while (AT1==0){ tempo_ms (1000);
    sputc(224+i);sputc(202);sputc(232);sputc(64);sputc(198);sputc(222);
    sputc(218);sputc(218);sputc(64);sputc(222);sputc(224);sputc(202);
    sputc(220);sputc(64);sputc(84);sputc(166);sputc(194);sputc(220);
    sputc(170);sputc(166);sputc(132);sputc(84);sputc(26);
    inverte_saida(pin_b7);}
    AT1=0;--i;

    sputc(225+i);sputc(202);sputc(232);sputc(64);sputc(198);sputc(222);
    sputc(218);sputc(218);sputc(64);sputc(228);sputc(202);sputc(218);
    sputc(222);sputc(232);sputc(202);sputc(64);sputc(60); 
    sputc(26);inverte_saida(pin_b7);
    tempo_ms (500);inverte_saida(pin_b7);
    while (AT1==0){ tempo_ms (1000);
    sputc(225+i);sputc(202);sputc(232);sputc(64);sputc(198);sputc(222);
    sputc(218);sputc(218);sputc(64);sputc(228);sputc(202);sputc(218);
    sputc(222);sputc(232);sputc(202);sputc(64);sputc(84);sputc(166);
    sputc(194);sputc(220);sputc(170);sputc(166);sputc(132);sputc(84);
    sputc(26);inverte_saida(pin_b7);}
    AT1=0;--i;

    sputc(226+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(224);
    sputc(64);sputc(216);sputc(222);sputc(198);sputc(194);sputc(216);
    sputc(64);sputc(112);sputc(96);sputc(26);
    tempo_ms (500);inverte_saida(pin_b7);
    while (AT1==0){ tempo_ms (1000);
    sputc(226+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(224);
    sputc(64);sputc(216);sputc(222);sputc(198);sputc(194);sputc(216);
    sputc(64);sputc(112);sputc(96);sputc(26);
    inverte_saida(pin_b7);}
    AT1=0;--i;

    sputc(227+i);sputc(194);sputc(236);sputc(202);sputc(26);
    tempo_ms (1000); inverte_saida(pin_b7);
    while (AT1==0){ tempo_ms (2000);
    sputc(227+i);sputc(194);sputc(236);sputc(202);sputc(26);
    tempo_ms (1000); inverte_saida(pin_b7);
    inverte_saida(pin_b7);}
    AT1=0;--i;

     sputc(210+i);sputc(222);sputc(210);sputc(220);sputc(64);swputc(rede[0]);
     swputc(rede[1]);swputc(rede[2]);swputc(rede[3]);swputc(rede[4]);swputc(rede[5]);
     swputc(rede[6]);swputc(rede[7]);swputc(rede[8]);swputc(rede[9]);swputc(rede[10]);
     swputc(rede[11]);swputc(rede[12]);swputc(rede[13]);swputc(rede[14]);swputc(rede[15]);
     swputc(rede[16]);swputc(rede[17]);sputc(26);inverte_saida(pin_b7);
     tempo_ms (4000); inverte_saida(pin_b7);
     while (AT2==0){ tempo_ms (4000);
     sputc(210+i);sputc(222);sputc(210);sputc(220);sputc(64);swputc(rede[0]);
     swputc(rede[1]);swputc(rede[2]);swputc(rede[3]);swputc(rede[4]);swputc(rede[5]);
     swputc(rede[6]);swputc(rede[7]);swputc(rede[8]);swputc(rede[9]);swputc(rede[10]);
     swputc(rede[11]);swputc(rede[12]);swputc(rede[13]);swputc(rede[14]);swputc(rede[15]);
     swputc(rede[16]);swputc(rede[17]);sputc(26);inverte_saida(pin_b7);
                    }
     AT2=0;--i;


}

#endif