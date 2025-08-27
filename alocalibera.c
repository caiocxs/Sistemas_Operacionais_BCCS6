// PARA RODAR:
// cd /c/Users/carme/source/repos/Paradigmas_Programacao_BCCS6
// gcc ex04_1808.c -o main.exe

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t buffer[4096];
uint8_t* buffer_livre = buffer;

// zera o buffer
void zerar_buffer(){
    for(int i = 0; i < 4096; i++){
        buffer[i] = 0;
    }
}

void* aloca(int size){
    uint8_t* ponteiro;
    if(buffer_livre != NULL){
        ponteiro = buffer_livre;
    } else {
        return NULL;
    }

    for(int i = 0; i < size; i++){
        buffer[i] = 1;
    }

    if(size < sizeof(buffer)){
        buffer_livre = &buffer[size];
    }
    else
        if(buffer[0] == 0){
            buffer_livre = buffer;
        }
    return ponteiro;
}

void libera(void* pointer){
    int size = sizeof(pointer);
    for(int i = 0; i < size; i++){
        buffer[i] = 0;
    }
}

// ----------------------------




int main(void){
    zerar_buffer();

    char* ch = aloca(3 * sizeof(char));
    int* in = aloca(3 * sizeof(int));

    ch[0] = 'o';
    ch[1] = 'p';
    ch[2] = 'a';

    in[0] = 1;
    in[1] = 2;
    in[2] = 3;

    for(int i = 0; i < 3; i++){
        printf("%c", ch[i]);
    }
    printf("\n");

    for(int i = 0; i < 3; i++){
        printf("%d", in[i]);
    }
    printf("\n");

    libera(ch);
    libera(in);
}