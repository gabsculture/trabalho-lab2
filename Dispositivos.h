#ifndef DISPOSITIVOS_H
#define DISPOSITIVOS_H

#include "estruturas.h"
#include <stdbool.h>

Dispositivo* inicializa(void);

Dispositivo* criar_dispositivo(int id, char* descricao, char* tipo, char* status);

void insere_dispositivo(Dispositivo** lista, Dispositivo* novo);

void remove_dispositivo(Dispositivo** lista, int id);

bool valida_id(Dispositivo* lista, int id);

void busca(Dispositivo* dispositivo);

void listar_dispositivos(Dispositivo* lista);

void minusculas(char* str);

void confere_dispositivos(char* tipo);

void condicoes_validas(char* status);

void libera(Dispositivo* lst);

Dispositivo* opera_dispositivos(Dispositivo* dispositivo);

#endif
