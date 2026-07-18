#include <stdio.h>
#include <stddef.h>

#include "alfabeto.h"
#include "pilha.h"
#include "valida_string_simbolos.h"

int montar_tabelas(struct tabelasAlfabeto *tabela_montada)
{
    const unsigned char aberturas[] = "([{$";
    const unsigned char fechamentos[] = ")]}?";

    return preenche_tabelas_alfabeto(aberturas, fechamentos, tabela_montada);
}



int analisar_cadeia(const unsigned char *cadeia)
{
    if(!cadeia) return -11;


    struct tabelasAlfabeto tabela_montada;
    int status_montagem = montar_tabelas(&tabela_montada);
    if(status_montagem != 0){
        return status_montagem;
    }

    int tamanho_cadeia = tamanho_array_caracteres(cadeia);
    struct Pilha pilha;
    int status_pilha = inicializar_pilha(&pilha, tamanho_cadeia);

    if(status_pilha != 0){
        return -11;
    }


    unsigned int i = 0;

    while(cadeia[i] != '\0'){
        unsigned char c_atual = cadeia[i];

        bool eh_abertura = tabela_montada.eh_abertura[c_atual];
        bool eh_fechamento = tabela_montada.eh_fechamento[c_atual];


        if(!eh_abertura && !eh_fechamento){
            destruir_pilha(&pilha);
            return -13;
        }


        if(eh_abertura){
            empilhar(&pilha, c_atual);
        } else {
            if(is_empty(&pilha)){
                destruir_pilha(&pilha);
                return 1;
            }

            unsigned char simbolo_topo;
            topo(&pilha, &simbolo_topo);

            unsigned char abertura_esperada = tabela_montada.aberturas_correspondentes[c_atual];

            if(simbolo_topo != abertura_esperada){
                destruir_pilha(&pilha);
                return 2;
            }

            desempilhar(&pilha);
        }
        i++;
    }

    if(!is_empty(&pilha)){
        destruir_pilha(&pilha);
        return 3;
    }

    destruir_pilha(&pilha);
    return 0;
}



