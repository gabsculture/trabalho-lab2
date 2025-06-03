#include "estruturas.h"
#include "Funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Fila* cria(void) { //aloca a memoria para a fila e cria a fila vazia
    Fila* fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void insere_fila(Fila *fila, Evento *evento) {
    // Se a fila estiver vazia
    if (fila->inicio == NULL) {
        fila->inicio = evento;
        fila->fim = evento;
    } else if (strcmp(evento->prioridade, "alta") == 0) {
        // Inserção no início
        evento->proximo = fila->inicio;
        fila->inicio = evento;
    } else if (strcmp(evento->prioridade, "media") == 0) {
        // Inserção após os "altas", antes dos "baixas"
        Evento *atual = fila->inicio;
        Evento *anterior = NULL;

        while (atual != NULL && strcmp(atual->prioridade, "alta") == 0) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (anterior == NULL) {
            evento->proximo = fila->inicio;
            fila->inicio = evento;
        } else {
            evento->proximo = anterior->proximo;
            anterior->proximo = evento;
        }

        if (evento->proximo == NULL) {
            fila->fim = evento;
        }

    } else {
        // Prioridade baixa: inserção no fim
        fila->fim->proximo = evento;
        fila->fim = evento;
    }

    fila->tamanho++;
}


Evento* remove_da_fila(Fila *fila) {
    Evento *remover = fila->inicio;

    if (remover != NULL) {
        fila->inicio = fila->inicio->proximo;
        if (fila->inicio == NULL) {
            fila->fim = NULL;
        }
        fila->tamanho--;
    } else {
        printf("Fila vazia!\n");
    }
    return remover;
}

Evento* criar_evento(Dispositivo* dispositivo, int id, int id_sensor, char* descricao, char* prioridade, float valor) {
    Evento* novo = (Evento*)malloc(sizeof(Evento));
    Dispositivo* lista = dispositivo;
    Sensor* sensor = NULL;

    // Buscar o dispositivo com o ID fornecido
    while (lista != NULL && lista->id != id) {
        lista = lista->proximo;
    }
    if (lista == NULL) {
        printf("dispositivo nao encontrado!\n");
        free(novo); // Libera a memória alocada antes de retornar
        return NULL;
    }

    // Se houver id_sensor, buscar o sensor associado ao dispositivo
    if (id_sensor != -1) {
        Sensor* sensor_atual = lista->sensores;  // Acessa a lista de sensores do dispositivo
        while (sensor_atual != NULL && sensor_atual->id != id_sensor) {
            sensor_atual = sensor_atual->proximo;
        }
        if (sensor_atual == NULL) {
            printf("Sensor nao encontrado!\n");
            free(novo); // Libera a memória alocada antes de retornar
            return NULL;
        }
        sensor = sensor_atual;
    }

    // Preenche o evento
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
    printf("Digite a descrição do evento: ");
    scanf(" %99[^\n]",descricao);
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
                //TODO arrumar para colocar a função insere_valor
                sensor->valores->valor = evento->valor;
                incluirTimeStamp(sensor, evento->valor);
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

void opera_evento(Dispositivo* dispositivo, Fila* alta, Fila* media, Fila* baixa) {
    int opicao;

    if(alta == NULL || media == NULL || baixa == NULL) {
        printf("Erro: filas não inicializadas!\n");
        return;
    }

    do {
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
                printf("Saindo");
            break;
            default:
                printf("Digite um valor valido");
            break;
        }
    } while(opicao != 4);
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
