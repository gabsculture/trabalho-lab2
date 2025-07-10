#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"
#include <stdio.h>
#include <stdbool.h>


extern FILE *arquivoCsv;

Valor* insere_valor(Valor *listaValor, float valor);
Dispositivo* encontrarSensor(Dispositivo *listaDispositivos, int id_dispositivo, int id_sensor);
void printa_lista_crescente(int id_dispositivo, int id_sensor);
void printa_lista_decrescente(int id_dispositivo, int id_sensor);
void ordem_da_lista();

void minusculas(char* str);  
void pegaTempo(char *buffer, int tamanho);
void incluirTimeStamp(Sensor* sensor, float valor);

int compararCrescente(const void *a, const void *b);
int compararDecrescente(const void *a, const void *b);

bool verificacsv(char *timestamp);
void exportacsv(Sensor* sensor, Dispositivo* dispositivo);
void importacsv(Sensor* sensor, Dispositivo* dispositivo);

#endif
