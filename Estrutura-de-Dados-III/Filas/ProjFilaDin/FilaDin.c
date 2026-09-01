#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h"

// elemento da fila
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

// descritor da fila
struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

Fila* cria_Fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    if(fi != NULL){
        Elem* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int consulta_Fila(Fila* fi, struct aluno *al){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)
        return 0;
    *al = fi->inicio->dados;
    return 1;
}

int insere_Fila(Fila* fi, struct aluno al){
    if(fi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)
        return 0;
    Elem *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    return fi->qtd;
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)
        return 1;
    if(fi->inicio == NULL)
        return 1;
    return 0;
}

int Fila_cheia(Fila* fi){
    return 0;
}

void imprime_Fila(Fila* fi){
    if(fi == NULL)
        return;
    Elem* no = fi->inicio;
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

// Questao 1
// divide a fila em duas a partir de uma matricula
int separa(Fila* f1, Fila* f2, int matricula){
    if(f1 == NULL || f2 == NULL)
        return 0;

    Elem* no = f1->inicio;
    Elem* anterior = NULL;
    int encontrou = 0;

    while(no != NULL && !encontrou){
        if(no->dados.matricula == matricula){
            encontrou = 1;
        } else {
            anterior = no;
            no = no->prox;
        }
    }

    if(!encontrou)
        return 0;

    if(anterior == NULL){
        // matricula ta no primeiro elemento
        f2->inicio = f1->inicio;
        f2->final = f1->final;
        f2->qtd = f1->qtd;
        f1->inicio = NULL;
        f1->final = NULL;
        f1->qtd = 0;
    } else {
        // corta a fila no ponto encontrado
        f2->inicio = no;
        f2->final = f1->final;
        f2->qtd = 0;

        Elem* temp = no;
        while(temp != NULL){
            f2->qtd++;
            temp = temp->prox;
        }

        anterior->prox = NULL;
        f1->final = anterior;
        f1->qtd -= f2->qtd;
    }

    return 1;
}

// Questao 3
// inverte a fila usando uma pilha temporaria
void inverte_Fila(Fila* fi){
    if(fi == NULL || fi->inicio == NULL)
        return;

    Elem* pilha = NULL;
    struct aluno al;

    // desenfileira tudo e empilha
    while(!Fila_vazia(fi)){
        consulta_Fila(fi, &al);
        remove_Fila(fi);

        Elem* novo = (Elem*) malloc(sizeof(Elem));
        novo->dados = al;
        novo->prox = pilha;
        pilha = novo;
    }

    // desempilha e enfileira (fica invertido)
    while(pilha != NULL){
        al = pilha->dados;
        insere_Fila(fi, al);

        Elem* temp = pilha;
        pilha = pilha->prox;
        free(temp);
    }
}

// Questao 4
// coloca um elemento no inicio da fila
int FuraFila(Fila* fi, struct aluno al){
    if(fi == NULL)
        return 0;

    Elem* novo = (Elem*) malloc(sizeof(Elem));
    if(novo == NULL)
        return 0;

    novo->dados = al;
    novo->prox = fi->inicio;
    fi->inicio = novo;

    if(fi->final == NULL)
        fi->final = novo;

    fi->qtd++;
    return 1;
}

// Questao 5
// simula controle de aeroporto
void adiciona_Aviao(Fila* fi, int id, char modelo[], char companhia[]){
    struct aluno al;
    al.matricula = id;
    strcpy(al.nome, modelo);
    al.n1 = 0; al.n2 = 0; al.n3 = 0;
    al.n1 = 1;

    insere_Fila(fi, al);
}

void autoriza_Decolagem(Fila* fi){
    if(!Fila_vazia(fi)){
        remove_Fila(fi);
        printf("Decolagem autorizada!\n");
    } else {
        printf("Nenhum aviao na fila.\n");
    }
}

void lista_Avioes(Fila* fi){
    if(Fila_vazia(fi)){
        printf("Nenhum aviao na fila.\n");
        return;
    }

    Elem* no = fi->inicio;
    int cont = 1;
    while(no != NULL){
        printf("Aviao %d: ID %d - %s (%s)\n", cont, no->dados.matricula,
               no->dados.nome, "Companhia");
        no = no->prox;
        cont++;
    }
}

void lista_PrimeiroAviao(Fila* fi){
    if(Fila_vazia(fi)){
        printf("Nenhum aviao na fila.\n");
        return;
    }

    struct aluno al;
    consulta_Fila(fi, &al);
    printf("Primeiro aviao: ID %d - %s\n", al.matricula, al.nome);
}

// Questao 6
// mescla duas filas ordenadas em uma terceira
void mescla_FilasOrdenadas(Fila* f1, Fila* f2, Fila* f3){
    if(f1 == NULL || f2 == NULL || f3 == NULL)
        return;

    struct aluno al1, al2;
    int tem1 = consulta_Fila(f1, &al1);
    int tem2 = consulta_Fila(f2, &al2);

    while(tem1 || tem2){
        if(tem1 && tem2){
            if(al1.matricula <= al2.matricula){
                remove_Fila(f1);
                insere_Fila(f3, al1);
                tem1 = consulta_Fila(f1, &al1);
            } else {
                remove_Fila(f2);
                insere_Fila(f3, al2);
                tem2 = consulta_Fila(f2, &al2);
            }
        } else if(tem1){
            remove_Fila(f1);
            insere_Fila(f3, al1);
            tem1 = consulta_Fila(f1, &al1);
        } else {
            remove_Fila(f2);
            insere_Fila(f3, al2);
            tem2 = consulta_Fila(f2, &al2);
        }
    }
}

// Questao 7
// inverte a fila invertendo os ponteiros diretamente
void reverso(Fila* fi){
    if(fi == NULL || fi->inicio == NULL)
        return;

    Elem* anterior = NULL;
    Elem* atual = fi->inicio;
    Elem* proximo = NULL;

    while(atual != NULL){
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    fi->final = fi->inicio;
    fi->inicio = anterior;
}

// Questao 8
// menu interativo
void menu(){
    printf("1-Inicializa fila.\n");
    printf("2-Verifica se a fila e vazia.\n");
    printf("3-Verifica se a fila e cheia.\n");
    printf("4-Enfileira o elemento na fila.\n");
    printf("5-Desefileira elemento da fila.\n");
    printf("6-Le o numero no inicio da fila.\n");
    printf("7-Testar qual fila possui mais elementos .\n");
    printf("8-Furar a fila .\n");
    printf("9-Sair.\n");
}

void executa_Menu(){
    Fila* fi = NULL;
    Fila* fi2 = NULL;
    int opcao;
    struct aluno al;

    do{
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(fi != NULL)
                    libera_Fila(fi);
                fi = cria_Fila();
                printf("Fila inicializada.\n");
                break;

            case 2:
                if(fi == NULL)
                    printf("Fila nao foi inicializada.\n");
                else if(Fila_vazia(fi))
                    printf("Fila esta vazia.\n");
                else
                    printf("Fila nao esta vazia.\n");
                break;

            case 3:
                if(fi == NULL)
                    printf("Fila nao foi inicializada.\n");
                else if(Fila_cheia(fi))
                    printf("Fila esta cheia.\n");
                else
                    printf("Fila nao esta cheia.\n");
                break;

            case 4:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                printf("Digite a matricula: ");
                scanf("%d", &al.matricula);
                printf("Digite o nome: ");
                scanf("%s", al.nome);
                printf("Digite as 3 notas: ");
                scanf("%f %f %f", &al.n1, &al.n2, &al.n3);

                if(insere_Fila(fi, al))
                    printf("Elemento inserido com sucesso.\n");
                else
                    printf("Erro ao inserir elemento.\n");
                break;

            case 5:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                if(remove_Fila(fi))
                    printf("Elemento removido com sucesso.\n");
                else
                    printf("Erro ao remover elemento.\n");
                break;

            case 6:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                if(consulta_Fila(fi, &al))
                    printf("Primeiro elemento: Matricula %d, Nome %s\n", al.matricula, al.nome);
                else
                    printf("Fila vazia.\n");
                break;

            case 7:
                if(fi == NULL){
                    printf("Primeira fila nao foi inicializada.\n");
                    break;
                }
                if(fi2 == NULL){
                    fi2 = cria_Fila();
                    printf("Segunda fila criada. Adicione elementos a ela.\n");
                }
                printf("Fila 1 tem %d elementos.\n", tamanho_Fila(fi));
                printf("Fila 2 tem %d elementos.\n", tamanho_Fila(fi2));
                if(tamanho_Fila(fi) > tamanho_Fila(fi2))
                    printf("Fila 1 tem mais elementos.\n");
                else if(tamanho_Fila(fi2) > tamanho_Fila(fi))
                    printf("Fila 2 tem mais elementos.\n");
                else
                    printf("As filas tem o mesmo numero de elementos.\n");
                break;

            case 8:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                printf("Digite a matricula: ");
                scanf("%d", &al.matricula);
                printf("Digite o nome: ");
                scanf("%s", al.nome);
                printf("Digite as 3 notas: ");
                scanf("%f %f %f", &al.n1, &al.n2, &al.n3);

                if(FuraFila(fi, al))
                    printf("Elemento inserido no inicio da fila.\n");
                else
                    printf("Erro ao inserir elemento.\n");
                break;

            case 9:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

        if(opcao != 9){
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }

    } while(opcao != 9);

    if(fi != NULL)
        libera_Fila(fi);
    if(fi2 != NULL)
        libera_Fila(fi2);
}
