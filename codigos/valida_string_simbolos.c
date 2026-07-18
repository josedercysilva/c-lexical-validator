#include <stdio.h>
#include <stddef.h>
#include "alfabeto.h"
#include "pilha.h"

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



int main(void)
{


    const unsigned char cadeia_analise_pares[] = "$?([][{{}}])";




    printf(" Analisador de Cadeias - dercy\n");
    printf("Testando a expressao: %s\n", cadeia_analise_pares);

    int resultado = analisar_cadeia(cadeia_analise_pares);


    switch(resultado){
        case 0:
            printf("Status 0: A expressao esta CORRETA e BALANCEADA.\n");
            break;

        case 1:
            printf("Erro 1: Fechamento prematuro. O simbolo de fechamento nao possui abertura correspondente, Pilha vazia.\n");
            break;

        case 2:
            printf("Erro 2: Incompatibilidade. O simbolo de fechamento nao corresponde a ultima abertura.\n");
            break;

        case 3:
            printf("Erro 3: Faltam fechamentos. A expressao terminou, mas sobraram aberturas na memoria.\n");
            break;

        case -11:
            printf("Erro Critico -11: Falha de alocacao de memoria ou ponteiro invalido detectado.\n");
            break;
        case -13:
            printf("Erro -13: algum dos simbolos da string não são reconhecidos no alfabeto\n");
            return 1;
        default:
            if(resultado < 0){
                printf("Erro Interno [%d]: Falha ao carregar as tabelas do alfabeto.\n", resultado);
            } else {
                printf("Erro Desconhecido [%d].\n", resultado);
            }
            return 1;
    }

    return 0;
}
