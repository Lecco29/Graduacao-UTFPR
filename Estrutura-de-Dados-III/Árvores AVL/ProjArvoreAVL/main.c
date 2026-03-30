#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(){
    ArvAVL* avl;
    int res,i;
    int N = 10, dados[10] = {1,2,3,10,4,5,9,7,8,6};

    avl = cria_ArvAVL();

    for(i=0;i<N;i++){
        res = insere_ArvAVL(avl,dados[i]);
    }

    printf("\navl tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,6);
    printf("\navl tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,7);
    printf("\navl tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,4);
    printf("\navl tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    // questao 4: rotacaorr eh usada automaticamente nas insercoes/remocoes
    printf("\nquestao 4: rotacaorr\n");
    printf("a rotacao rr ja foi usada nas insercoes acima\n");

    // questao 7: verifica se eh avl
    printf("\nquestao 7: verifica se eh avl\n");
    if(verificaavl(avl))
        printf("a arvore eh uma avl valida!\n");
    else
        printf("a arvore nao eh uma avl valida!\n");

    // questao 8: transforma abb em avl
    printf("\nquestao 8: transforma abb em avl\n");
    ArvAVL* abb = cria_ArvAVL();
    int dados_abb[] = {50, 30, 20, 10, 5, 70, 80, 90, 100};
    int n_abb = 9;
    for(i = 0; i < n_abb; i++){
        insere_ArvAVL(abb, dados_abb[i]);
    }
    printf("abb criada (em ordem):\n");
    emOrdem_ArvAVL(abb);

    printf("\ntransformando em avl...\n");
    ArvAVL* avl_transformada = transformaavl(abb);
    if(avl_transformada != NULL){
        printf("avl transformada (em ordem):\n");
        emOrdem_ArvAVL(avl_transformada);
        if(verificaavl(avl_transformada))
            printf("eh avl valida!\n");
        else
            printf("nao eh avl valida\n");
        libera_ArvAVL(avl_transformada);
    }
    libera_ArvAVL(abb);

    libera_ArvAVL(avl);

    printf("\nfim\n");
    return 0;
}
