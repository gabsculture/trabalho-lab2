// Diogo Dalbianco dos Santos e Gabriela Vitória da Rosa Soares 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

bool valida_id(Dispositivo* lista, int id) {
    while(lista != NULL) {
        if(lista->id == id) {
            return false;
        }
    
        lista = lista->proximo;
    }
    return true;
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

void minusculas(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    Dispositivo* lista = inicializa();
    int opicao, id, valido, i, j;
    char descricao[100], tipo[100], status[100], tipo_sensor[100];
    const char *tipos_validos[] = {"lampada", "camera", "tomada", "sensor", "ventilador", "ar_condicionado"};
    int num_tipos = sizeof(tipos_validos) / sizeof(tipos_validos[0]);
    const char *condicoes_validas[] = {"ligado", "desligado", "offline", "com_erro", "em_espera", "em_manutencao"};
    int num_condicoes = sizeof(condicoes_validas) / sizeof(condicoes_validas[0]);
    const char *tipos_sensores[] = {"temperatura", "umidade", "movimento", "luminosidade", "pressao", "proximidade", "fumaca", "gas", "agua"};
    int num_sensores = sizeof(tipos_sensores) / sizeof(tipos_sensores[0]);
    bool verifica;



    do {
        printf("\n1 - Inserir dispositivo\n2 - Remover dispositivo\n3 - Listar dispositivos\n4 - Adicionar sensor a um dispositivo\n5 - Listar sensores de um dispositivo\n6 - Sair\nopicao: ");
        scanf("%d", &opicao);

        switch (opicao) {
            case 1:
                do{
                    printf("ID: "); scanf("%d", &id);
                    verifica = valida_id(lista, id);
                }while(verifica != true); 
                
                printf("descricao: "); scanf("%s", descricao);

                //le a entrtada do usuario e verifica se o dispositivo é valido
                do{
                    printf("Tipo de dispositivo: ");
                    scanf("%19s", tipo);
                    
                    minusculas(tipo);
                    
                    valido = 0;
                    i = 0;
                    while(i < num_tipos &&  valido == 0){
                        if(strcmp(tipo, tipos_validos[i]) == 0){
                            valido = 1;
                        }
                        i++;
                    }
                    
                    if(!valido){
                        printf("Tipo invalido! Os tipos validos sao:\n");
                        for(i = 0; i < num_tipos; i++){
                            printf("- %s\n", tipos_validos[i]);
                        }
                    }
                }while(valido != 1);
                valido = 0;

                //le a entrtada do usuario e verifica se a condição é valida
                do{
                    printf("Condição do dispositivo: ");
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
                        for(j = 0; j < num_condicoes; j++){
                            printf("- %s\n", condicoes_validas[j]);
                        }
                    }
                }while(valido != 1);
                valido = 0;
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
                do{
                    printf("Tipo do sensor: ");
                    scanf("%19s", tipo_sensor);
    
                    minusculas(tipo_sensor);
                    
                    valido = 0;
                    i = 0;
                    while(i < num_sensores && valido == 0){
                        if(strcmp(tipo_sensor, tipos_sensores[i]) == 0){
                            valido = 1;
                        }
                        i++;
                    }
                    
                    if(!valido){
                        printf("Tipo de sensor invalido! Os tipos validos sao:\n");
                        for(j = 0; j < num_sensores; j++){
                            printf("- %s\n", tipos_sensores[j]);
                        }
                    }
                }while(valido != 1);
                insere_sensor(dispositivo, criar_sensor(id, tipo_sensor));
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
