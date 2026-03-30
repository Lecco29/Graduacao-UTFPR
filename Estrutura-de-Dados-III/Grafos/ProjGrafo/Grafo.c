#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

// estrutura do grafo com matriz de adjacencia
struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};

// cria grafo
Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0)?1:0;
        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for(i=0; i<nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->eh_ponderado){
            gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
            for(i=0; i<nro_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }

    }
    return gr;
}

// libera grafo
void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->eh_ponderado){
            for(i=0; i<gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(eh_digrafo == 0)
        insereAresta(gr,dest,orig,1,peso);
    return 1;
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig])
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if(gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if(eh_digrafo == 0)
        removeAresta(gr,dest,orig,1);
    return 1;
}

void imprime_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->nro_vertices; i++){
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){
            if(gr->eh_ponderado)
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("%d, ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

// questao 5: algoritmo de prim pra arvore geradora minima
float algoritmoprim(Grafo* gr, int origem, int* pais){
    if(gr == NULL)
        return -1;
    if(!gr->eh_ponderado)
        return -1;
    if(origem < 0 || origem >= gr->nro_vertices)
        return -1;

    float* dist = (float*) malloc(gr->nro_vertices * sizeof(float));
    int* incluido = (int*) calloc(gr->nro_vertices, sizeof(int));

    int i;
    for(i = 0; i < gr->nro_vertices; i++){
        dist[i] = 999999.0;
        pais[i] = -1;
    }

    dist[origem] = 0.0;
    pais[origem] = origem;

    float custo_total = 0.0;
    int u, v, j;

    for(i = 0; i < gr->nro_vertices - 1; i++){
        // acha vertice com menor distancia nao incluido
        u = -1;
        float menor_dist = 999999.0;
        for(j = 0; j < gr->nro_vertices; j++){
            if(!incluido[j] && dist[j] < menor_dist){
                menor_dist = dist[j];
                u = j;
            }
        }

        if(u == -1)
            break;

        incluido[u] = 1;
        custo_total += dist[u];

        // atualiza distancias dos adjacentes
        for(j = 0; j < gr->grau[u]; j++){
            v = gr->arestas[u][j];
            float peso = gr->pesos[u][j];

            if(!incluido[v] && peso < dist[v]){
                dist[v] = peso;
                pais[v] = u;
            }
        }
    }

    free(dist);
    free(incluido);

    return custo_total;
}

// questao 6a: verifica se no existe no grafo
int encontrano(Grafo* gr, int no){
    if(gr == NULL)
        return 0;
    if(no < 0 || no >= gr->nro_vertices)
        return 0;
    return 1;
}

// questao 6b: acha aresta de menor peso
int encontraarestamenorpeso(Grafo* gr, int* orig, int* dest, float* peso){
    if(gr == NULL)
        return 0;
    if(!gr->eh_ponderado)
        return 0;

    float menor_peso = 999999.0;
    int encontrou = 0;
    int i, j;

    for(i = 0; i < gr->nro_vertices; i++){
        for(j = 0; j < gr->grau[i]; j++){
            if(gr->pesos[i][j] < menor_peso){
                menor_peso = gr->pesos[i][j];
                *orig = i;
                *dest = gr->arestas[i][j];
                *peso = menor_peso;
                encontrou = 1;
            }
        }
    }

    return encontrou;
}

// questao 4: nova estrutura de grafo com lista de adjacencia

// no da lista de adjacencia
struct no_lista{
    int destino;
    float peso;
    struct no_lista* prox;
};
typedef struct no_lista NoLista;

// lista de adjacencia
struct lista{
    NoLista* primeiro;
};

// nova estrutura do grafo
struct grafo_novo{
    Lista** vet;
    int nos;
    int eh_ponderado;
};

Lista* cria_Lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if(l != NULL)
        l->primeiro = NULL;
    return l;
}

void libera_Lista(Lista* l){
    if(l != NULL){
        NoLista* no = l->primeiro;
        NoLista* aux;
        while(no != NULL){
            aux = no;
            no = no->prox;
            free(aux);
        }
        free(l);
    }
}

int insere_Lista(Lista* l, int dest, float peso){
    if(l == NULL)
        return 0;

    NoLista* novo = (NoLista*) malloc(sizeof(NoLista));
    if(novo == NULL)
        return 0;

    novo->destino = dest;
    novo->peso = peso;
    novo->prox = l->primeiro;
    l->primeiro = novo;
    return 1;
}

int remove_Lista(Lista* l, int dest){
    if(l == NULL || l->primeiro == NULL)
        return 0;

    NoLista* ant = NULL;
    NoLista* atual = l->primeiro;

    while(atual != NULL && atual->destino != dest){
        ant = atual;
        atual = atual->prox;
    }

    if(atual == NULL)
        return 0;

    if(ant == NULL)
        l->primeiro = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual);
    return 1;
}

// cria grafo novo com lista de adjacencia
GrafoNovo* criagrafonovo(int nro_vertices, int eh_ponderado){
    GrafoNovo* gr = (GrafoNovo*) malloc(sizeof(GrafoNovo));
    if(gr != NULL){
        gr->nos = nro_vertices;
        gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;

        gr->vet = (Lista**) malloc(nro_vertices * sizeof(Lista*));
        if(gr->vet != NULL){
            int i;
            for(i = 0; i < nro_vertices; i++){
                gr->vet[i] = cria_Lista();
                if(gr->vet[i] == NULL){
                    int j;
                    for(j = 0; j < i; j++)
                        libera_Lista(gr->vet[j]);
                    free(gr->vet);
                    free(gr);
                    return NULL;
                }
            }
        } else {
            free(gr);
            return NULL;
        }
    }
    return gr;
}

void liberagrafonovo(GrafoNovo* gr){
    if(gr != NULL){
        int i;
        for(i = 0; i < gr->nos; i++){
            libera_Lista(gr->vet[i]);
        }
        free(gr->vet);
        free(gr);
    }
}

int inserearestagrafonovo(GrafoNovo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nos)
        return 0;
    if(dest < 0 || dest >= gr->nos)
        return 0;

    if(!insere_Lista(gr->vet[orig], dest, peso))
        return 0;

    if(eh_digrafo == 0){
        if(!insere_Lista(gr->vet[dest], orig, peso))
            return 0;
    }

    return 1;
}

int removearestagrafonovo(GrafoNovo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nos)
        return 0;
    if(dest < 0 || dest >= gr->nos)
        return 0;

    if(!remove_Lista(gr->vet[orig], dest))
        return 0;

    if(eh_digrafo == 0){
        remove_Lista(gr->vet[dest], orig);
    }

    return 1;
}

void imprimegrafonovo(GrafoNovo* gr){
    if(gr == NULL)
        return;

    int i;
    for(i = 0; i < gr->nos; i++){
        printf("%d: ", i);
        NoLista* no = gr->vet[i]->primeiro;
        while(no != NULL){
            if(gr->eh_ponderado)
                printf("%d(%.2f), ", no->destino, no->peso);
            else
                printf("%d, ", no->destino);
            no = no->prox;
        }
        printf("\n");
    }
}
