#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

