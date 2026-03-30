#include <stdio.h>
#include <stdlib.h>
#include "PilhaDin.h"

int main(){
    Pilha* pi = cria_Pilha();

    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};

    // empilha os alunos
    int i;
    for(i = 0; i < 4; i++)
        insere_Pilha(pi, a[i]);

    printf("pilha com %d elementos\n", tamanho_Pilha(pi));
    imprime_Pilha(pi);

    // teste pop2
    printf("\ntestando pop2:\n");
    pop2(pi);
    printf("apos pop2 - tamanho: %d\n", tamanho_Pilha(pi));

    // teste push2
    struct aluno n1 = {5, "Carlos", 8.0, 7.5, 9.0};
    struct aluno n2 = {6, "Maria", 6.5, 8.0, 7.5};
    push2(pi, n1, n2);
    printf("apos push2 - tamanho: %d\n", tamanho_Pilha(pi));

    // teste popN
    printf("\ntestando popN(3):\n");
    popN(pi, 3);
    printf("tamanho apos popN: %d\n", tamanho_Pilha(pi));

    // teste copia
    insere_Pilha(pi, a[0]);
    insere_Pilha(pi, a[1]);
    Pilha* copia = pilha_copia(pi);
    if(copia != NULL){
        printf("\npilha original:\n");
        imprime_Pilha(pi);
        printf("copia:\n");
        imprime_Pilha(copia);
        libera_Pilha(copia);
    }

    // teste maior menor media
    int maior, menor;
    float media;
    maior_menor_media(pi, &maior, &menor, &media);
    printf("\nmaior: %d, menor: %d, media: %.2f\n", maior, menor, media);

    // teste pares e impares
    int pares, impares;
    conta_pares_impares(pi, &pares, &impares);
    printf("pares: %d, impares: %d\n", pares, impares);

    // teste palindromo
    char texto[] = "arara";
    if(verifica_palindromo(texto))
        printf("\n%s e palindromo\n", texto);
    else
        printf("\n%s nao e palindromo\n", texto);

    // teste cadeia xCy
    char cadeia[] = "ABCBA";
    if(verifica_cadeia_xCy(cadeia))
        printf("%s segue o padrao xCy\n", cadeia);
    else
        printf("%s nao segue xCy\n", cadeia);

    // teste pilhas iguais
    Pilha* pi2 = cria_Pilha();
    insere_Pilha(pi2, a[0]);
    insere_Pilha(pi2, a[1]);
    if(pilhas_iguais(pi, pi2))
        printf("\npilhas iguais\n");
    else
        printf("\npilhas diferentes\n");
    libera_Pilha(pi2);

    libera_Pilha(pi);
    return 0;
}
