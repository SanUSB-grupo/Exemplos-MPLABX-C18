#include "SanUSB48.h" //https://www.youtube.com/watch?v=bqnKE2Qwz2c

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c

void verificar_botao();
void exibir_senha();
void nova_senha();
void verificar_senha();
void adicionar_digito(unsigned int dig);
void digitando();

unsigned char set_seg_anodo[12] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x08, 0x06};
//unsigned char set_seg_catodo[12] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0x77, 0x79};
unsigned char senha[6] = {0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F},j;

unsigned int i, ok = 0, count = 0, digitando_nova_senha = 0;
//

void interrupcao() {
}

void verificar_botao() {
    if (!entrada_pin_e3) {
        Reset();
    }
}

void exibir_senha() {
    PORTB = senha[count];
    nivel_baixo(pin_c0); //SELECIONA 1. DISPLAY
    nivel_alto(pin_c1);
    tempo_ms(5);

    PORTB = senha[count + 1];
    nivel_baixo(pin_c1); //SELECIONA 2. DISPLAY
    nivel_alto(pin_c0);
    tempo_ms(5);
}

void nova_senha() {
    digitando_nova_senha = 1;
    for (i = 0; i < 100; i++) {
        PORTB = 0xC;//p
        nivel_baixo(pin_c0); //SELECIONA 1. DISPLAY
        nivel_alto(pin_c1);
        tempo_ms(5);

        PORTB = 0x46;//c
        nivel_baixo(pin_c1); //SELECIONA 2. DISPLAY
        nivel_alto(pin_c0);
        tempo_ms(5);
    }
    exibir_senha();
    while (digitando_nova_senha){
        exibir_senha();
        digitando();
    }
    for (i = 0; i < 4; i++) {
        escreve_eeprom(i, senha[i + 2]);
    }
    count = 0;
    senha[2] = 0x3F;
    senha[3] = 0x3F;
    senha[4] = 0x3F;
    senha[5] = 0x3F;
    for (i = 0; i < 100; i++) {
        PORTB = 0x40;
        nivel_baixo(pin_c0); //SELECIONA 1. DISPLAY
        nivel_alto(pin_c1);
        tempo_ms(5);

        PORTB = 0x09;
        nivel_baixo(pin_c1); //SELECIONA 2. DISPLAY
        nivel_alto(pin_c0);
        tempo_ms(5);
    }
    exibir_senha();
}

void verificar_senha() {
    for (i = 0; i < 4; i++) {
        if (senha[i + 2] == le_eeprom(i))
            ok++;
    }
    count = 0;
    senha[2] = 0x3F;
    senha[3] = 0x3F;
    senha[4] = 0x3F;
    senha[5] = 0x3F;
    if (ok == 4) {
        nivel_baixo(pin_a4);
        for (i = 0; i < 200; i++) {
            if (!entrada_pin_a3) {
                while (!entrada_pin_a3);
                nova_senha();
                break;
            }
            PORTB = 0xC0;
            nivel_baixo(pin_c0); //SELECIONA 1. DISPLAY
            nivel_alto(pin_c1);
            tempo_ms(5);

            PORTB = 0x89;
            nivel_baixo(pin_c1); //SELECIONA 2. DISPLAY
            nivel_alto(pin_c0);
            tempo_ms(5);            
        }
    } else {
        for (i = 0; i < 200; i++) {
            PORTB = 0x06;
            nivel_baixo(pin_c0); //SELECIONA 1. DISPLAY
            nivel_alto(pin_c1);
            tempo_ms(5);

            PORTB = 0x2F;
            nivel_baixo(pin_c1); //SELECIONA 2. DISPLAY
            nivel_alto(pin_c0);
            tempo_ms(5);
        }
    }

    ok = 0;
    exibir_senha();
}

void adicionar_digito(unsigned int dig) {
    if (dig < 10) {
        senha[count + 2] = set_seg_anodo[dig];
        count++;
        exibir_senha();
    }
    if (dig == 10) {
        exibir_senha();
    }
    if (dig == 11) {
        if (count > 0) {
            senha[count + 2] = 0x3F;
            count--;
            exibir_senha();
        }
    }
    if (count > 3) {
        if (digitando_nova_senha) {
            digitando_nova_senha = 0;
            return;
        }
        verificar_senha();
    }

}

void digitando() {
    nivel_baixo(pin_a4);
    nivel_alto(pin_a5);
    nivel_alto(pin_c2);
    if (!entrada_pin_a0) {
        adicionar_digito(1);
        while (!entrada_pin_a0) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a1) {
        adicionar_digito(4);
        while (!entrada_pin_a1) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a2) {
        adicionar_digito(7);
        while (!entrada_pin_a2) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a3) {
        adicionar_digito(10);
        while (!entrada_pin_a3) {
            exibir_senha();
        }
        tempo_ms(200);
    }

    nivel_alto(pin_a4);
    nivel_baixo(pin_a5);
    nivel_alto(pin_c2);
    if (!entrada_pin_a0) {
        adicionar_digito(2);
        while (!entrada_pin_a0) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a1) {
        adicionar_digito(5);
        while (!entrada_pin_a1) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a2) {
        adicionar_digito(8);
        while (!entrada_pin_a2) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a3) {
        adicionar_digito(0);
        while (!entrada_pin_a3) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    nivel_alto(pin_a4);
    nivel_alto(pin_a5);
    nivel_baixo(pin_c2);
    if (!entrada_pin_a0) {
        adicionar_digito(3);
        while (!entrada_pin_a0) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a1) {
        adicionar_digito(6);
        while (!entrada_pin_a1) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a2) {
        adicionar_digito(9);
        while (!entrada_pin_a2) {
            exibir_senha();
        }
        tempo_ms(200);
    }
    if (!entrada_pin_a3) {
        adicionar_digito(11);
        while (!entrada_pin_a3) {
            exibir_senha();
        }
        tempo_ms(200);
    }
}

void main() {
    clock_int_48MHz();
    TRISB = 0b00000000;
    
    if (le_eeprom(0)==0xFF) {
        for (i = 0; i < 4; i++) {
            escreve_eeprom(i, set_seg_anodo[5]);
        }
    }

    while (1) {
        verificar_botao();
        digitando();
        exibir_senha();
    }
}
