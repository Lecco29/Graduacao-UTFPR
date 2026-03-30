#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
int main(){
    int eh_digrafo = 1;
    Grafo* gr = cria_Grafo(5, 5, 0);

    insereAresta(gr, 0, 1, eh_digrafo, 0);
    insereAresta(gr, 1, 3, eh_digrafo, 0);
    insereAresta(gr, 1, 2, eh_digrafo, 0);
    insereAresta(gr, 2, 4, eh_digrafo, 0);
    insereAresta(gr, 3, 0, eh_digrafo, 0);
    insereAresta(gr, 3, 4, eh_digrafo, 0);
    insereAresta(gr, 4, 1, eh_digrafo, 0);

    imprime_Grafo(gr);
    printf("\nbusca \n");

    libera_Grafo(gr);

    // questao 5: teste algoritmo de prim
    printf("\nquestao 5: algoritmo de prim\n");
    Grafo* gr_prim = cria_Grafo(5, 5, 1);
    if(gr_prim != NULL){
        insereAresta(gr_prim, 0, 1, 0, 2.0);
        insereAresta(gr_prim, 0, 3, 0, 6.0);
        insereAresta(gr_prim, 1, 2, 0, 3.0);
        insereAresta(gr_prim, 1, 3, 0, 8.0);
        insereAresta(gr_prim, 1, 4, 0, 5.0);
        insereAresta(gr_prim, 2, 4, 0, 7.0);
        insereAresta(gr_prim, 3, 4, 0, 9.0);

        printf("grafo para prim:\n");
        imprime_Grafo(gr_prim);

        int* pais_prim = (int*) malloc(5 * sizeof(int));
        float custo = algoritmoprim(gr_prim, 0, pais_prim);

        if(custo >= 0){
            printf("\narvore geradora minima:\n");
            printf("custo total: %.2f\n", custo);
            printf("pais:\n");
            int i;
            for(i = 0; i < 5; i++){
                printf("vertice %d -> pai: %d\n", i, pais_prim[i]);
            }
        } else {
            printf("erro ao executar prim!\n");
        }

        free(pais_prim);
        libera_Grafo(gr_prim);
    }

    // questao 6a: teste encontra no
    printf("\nquestao 6a: encontra no\n");
    Grafo* gr_teste = cria_Grafo(5, 5, 0);
    if(encontrano(gr_teste, 0))
        printf("no 0 encontrado!\n");
    else
        printf("no 0 nao encontrado!\n");

    if(encontrano(gr_teste, 10))
        printf("no 10 encontrado!\n");
    else
        printf("no 10 nao encontrado (esperado)!\n");
    libera_Grafo(gr_teste);

    // questao 6b: teste aresta de menor peso
    printf("\nquestao 6b: aresta de menor peso\n");
    Grafo* gr_peso = cria_Grafo(4, 4, 1);
    if(gr_peso != NULL){
        insereAresta(gr_peso, 0, 1, 0, 5.0);
        insereAresta(gr_peso, 0, 2, 0, 3.0);
        insereAresta(gr_peso, 1, 3, 0, 2.0);
        insereAresta(gr_peso, 2, 3, 0, 4.0);

        printf("grafo para teste:\n");
        imprime_Grafo(gr_peso);

        int orig, dest;
        float peso;
        if(encontraarestamenorpeso(gr_peso, &orig, &dest, &peso)){
            printf("aresta de menor peso: %d -> %d (peso: %.2f)\n", orig, dest, peso);
        } else {
            printf("nao achou aresta de menor peso!\n");
        }

        libera_Grafo(gr_peso);
    }

    // questao 4: teste nova estrutura
    printf("\nquestao 4: nova estrutura com lista** vet\n");
    GrafoNovo* gr_novo = criagrafonovo(4, 1);
    if(gr_novo != NULL){
        printf("novo grafo criado com 4 nos\n");

        inserearestagrafonovo(gr_novo, 0, 1, 0, 2.5);
        inserearestagrafonovo(gr_novo, 0, 2, 0, 1.5);
        inserearestagrafonovo(gr_novo, 1, 3, 0, 3.0);
        inserearestagrafonovo(gr_novo, 2, 3, 0, 2.0);

        printf("novo grafo:\n");
        imprimegrafonovo(gr_novo);

        printf("\nremovendo aresta 0-2:\n");
        removearestagrafonovo(gr_novo, 0, 2, 0);
        imprimegrafonovo(gr_novo);

        liberagrafonovo(gr_novo);
    }

    printf("\nfim\n");

    system("pause");
    return 0;
}
