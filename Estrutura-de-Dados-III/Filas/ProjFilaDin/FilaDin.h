// FilaDin.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct fila Fila;

Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
void imprime_Fila(Fila* fi);
int separa(Fila* f1, Fila* f2, int matricula);
void inverte_Fila(Fila* fi);
int FuraFila(Fila* fi, struct aluno al);
void adiciona_Aviao(Fila* fi, int id, char modelo[], char companhia[]);
void autoriza_Decolagem(Fila* fi);
void lista_Avioes(Fila* fi);
void lista_PrimeiroAviao(Fila* fi);
void mescla_FilasOrdenadas(Fila* f1, Fila* f2, Fila* f3);
void reverso(Fila* fi);
void menu();
void executa_Menu();
