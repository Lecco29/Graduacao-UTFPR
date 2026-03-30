// Grafo.h

typedef struct grafo Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);
void imprime_Grafo(Grafo *gr);

// questao 5: algoritmo de prim
float algoritmoprim(Grafo* gr, int origem, int* pais);

// questao 6a: encontra no
int encontrano(Grafo* gr, int no);

// questao 6b: encontra aresta de menor peso
int encontraarestamenorpeso(Grafo* gr, int* orig, int* dest, float* peso);

// questao 4: nova estrutura de grafo
typedef struct grafo_novo GrafoNovo;
typedef struct lista Lista;

GrafoNovo* criagrafonovo(int nro_vertices, int eh_ponderado);
void liberagrafonovo(GrafoNovo* gr);
int inserearestagrafonovo(GrafoNovo* gr, int orig, int dest, int eh_digrafo, float peso);
int removearestagrafonovo(GrafoNovo* gr, int orig, int dest, int eh_digrafo);
void imprimegrafonovo(GrafoNovo* gr);
