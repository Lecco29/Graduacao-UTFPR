// PilhaDin.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Pilha;

// funcoes basicas da pilha
Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int consulta_topo_Pilha(Pilha* pi, struct aluno *al);
int insere_Pilha(Pilha* pi, struct aluno al);
int remove_Pilha(Pilha* pi);
int tamanho_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);
int Pilha_cheia(Pilha* pi);
void imprime_Pilha(Pilha* pi);
int pop2(Pilha* pi);
int push2(Pilha* pi, struct aluno al1, struct aluno al2);
int popN(Pilha* pi, int n);
Pilha* pilha_copia(Pilha* p);
void maior_menor_media(Pilha* pi, int* maior, int* menor, float* media);
int pilhas_iguais(Pilha* p1, Pilha* p2);
void texto_inverso();
int verifica_palindromo(char* texto);
void conta_pares_impares(Pilha* pi, int* pares, int* impares);
int verifica_cadeia_xCy(char* texto);
void menu();
void menu_principal();
