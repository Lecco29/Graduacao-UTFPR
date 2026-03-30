#include "matriz.h"

// cria arvore vazia
Arvore* cria_arvore(){
    Arvore* arv = (Arvore*) malloc(sizeof(Arvore));
    if(arv == NULL)
        return NULL;

    No* raiz = (No*) malloc(sizeof(No));
    if(raiz == NULL){
        free(arv);
        return NULL;
    }

    strcpy(raiz->nome, "/");
    raiz->eh_arquivo = 0;
    raiz->pai = NULL;
    raiz->primeiro_filho = NULL;
    raiz->proximo_irmao = NULL;

    arv->raiz = raiz;
    arv->atual = raiz;

    return arv;
}

// libera no e seus filhos
void libera_no(No* no){
    if(no == NULL)
        return;

    No* filho = no->primeiro_filho;
    while(filho != NULL){
        No* proximo = filho->proximo_irmao;
        libera_no(filho);
        filho = proximo;
    }

    free(no);
}

// libera arvore toda
void libera_arvore(Arvore* arv){
    if(arv == NULL)
        return;

    libera_no(arv->raiz);
    free(arv);
}

// encontra no pelo nome no diretorio atual
No* encontra_no(No* diretorio, const char* nome){
    if(diretorio == NULL || nome == NULL)
        return NULL;

    No* filho = diretorio->primeiro_filho;
    while(filho != NULL){
        if(strcmp(filho->nome, nome) == 0)
            return filho;
        filho = filho->proximo_irmao;
    }

    return NULL;
}

// adiciona caminho na arvore (ex: "Meus Documentos/apresentacao.ppt")
int adiciona_caminho(Arvore* arv, const char* caminho){
    if(arv == NULL || caminho == NULL)
        return 0;

    char caminho_copia[1024];
    strcpy(caminho_copia, caminho);

    char* token = strtok(caminho_copia, "/");
    No* atual = arv->raiz;

    while(token != NULL){
        No* encontrado = encontra_no(atual, token);

        if(encontrado == NULL){
            No* novo = (No*) malloc(sizeof(No));
            if(novo == NULL)
                return 0;

            strcpy(novo->nome, token);
            // se tem extensao, eh arquivo
            if(strchr(token, '.') != NULL)
                novo->eh_arquivo = 1;
            else
                novo->eh_arquivo = 0;

            novo->pai = atual;
            novo->primeiro_filho = NULL;
            novo->proximo_irmao = NULL;

            if(atual->primeiro_filho == NULL){
                atual->primeiro_filho = novo;
            } else {
                No* ultimo = atual->primeiro_filho;
                while(ultimo->proximo_irmao != NULL)
                    ultimo = ultimo->proximo_irmao;
                ultimo->proximo_irmao = novo;
            }

            atual = novo;
        } else {
            atual = encontrado;
        }

        token = strtok(NULL, "/");
    }

    return 1;
}

// le arquivo in.txt e monta arvore
int ler_arquivo(Arvore* arv, const char* nome_arquivo){
    if(arv == NULL || nome_arquivo == NULL)
        return 0;

    FILE* arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL)
        return 0;

    char linha[1024];
    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        linha[strcspn(linha, "\n\r")] = '\0';

        if(strlen(linha) == 0)
            continue;

        adiciona_caminho(arv, linha);
    }

    fclose(arquivo);
    return 1;
}

// mostra alternativas quando diretorio nao existe
void encontra_alternativas(Arvore* arv, const char* prefixo){
    if(arv == NULL || prefixo == NULL)
        return;

    int encontrou_alternativas = 0;
    No* filho = arv->atual->primeiro_filho;

    printf("diretorios possiveis:\n");
    while(filho != NULL){
        if(!filho->eh_arquivo && strncmp(filho->nome, prefixo, strlen(prefixo)) == 0){
            printf("  - %s\n", filho->nome);
            encontrou_alternativas = 1;
        }
        filho = filho->proximo_irmao;
    }

    if(!encontrou_alternativas)
        printf("diretorio nao encontrado\n");
}

// comando cd: entra em diretorio
int comando_cd(Arvore* arv, const char* nome_dir){
    if(arv == NULL || nome_dir == NULL)
        return 0;

    if(strcmp(nome_dir, "..") == 0){
        if(arv->atual->pai != NULL){
            arv->atual = arv->atual->pai;
            return 1;
        }
        return 0;
    }

    if(strcmp(nome_dir, "/") == 0){
        arv->atual = arv->raiz;
        return 1;
    }

    No* encontrado = encontra_no(arv->atual, nome_dir);

    if(encontrado == NULL){
        encontra_alternativas(arv, nome_dir);
        return 0;
    }

    if(encontrado->eh_arquivo){
        printf("erro: %s eh um arquivo, nao um diretorio\n", nome_dir);
        return 0;
    }

    arv->atual = encontrado;
    return 1;
}

// busca recursiva pra comando search
void busca_recursiva(No* no, const char* nome, char* caminho_atual, int* encontrou){
    if(no == NULL || nome == NULL)
        return;

    if(strcmp(no->nome, nome) == 0){
        printf("encontrado: %s/%s\n", caminho_atual, nome);
        *encontrou = 1;
    }

    if(!no->eh_arquivo){
        char novo_caminho[1024];
        if(strcmp(caminho_atual, "/") == 0)
            sprintf(novo_caminho, "/%s", no->nome);
        else
            sprintf(novo_caminho, "%s/%s", caminho_atual, no->nome);

        No* filho = no->primeiro_filho;
        while(filho != NULL){
            busca_recursiva(filho, nome, novo_caminho, encontrou);
            filho = filho->proximo_irmao;
        }
    }
}

// comando search: busca arquivo ou pasta
void comando_search(Arvore* arv, const char* nome){
    if(arv == NULL || nome == NULL)
        return;

    int encontrou = 0;
    busca_recursiva(arv->raiz, nome, "/", &encontrou);

    if(!encontrou)
        printf("arquivo ou pasta '%s' nao encontrado\n", nome);
}

// comando rm: remove diretorio recursivamente
int comando_rm(Arvore* arv, const char* nome_dir){
    if(arv == NULL || nome_dir == NULL)
        return 0;

    No* encontrado = encontra_no(arv->atual, nome_dir);

    if(encontrado == NULL){
        printf("diretorio '%s' nao encontrado\n", nome_dir);
        return 0;
    }

    if(encontrado->eh_arquivo){
        printf("erro: %s eh um arquivo, use rm apenas para diretorios\n", nome_dir);
        return 0;
    }

    No* pai = arv->atual;
    No* filho = pai->primeiro_filho;

    if(filho == encontrado){
        pai->primeiro_filho = encontrado->proximo_irmao;
    } else {
        while(filho != NULL && filho->proximo_irmao != encontrado)
            filho = filho->proximo_irmao;
        if(filho != NULL)
            filho->proximo_irmao = encontrado->proximo_irmao;
    }

    libera_no(encontrado);

    printf("diretorio '%s' removido com sucesso\n", nome_dir);
    return 1;
}

// comando list: lista o que tem na pasta atual
void comando_list(Arvore* arv){
    if(arv == NULL)
        return;

    No* filho = arv->atual->primeiro_filho;

    if(filho == NULL){
        printf("diretorio vazio\n");
        return;
    }

    while(filho != NULL){
        if(filho->eh_arquivo)
            printf("  [arquivo] %s\n", filho->nome);
        else
            printf("  [diretorio] %s\n", filho->nome);
        filho = filho->proximo_irmao;
    }
}

// comando mkdir: cria nova pasta
int comando_mkdir(Arvore* arv, const char* nome_dir){
    if(arv == NULL || nome_dir == NULL)
        return 0;

    if(encontra_no(arv->atual, nome_dir) != NULL){
        printf("erro: diretorio '%s' ja existe\n", nome_dir);
        return 0;
    }

    No* novo = (No*) malloc(sizeof(No));
    if(novo == NULL)
        return 0;

    strcpy(novo->nome, nome_dir);
    novo->eh_arquivo = 0;
    novo->pai = arv->atual;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;

    if(arv->atual->primeiro_filho == NULL){
        arv->atual->primeiro_filho = novo;
    } else {
        No* ultimo = arv->atual->primeiro_filho;
        while(ultimo->proximo_irmao != NULL)
            ultimo = ultimo->proximo_irmao;
        ultimo->proximo_irmao = novo;
    }

    printf("diretorio '%s' criado com sucesso\n", nome_dir);
    return 1;
}

// comando clear: limpa tela
void comando_clear(){
    int i;
    for(i = 0; i < 50; i++)
        printf("\n");
}

// comando help
void comando_help(){
    printf("\ncomandos disponiveis:\n\n");
    printf("cd <diretorio>     - entra no diretorio\n");
    printf("cd ..              - volta pro diretorio pai\n");
    printf("cd /               - volta pra raiz\n");
    printf("search <nome>      - busca arquivo ou pasta\n");
    printf("rm <diretorio>     - remove diretorio e seus arquivos\n");
    printf("list               - lista tudo na pasta atual\n");
    printf("mkdir <nome>       - cria uma nova pasta\n");
    printf("clear              - limpa a tela\n");
    printf("help               - mostra essa ajuda\n");
    printf("exit               - encerra o programa\n\n");
}

// imprime caminho atual
void imprime_caminho_atual(Arvore* arv){
    if(arv == NULL)
        return;

    char caminho[1024] = "";
    No* atual = arv->atual;

    while(atual != NULL && atual != arv->raiz){
        char temp[1024];
        if(strlen(caminho) == 0)
            sprintf(temp, "%s", atual->nome);
        else
            sprintf(temp, "%s/%s", atual->nome, caminho);
        strcpy(caminho, temp);
        atual = atual->pai;
    }

    if(strlen(caminho) == 0)
        printf("/");
    else
        printf("/%s", caminho);
}
