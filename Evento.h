#ifndef EVENTO_H
#define EVENTO_H

#include "estruturas.h"
#include "Funcoes.h"

Fila* cria(void);
void insere_fila(Fila *fila, Evento *evento);
Evento* remove_da_fila(Fila *fila);

Evento* criar_evento(Dispositivo* dispositivo, int id, int id_sensor, char* descricao, char* prioridade, float valor);
void insere_evento(Dispositivo* dispositivo, Fila* alta, Fila* media, Fila* baixa);

void executa_evento(Fila* alta, Fila* media, Fila* baixa);
void listar_eventos(Fila *alta, Fila *media, Fila *baixa);
void opera_evento(Dispositivo* dispositivo, Fila* alta, Fila* media, Fila* baixa);

void liberar_fila(Fila* fila);
void liberar_todas_filas(Fila* alta, Fila* media, Fila* baixa);

#endif
