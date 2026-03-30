#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;
            }
            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int altura_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if(alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

int totalNO_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    return 1 + totalNO_ArvBin(&((*raiz)->esq)) + totalNO_ArvBin(&((*raiz)->dir));
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info)
            return 1;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d ", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d ", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d ", (*raiz)->info);
    }
}

// exercicio 1
// conta nos folha da arvore
int conta_folhas(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return 0;
    // se nao tem filhos, eh folha
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        return 1;
    return conta_folhas(&((*raiz)->esq)) + conta_folhas(&((*raiz)->dir));
}

// exercicio 2
// imprime arvore mostrando tipo de cada no
void imprime_no(struct NO* no, struct NO* pai, int nivel){
    if(no == NULL)
        return;

    imprime_no(no->esq, no, nivel + 1);

    int i;
    for(i = 0; i < nivel; i++)
        printf("   ");

    if(pai == NULL)
        printf("%d (raiz)\n", no->info);
    else if(no->esq == NULL && no->dir == NULL)
        printf("%d (folha, pai: %d)\n", no->info, pai->info);
    else
        printf("%d (interno, pai: %d)\n", no->info, pai->info);

    imprime_no(no->dir, no, nivel + 1);
}

void imprime_arvore(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL){
        printf("arvore vazia\n");
        return;
    }
    imprime_no(*raiz, NULL, 0);
}

// exercicio 3
// conta quantas vezes valor aparece na arvore
int conta_valor(ArvBin *raiz, int valor){
    if(raiz == NULL || *raiz == NULL)
        return 0;
    int cont = 0;
    if((*raiz)->info == valor)
        cont = 1;
    return cont + conta_valor(&((*raiz)->esq), valor) + conta_valor(&((*raiz)->dir), valor);
}

// exercicio 4
// imprime folhas em ordem decrescente
void folhas_decrescente(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    // percorre direita primeiro pra sair decrescente
    folhas_decrescente(&((*raiz)->dir));
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        printf("%d ", (*raiz)->info);
    folhas_decrescente(&((*raiz)->esq));
}

// exercicio 5
// verifica se duas arvores sao iguais
int arvores_iguais(ArvBin *raiz1, ArvBin *raiz2){
    if(raiz1 == NULL && raiz2 == NULL)
        return 1;
    if(raiz1 == NULL || raiz2 == NULL)
        return 0;
    if(*raiz1 == NULL && *raiz2 == NULL)
        return 1;
    if(*raiz1 == NULL || *raiz2 == NULL)
        return 0;
    if((*raiz1)->info != (*raiz2)->info)
        return 0;
    return arvores_iguais(&((*raiz1)->esq), &((*raiz2)->esq)) &&
           arvores_iguais(&((*raiz1)->dir), &((*raiz2)->dir));
}

// exercicio 6
// elimina todos os pares da arvore
void elimina_pares(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;

    // pos-ordem pra nao perder referencia
    elimina_pares(&((*raiz)->esq));
    elimina_pares(&((*raiz)->dir));

    // ve se o no atual eh par
    if((*raiz)->info % 2 == 0)
        remove_ArvBin(raiz, (*raiz)->info);
}

// exercicio 7
// verifica se duas arvores sao similares (mesma estrutura)
int arvores_similares(ArvBin *raiz1, ArvBin *raiz2){
    if(raiz1 == NULL && raiz2 == NULL)
        return 1;
    if(raiz1 == NULL || raiz2 == NULL)
        return 0;
    if(*raiz1 == NULL && *raiz2 == NULL)
        return 1;
    if(*raiz1 == NULL || *raiz2 == NULL)
        return 0;
    return arvores_similares(&((*raiz1)->esq), &((*raiz2)->esq)) &&
           arvores_similares(&((*raiz1)->dir), &((*raiz2)->dir));
}

// exercicio 8
// percurso imprimindo como char (pra arvore de letras)
void emOrdem_char(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_char(&((*raiz)->esq));
        printf("%c ", (*raiz)->info);
        emOrdem_char(&((*raiz)->dir));
    }
}

void preOrdem_char(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%c ", (*raiz)->info);
        preOrdem_char(&((*raiz)->esq));
        preOrdem_char(&((*raiz)->dir));
    }
}

void imprime_no_char(struct NO* no, struct NO* pai, int nivel){
    if(no == NULL)
        return;

    imprime_no_char(no->esq, no, nivel + 1);

    int i;
    for(i = 0; i < nivel; i++)
        printf("   ");

    if(pai == NULL)
        printf("%c (raiz)\n", no->info);
    else if(no->esq == NULL && no->dir == NULL)
        printf("%c (folha, pai: %c)\n", no->info, pai->info);
    else
        printf("%c (interno, pai: %c)\n", no->info, pai->info);

    imprime_no_char(no->dir, no, nivel + 1);
}

void imprime_arvore_char(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL){
        printf("arvore vazia\n");
        return;
    }
    imprime_no_char(*raiz, NULL, 0);
}

// exercicio 9
// monta arvore de expressao a partir de notacao posfixa
int insere_expressao(ArvBin *raiz, char *expressao){
    if(raiz == NULL || expressao == NULL)
        return 0;

    // usa pilha de nos pra montar a arvore
    struct NO* pilha[100];
    int topo = -1;
    int i;

    for(i = 0; expressao[i] != '\0'; i++){
        char c = expressao[i];
        if(c == ' ')
            continue;

        struct NO* novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        novo->esq = NULL;
        novo->dir = NULL;

        if(c >= '0' && c <= '9'){
            novo->info = c - '0';
            topo++;
            pilha[topo] = novo;
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/'){
            novo->info = c;
            if(topo < 1){
                free(novo);
                return 0;
            }
            novo->dir = pilha[topo]; topo--;
            novo->esq = pilha[topo]; topo--;
            topo++;
            pilha[topo] = novo;
        }
    }

    if(topo == 0)
        *raiz = pilha[0];

    return 1;
}

// calcula resultado da expressao
float calcula_expressao(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return 0;
    int info = (*raiz)->info;

    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        return (float)info;

    float esq = calcula_expressao(&((*raiz)->esq));
    float dir = calcula_expressao(&((*raiz)->dir));

    switch(info){
        case '+': return esq + dir;
        case '-': return esq - dir;
        case '*': return esq * dir;
        case '/': return (dir != 0) ? esq / dir : 0;
    }
    return 0;
}

// imprime notacao infixa
void imprime_infixa(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    int info = (*raiz)->info;
    int eh_operador = (info == '+' || info == '-' || info == '*' || info == '/');

    if(eh_operador) printf("(");
    imprime_infixa(&((*raiz)->esq));
    if(eh_operador)
        printf(" %c ", info);
    else
        printf("%d", info);
    imprime_infixa(&((*raiz)->dir));
    if(eh_operador) printf(")");
}

// imprime notacao prefixa
void imprime_prefixa(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    int info = (*raiz)->info;
    if(info == '+' || info == '-' || info == '*' || info == '/')
        printf("%c ", info);
    else
        printf("%d ", info);
    imprime_prefixa(&((*raiz)->esq));
    imprime_prefixa(&((*raiz)->dir));
}

// imprime notacao posfixa
void imprime_posfixa(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)
        return;
    imprime_posfixa(&((*raiz)->esq));
    imprime_posfixa(&((*raiz)->dir));
    int info = (*raiz)->info;
    if(info == '+' || info == '-' || info == '*' || info == '/')
        printf("%c ", info);
    else
        printf("%d ", info);
}
