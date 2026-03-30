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

// questao 1 - pop2 e push2
int pop2(Pilha* pi);
int push2(Pilha* pi, struct aluno al1, struct aluno al2);

// questao 2 - popN
int popN(Pilha* pi, int n);

// questao 3 - copia da pilha
Pilha* pilha_copia(Pilha* p);

// questao 4 - maior menor e media
void maior_menor_media(Pilha* pi, int* maior, int* menor, float* media);

// questao 5 - pilhas iguais
int pilhas_iguais(Pilha* p1, Pilha* p2);

// questao 6 - texto inverso e palindromo
void texto_inverso();
int verifica_palindromo(char* texto);

// questao 7 - pares e impares
void conta_pares_impares(Pilha* pi, int* pares, int* impares);

// questao 8 - cadeia xCy
int verifica_cadeia_xCy(char* texto);

// questao 9 - menu
void menu();
void menu_principal();
