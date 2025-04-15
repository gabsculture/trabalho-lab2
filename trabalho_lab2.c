// Diogo Dalbianco dos Santos e Gabriela Vitória da Rosa Soares 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Sensor {
    int id;
    char tipo[100];
    char subtipo[100];
    float valor;
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

typedef struct Evento {
    char descricao[100];
    char prioridade[100];
    float valor;
    struct Evento* proximo;
} Evento;

typedef struct Fila {
    Evento* inicio;
    Evento* fim;
} fila;

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

Fila* cria(void) {
    Fila* fila = (Fila*(malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void insere_fila(Fila* fila, int v) {
    Evento* novo = (Evento*(malloc(sizeof(Evento));
    novo->proximo = NULL;
    if(fila->fim == NULL) {
        fila->fim->proximo = novo;
    } else {
        fila->inicio = novo;
    }
    fila->fim = novo;
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

//verificar essa função
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
        printf("ID sensor: %d | tipo: %s\n", atual->id, atual->tipo);
        atual = atual->proximo;
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

void insere_evento(Evento* evento){
    
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

            printf("descricao: "); scanf("%s", descricao);

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
}

void opera_sensores(Dispositivo* dispositivo){
    Dispositivo* lista = dispositivo;
    char tipo_sensor[100], subtipo_sensor[100];
    int op ,id;

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

            insere_sensor(dispositivo, criar_sensor(id, subtipo_sensor));
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
}

int main() {
    Dispositivo* lista = inicializa();
    int opicao;


    do {
        printf("\nCom o que deseja mexer: \n1 - Dispositivos\n2 - Sensores\n3 - Eventos\n4 - Sair\n\nEscolha uma opção");
        scanf("%d", &opicao);

        switch (opicao) {
            case 1:
                lista = opera_dispositivos(lista);
                break;
            case 2:
                opera_sensores(lista);
                break;
            case 3:
                break;
            case 4:
                printf("finalizado\n");
                break;
            default:
                printf("opicao invalida!\n");
        }
    } while (opicao != 4);

    libera(lista);
    return 0;
}
