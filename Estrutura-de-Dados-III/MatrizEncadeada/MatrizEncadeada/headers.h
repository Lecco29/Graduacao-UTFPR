#ifndef HEADERS_H
#define HEADERS_H

typedef struct no {
  int valor;
  struct no *esquerda, *direita, *cima, *baixo;
} No;

typedef struct matriz {
  No *inicio;
  int linhas, colunas;
} Matriz;

void separador();
void saudacao();
Matriz* alocarMatriz(int linhas, int colunas);
void liberaMatriz(Matriz *matriz);
int inserirMatriz(Matriz *matriz, int valor, int linha, int coluna);
void modificarMatriz(Matriz **matriz);
No* consultarValorqq(Matriz *matriz, int linha, int coluna);
No* ProcurarValorqq(Matriz *matriz, int valor);
void liberaMatriz(Matriz *matriz);
void imprimirVizinhos(Matriz *matriz, int linha, int coluna);
void mostrarMatriz(Matriz *matriz);
Matriz* criarSubmatriz(Matriz *matriz, int excluirLinha, int excluirColuna);
int calcularDeterminante(Matriz *matriz);
Matriz* TransporMatriz(Matriz *matriz);
void MatrizSimetrica(Matriz *matriz);

#endif //HEADERS_H
