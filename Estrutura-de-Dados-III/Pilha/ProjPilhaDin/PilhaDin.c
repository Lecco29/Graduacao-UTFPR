#include <stdio.h>
#include <stdlib.h>
#include "PilhaDin.h"

// estrutura da pilha
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

// cria pilha vazia
Pilha* cria_Pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

// libera memoria
void libera_Pilha(Pilha* pi){
    if(pi != NULL){
        Elem* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

// consulta o topo
int consulta_topo_Pilha(Pilha* pi, struct aluno *al){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    *al = (*pi)->dados;
    return 1;
}

// empilha
int insere_Pilha(Pilha* pi, struct aluno al){
    if(pi == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

// desempilha
int remove_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    Elem *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

// conta elementos
int tamanho_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    int cont = 0;
    Elem* no = *pi;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

// verifica se ta cheia
int Pilha_cheia(Pilha* pi){
    return 0;
}

// verifica se ta vazia
int Pilha_vazia(Pilha* pi){
    if(pi == NULL)
        return 1;
    if(*pi == NULL)
        return 1;
    return 0;
}

// imprime
void imprime_Pilha(Pilha* pi){
    if(pi == NULL)
        return;
    Elem* no = *pi;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %.2f %.2f %.2f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

// questao 1
// tira dois de uma vez
int pop2(Pilha* pi){
    if(pi == NULL || (*pi) == NULL)
        return 0;

    // ve se tem pelo menos 2
    if(tamanho_Pilha(pi) < 2)
        return 0;

    // tira o primeiro
    Elem *no1 = *pi;
    *pi = no1->prox;
    free(no1);

    // tira o segundo
    Elem *no2 = *pi;
    *pi = no2->prox;
    free(no2);

    return 1;
}

// coloca dois de uma vez
int push2(Pilha* pi, struct aluno al1, struct aluno al2){
    if(pi == NULL)
        return 0;

    // coloca o primeiro
    Elem* no1 = (Elem*) malloc(sizeof(Elem));
    if(no1 == NULL)
        return 0;
    no1->dados = al1;
    no1->prox = (*pi);
    *pi = no1;

    // coloca o segundo
    Elem* no2 = (Elem*) malloc(sizeof(Elem));
    if(no2 == NULL)
        return 0;
    no2->dados = al2;
    no2->prox = (*pi);
    *pi = no2;

    return 1;
}

// questao 2
// tira n elementos
int popN(Pilha* pi, int n){
    if(pi == NULL || (*pi) == NULL || n <= 0)
        return 0;

    // ve se tem o suficiente
    int tam = tamanho_Pilha(pi);
    if(n > tam)
        return 0;

    // tira n
    Elem *no;
    for(int i = 0; i < n; i++){
        no = *pi;
        *pi = (*pi)->prox;
        free(no);
    }
    return 1;
}

// questao 3
// copia a pilha
Pilha* pilha_copia(Pilha* p){
    if(p == NULL || Pilha_vazia(p))
        return NULL;

    Pilha* aux = cria_Pilha();
    Pilha* copia = cria_Pilha();

    if(aux == NULL || copia == NULL)
        return NULL;

    // joga tudo da original pra aux
    Elem* no = *p;
    while(no != NULL){
        insere_Pilha(aux, no->dados);
        no = no->prox;
    }

    // passa de aux pra copia
    while(!Pilha_vazia(aux)){
        struct aluno al;
        consulta_topo_Pilha(aux, &al);
        insere_Pilha(copia, al);
        remove_Pilha(aux);
    }

    // restaura a original
    while(!Pilha_vazia(copia)){
        struct aluno al;
        consulta_topo_Pilha(copia, &al);
        insere_Pilha(p, al);
        remove_Pilha(copia);
    }

    // passa pra copia final
    while(!Pilha_vazia(aux)){
        struct aluno al;
        consulta_topo_Pilha(aux, &al);
        insere_Pilha(copia, al);
        remove_Pilha(aux);
    }

    libera_Pilha(aux);
    return copia;
}

// questao 4
// acha maior menor e media
void maior_menor_media(Pilha* pi, int* maior, int* menor, float* media){
    if(pi == NULL || Pilha_vazia(pi)){
        printf("Pilha vazia!\n");
        return;
    }

    int soma = 0;
    int count = 0;

    // comeca com o primeiro
    Elem* no = *pi;
    *maior = no->dados.matricula;
    *menor = no->dados.matricula;

    // percorre tudo
    while(no != NULL){
        int valor = no->dados.matricula;
        soma += valor;
        count++;

        // atualiza
        if(valor > *maior)
            *maior = valor;
        if(valor < *menor)
            *menor = valor;

        no = no->prox;
    }

    // calcula media
    *media = (float)soma / count;
}

// questao 5
// ve se duas pilhas sao iguais
int pilhas_iguais(Pilha* p1, Pilha* p2){
    if(p1 == NULL || p2 == NULL)
        return 0;

    // ve se tem o mesmo tamanho
    int tam1 = tamanho_Pilha(p1);
    int tam2 = tamanho_Pilha(p2);

    if(tam1 != tam2)
        return 0;

    // compara um por um
    Elem* no1 = *p1;
    Elem* no2 = *p2;

    while(no1 != NULL && no2 != NULL){
        if(no1->dados.matricula != no2->dados.matricula)
            return 0;
        no1 = no1->prox;
        no2 = no2->prox;
    }

    return 1;
}

// questao 6
// imprime texto ao contrario
void texto_inverso(){
    char texto[100];
    printf("Digite um texto: ");
    fgets(texto, sizeof(texto), stdin);

    // tira o \n
    char *p = texto;
    while(*p != '\0' && *p != '\n'){
        p++;
    }
    *p = '\0';

    Pilha* pi = cria_Pilha();
    struct aluno temp;

    // empilha cada letra
    p = texto;
    while(*p != '\0'){
        temp.nome[0] = *p;
        temp.nome[1] = '\0';
        insere_Pilha(pi, temp);
        p++;
    }

    // desempilha e imprime invertido
    printf("Texto inverso: ");
    Elem* no = *pi;
    while(no != NULL){
        printf("%c", no->dados.nome[0]);
        no = no->prox;
    }
    printf("\n");

    libera_Pilha(pi);
}

// converte pra minuscula
char to_lower(char c){
    if(c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

// verifica se e palindromo
int verifica_palindromo(char* texto){
    Pilha* pi = cria_Pilha();
    struct aluno temp;

    // empilha so as letras
    char *p = texto;
    while(*p != '\0'){
        char c = *p;
        if(c != ' ' && c != '.' && c != ',' && c != '!' && c != '?'){
            temp.nome[0] = to_lower(c);
            temp.nome[1] = '\0';
            insere_Pilha(pi, temp);
        }
        p++;
    }

    // compara
    p = texto;
    Elem* no = *pi;
    while(no != NULL && *p != '\0'){
        char c = to_lower(*p);
        if(c != ' ' && c != '.' && c != ',' && c != '!' && c != '?'){
            if(c != no->dados.nome[0]){
                libera_Pilha(pi);
                return 0;
            }
            no = no->prox;
        }
        p++;
    }

    libera_Pilha(pi);
    return 1;
}

// questao 7
// conta pares e impares
void conta_pares_impares(Pilha* pi, int* pares, int* impares){
    *pares = 0;
    *impares = 0;

    if(pi == NULL || Pilha_vazia(pi))
        return;

    // percorre contando
    Elem* no = *pi;
    while(no != NULL){
        if(no->dados.matricula % 2 == 0)
            (*pares)++;
        else
            (*impares)++;
        no = no->prox;
    }
}

// questao 8
// verifica cadeia xCy
int verifica_cadeia_xCy(char* texto){
    Pilha* pi = cria_Pilha();
    struct aluno temp;
    char *p = texto;

    // empilha A e B ate achar C
    while(*p != '\0' && *p != 'C'){
        if(*p == 'A' || *p == 'B'){
            temp.nome[0] = *p;
            temp.nome[1] = '\0';
            insere_Pilha(pi, temp);
        }
        p++;
    }

    // viu se achou o C
    if(*p != 'C'){
        libera_Pilha(pi);
        return 0;
    }

    p++; // pula o C

    // compara com o inverso
    Elem* no = *pi;
    while(no != NULL && *p != '\0'){
        if(*p != no->dados.nome[0]){
            libera_Pilha(pi);
            return 0;
        }
        no = no->prox;
        p++;
    }

    int resultado = (no == NULL && *p == '\0');
    libera_Pilha(pi);
    return resultado;
}

// questao 9
// menu
void menu(){
    printf("1-Inicializa pilha.\n");
    printf("2-Verifica se a pilha e vazia.\n");
    printf("3-Verifica se a pilha e cheia.\n");
    printf("4-Empilha o elemento na pilha.\n");
    printf("5-Desempilha elemento da pilha.\n");
    printf("6-Le topo de um pilha.\n");
    printf("7-Converte um numero decimal em binario.\n");
    printf("8-Sair.\n");
}

void menu_principal(){
    Pilha* pi = NULL;
    int opcao;
    struct aluno al;

    while(1){
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(pi != NULL)
                    libera_Pilha(pi);
                pi = cria_Pilha();
                printf("Pilha inicializada!\n");
                break;

            case 2:
                if(pi == NULL)
                    printf("Pilha nao inicializada!\n");
                else if(Pilha_vazia(pi))
                    printf("Pilha ta vazia!\n");
                else
                    printf("Pilha nao ta vazia!\n");
                break;

            case 3:
                if(pi == NULL)
                    printf("Pilha nao inicializada!\n");
                else if(Pilha_cheia(pi))
                    printf("Pilha ta cheia!\n");
                else
                    printf("Pilha nao ta cheia!\n");
                break;

            case 4:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                printf("Digite matricula: ");
                scanf("%d", &al.matricula);
                printf("Digite nome: ");
                scanf("%s", al.nome);
                printf("Digite nota 1: ");
                scanf("%f", &al.n1);
                printf("Digite nota 2: ");
                scanf("%f", &al.n2);
                printf("Digite nota 3: ");
                scanf("%f", &al.n3);

                if(insere_Pilha(pi, al))
                    printf("Empilhou!\n");
                else
                    printf("Erro ao empilhar!\n");
                break;

            case 5:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                if(remove_Pilha(pi))
                    printf("Desempilhou!\n");
                else
                    printf("Erro ao desempilhar!\n");
                break;

            case 6:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                if(consulta_topo_Pilha(pi, &al)){
                    printf("Topo: %d - %s\n", al.matricula, al.nome);
                    printf("Notas: %.2f %.2f %.2f\n", al.n1, al.n2, al.n3);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;

            case 7:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                printf("Em binario:\n");
                Elem* no = *pi;
                while(no != NULL){
                    printf("Mat %d = ", no->dados.matricula);
                    int num = no->dados.matricula;
                    if(num == 0){
                        printf("0");
                    } else {
                        Pilha* bin = cria_Pilha();
                        struct aluno bit;
                        while(num > 0){
                            bit.matricula = num % 2;
                            insere_Pilha(bin, bit);
                            num /= 2;
                        }
                        Elem* b = *bin;
                        while(b != NULL){
                            printf("%d", b->dados.matricula);
                            b = b->prox;
                        }
                        libera_Pilha(bin);
                    }
                    printf("\n");
                    no = no->prox;
                }
                break;

            case 8:
                if(pi != NULL)
                    libera_Pilha(pi);
                printf("Saindo...\n");
                return;

            default:
                printf("Opcao invalida!\n");
        }
        printf("\n");
    }
}
