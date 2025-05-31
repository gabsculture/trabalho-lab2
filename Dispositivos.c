#include "estruturas.h"
#include "Sensores.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


Dispositivo* inicializa() { //inicia a lista vazia
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

bool valida_id(Dispositivo* lista, int id) {
    while(lista != NULL) {
        if(lista->id == id) {
            return false;
        }

        lista = lista->proximo;
    }
    return true;
}

void busca(Dispositivo* dispositivo){
    Dispositivo* lst;
    int verifica = 0, id, opcao;
    char descricao[100];

    printf("Como deseja buscar um dispositivo na lista:\n1 - Por id\n2 - por Descricao\nDigite:");
    scanf("%d", &opcao);

    if(opcao == 1){
        printf("Digite o id: ");
        scanf("%d", &id);
        for(lst = dispositivo; lst != NULL; lst = lst->proximo){
            if(lst->id == id){
                printf("ID: %d | descricao: %s | tipo: %s | status: %s\n", lst->id, lst->descricao, lst->tipo, lst->status);
                verifica = 1;
            }
        }
        if(verifica == 0){
            printf("Nao foi possivel achar o dispositivo");
        }

    }else{
        printf("Digite a descricao: ");
        scanf("%19s", descricao);

        for(lst = dispositivo; lst != NULL; lst = lst->proximo){
            if(strcmp(lst->descricao, descricao) == 0) {
                printf("ID: %d | descricao: %s | tipo: %s | status: %s\n", lst->id, lst->descricao, lst->tipo, lst->status);
                verifica = 1;
            }
        }
        if(verifica == 0){
            printf("Nao foi possivel achar o dispositivo");
        }
    }
}

void listar_dispositivos(Dispositivo* lista) {
    while (lista != NULL) {
        printf("ID: %d | descricao: %s | tipo: %s | status: %s\n",
               lista->id, lista->descricao, lista->tipo, lista->status);
        lista = lista->proximo;
    }
}

void minusculas(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void confere_dispositivos(char* tipo){ //função responsavel por verificar os dispositivos que o usuario digita
    const char *tipos_validos[] = {"lampada", "camera", "tomada", "sensor", "ventilador", "ar_condicionado"}; //faz uma pequena lista dos dispositivos que podem ser adicionados
    int num_tipos = sizeof(tipos_validos) / sizeof(tipos_validos[0]), valido, i;

    do{
        printf("Tipo de dispositivo: ");
        scanf("%19s", tipo);

        minusculas(tipo); //Caso seja digitado em letras maiusculas, converte para minusculas

        valido = 0;
        i = 0;
        while(i < num_tipos &&  valido == 0){ //Compara todos tipos validos com os tipos digitados
            if(strcmp(tipo, tipos_validos[i]) == 0){
                valido = 1;
            }
            i++;
        }

        if(!valido){ //Xinga usuario
            printf("Tipo invalido! Os tipos validos sao:\n");
            for(i = 0; i < num_tipos; i++){
                printf("- %s\n", tipos_validos[i]);
            }
        }
    }while(valido != 1);
}

void condicoes_validas(char* status){
    const char *condicoes_validas[] = {"ligado", "desligado", "offline", "com_erro", "em_espera", "em_manutencao"};
    int num_condicoes = sizeof(condicoes_validas) / sizeof(condicoes_validas[0]), valido, i;

    do{
        printf("Condicao do dispositivo: ");
        scanf("%19s", status);

        minusculas(status);

        valido = 0;
        i = 0;
        while(i < num_condicoes && valido == 0){
            if(strcmp(status, condicoes_validas[i]) == 0){
                valido = 1;
            }
            i++;
        }

        if(!valido){
            printf("Condicao invalida! As condicoes permitidas sao:\n");
            for(i = 0; i < num_condicoes; i++){
                printf("- %s\n", condicoes_validas[i]);
            }
        }
    }while(valido != 1);
}

void libera(Dispositivo* lst) {
    Dispositivo* aux = lst;
    while(aux != NULL) {
        // Liberar sensores primeiro
        Sensor* sensor = aux->sensores;
        while(sensor != NULL) {
            Sensor* tmp = sensor->proximo;
            free(sensor);
            sensor = tmp;
        }

        Dispositivo* tmp = aux->proximo;
        free(aux);
        aux = tmp;
    }
}

Dispositivo *opera_dispositivos(Dispositivo *dispositivo){
    Dispositivo* lista = dispositivo;
    int op, id;
    char descricao[100], tipo[100], status[100];
    bool verifica;

    printf("\n1 - Inserir dispositivo\n2 - Remover dispositivo\n3 - Busca dispositivo\n4 - Listar dispositivos");
    scanf("%d", &op);

    switch(op){
        case 1:
            do{ //verifica se o id já não foi digitado
                printf("ID: "); scanf("%d", &id);
                verifica = valida_id(lista, id);
            }while(verifica != true);

        printf("descricao: ");
        scanf(" %99[^\n]",descricao);

        //le a entrtada do usuario e verifica se o dispositivo é valido
        confere_dispositivos(tipo);

        //le a entrtada do usuario e verifica se a condição é valida
        condicoes_validas(status);

        insere_dispositivo(&lista, criar_dispositivo(id, descricao, tipo, status));
        break;
        case 2:
            printf("ID do dispositivo q deseja remover: "); scanf("%d", &id);
        remove_dispositivo(&lista, id);
        break;
        case 3:
            busca(lista);
        break;
        case 4:
            listar_dispositivos(lista);
        break;
        default:
            printf("opicao invalida!\n");
    }
    return lista;
}