#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no{
    char nome[256];
    int eh_arquivo;
    struct no* pai;
    struct no* primeiro_filho;
    struct no* proximo_irmao;
};
typedef struct no No;


struct arvore{
    No* raiz;
    No* atual;
};
typedef struct arvore Arvore;

Arvore* cria_arvore();
void libera_arvore(Arvore* arv);
void libera_no(No* no);
int ler_arquivo(Arvore* arv, const char* nome_arquivo);
int adiciona_caminho(Arvore* arv, const char* caminho);
No* encontra_no(No* diretorio, const char* nome);
No* encontra_caminho(Arvore* arv, const char* caminho);
int comando_cd(Arvore* arv, const char* nome_dir);
void comando_search(Arvore* arv, const char* nome);
void busca_recursiva(No* no, const char* nome, char* caminho_atual, int* encontrou);
int comando_rm(Arvore* arv, const char* nome_dir);
void comando_list(Arvore* arv);
int comando_mkdir(Arvore* arv, const char* nome_dir);
void comando_clear();
void comando_help();
void imprime_caminho_atual(Arvore* arv);
void encontra_alternativas(Arvore* arv, const char* prefixo);

#endif // MATRIZ_H
