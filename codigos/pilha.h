#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

struct Pilha{
    unsigned int quantidade;
    unsigned int capacidade;
    unsigned char *array_pilha;
};


int inicializar_pilha(struct Pilha *pilha, unsigned int tamanho);

bool is_empty(const struct Pilha *pilha);
int empilhar(struct Pilha *pilha, unsigned char simbolo);
int desempilhar(struct Pilha *pilha);
int topo(const struct Pilha *pilha, unsigned char *simbolo_topo);
int destruir_pilha(struct Pilha *pilha);

#endif
