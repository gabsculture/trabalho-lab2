#include "estruturas.h"
#include "Dispositivos.h"
#include "Funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Sensor* criar_sensor(int id, char* tipo, char* subtipo, float valor) {
    Sensor* novo = (Sensor*)malloc(sizeof(Sensor));
    if (novo == NULL) {
        printf("erro!\n");
        exit(1);
    }
    novo->id = id;
    strcpy(novo->tipo, tipo);
    strcpy(novo->subtipo, subtipo);
    novo->valores->valor = valor; //TODO incluir o insere na lista e o timestamp
    novo->proximo = NULL;
    return novo;
}

void insere_sensor(Dispositivo* dispositivo, Sensor* novo) {
    novo->proximo = dispositivo->sensores;
    dispositivo->sensores = novo;
}

void remove_sensor(Dispositivo* dispositivo, int id){
    if (dispositivo == NULL) {
        printf("Dispositivo invalido!\n");
        return;
    }

    Sensor *atual = dispositivo->sensores;
    Sensor *anterior = NULL;

    while(atual != NULL && atual->id != id){
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Sensor nao encontrado!\n");
        return;
    }
    if (anterior == NULL) {
        dispositivo->sensores = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Sensor removido com sucesso!\n");
}

void listar_sensores(Dispositivo* dispositivo) {
    Sensor* atual = dispositivo->sensores;
    if (atual == NULL) {
        printf("nenhum sensor encontrado para este dispositivo.\n");
        return;
    }
    while (atual != NULL) {
        printf("ID sensor: %d | tipo: %s | subtipo: %s |valor: %f |\n", atual->id, atual->tipo, atual->subtipo, atual->valores->valor);
        atual = atual->proximo;
    }
}

void tipo_validos(char* tipo_sensor) {
    const char *tipos_sensores[] = {"sensor", "atuador"};
    int num_tiposensores = sizeof(tipos_sensores) / sizeof(tipos_sensores[0]), valido, i;

    do{
        printf("Tipo do sensor: ");
        scanf("%19s", tipo_sensor);

        minusculas(tipo_sensor);

        valido = 0;
        i = 0;
        while(i < num_tiposensores && valido == 0){
            if(strcmp(tipo_sensor, tipos_sensores[i]) == 0){
                valido = 1;
            }
            i++;
        }

        if(!valido){
            printf("Tipo de sensor invalido! Os tipos validos sao:\n");
            for(i = 0; i < num_tiposensores; i++){
                printf("- %s\n", tipos_sensores[i]);
            }
        }
    }while(valido != 1);
}

void subtipo_validos(char* subtipo_sensor) {
    const char *subtipos_sensores[] = {"temperatura", "umidade", "movimento", "luminosidade", "pressao", "proximidade", "fumaca", "gas", "agua"};
    int num_subsensores = sizeof(subtipos_sensores) / sizeof(subtipos_sensores[0]), valido, i;

    do{
        printf("Subtipo do sensor: ");
        scanf("%19s", subtipo_sensor);

        minusculas(subtipo_sensor);

        valido = 0;
        i = 0;
        while(i < num_subsensores && valido == 0){
            if(strcmp(subtipo_sensor, subtipos_sensores[i]) == 0){
                valido = 1;
            }
            i++;
        }

        if(!valido){
            printf("Tipo de sensor invalido! Os tipos validos sao:\n");
            for(i = 0; i < num_subsensores; i++){
                printf("- %s\n", subtipos_sensores[i]);
            }
        }
    }while(valido != 1);
}

Dispositivo *opera_sensores(Dispositivo *dispositivo){
    Dispositivo* lista = dispositivo;
    char tipo_sensor[100], subtipo_sensor[100];
    int op ,id;
    float valor;

    printf("\n1 - Adicionar sensor a um dispositivo\n2 - Remover um sensor\n3 - Listar sensores de um dispositivo");
    scanf("%d", &op);

    switch(op) {
        case 1:
            printf("ID do dispositivo q deseja adicionar sensor: "); scanf("%d", &id);
        while (dispositivo != NULL && dispositivo->id != id) {
            dispositivo = dispositivo->proximo;
        }
        if (dispositivo == NULL) {
            printf("dispositivo nao encontrado!\n");
            break;
        }
        printf("ID do sensor: "); scanf("%d", &id);

        tipo_validos(tipo_sensor);
        //le a entrtada do usuario e verifica se o subtipo do sensor é valido
        subtipo_validos(subtipo_sensor);

        if(strcmp(tipo_sensor, "sensor") == 0) {
            printf("\nDigite o valor do sensor\n");
            scanf("%f", &valor);
        }else{
            valor = 0;
        }

        insere_sensor(dispositivo, criar_sensor(id, tipo_sensor,subtipo_sensor, valor));
        break;
        case 2:
            printf("ID do dispositivo q deseja adicionar sensor: ");
        scanf("%d", &id);

        remove_sensor(dispositivo, id);
        break;
        case 3:
            printf("ID do dispositivo q deseja ver os sensores: "); scanf("%d", &id);
        while (dispositivo != NULL && dispositivo->id != id) {
            dispositivo = dispositivo->proximo;
        }
        if (dispositivo == NULL) {
            printf("dispositivo nao encontrado!\n");
            break;
        }
        listar_sensores(dispositivo);
        break;
        default:
            printf("opicao invalida!\n");
    }

    return dispositivo;
}

