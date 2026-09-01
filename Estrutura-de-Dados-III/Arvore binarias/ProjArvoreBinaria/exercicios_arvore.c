#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

// exercicio 1 - insere e remove
void exercicio1() {
    printf("exercicio 1\n\n");

    ArvBin* raiz = cria_ArvBin();

    printf("Inserindo valores: 50, 30, 70, 20, 40, 60, 80\n");
    insere_ArvBin(raiz, 50);
    insere_ArvBin(raiz, 30);
    insere_ArvBin(raiz, 70);
    insere_ArvBin(raiz, 20);
    insere_ArvBin(raiz, 40);
    insere_ArvBin(raiz, 60);
    insere_ArvBin(raiz, 80);

    printf("Arvore (pre-ordem):\n");
    preOrdem_ArvBin(raiz);

    printf("\nRemovendo valor 30:\n");
    if(remove_ArvBin(raiz, 30)) {
        printf("Removido com sucesso!\n");
        printf("Arvore apos remocao (pre-ordem):\n");
        preOrdem_ArvBin(raiz);
    } else {
        printf("Valor nao encontrado!\n");
    }

    libera_ArvBin(raiz);
    printf("\n");
}

// exercicio 2 - percursos
void exercicio2() {
    printf("exercicio 2\n\n");

    ArvBin* raiz = cria_ArvBin();

    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = 7;

    printf("Inserindo valores: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");

    printf("PRE-ORDEM:\n");
    preOrdem_ArvBin(raiz);
    printf("\n");

    printf("EM-ORDEM:\n");
    emordemarvore(raiz);
    printf("\n");

    printf("POS-ORDEM:\n");
    posordemarvbin(raiz);
    printf("\n");

    libera_ArvBin(raiz);
}

// exercicio 3 - conta nos
void exercicio3() {
    printf("exercicio 3\n\n");

    ArvBin* raiz = cria_ArvBin();

    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = 11;

    printf("Inserindo %d valores: ", n);
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");

    printf("Arvore (pre-ordem):\n");
    preOrdem_ArvBin(raiz);
    printf("\n");

    printf("Total de nos: %d\n", totalnoarvore(raiz));

    libera_ArvBin(raiz);
    printf("\n");
}

// exercicio 4 - consulta valor
void exercicio4() {
    printf("exercicio 4\n\n");

    ArvBin* raiz = cria_ArvBin();

    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = 11;

    printf("Inserindo valores: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");

    int consultas[] = {50, 25, 100, 35, 5, 80};
    int m = 6;

    printf("Testando consultas:\n");
    for(int i = 0; i < m; i++) {
        int valor = consultas[i];
        if(consarvore(raiz, valor))
            printf("Valor %d: ENCONTRADO\n", valor);
        else
            printf("Valor %d: NAO ENCONTRADO\n", valor);
    }

    libera_ArvBin(raiz);
    printf("\n");
}

// exercicio 5 - remocao de nos
void exercicio5() {
    printf("exercicio 5\n\n");

    ArvBin* raiz = cria_ArvBin();

    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = 11;

    printf("Inserindo valores: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");

    printf("Arvore original (pre-ordem):\n");
    preOrdem_ArvBin(raiz);
    printf("\n");

    printf("Removendo no 10 (sem filhos):\n");
    if(remove_ArvBin(raiz, 10)) {
        printf("Removido!\n");
        preOrdem_ArvBin(raiz);
    }
    printf("\n");

    printf("Removendo no 20 (com 1 filho):\n");
    if(remove_ArvBin(raiz, 20)) {
        printf("Removido!\n");
        preOrdem_ArvBin(raiz);
    }
    printf("\n");

    printf("Removendo no 30 (com 2 filhos):\n");
    if(remove_ArvBin(raiz, 30)) {
        printf("Removido!\n");
        preOrdem_ArvBin(raiz);
    }

    libera_ArvBin(raiz);
    printf("\n");
}

void menu() {
    printf("exercicios de arvore binaria\n\n");
    printf("1. Testar insere e remove\n");
    printf("2. Percursos em ordem e pos-ordem\n");
    printf("3. Contar nos da arvore\n");
    printf("4. Consultar valor\n");
    printf("5. Remover no especifico\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao) {
            case 1: exercicio1(); break;
            case 2: exercicio2(); break;
            case 3: exercicio3(); break;
            case 4: exercicio4(); break;
            case 5: exercicio5(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n"); break;
        }

        if(opcao != 0) {
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
            printf("\n");
        }

    } while(opcao != 0);

    return 0;
}
