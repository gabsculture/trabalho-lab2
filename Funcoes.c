#include "Funcoes.h"

#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

FILE *arquivoCsv;

Valor* insere_valor(Valor *listaValor, float valor) { //insere o valor do sensor/atuador e insere o timestamp
    Valor *novo = (Valor*)malloc(sizeof(Valor));

    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return listaValor;
    }

    novo->valor = valor;
    pegaTempo(novo->timestamp, sizeof(novo->timestamp));
    novo->proximo = listaValor;
    novo->anterior = NULL;

    if (listaValor != NULL) {
        listaValor->anterior = novo;
    }
    return novo;  // novo passa a ser a nova cabeça da lista
}

void pegaTempo(char *buffer, int tamanho) {
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    strftime(buffer, tamanho, "%Y-%m-%d %H:%M:%S", tm_info);
}

void incluirTimeStamp(Sensor* sensor, float valor) {
    sensor->valores = insere_valor(sensor->valores, valor);
}


//TODO revizar isso aqui
int compararCrescente(const void *a, const void *b) {
    return strcmp(((Valor*)a)->timestamp, ((Valor*)b)->timestamp);
}
//TODO revizar isso aqui
int compararDecrescente(const void *a, const void *b) {
    return strcmp(((Valor*)b)->timestamp, ((Valor*)a)->timestamp);
}

bool verificacsv(Sensor* sensor) { //função para verificar se existem timestamp iguais no arquivo
    FILE *arquivo = fopen(arquivoCsv, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.");
        return false;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char timestampArquivo[20];
        sscanf(linha, "%[^,],", timestampArquivo); // Lê o timestamp da linha

        if (strcmp(sensor->valores->timestamp, timestampArquivo) == 0) {
            fclose(arquivo);
            return true; // Timestamp já existe
        }
    }

    fclose(arquivo);
    return false; // Timestamp não encontrado

}

void exportacsv(Sensor* sensor, Dispositivo* dispositivo, int contador) {
    FILE *arquivo = fopen(arquivoCsv, "a");

    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    for (int i = 0; i < contador; i++) {
        if (verificacsv(sensor) == false) {
            printf("O Timestamp está %s duplicado", sensor->valores->timestamp);
        }
        fprintf(arquivo, "%s, %d, %d, %.2f", sensor->valores->timestamp, dispositivo->id, sensor->id, sensor->valores->valor);
    }

    fclose(arquivo);
}

void importacsv(Sensor* sensor, Dispositivo* dispositivo) {
    FILE *arquivo = fopen(arquivoCsv, "r");

    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char timestamp[20];
        int dispositivoId, sensorId;
        float valor;

        // Lê os valores do CSV (timestamp, dispositivoId, sensorId, valor)
        sscanf(linha, "%[^,], %d, %d, %f", timestamp, &dispositivoId, &sensorId, &valor);

        // Atualiza os dados nas estruturas Sensor e Dispositivo
        dispositivo->id = dispositivoId;
        sensor->id = sensorId;
        strcpy(sensor->valores->timestamp, timestamp);
        sensor->valores->valor = valor;

        // Aqui você pode adicionar lógica para armazenar ou manipular os dados importados
        printf("Importado: %s, %d, %d, %.2f\n", timestamp, dispositivoId, sensorId, valor);
    }

    fclose(arquivo); // Fecha o arquivo

}
