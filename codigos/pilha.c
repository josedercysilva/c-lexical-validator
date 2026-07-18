# include <stdlib.h>
#include "pilha.h"

int inicializar_pilha(struct Pilha *pilha, unsigned int tamanho)
{
    if(!pilha) return -1;

    pilha->array_pilha = malloc(tamanho * sizeof(unsigned char));
    if(!pilha->array_pilha) return -2;

    pilha->quantidade = 0;
    pilha->capacidade = tamanho;

    return 0;
}

bool is_empty(const struct Pilha *pilha)
{
    if(!pilha) return true;
    return pilha->quantidade == 0;
}

int empilhar(struct Pilha *pilha, unsigned char simbolo)
{
    if(!pilha) return - 1;
    if(pilha->quantidade >= pilha->capacidade) return -2;
    pilha->array_pilha[pilha->quantidade] = simbolo;
    pilha->quantidade++;

    return 0;
}

int desempilhar(struct Pilha *pilha)
{
    if(!pilha) return -1;
    if(is_empty(pilha)) return -2;

    pilha->quantidade--;

    return 0;
}

int topo(const struct Pilha *pilha,unsigned char *simbolo_topo){
    if(!pilha) return -1;
    if(is_empty(pilha)) return -2;
    if(!simbolo_topo) return -3;

    *simbolo_topo = pilha->array_pilha[pilha->quantidade - 1];
    return 0;
}

int destruir_pilha(struct Pilha *pilha)
{
    if(!pilha) return -1;

    if(pilha->array_pilha != NULL){
        free(pilha->array_pilha);
        pilha->array_pilha = NULL;
    }

    pilha->quantidade = 0;
    pilha->capacidade = 0;

    return 0;
}



