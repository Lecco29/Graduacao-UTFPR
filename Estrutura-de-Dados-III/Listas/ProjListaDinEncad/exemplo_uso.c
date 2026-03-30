#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"

int main(){
    Lista* li1 = cria_lista();
    Lista* li2 = cria_lista();

    struct aluno alunos[] = {
        {1, "Joao", 8.5, 7.0, 9.0},
        {2, "Maria", 9.0, 8.5, 7.5},
        {3, "Pedro", 6.5, 8.0, 7.0},
        {4, "Ana", 9.5, 9.0, 8.5}
    };

    // insere os alunos ordenado
    int i;
    for(i = 0; i < 4; i++)
        insere_lista_ordenada(li1, alunos[i]);

    printf("lista 1:\n");
    imprime_lista(li1);

    // consulta por matricula
    struct aluno c = consulta_lista_matricula(li1, 2);
    if(c.matricula != 0)
        printf("achou: %s - mat %d\n", c.nome, c.matricula);

    // consulta por posicao
    c = consulta_lista_posicao(li1, 1);
    if(c.matricula != 0)
        printf("posicao 1: %s\n", c.nome);

    // insere na posicao 2
    struct aluno novo = {5, "Carlos", 7.0, 8.0, 9.0};
    insere_lista_posicao(li1, novo, 2);
    printf("\napos inserir Carlos na pos 2:\n");
    imprime_lista(li1);

    // constroi lista a partir de vetor
    float notas[] = {8.5, 7.0, 9.0, 6.5};
    Lista* li_vet = constroi_lista_vetor(notas, 4);
    printf("\nlista do vetor:\n");
    imprime_lista(li_vet);

    // remove todos com matricula 3
    int rem = remove_todos_valor(li1, 3);
    printf("\nremoveu %d com mat 3\n", rem);

    // concatena listas
    insere_lista_ordenada(li2, alunos[0]);
    insere_lista_ordenada(li2, alunos[1]);
    concatena_listas(li1, li2);
    printf("\napos concatenar:\n");
    imprime_lista(li1);

    // remove repetidos
    int rep = remove_repetidos(li1);
    printf("\ntirou %d repetidos\n", rep);
    imprime_lista(li1);

    // fusao ordenada
    Lista* li3 = cria_lista();
    Lista* li4 = cria_lista();
    struct aluno al1 = {10, "Teste1", 5.0, 6.0, 7.0};
    struct aluno al2 = {20, "Teste2", 6.0, 7.0, 8.0};
    struct aluno al3 = {15, "Teste3", 7.0, 8.0, 9.0};
    insere_lista_ordenada(li3, al1);
    insere_lista_ordenada(li3, al3);
    insere_lista_ordenada(li4, al2);
    fusao_listas_ordenadas(li3, li4);
    printf("\nfusao ordenada:\n");
    imprime_lista(li3);

    libera_lista(li1);
    libera_lista(li_vet);
    libera_lista(li3);

    return 0;
}
