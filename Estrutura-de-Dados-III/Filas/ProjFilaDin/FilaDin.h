// FilaDin.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct fila Fila;

// funcoes basicas da fila
Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
void imprime_Fila(Fila* fi);

// Questao 1: separa fila em duas
int separa(Fila* f1, Fila* f2, int matricula);

// Questao 3: inverte fila com pilha
void inverte_Fila(Fila* fi);

// Questao 4: fura fila
int FuraFila(Fila* fi, struct aluno al);

// Questao 5: controle de aeroporto
void adiciona_Aviao(Fila* fi, int id, char modelo[], char companhia[]);
void autoriza_Decolagem(Fila* fi);
void lista_Avioes(Fila* fi);
void lista_PrimeiroAviao(Fila* fi);

// Questao 6: mescla filas ordenadas
void mescla_FilasOrdenadas(Fila* f1, Fila* f2, Fila* f3);

// Questao 7: reverso
void reverso(Fila* fi);

// Questao 8: menu
void menu();
void executa_Menu();
