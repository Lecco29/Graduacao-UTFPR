// declaracao forward da estrutura NO
struct NO;

typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int data);
int remove_ArvAVL(ArvAVL *raiz, int valor);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);

// questao 4: rotacao simples a direita
void rotacaorr(ArvAVL *raiz);

// questao 7: verifica se eh avl
int verificaavl(ArvAVL *raiz);

// questao 8: transforma abb em avl
ArvAVL* transformaavl(ArvAVL *raiz);
void transformaavlrecursivo(struct NO* no, ArvAVL* nova_avl);
