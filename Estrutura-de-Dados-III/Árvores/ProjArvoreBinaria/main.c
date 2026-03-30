#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main(){
    int i;

    // exercicio 1
    printf("-- exercicio 1: contar nos folha\n");
    ArvBin* raiz = cria_ArvBin();
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    for(i = 0; i < 7; i++)
        insere_ArvBin(raiz, valores[i]);

    printf("arvore (em ordem): ");
    emOrdem_ArvBin(raiz);
    printf("\nnos folha: %d\n", conta_folhas(raiz));

    // exercicio 2
    printf("\n-- exercicio 2: imprimir arvore\n");
    imprime_arvore(raiz);

    // exercicio 3
    printf("\n-- exercicio 3: contar ocorrencias\n");
    printf("valor 50 aparece %d vez(es)\n", conta_valor(raiz, 50));
    printf("valor 99 aparece %d vez(es)\n", conta_valor(raiz, 99));

    // exercicio 4
    printf("\n-- exercicio 4: folhas decrescente\n");
    printf("folhas decrescente: ");
    folhas_decrescente(raiz);
    printf("\n");

    // exercicio 5
    printf("\n-- exercicio 5: arvores iguais\n");
    ArvBin* raiz2 = cria_ArvBin();
    for(i = 0; i < 7; i++)
        insere_ArvBin(raiz2, valores[i]);

    if(arvores_iguais(raiz, raiz2))
        printf("as arvores sao iguais\n");
    else
        printf("as arvores sao diferentes\n");

    insere_ArvBin(raiz2, 99);
    if(arvores_iguais(raiz, raiz2))
        printf("apos inserir 99: as arvores sao iguais\n");
    else
        printf("apos inserir 99: as arvores sao diferentes\n");

    libera_ArvBin(raiz2);
    libera_ArvBin(raiz);

    // exercicio 6
    printf("\n-- exercicio 6: eliminar pares\n");
    ArvBin* raiz_pares = cria_ArvBin();
    int valores_pares[] = {45, 30, 73, 20, 37, 60, 81};
    for(i = 0; i < 7; i++)
        insere_ArvBin(raiz_pares, valores_pares[i]);

    printf("antes: ");
    emOrdem_ArvBin(raiz_pares);
    printf("\n");
    elimina_pares(raiz_pares);
    printf("depois (sem pares): ");
    emOrdem_ArvBin(raiz_pares);
    printf("\n");

    libera_ArvBin(raiz_pares);

    // exercicio 7
    printf("\n-- exercicio 7: arvores similares\n");
    ArvBin* arv1 = cria_ArvBin();
    ArvBin* arv2_sim = cria_ArvBin();

    insere_ArvBin(arv1, 10);
    insere_ArvBin(arv1, 5);
    insere_ArvBin(arv1, 15);

    insere_ArvBin(arv2_sim, 20);
    insere_ArvBin(arv2_sim, 8);
    insere_ArvBin(arv2_sim, 30);

    if(arvores_similares(arv1, arv2_sim))
        printf("arvores sao similares (mesma estrutura)\n");
    else
        printf("arvores nao sao similares\n");

    insere_ArvBin(arv2_sim, 3);
    if(arvores_similares(arv1, arv2_sim))
        printf("apos inserir: arvores sao similares\n");
    else
        printf("apos inserir: arvores nao sao similares\n");

    libera_ArvBin(arv1);
    libera_ArvBin(arv2_sim);

    // exercicio 8
    printf("\n-- exercicio 8: arvore de chars\n");
    ArvBin* arv_char = cria_ArvBin();
    char letras[] = {'M','F','S','D','J','P','U','A','E','H','Q','T','W','K'};
    int n = 14;

    printf("inserindo na ordem: ");
    for(i = 0; i < n; i++){
        printf("%c ", letras[i]);
        insere_ArvBin(arv_char, letras[i]);
    }
    printf("\n");

    printf("pre-ordem: ");
    preOrdem_char(arv_char);
    printf("\n");

    printf("em-ordem (ordem alfabetica): ");
    emOrdem_char(arv_char);
    printf("\n");

    printf("\nestrutura da arvore:\n");
    imprime_arvore_char(arv_char);

    libera_ArvBin(arv_char);

    // exercicio 9
    printf("\n-- exercicio 9: arvore de expressao\n");
    // (6-3) * (4-1) + 5
    // em notacao posfixa: 6 3 - 4 1 - * 5 +
    ArvBin* arv_exp = cria_ArvBin();
    char* expressao = "63-41-*5+";

    printf("expressao posfixa: %s\n", expressao);
    insere_expressao(arv_exp, expressao);

    float resultado = calcula_expressao(arv_exp);
    printf("resultado: %.0f\n", resultado);

    printf("infixa: ");
    imprime_infixa(arv_exp);
    printf("\n");

    printf("prefixa: ");
    imprime_prefixa(arv_exp);
    printf("\n");

    printf("posfixa: ");
    imprime_posfixa(arv_exp);
    printf("\n");

    libera_ArvBin(arv_exp);

    printf("\nfim!\n");
    return 0;
}
