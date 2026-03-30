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

// exercicio 1
int conta_folhas(ArvBin *raiz);

// exercicio 2
void imprime_arvore(ArvBin *raiz);

// exercicio 3
int conta_valor(ArvBin *raiz, int valor);

// exercicio 4
void folhas_decrescente(ArvBin *raiz);

// exercicio 5
int arvores_iguais(ArvBin *raiz1, ArvBin *raiz2);

// exercicio 6
void elimina_pares(ArvBin *raiz);

// exercicio 7
int arvores_similares(ArvBin *raiz1, ArvBin *raiz2);

// exercicio 8
void emOrdem_char(ArvBin *raiz);
void preOrdem_char(ArvBin *raiz);
void imprime_arvore_char(ArvBin *raiz);

// exercicio 9
int insere_expressao(ArvBin *raiz, char *expressao);
float calcula_expressao(ArvBin *raiz);
void imprime_infixa(ArvBin *raiz);
void imprime_prefixa(ArvBin *raiz);
void imprime_posfixa(ArvBin *raiz);
