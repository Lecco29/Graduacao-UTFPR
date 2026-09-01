#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
int main(){
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();

    int i;
    for(i=0; i < N; i++)
        insere_ArvBin(raiz,dados[i]);

    printf("testes dos exercicios\n\n");

    // questao 1: insercao e remocao
    printf("--- questao 1 ---\n");
    printf("arvore apos insercoes (pre-ordem):\n");
    preOrdem_ArvBin(raiz);
    printf("\n");

    // questao 2: varreduras
    printf("--- questao 2 ---\n");
    printf("pre-ordem:\n");
    preOrdem_ArvBin(raiz);
    printf("\n");

    printf("em-ordem:\n");
    emordemarvore(raiz);
    printf("\n");

    printf("pos-ordem:\n");
    posordemarvbin(raiz);
    printf("\n");

    // questao 3: total de nos
    printf("--- questao 3 ---\n");
    printf("total de nos: %d\n\n", totalnoarvore(raiz));

    // questao 4: consulta
    printf("--- questao 4 ---\n");
    int valorBusca = 45;
    if(consarvore(raiz, valorBusca))
        printf("valor %d encontrado\n", valorBusca);
    else
        printf("valor %d nao encontrado\n", valorBusca);

    valorBusca = 99;
    if(consarvore(raiz, valorBusca))
        printf("valor %d encontrado\n", valorBusca);
    else
        printf("valor %d nao encontrado\n", valorBusca);
    printf("\n");

    // questao 5: remocao
    printf("--- questao 5 ---\n");
    printf("removendo valor 50 (raiz)...\n");
    if(remove_ArvBin(raiz, 50)){
        printf("removido com sucesso!\n");
        printf("arvore apos remocao (em-ordem):\n");
        emordemarvore(raiz);
    } else
        printf("nao removido\n");
    printf("\n");

    printf("total de nos apos remocao: %d\n\n", totalnoarvore(raiz));
    printf("altura da arvore: %d\n", altura_ArvBin(raiz));

    libera_ArvBin(raiz);
    printf("\nfim!\n");
    return 0;
}
