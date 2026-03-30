#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaDin.h"

int main(){
    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};

    // teste questao 1 - separa
    printf("--- questao 1 ---\n");
    Fila* f1 = cria_Fila();
    Fila* f2 = cria_Fila();
    int i;
    for(i = 0; i < 4; i++)
        insere_Fila(f1, a[i]);

    printf("fila original:\n");
    imprime_Fila(f1);

    if(separa(f1, f2, 1)){
        printf("\nf1 apos separar:\n");
        imprime_Fila(f1);
        printf("\nf2:\n");
        imprime_Fila(f2);
    }
    libera_Fila(f1);
    libera_Fila(f2);

    // teste questao 3 - inverter
    printf("\n--- questao 3 ---\n");
    Fila* fi = cria_Fila();
    struct aluno t[3] = {{1,"Ana",5.7,6.1,7.4},
                         {2,"Bruno",8.5,7.2,9.1},
                         {3,"Carlos",6.8,8.3,7.5}};
    for(i = 0; i < 3; i++)
        insere_Fila(fi, t[i]);

    printf("antes:\n");
    imprime_Fila(fi);
    inverte_Fila(fi);
    printf("depois de inverter:\n");
    imprime_Fila(fi);
    libera_Fila(fi);

    // teste questao 4 - fura fila
    printf("\n--- questao 4 ---\n");
    fi = cria_Fila();
    for(i = 0; i < 2; i++)
        insere_Fila(fi, t[i]);
    printf("fila normal:\n");
    imprime_Fila(fi);
    FuraFila(fi, t[2]);
    printf("apos furar fila com Carlos:\n");
    imprime_Fila(fi);
    libera_Fila(fi);

    // teste questao 5 - aeroporto
    printf("\n--- questao 5 ---\n");
    Fila* fa = cria_Fila();
    adiciona_Aviao(fa, 101, "Boeing737", "GOL");
    adiciona_Aviao(fa, 102, "AirbusA320", "LATAM");
    adiciona_Aviao(fa, 103, "Boeing777", "Azul");
    printf("avioes na fila: %d\n", tamanho_Fila(fa));
    lista_Avioes(fa);
    printf("\nautorizando decolagem...\n");
    autoriza_Decolagem(fa);
    printf("restantes:\n");
    lista_Avioes(fa);
    libera_Fila(fa);

    // teste questao 6 - mescla ordenada
    printf("\n--- questao 6 ---\n");
    Fila* fo1 = cria_Fila();
    Fila* fo2 = cria_Fila();
    Fila* fo3 = cria_Fila();
    struct aluno ord1[2] = {{1,"Ana",5.7,6.1,7.4}, {3,"Carlos",6.8,8.3,7.5}};
    struct aluno ord2[2] = {{2,"Bruno",8.5,7.2,9.1}, {4,"Diana",7.2,8.1,6.9}};
    for(i = 0; i < 2; i++){
        insere_Fila(fo1, ord1[i]);
        insere_Fila(fo2, ord2[i]);
    }
    mescla_FilasOrdenadas(fo1, fo2, fo3);
    printf("fila mesclada:\n");
    imprime_Fila(fo3);
    libera_Fila(fo1);
    libera_Fila(fo2);
    libera_Fila(fo3);

    // teste questao 7 - reverso
    printf("\n--- questao 7 ---\n");
    fi = cria_Fila();
    for(i = 0; i < 3; i++)
        insere_Fila(fi, t[i]);
    printf("antes:\n");
    imprime_Fila(fi);
    reverso(fi);
    printf("apos reverso:\n");
    imprime_Fila(fi);
    libera_Fila(fi);

    // menu interativo (questao 8)
    printf("\n--- menu ---\n");
    executa_Menu();

    return 0;
}
