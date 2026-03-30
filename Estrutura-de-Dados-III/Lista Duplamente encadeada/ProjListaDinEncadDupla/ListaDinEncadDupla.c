#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

// elemento da lista dupla
struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}

// Questao 1: remove por matricula
int remove_lista_matricula(Lista* li, int matricula){
    if(li == NULL)
        return 0;
    if(*li == NULL)
        return 0;

    Elem *no = *li;

    while(no != NULL && no->dados.matricula != matricula){
        no = no->prox;
    }

    if(no == NULL)
        return 0;

    if(no->ant == NULL){
        // primeiro elemento
        *li = no->prox;
        if(no->prox != NULL)
            no->prox->ant = NULL;
    }
    else if(no->prox == NULL){
        // ultimo elemento
        no->ant->prox = NULL;
    }
    else{
        // elemento do meio
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
    }

    free(no);
    return 1;
}

// Questao 2: insere ordenado por matricula
int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;

    no->dados = al;

    if(*li == NULL){
        no->ant = NULL;
        no->prox = NULL;
        *li = no;
        return 1;
    }

    Elem *atual = *li;
    Elem *anterior = NULL;

    while(atual != NULL && atual->dados.matricula < al.matricula){
        anterior = atual;
        atual = atual->prox;
    }

    if(anterior == NULL){
        // insere no inicio
        no->ant = NULL;
        no->prox = *li;
        if(*li != NULL)
            (*li)->ant = no;
        *li = no;
    }
    else{
        // insere no meio ou fim
        no->ant = anterior;
        no->prox = atual;
        anterior->prox = no;
        if(atual != NULL)
            atual->ant = no;
    }

    return 1;
}

// Questao 3: conta alunos com nota especifica
int conta_lista_nota(Lista* li, int n1){
    if(li == NULL)
        return 0;

    int contador = 0;
    Elem *no = *li;

    while(no != NULL){
        if(no->dados.n1 == n1){
            contador++;
        }
        no = no->prox;
    }

    return contador;
}

// Questao 4: funcoes pra lista circular

// insere no inicio da circular
int insere_lista_inicio_circular(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;

    no->dados = al;

    if(*li == NULL){
        no->ant = no;
        no->prox = no;
        *li = no;
    }
    else{
        Elem *ultimo = *li;
        while(ultimo->prox != *li){
            ultimo = ultimo->prox;
        }

        no->ant = ultimo;
        no->prox = *li;
        (*li)->ant = no;
        ultimo->prox = no;
        *li = no;
    }

    return 1;
}

// insere no final da circular
int insere_lista_final_circular(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;

    no->dados = al;

    if(*li == NULL){
        no->ant = no;
        no->prox = no;
        *li = no;
    }
    else{
        Elem *ultimo = *li;
        while(ultimo->prox != *li){
            ultimo = ultimo->prox;
        }

        no->ant = ultimo;
        no->prox = *li;
        ultimo->prox = no;
        (*li)->ant = no;
    }

    return 1;
}

// remove do inicio da circular
int remove_lista_inicio_circular(Lista* li){
    if(li == NULL)
        return 0;
    if(*li == NULL)
        return 0;

    Elem *no = *li;

    if(no->prox == no){
        // so tem um elemento
        *li = NULL;
    }
    else{
        Elem *ultimo = *li;
        while(ultimo->prox != *li){
            ultimo = ultimo->prox;
        }

        Elem *proximo = no->prox;
        ultimo->prox = proximo;
        proximo->ant = ultimo;
        *li = proximo;
    }

    free(no);
    return 1;
}

// remove do final da circular
int remove_lista_final_circular(Lista* li){
    if(li == NULL)
        return 0;
    if(*li == NULL)
        return 0;

    Elem *ultimo = *li;
    while(ultimo->prox != *li){
        ultimo = ultimo->prox;
    }

    if(ultimo == *li){
        // so tem um elemento
        *li = NULL;
    }
    else{
        Elem *penultimo = ultimo->ant;
        penultimo->prox = *li;
        (*li)->ant = penultimo;
    }

    free(ultimo);
    return 1;
}

// percorre e imprime a lista circular
void percorre_lista_circular(Lista* li){
    if(li == NULL)
        return;
    if(*li == NULL)
        return;

    Elem *p = *li;

    do{
        printf("Matricula: %d\n", p->dados.matricula);
        printf("Nome: %s\n", p->dados.nome);
        printf("Notas: %f %f %f\n", p->dados.n1, p->dados.n2, p->dados.n3);
        printf("-------------------------------\n");

        p = p->prox;
    } while(p != *li);
}

// Questao 5: fila usando ponteiros

int inicializa_fila(Lista* li){
    if(li == NULL)
        return 0;
    *li = NULL;
    return 1;
}

// enfileira no final
int enfileirar(Lista* li, int elem){
    if(li == NULL)
        return 0;

    Elem *novo = (Elem*)malloc(sizeof(Elem));
    if(novo == NULL)
        return 0;

    novo->dados.matricula = elem;
    novo->prox = NULL;
    novo->ant = NULL;

    if(*li == NULL){
        *li = novo;
    }
    else{
        Elem *aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }

    return 1;
}

// desenfileira do inicio
int desenfileirar(Lista* li, int *elem){
    if(li == NULL)
        return 0;
    if(*li == NULL)
        return 0;

    Elem *aux = *li;
    *elem = aux->dados.matricula;

    if(aux->prox == NULL){
        *li = NULL;
    }
    else{
        *li = aux->prox;
        (*li)->ant = NULL;
    }

    free(aux);
    return 1;
}
