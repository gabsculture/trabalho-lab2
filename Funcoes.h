#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"
#include <stdio.h>
#include <stdbool.h>


extern FILE *arquivoCsv;

Valor* insere_valor(Valor *listaValor, float valor);
Sensor* encontrarSensor(Sensor *listaSensores, int id);
void printa_lista_crescente(int id);
void printa_lista_decrescente(int id);
void ordem_da_lista();

void minusculas(char* str);  
void pegaTempo(char *buffer, int tamanho);
void incluirTimeStamp(Sensor* sensor, float valor);

int compararCrescente(const void *a, const void *b);
int compararDecrescente(const void *a, const void *b);

bool verificacsv(Sensor* sensor);
void exportacsv(Sensor* sensor, Dispositivo* dispositivo, int contador);
void importacsv(Sensor* sensor, Dispositivo* dispositivo);

#endif
