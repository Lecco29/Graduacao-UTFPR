#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// questao 1 - diferencas entre p++, (*p)++, *(p++), *(p+n)
void questao1() {
    printf("questao 1\n\n");

    int vetor[] = {10, 20, 30, 40, 50};
    int *p = vetor;

    printf("Vetor inicial: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n\n");

    printf("1) p++\n");
    printf("   Antes: %d\n", *p);
    p++;
    printf("   Depois: %d\n\n", *p);

    printf("2) (*p)++\n");
    printf("   Antes: %d\n", *p);
    (*p)++;
    printf("   Depois: %d\n", *p);
    printf("   Vetor: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n\n");

    printf("3) *(p++)\n");
    printf("   Valor: %d\n", *(p++));
    printf("   Agora aponta: %d\n\n", *p);

    printf("4) *(p+10)\n");
    printf("   *(p+10) = %d\n", *(p+10));
    printf("   *(p+2) = %d\n\n", *(p+2));
}

// questao 2 - codigo com ponteiros
void questao2() {
    printf("questao 2\n\n");

    int y, *p, x;

    y = 0;
    printf("y = %d\n", y);

    p = &y;
    printf("p = %p\n", p);

    x = *p;
    printf("x = %d\n", x);

    x = 4;
    printf("x = %d\n", x);

    (*p)++;
    printf("y = %d\n", y);

    x--;
    printf("x = %d\n", x);

    (*p) += x;
    printf("y = %d\n", y);

    printf("\nFinal: y = %d\n", y);
}

// questao 3 - ponteiro pra ponteiro
void questao3() {
    printf("questao 3\n\n");

    int x, *p, **q;

    x = 10;
    p = &x;
    q = &p;

    printf("Errado: printf(\"%%d\", &q)\n");
    printf("Resultado: %p\n\n", &q);

    printf("Certo: printf(\"%%d\", **q)\n");
    printf("Resultado: %d\n", **q);
}

// questao 4 - aloca vetor dinamico
void questao4() {
    printf("questao 4\n\n");

    int n;
    int *V;

    printf("Tamanho do vetor: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Erro!\n");
        return;
    }

    V = (int*) malloc(n * sizeof(int));

    if(V == NULL) {
        printf("Erro na alocacao!\n");
        return;
    }

    printf("Vetor alocado!\n");

    for(int i = 0; i < n; i++) {
        V[i] = i + 1;
        printf("V[%d] = %d\n", i, V[i]);
    }

    free(V);
    printf("Memoria liberada!\n");
}

// questao 5 - inverte vetor e retorna maior
int inverte_vetor(int *v1, int *v2, int n) {
    int maior = v1[0];

    for(int i = 0; i < n; i++) {
        v2[i] = v1[n-1-i];

        if(v1[i] > maior) {
            maior = v1[i];
        }
    }

    return maior;
}

void questao5() {
    printf("questao 5\n\n");

    int n;
    int *v1, *v2;

    printf("Tamanho dos vetores: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Erro!\n");
        return;
    }

    v1 = (int*) malloc(n * sizeof(int));
    v2 = (int*) malloc(n * sizeof(int));

    if(v1 == NULL || v2 == NULL) {
        printf("Erro na alocacao!\n");
        return;
    }

    printf("Elementos do vetor V1:\n");
    for(int i = 0; i < n; i++) {
        printf("V1[%d] = ", i);
        scanf("%d", &v1[i]);
    }

    int maior = inverte_vetor(v1, v2, n);

    printf("\nV1: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", v1[i]);
    }

    printf("\nV2: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", v2[i]);
    }

    printf("\nMaior: %d\n", maior);

    free(v1);
    free(v2);
}

// questao 6 - string inversa com ponteiros
void questao6() {
    printf("questao 6\n\n");

    char s[10] = "abcde";
    char* cptr;

    printf("Original: %s\n", s);
    printf("Inversa: ");

    cptr = s;
    while(*cptr != '\0') {
        cptr++;
    }

    cptr--;
    while(cptr >= s) {
        printf("%c", *cptr);
        cptr--;
    }
    printf("\n");
}

// questao 7 - cadastro de produtos
struct Produto {
    int codigo;
    char nome[50];
    float preco;
};

void questao7() {
    printf("questao 7\n\n");

    int n;
    struct Produto *produtos;

    printf("Numero de produtos: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Erro!\n");
        return;
    }

    produtos = (struct Produto*) malloc(n * sizeof(struct Produto));

    if(produtos == NULL) {
        printf("Erro na alocacao!\n");
        return;
    }

    printf("\nCadastro:\n");
    for(int i = 0; i < n; i++) {
        printf("\nProduto %d:\n", i+1);
        printf("Codigo: ");
        scanf("%d", &produtos[i].codigo);
        printf("Nome: ");
        scanf("%s", produtos[i].nome);
        printf("Preco: ");
        scanf("%f", &produtos[i].preco);
    }

    printf("\nLista:\n");
    printf("Codigo\tNome\t\tPreco\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }

    int codigo_consulta;
    printf("\nConsulta por codigo: ");
    scanf("%d", &codigo_consulta);

    int encontrado = 0;
    for(int i = 0; i < n; i++) {
        if(produtos[i].codigo == codigo_consulta) {
            printf("Encontrado!\n");
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("Nao encontrado!\n");
    }

    free(produtos);
}

// questao 8 - le vetor
void ler_vetor(int *vetor, int n) {
    printf("Elementos do vetor:\n");
    for(int i = 0; i < n; i++) {
        printf("Elemento %d: ", i+1);
        scanf("%d", &vetor[i]);
    }
}

void questao8() {
    printf("questao 8\n\n");

    int n;
    int *vetor;

    printf("Tamanho do vetor: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Erro!\n");
        return;
    }

    vetor = (int*) malloc(n * sizeof(int));

    if(vetor == NULL) {
        printf("Erro na alocacao!\n");
        return;
    }

    printf("Vetor alocado!\n");

    ler_vetor(vetor, n);

    printf("\nVetor:\n");
    for(int i = 0; i < n; i++) {
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }

    free(vetor);
    printf("Memoria liberada!\n");
}

// questao 9 - matriz dinamica
int** alocar_matriz(int m, int n) {
    int **matriz;
    int i;

    matriz = (int**) malloc(m * sizeof(int*));

    if(matriz == NULL) {
        printf("Erro nas linhas!\n");
        return NULL;
    }

    for(i = 0; i < m; i++) {
        matriz[i] = (int*) malloc(n * sizeof(int));
        if(matriz[i] == NULL) {
            printf("Erro na linha %d!\n", i);
            for(int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

// libera matriz
void liberar_matriz(int **matriz, int m) {
    int i;

    if(matriz != NULL) {
        for(i = 0; i < m; i++) {
            if(matriz[i] != NULL) {
                free(matriz[i]);
            }
        }
        free(matriz);
    }
}

void questao9() {
    printf("questao 9\n\n");

    int m, n;
    int **matriz;

    printf("Linhas (m): ");
    scanf("%d", &m);
    printf("Colunas (n): ");
    scanf("%d", &n);

    if(m <= 0 || n <= 0) {
        printf("Erro!\n");
        return;
    }

    matriz = alocar_matriz(m, n);

    if(matriz == NULL) {
        printf("Erro na alocacao!\n");
        return;
    }

    printf("Matriz %dx%d alocada!\n", m, n);

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            matriz[i][j] = i * n + j + 1;
        }
    }

    printf("\nMatriz:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }

    liberar_matriz(matriz, m);
    printf("Memoria liberada!\n");
}

int main() {
    int opcao;

    printf("exercicios de ponteiros\n\n");

    do {
        printf("\nquestao (1-9) ou 0 pra sair: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: questao1(); break;
            case 2: questao2(); break;
            case 3: questao3(); break;
            case 4: questao4(); break;
            case 5: questao5(); break;
            case 6: questao6(); break;
            case 7: questao7(); break;
            case 8: questao8(); break;
            case 9: questao9(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n"); break;
        }

        if(opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }

    } while(opcao != 0);

    return 0;
}
