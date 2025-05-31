#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

FILE *arquivoCsv;

void pegaTempo(char *buffer, int tamanho) {
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    strftime(buffer, tamanho, "%Y-%m-%d %H:%M:%S", tm_info);
}

void incluirTimeStamp(Sensor* sensor) {
    if (totalRegistros >= MAX_VALORES) {
        printf("limite de registros atingido.\n");
        return;
    }
    pegaTempo(sensor->valor->timestamp, sizeof(sensor->valor->timestamp));
    sensor->valor->valor = valor;
    registros[totalRegistros++] = novo;
}

int compararCrescente(const void *a, const void *b) {
    return strcmp(((Valor*)a)->timestamp, ((Valor*)b)->timestamp);
}

int compararDecrescente(const void *a, const void *b) {
    return strcmp(((Valor*)b)->timestamp, ((Valor*)a)->timestamp);
}

bool verificacsv() { //função para verificar se existem timestamp iguais no arquivo

}

void exportacsv(Sensor* sensor, Dispositivo* dispositivo, int contador) {
    FILE *arquivo = fopen(arquivoCsv, "w");

    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    for (int i = 0; i < contador; i++) {//incluir a função verificacsv aqui
        fprintf(arquivo, "%s, %d, %d, %.2f", sensor->valor->timestamp, dispositivo->id, sensor->id, sensor->valor->valor);
    }
}

void importacsv(Sensor* sensor, Dispositivo* dispositivo) {
    FILE *arquivo = fopen(arquivoCsv, "r");
}