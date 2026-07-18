#include "alfabeto.h"

int tamanho_array_caracteres(const unsigned char array_caracteres[])
{
        if(!array_caracteres) return - 1;

        int tamanho = 0;
        while(array_caracteres[tamanho] != '\0'){
            tamanho++;
        }

        return tamanho;
}


int preenche_aberturas_correspondentes(const unsigned char simbolos_aberturas[],
                                       const unsigned char simbolos_fechamentos[],
                                       struct tabelasAlfabeto *tabela_alfabeto)
{
    if(!simbolos_aberturas) return -1;
    if(!simbolos_fechamentos) return -2;
    if(!tabela_alfabeto) return -3;

    unsigned int i = 0;
    unsigned char *mapa = tabela_alfabeto->aberturas_correspondentes;

    while(simbolos_fechamentos[i] != '\0'){

        unsigned char c_fechamento = simbolos_fechamentos[i];
        unsigned char c_abertura = simbolos_aberturas[i];

        mapa[c_fechamento] = c_abertura;
        i++;
    }

    return 0;
}


int preenche_eh_abertura_eh_fechamento(const unsigned char simbolos_aberturas[],
                                       const unsigned char simbolos_fechamentos[],
                                       struct tabelasAlfabeto *tabela_alfabeto)
{
    if(!simbolos_aberturas) return -1;
    if(!simbolos_fechamentos) return -2;
    if(!tabela_alfabeto) return -3;

    for(unsigned int i = 0; i < TAMANHO_ARRAYS; i++){
        tabela_alfabeto->eh_abertura[i] = false;
        tabela_alfabeto->eh_fechamento[i] = false;
    }

    unsigned int i = 0;
    while(simbolos_aberturas[i] != '\0'){

        unsigned char c_abertura = simbolos_aberturas[i];
        unsigned char c_fechamento = simbolos_fechamentos[i];

        tabela_alfabeto->eh_abertura[c_abertura] = true;
        tabela_alfabeto->eh_fechamento[c_fechamento] = true;

        i++;
    }

    return 0;
}

int preenche_tabelas_alfabeto(const unsigned char simbolos_aberturas[],
                              const unsigned char simbolos_fechamentos[],
                              struct tabelasAlfabeto *tabela_alfabeto)
{
    if(!simbolos_aberturas) return -1;
    if(!simbolos_fechamentos) return -2;
    if(!tabela_alfabeto) return -3;

    int tam_aberturas = tamanho_array_caracteres(simbolos_aberturas);
    int tam_fechamentos = tamanho_array_caracteres(simbolos_fechamentos);

    if(tam_aberturas != tam_fechamentos){
        return -4;
    }

    int status_aberturas = preenche_aberturas_correspondentes(simbolos_aberturas, simbolos_fechamentos, tabela_alfabeto);
    if(status_aberturas != 0){
        return -5;
    }

    int status_flags = preenche_eh_abertura_eh_fechamento(simbolos_aberturas, simbolos_fechamentos, tabela_alfabeto);
    if(status_flags != 0){
        return -6;
    }

    return 0;
}

