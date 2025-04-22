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
    char prioridade[10];
    float valor;
    Sensor* sensores;
    Dispositivo* dispositivos;
    struct Evento* proximo;
} Evento;

typedef struct Fila{
    Evento* inicio;
    Evento* fim;
    int tamanho;
} Fila;

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

Fila* cria(void) { //aloca a memoria para a fila e cria a fila vazia
    Fila* fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void insere_fila(Fila* fila, Evento* evento){ //insere os eventos na fila
    if(fila->fim == NULL){   //verifica se tem alguém na fila
        fila->fim = evento;
        fila->inicio = evento;
    }else { //caso não estaja vazia ela vai adicionar o evento no final
        fila->fim->proximo = evento;
        fila->fim = evento;
    }
    evento->proximo = NULL;
    fila->tamanho++;
}

Evento* remove_da_fila(Fila* fila){
    Evento *remover = fila->inicio; //pega o inicio da fila, somente para exibir depois

    if(fila->inicio != NULL){ //caso a fila não esteja vazia
        fila->inicio = fila->inicio->proximo; //O novo inicio sera o proximo da lista
    }else {
        printf("Fila vazia!\n");
    }

    if(fila->fim == NULL){ // caso a fila fique fazia ira atualizar o ponteiro do fim
        fila->fim = NULL;
    }
    fila->tamanho--;
    return remover;

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

Sensor* criar_sensor(int id, char* tipo, char* subtipo, float valor) {
    Sensor* novo = (Sensor*)malloc(sizeof(Sensor));
    if (novo == NULL) {
        printf("erro!\n");
        exit(1);
    }
    novo->id = id;
    strcpy(novo->tipo, tipo);
    strcpy(novo->subtipo, subtipo);
    novo->valor = valor;
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
        printf("ID sensor: %d | tipo: %s | subtipo: %s |valor: %f |\n", atual->id, atual->tipo, atual->subtipo, atual->valor);
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

        return lista;
    }
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

            if(subtipo_sensor == "umidade" || subtipo_sensor == "temperatura") {
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
}

Evento* criar_evento(Dispositivo* dispositivo, int id, int id_sensor, char* descricao, char* prioridade, float valor){
    Evento* novo = (Evento*)malloc(sizeof(Evento));
    Dispositivo* lista = dispositivo;
    Sensor* sensor = NULL;

    while(lista != NULL && lista->id != id){
        lista = lista->proximo;
    }
    if(lista == NULL) {
        printf("dispositivo nao encontrado!\n");
    }

    if(id_sensor != -1) {
        sensor = dispositivo->proximo;
        while(sensor != NULL && sensor->id != id_sensor) {
            sensor = sensor->proximo;
        }
        if(sensor == NULL) {
            printf("Sensor nao encontrado!\n");
        }
    }

    novo->dispositivos = lista;
    novo->sensores = sensor;
    strcpy(novo->descricao, descricao);
    strcpy(novo->prioridade, prioridade);
    novo->valor = valor;
    novo->proximo = NULL;

    return novo;


}

void insere_evento(Dispositivo* dispositivo, Fila* alta, Fila* media, Fila* baixa){
    char descricao[100], prioridade[10];
    int id, id_sensor;
    float valor;

    //pede as informações ao usuario
    printf("Digite o ID do dispositivo que deseja colocar um evento: ");
    scanf("%d", &id);
    printf("Digite o ID do sensor ligado ao dispositivo(caso o dispositivo não tenha id digite -1)");
    scanf("%d", &id_sensor);
    printf("Digite a descrição do dispositivo: ");
    scanf("%s", descricao);
    do { //confere prioridade do dispositivo
        printf("Digite a prioridade do dispositivo(alta, media, baixa): ");
        scanf("%s", prioridade);
    }while(strcmp(prioridade, "alta") != 0 && strcmp(descricao, "media") != 0 && strcmp(prioridade, "baixa") != 0 );
    printf("Digite o valor a ser alterado(caso não tenha valor para alterar digite 0): ");
    scanf("%f", &valor);

    Evento *novo = criar_evento(dispositivo, id, id_sensor, descricao, prioridade, valor); //cria um evento
    if(novo != NULL){
        //faz a comparação de prioridade e insere em uma fila
        if(strcmp(prioridade, "alta") == 0){
            insere_fila(alta, novo);
        }else if(strcmp(prioridade, "media") == 0){
            insere_fila(media, novo);
        }else{
            insere_fila(baixa, novo);
        }
    }
}

void executa_evento(Fila* alta, Fila* media, Fila* baixa){
    Evento* evento = NULL;

    if(alta->inicio != NULL) { //verifica se existe algo na lista e executa o comando de remover fila
        evento = remove_da_fila(alta);
    }else if(media->inicio != NULL) {
        evento = remove_da_fila(media);
    }else if(baixa->inicio != NULL) {
        evento = remove_da_fila(baixa);
    }else {
        printf("Não existe evento para ser removido"); //caso não tenha nenhum evento nas filas
    }

    if(evento != NULL){ //caso existir um evento vai imprimir qual foi
      printf("\nO evento '%s' foi executado", evento->descricao);
        if(evento->sensores->id != -1){ //acha o sensor que foi vai ser alterado no evento
            Sensor* sensor = evento->dispositivos->sensores;
            while(sensor != NULL && sensor->id != evento->sensores->id){ //percorre por todos os sensores até achar o id correspondente
                sensor = sensor->proximo;
            }
            if(sensor == NULL) {
                printf("Sensor nao encontrado!\n");
            }
            if(sensor != NULL){ //caso esse sensor exista ele troca o valor
                sensor->valor = evento->valor;
            }
        }
      
        free(evento);
    }
}

void listar_eventos(Fila *alta, Fila *media, Fila *baixa){
    //Fila *alta, *media, *baixa;
    printf("\n--- Eventos de prioridade: Alta (%d) ---\n", alta->tamanho);
    Evento* atual = alta->inicio;
    while (atual != NULL) {
        printf("Descricao: %s | Dispositivo: %d", atual->descricao, atual->dispositivos->id);
        if (atual->sensores != NULL) {
            printf(" | Sensor: %d", atual->sensores->id);
        }
        printf(" | Valor: %.2f\n", atual->valor);
        atual = atual->proximo;
    }

    printf("\n--- Eventos de prioridade: Media (%d) ---\n", media->tamanho);
    atual = media->inicio;
    while (atual != NULL) {
        printf("Descricao: %s | Dispositivo: %d", atual->descricao, atual->dispositivos->id);
        if (atual->sensores != NULL) {
            printf(" | Sensor: %d", atual->sensores->id);
        }
        printf(" | Valor: %.2f\n", atual->valor);
        atual = atual->proximo;
    }

    printf("\n--- Eventos de prioridade: Baixa (%d) ---\n", baixa->tamanho);
    atual = baixa->inicio;
    while (atual != NULL) {
        printf("Descricao: %s | Dispositivo: %d", atual->descricao, atual->dispositivos->id);
        if (atual->sensores != NULL) {
            printf(" | Sensor: %d", atual->sensores->id);
        }
        printf(" | Valor: %.2f\n", atual->valor);
        atual = atual->proximo;
    }
}

Dispositivo* opera_evento(Dispositivo* dispositivo, Fila* alta, Fila* media, Fila* baixa){
    int opicao;

    if(alta == NULL || media == NULL || baixa == NULL) {
        printf("Erro: filas não inicializadas!\n");
        return dispositivo;
    }

    do{
        printf("\nDigite uma das opções: \n1 - insere novo evento\n2 - Executa evento\n3 - listar eventos\n4 - Sair");
        scanf("%d", &opicao);
        switch(opicao) {
            case 1:
                insere_evento(dispositivo, alta, media, baixa);
                break;
            case 2:
                executa_evento(alta, media, baixa);
                break;
            case 3:
                listar_eventos(alta, media, baixa);
                break;
            case 4:
                printf("Saindo!");
                break;
            default:
                printf("Digite um valor valido");
                break;
        }
    }while(opicao != 4);

    return dispositivo;
}

void liberar_fila(Fila* fila) {
    if (fila == NULL) return;

    Evento* atual = fila->inicio;
    Evento* proximo;

    // Libera todos os eventos da fila
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);  // Libera o evento atual
        atual = proximo;
    }

    // Libera a estrutura da fila
    free(fila);
}

void liberar_todas_filas(Fila* alta, Fila* media, Fila* baixa){
    if (alta != NULL) {
        liberar_fila(alta);
    }
    if (media != NULL) {
        liberar_fila(media);
    }
    if (baixa != NULL) {
        liberar_fila(baixa);
    }
}


int main() {
    Dispositivo* lista = inicializa();
    Fila *alta = cria();
    Fila *media = cria();
    Fila *baixa = cria();
    int opicao;


    do {
        printf("\nCom o que deseja mexer: \n1 - Dispositivos\n2 - Sensores\n3 - Eventos\n4 - Sair\n\nEscolha uma opção");
        scanf("%d", &opicao);

        switch (opicao) {
            case 1:
                lista = opera_dispositivos(lista); //faz as operações com dispositivos e retorna a lista atualizada
                break;
            case 2:
                lista = opera_sensores(lista); //faz as operações com sensores e retorna na lista atualizada 
                break;
            case 3:
                opera_evento(lista, alta, media, baixa); //faz as operações com os eventos 
                break;
            case 4:
                printf("finalizado\n");
                break;
            default:
                printf("opição invalida!\n");
        }
    } while (opicao != 4);
    
    //libera as listas e as filas
    libera(lista);
    liberar_todas_filas(alta, media, baixa);

    //anular ponteiros após liberar
    lista = NULL;
    alta = media = baixa = NULL;

    return 0;
}
