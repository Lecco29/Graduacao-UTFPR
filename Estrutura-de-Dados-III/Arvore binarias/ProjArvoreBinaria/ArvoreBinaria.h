// ArvoreBinaria.h

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
struct NO* remove_atual(struct NO* atual);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

// questao 2: percursos em ordem e pos-ordem
void emordemarvore(ArvBin *raiz);
void posordemarvbin(ArvBin *raiz);

// questao 3: total de nos
int totalnoarvore(ArvBin *raiz);

// questao 4: consulta valor
int consarvore(ArvBin *raiz, int valor);

// questao 5: remove no atual
struct NO* removearvoreatual(struct NO* atual);
