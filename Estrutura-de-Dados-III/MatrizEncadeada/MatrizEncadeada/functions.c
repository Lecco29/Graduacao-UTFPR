#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

// limpa a tela
void separador() {
    for (int i = 0; i < 10; i++) {
        printf("\n");
    }
}

// funcao principal com menu
void saudacao() {

    int linhas = 3, colunas = 3;
    Matriz *matriz = alocarMatriz(linhas, colunas);

    inserirMatriz(matriz, 1, 1, 1);
    inserirMatriz(matriz, 1, 1, 2);
    inserirMatriz(matriz, 1, 1, 3);
    inserirMatriz(matriz, 2, 2, 1);
    inserirMatriz(matriz, 2, 2, 2);
    inserirMatriz(matriz, 2, 2, 3);
    inserirMatriz(matriz, 3, 3, 1);
    inserirMatriz(matriz, 3, 3, 2);
    inserirMatriz(matriz, 3, 3, 3);

    printf("Matriz completa:\n");
    mostrarMatriz(matriz);

    printf("\n");

    int choose = 999;

    do {
        printf("\nMenu de Operaces:\n");
        printf("1 - Modificar Matriz\n");
        printf("2 - Consultar Valor\n");
        printf("3 - Procurar Valor\n");
        printf("4 - Liberar Matriz\n");
        printf("5 - Imprimir Vizinhos\n");
        printf("6 - Mostrar Matriz\n");
        printf("7 - Calcular Determinante\n");
        printf("8 - Transpor Matriz\n");
        printf("9 - Verificar Simetria\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao:");
        scanf("%d", &choose);

        separador();

        switch (choose) {
            case 1:
                modificarMatriz(&matriz);
                printf("Valores da nova Matriz:\n");
                mostrarMatriz(matriz);
                system("pause");
                break;

            case 2: {
                int x, y;
                printf("Digite, respectivamente, as ordenadas da matriz para saber o valor do elemento: ");
                scanf("%d %d", &x, &y);
                No *elemento = consultarValorqq(matriz, x, y);
                if (elemento) {
                    printf("\nValor na posicao (%d, %d): %d\n", x, y, elemento->valor);
                } else {
                    printf("\nElemento nao encontrado na posicao (%d, %d).\n", x, y);
                }
                system("pause");
                break;
            }

            case 3: {
                int valor;
                printf("Digite o valor a ser encontrado na matriz:");
                scanf("%d", &valor);
                ProcurarValorqq(matriz, valor);
                system("pause");
                break;
            }

            case 4:
                liberaMatriz(matriz);
                matriz = NULL;
                printf("Matriz deletada!\n");
                system("pause");
                break;

            case 5:
                printf("Digite as coordenadas do elemento que deseja saber os vizinhos:\n");
                int x, y;
                scanf("%d %d", &x, &y);
                imprimirVizinhos(matriz, x, y);
                system("pause");
                break;

            case 6:
                printf("Matriz atual:\n");
                mostrarMatriz(matriz);
                system("pause");
                break;

            case 7:
                printf("A matriz:\n");
                mostrarMatriz(matriz);
                printf("\n\nTem como determinante: %d\n", calcularDeterminante(matriz));
                system("pause");
                break;

            case 8:
                printf("A matriz transposta eh: \n");
                TransporMatriz(matriz);
                mostrarMatriz(matriz);
                system("pause");
                break;

            case 9:
                MatrizSimetrica(matriz);
                system("pause");
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (choose != 0);

    if (matriz) {
        liberaMatriz(matriz);
    }
}

// aloca matriz encadeada linhas x colunas
Matriz *alocarMatriz(int linhas, int colunas) {
    Matriz *matriz = malloc(sizeof(Matriz));
    if (matriz == NULL) {
        printf("Erro ao alocaMatriz");
        return NULL;
    }
    matriz->linhas = linhas;
    matriz->colunas = colunas;
    matriz->inicio = NULL;

    No **superiores = malloc(colunas * sizeof(No *));
    if (superiores == NULL){
        printf("Erro alocar memoria\n");
        return NULL;
    }

    for (int j = 0; j < colunas; j++) {
        superiores[j] = NULL;
    }

    for (int i = 0; i < linhas; i++) {
        No *anterior = NULL;
        for (int j = 0; j < colunas; j++) {
            No *novo = malloc(sizeof(No));
            if (novo == NULL) {
                printf("Erro alocar memoria\n");
                return NULL;
            }
            novo->valor = 0;
            novo->esquerda = anterior;
            novo->cima = (i > 0) ? superiores[j] : NULL;
            novo->direita = NULL;
            novo->baixo = NULL;

            if (anterior)
                anterior->direita = novo;

            if (i > 0 && superiores[j])
                superiores[j]->baixo = novo;

            superiores[j] = novo;
            anterior = novo;

            if (i == 0 && j == 0) matriz->inicio = novo;
        }
    }

    free(superiores);
    return matriz;
}

// libera toda a memoria da matriz
void liberaMatriz(Matriz *matriz) {
    if (!matriz) return;
    No *linhaAtual = matriz->inicio;
    while (linhaAtual) {
        No *colunaAtual = linhaAtual;
        linhaAtual = linhaAtual->baixo;
        while (colunaAtual) {
            No *proximo = colunaAtual->direita;
            free(colunaAtual);
            colunaAtual = proximo;
        }
    }
    free(matriz);
    printf("Matriz liberada!\n");
}

// insere valor na posicao (linha, coluna)
int inserirMatriz(Matriz *matriz, int valor, int linha, int coluna) {
    if (!matriz) return 0;

    if(linha > matriz->linhas || coluna > matriz->colunas) {
        printf("Numero inserido de linhas ou colunas maior que o da matriz!\n");
        return 0;
    }

    No *aux = matriz->inicio;

    if(linha > 0) linha--;
    if(coluna > 0) coluna--;

    while (linha != 0) {
        aux = aux->baixo;
        linha--;
        if (aux == NULL) {
            printf("Erro! noh inexistente");
            return 0;
        }
    }
    while (coluna != 0) {
        aux = aux->direita;
        coluna--;
        if (aux == NULL) {
            printf("Erro! noh inexistente");
            return 0;
        }
    }

    aux->valor = valor;
    return 1;
}

// modifica a matriz pedindo novos valores
void modificarMatriz(Matriz **matriz) {
    int novasLinhas, novasColunas;

    printf("Digite o novo espaco da matriz, digitando respectivamente o novo numero de linhas e de colunas:\n");
    scanf("%d %d", &novasLinhas, &novasColunas);

    if (novasLinhas <= 0 || novasColunas <= 0) {
        printf("nao existe matriz de tamanho nulo ou negativo\n");
        return;
    }

    if (*matriz) {
        liberaMatriz(*matriz);
    }

    *matriz = alocarMatriz(novasLinhas, novasColunas);
    if (!*matriz) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    printf("Preencha os valores da nova matriz (%dx%d):\n", novasLinhas, novasColunas);
    for (int i = 1; i <= novasLinhas; i++) {
        for (int j = 1; j <= novasColunas; j++) {
            int valor;
            printf("Valor para posicao (%d, %d): ", i, j);
            if (scanf("%d", &valor) != 1) {
                printf("Erro: Entrada invalida.\n");
                return;
            }
            inserirMatriz(*matriz, valor, i, j);
        }
    }
}

// consulta valor na posicao (linha, coluna)
No* consultarValorqq(Matriz *matriz, int linha, int coluna) {
    if (!matriz) return NULL;

    if(linha > matriz->linhas || coluna > matriz->colunas || linha == 0 || coluna == 0) {
        printf("Numero inserido de linhas ou colunas maior que o da matriz!\n");
        return NULL;
    }

    No *aux = matriz->inicio;

    linha--;
    coluna--;

    while (linha != 0) {
        aux = aux->baixo;
        linha--;
    }
    while (coluna != 0) {
        aux = aux->direita;
        coluna--;
    }

    return aux;
}

// procura valor na matriz e retorna primeiro encontrado
No *ProcurarValorqq(Matriz *matriz, int valor) {
    if (!matriz) {
        printf("\nMatriz invalida ou vazia\n");
        return NULL;
    }

    No *auxLinha = matriz->inicio;
    No *primeiroEncontrado = NULL;

    int linha = 1;
    int encontrado = 0;

    while (auxLinha != NULL) {
        No *aux = auxLinha;
        int coluna = 1;

        while (aux != NULL) {
            if (aux->valor == valor) {
                printf("Valor %d encontrado na posicao (%d, %d)\n", valor, linha, coluna);
                if (!primeiroEncontrado) {
                    primeiroEncontrado = aux;
                }
                encontrado = 1;
            }
            aux = aux->direita;
            coluna++;
        }
        auxLinha = auxLinha->baixo;
        linha++;
    }

    if (!encontrado) {
        printf("\nValor %d nao encontrado na matriz...\n", valor);
        return NULL;
    }

    return primeiroEncontrado;
}

// imprime vizinhos de um no
void imprimirVizinhos(Matriz *matriz, int linha, int coluna) {
    No *no = consultarValorqq(matriz, linha, coluna);

    if (no) {
        printf("Vizinhos do noh (%d, %d):\n", linha, coluna);
        printf("Cima: %d\n", no->cima ? no->cima->valor : -1);
        printf("Baixo: %d\n", no->baixo ? no->baixo->valor : -1);
        printf("Esquerda: %d\n", no->esquerda ? no->esquerda->valor : -1);
        printf("Direita: %d\n", no->direita ? no->direita->valor : -1);
    }else {
        printf("Noh (%d, %d) nao encontrado.\n", linha, coluna);
    }
}

// mostra a matriz inteira
void mostrarMatriz(Matriz *matriz) {
    No *linha = matriz->inicio;
    while (linha) {
        No *coluna = linha;
        while (coluna) {
            printf("|%d|", coluna->valor);
            coluna = coluna->direita;
        }
        printf("\n");
        linha = linha->baixo;
    }
}

// cria submatriz excluindo uma linha e coluna (pra cofator)
Matriz* criarSubmatriz(Matriz *matriz, int excluirLinha, int excluirColuna) {
    if (!matriz || !matriz->inicio) return NULL;

    Matriz *submatriz = alocarMatriz(matriz->linhas - 1, matriz->colunas - 1);
    No *linhaAtual = matriz->inicio;
    No *subLinha = submatriz->inicio;

    for (int i = 0; i < matriz->linhas; i++) {
        if (i == excluirLinha) {
            linhaAtual = linhaAtual->baixo;
            continue;
        }

        No *colunaAtual = linhaAtual;
        No *subColuna = subLinha;

        for (int j = 0; j < matriz->colunas; j++) {
            if (j == excluirColuna) {
                colunaAtual = colunaAtual->direita;
                continue;
            }

            subColuna->valor = colunaAtual->valor;

            colunaAtual = colunaAtual->direita;
            subColuna = subColuna->direita;
        }

        linhaAtual = linhaAtual->baixo;
        subLinha = subLinha->baixo;
    }

    return submatriz;
}

// calcula determinante recursivamente
int calcularDeterminante(Matriz *matriz) {
    if (!matriz || !matriz->inicio || matriz->linhas != matriz->colunas) {
        printf("Erro: Matriz invalida ou nao quadrada.\n");
        return 0;
    }

    if (matriz->linhas == 1) {
        return matriz->inicio->valor;
    }

    if (matriz->linhas == 2) {
        No *a = matriz->inicio;
        No *b = a->direita;
        No *c = a->baixo;
        No *d = c->direita;

        return (a->valor * d->valor) - (b->valor * c->valor);
    }

    int det = 0;
    No *colunaAtual = matriz->inicio;
    int sinal = 1;

    for (int j = 0; j < matriz->colunas; j++) {
        Matriz *submatriz = criarSubmatriz(matriz, 0, j);

        det += sinal * colunaAtual->valor * calcularDeterminante(submatriz);
        sinal = -sinal;

        liberaMatriz(submatriz);
        colunaAtual = colunaAtual->direita;
    }

    return det;
}

// transpoe a matriz (inverte linhas e colunas)
Matriz* TransporMatriz(Matriz *matriz) {
    if(!matriz) return NULL;

    int linhaTranspor = matriz->colunas;
    int colunaTranspor = matriz->linhas;

    Matriz* matriz_transposta = alocarMatriz(linhaTranspor, colunaTranspor);

    No *aux = matriz->inicio;
    No *auxLinha = matriz->inicio;
    No *matT = matriz_transposta->inicio;
    No *matColuna = matriz_transposta->inicio;

    while (auxLinha != NULL) {
        aux = auxLinha;
        while (aux != NULL) {
            matT->valor = aux->valor;
            matT = matT->baixo;
            if (matT == NULL) {
                matColuna = matColuna->direita;
                if (matColuna != NULL) {
                    matT = matColuna;
                }
            }
            aux = aux->direita;
        }
        auxLinha = auxLinha->baixo;
    }
    return matriz_transposta;
}

// verifica se a matriz eh simetrica
void MatrizSimetrica(Matriz *matriz) {
    if (!matriz) return;

    if (matriz->linhas != matriz->colunas) {
        printf("\nMatriz nao eh quadratica (NxN), nao tem como ser simetrica!..\n");
        return;
    }

    Matriz *simetrica = TransporMatriz(matriz);

    No *aux = matriz->inicio;
    No *auxLinha = matriz->inicio;
    No *mat = simetrica->inicio;
    No *matrizLinha = simetrica->inicio;

    while (auxLinha != NULL) {
        aux = auxLinha;
        while (aux != NULL) {
            if(mat->valor == aux->valor) {
                mat = mat->direita;
                if (mat == NULL) {
                    matrizLinha = matrizLinha->baixo;
                    mat = matrizLinha;
                }
            }
            else {
                printf("\nMatriz nao eh simetrica...\n");
                printf("\nMatriz Inicial: \n");
                mostrarMatriz(matriz);
                printf("\nMatriz Transposta: \n\n");
                mostrarMatriz(simetrica);
                return;
            }
            aux = aux->direita;
        }
        auxLinha = auxLinha->baixo;
    }

    printf("\nMatriz eh simetrica...\n");
    printf("\nMatriz Inicial: \n");
    mostrarMatriz(matriz);
    printf("\nMatriz Transposta: \n\n");
    mostrarMatriz(simetrica);

    liberaMatriz(simetrica);
    return;
}
