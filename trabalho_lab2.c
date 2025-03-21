#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sensor {
    int id;
    char tipo[100];
    struct Sensor* proximo;
} Sensor;

typedef struct Dispositivo {
    int id;
    char descricao[100];
    char tipo[100];
    char status[100];
    Sensor* sensores;
    struct Dispositivo* proximo;
} Dispositivo;

Dispositivo* inicializa() {
    return NULL;
}

Dispositivo* criar_dispositivo(int id, char* descricao, char* tipo, char* status) {
    Dispositivo* novo = (Dispositivo*)malloc(sizeof(Dispositivo));
    if (novo == NULL) {
        printf("Erro!\n");
        exit(1);
    }
    novo->id = id;
    strcpy(novo->descricao, descricao);
    strcpy(novo->tipo, tipo);
    strcpy(novo->status, status);
    novo->sensores = NULL;
    novo->proximo = NULL;
    return novo;
}

void insere_dispositivo(Dispositivo** lista, Dispositivo* novo) {
    novo->proximo = *lista;
    *lista = novo;
}

void remove_dispositivo(Dispositivo** lista, int id) {
    Dispositivo *atual = *lista, *anterior = NULL;
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("dispositivo nao encontrado!\n");
        return;
    }
    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("dispositivo removido com sucesso!\n");
}

void listar_dispositivos(Dispositivo* lista) {
    while (lista != NULL) {
        printf("ID: %d | descricao: %s | tipo: %s | status: %s\n",
               lista->id, lista->descricao, lista->tipo, lista->status);
        lista = lista->proximo;
    }
}

Sensor* criar_sensor(int id, char* tipo) {
    Sensor* novo = (Sensor*)malloc(sizeof(Sensor));
    if (novo == NULL) {
        printf("erro!\n");
        exit(1);
    }
    novo->id = id;
    strcpy(novo->tipo, tipo);
    novo->proximo = NULL;
    return novo;
}

void insere_sensor(Dispositivo* dispositivo, Sensor* novo) {
    novo->proximo = dispositivo->sensores;
    dispositivo->sensores = novo;
}

void listar_sensores(Dispositivo* dispositivo) {
    Sensor* atual = dispositivo->sensores;
    if (atual == NULL) {
        printf("nenhum sensor encontrado para este dispositivo.\n");
        return;
    }
    while (atual != NULL) {
        printf("ID sensor: %d | tipo: %s\n", atual->id, atual->tipo);
        atual = atual->proximo;
    }
}

int main() {
    Dispositivo* lista = inicializa();
    int opicao, id;
    char descricao[100], tipo[100], status[100];

    do {
        printf("\n1 - Inserir dispositivo\n2 - Remover dispositivo\n3 - Listar dispositivos\n4 - Adicionar sensor a um dispositivo\n5 - Listar sensores de um dispositivo\n6 - Sair\nopicao: ");
        scanf("%d", &opicao);

        switch (opicao) {
            case 1:
                printf("ID: "); scanf("%d", &id);
                printf("descricao: "); scanf("%s", descricao);
                printf("dipo: "); scanf("%s", tipo);
                printf("status: "); scanf("%s", status);
                insere_dispositivo(&lista, criar_dispositivo(id, descricao, tipo, status));
                break;
            case 2:
                printf("ID do dispositivo q deseja remover: "); scanf("%d", &id);
                remove_dispositivo(&lista, id);
                break;
            case 3:
                listar_dispositivos(lista);
                break;
            case 4:
                printf("ID do dispositivo q deseja adicionar sensor: "); scanf("%d", &id);
                Dispositivo* dispositivo = lista;
                while (dispositivo != NULL && dispositivo->id != id) {
                    dispositivo = dispositivo->proximo;
                }
                if (dispositivo == NULL) {
                    printf("dispositivo nao encontrado!\n");
                    break;
                }
                printf("ID do sensor: "); scanf("%d", &id);
                printf("tipo do sensor: "); scanf("%s", tipo);
                insere_sensor(dispositivo, criar_sensor(id, tipo));
                break;
            case 5:
                printf("ID do dispositivo q deseja ver os sensores: "); scanf("%d", &id);
                dispositivo = lista;
                while (dispositivo != NULL && dispositivo->id != id) {
                    dispositivo = dispositivo->proximo;
                }
                if (dispositivo == NULL) {
                    printf("dispositivo nao encontrado!\n");
                    break;
                }
                listar_sensores(dispositivo);
                break;
            case 6:
                printf("finalizado\n");
                break;
            default:
                printf("opicao invalida!\n");
        }
    } while (opicao != 6);

    return 0;
}
