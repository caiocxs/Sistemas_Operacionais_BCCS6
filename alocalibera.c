// PARA RODAR:
// cd /c/Users/carme/source/repos/Paradigmas_Programacao_BCCS6
// gcc ex04_1808.c -o main.exe

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t buffer[4096] = {0};
uint8_t* buffer_livre = buffer;

typedef struct value_pointer* ptr;
struct value_pointer {
    void* pointer;
    int size;
};

void* aloca(int size){
    printf("aloca: %d\n", size);
    uint8_t* ponteiro;
    if(buffer_livre != NULL){
        ponteiro = buffer_livre;
    } else {
        return NULL;
    }

    for(int i = 0; i < size; i++){
        if((*ponteiro) != 0){
            return NULL;
        }
        ponteiro++;
    }

    ponteiro = buffer_livre;
    for(int i = 0; i < size; i++){
        (*ponteiro) = 1;
        ponteiro++;
    }

    uint8_t* ponteiro_retorno = buffer_livre;
    if(size < sizeof(buffer)){
        ponteiro++;
        buffer_livre = ponteiro;
    }
    else
        if(buffer[0] == 0){
            buffer_livre = buffer;
        }
    return ponteiro_retorno;
}

ptr criar_ponteiro(void* ponteiro, int size){
    ptr r = (ptr)aloca(sizeof(struct value_pointer));
    r->pointer = ponteiro;
    r->size = size;

    return r;
}

void libera(ptr ponteiro){
    int size = ponteiro->size;
    printf("libera: %d\n", size);
    uint8_t* q = ponteiro->pointer;
    for(int i = 0; i < size; i++){
        (*q) = 0;
        q++;
    }
}

void print_memoria() {
    int quantos_valores = 64;
    for (int linha = 0; linha < 32; linha++) printf(" - ");
    printf("\n");
    for (int dado = 0; dado < quantos_valores; dado++) {
        if (dado % 32 == 0) {
            printf("| ");
        }

        printf("%3d ", buffer[dado]);

        if ((dado + 1) % 32 == 0) {
            printf("|\n");
        }
    }

    if (quantos_valores % 32 != 0) {
        printf("|\n");
    }
    for (int linha = 0; linha < 32; linha++) printf(" - ");
    printf("\n");
}

// ----------------------------

typedef struct node* link;
struct node {
    int value;
    link next;
};

void add_value(link* list, int value){
    link new_node = (link)aloca(sizeof(struct node));
    if (new_node == NULL){
        printf("Erro ao alocar na memória!\n");
        return;
    }
    new_node->value = value;
    new_node->next = NULL;

    if((*list) == NULL){
        (*list) = new_node;
        return;
    }

    link q = (*list);
    while(q->next != NULL){
        q = q->next;
    }
    
    q->next = new_node;
}

void remove_value(link* list, int value){
    link p = NULL;
    link q = *list;

    while(q->value != value){
        p = q;
        q = q->next;
    }

    if(p == NULL){
        *list = q->next;
    } else{
        p->next = q->next;
    }

    ptr r = criar_ponteiro(q, sizeof(struct node));
    libera(r);
}

void print_list(link list){
    link q = list;

    while(q != NULL){
        printf("(%d) -> ", q->value);
        q = q->next;
    }
    printf("NULL\n");
}

int main(void){
    
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

    print_memoria();

    libera(criar_ponteiro(ch, 3*sizeof(ch)));

    print_memoria();

    libera(criar_ponteiro(ch, 3*sizeof(in)));

    print_memoria();

    link list = aloca(sizeof(struct node));
    list->value = 1;
    list->next = NULL;

    print_list(list);
    print_memoria();

    add_value(&list, 2);

    print_list(list);
    print_memoria();

    add_value(&list, 3);

    print_list(list);
    print_memoria();

    add_value(&list, 4);

    print_list(list);
    print_memoria();

    add_value(&list, 5);

    print_list(list);
    print_memoria();

    remove_value(&list, 3);

    print_list(list);
    print_memoria();

    remove_value(&list, 1);

    print_list(list);
    print_memoria();


}