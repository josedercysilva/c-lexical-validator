#include <stdio.h>
#include "valida_string_simbolos.h"


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
