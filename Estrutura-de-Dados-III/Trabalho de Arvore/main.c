#include "matriz.h"

int main(){
    Arvore* arv = cria_arvore();
    if(arv == NULL){
        printf("erro ao criar arvore\n");
        return 1;
    }

    printf("lendo arquivo in.txt...\n");
    if(!ler_arquivo(arv, "in.txt")){
        printf("erro ao ler arquivo in.txt\n");
        printf("continuando sem arquivo...\n");
    } else {
        printf("arquivo in.txt lido com sucesso!\n");
    }

    printf("\nsistema de diretorios\n");
    printf("digite 'help' para ver os comandos disponiveis\n\n");

    char comando[256];
    char arg[256];

    while(1){
        imprime_caminho_atual(arv);
        printf("$ ");

        if(fgets(comando, sizeof(comando), stdin) == NULL)
            break;

        comando[strcspn(comando, "\n\r")] = '\0';

        if(strlen(comando) == 0)
            continue;

        if(sscanf(comando, "%s %s", comando, arg) == 1){
            arg[0] = '\0';
        }

        if(strcmp(comando, "exit") == 0){
            printf("encerrando programa...\n");
            break;
        }
        else if(strcmp(comando, "cd") == 0){
            if(strlen(arg) == 0)
                printf("uso: cd <diretorio>\n");
            else
                comando_cd(arv, arg);
        }
        else if(strcmp(comando, "search") == 0){
            if(strlen(arg) == 0)
                printf("uso: search <nome>\n");
            else
                comando_search(arv, arg);
        }
        else if(strcmp(comando, "rm") == 0){
            if(strlen(arg) == 0)
                printf("uso: rm <diretorio>\n");
            else
                comando_rm(arv, arg);
        }
        else if(strcmp(comando, "list") == 0){
            comando_list(arv);
        }
        else if(strcmp(comando, "mkdir") == 0){
            if(strlen(arg) == 0)
                printf("uso: mkdir <nome>\n");
            else
                comando_mkdir(arv, arg);
        }
        else if(strcmp(comando, "clear") == 0){
            comando_clear();
        }
        else if(strcmp(comando, "help") == 0){
            comando_help();
        }
        else{
            printf("comando nao reconhecido: %s\n", comando);
            printf("digite 'help' para ver os comandos disponiveis\n");
        }

        printf("\n");
    }

    libera_arvore(arv);
    printf("memoria liberada. programa encerrado.\n");

    return 0;
}
