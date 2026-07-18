#ifndef ALFABETO_H
#define ALFABETO_H

#include <stdbool.h>

#define TAMANHO_ARRAYS 256

struct tabelasAlfabeto{
    unsigned char aberturas_correspondentes[TAMANHO_ARRAYS];
    bool eh_abertura[TAMANHO_ARRAYS];
    bool eh_fechamento[TAMANHO_ARRAYS];
};

int tamanho_array_caracteres(const unsigned char array_caracteres[]);

int preenche_aberturas_correspondentes(const unsigned char simbolos_aberturas[],
                                       const unsigned char simbolos_fechamentos[],
                                       struct tabelasAlfabeto *tabela_alfabeto);

int preenche_eh_abertura_eh_fechamento(const unsigned char simbolos_aberturas[],
                                       const unsigned char simbolos_fechamentos[],
                                       struct tabelasAlfabeto *tabela_alfabeto);

int preenche_tabelas_alfabeto(const unsigned char simbolos_aberturas[],
                              const unsigned char simbolos_fechamentos[],
                              struct tabelasAlfabeto *tabela_alfabeto);

#endif
