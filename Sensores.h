#ifndef SENSORES_H
#define SENSORES_H

#include "estruturas.h"

extern Sensor* listaSensores;

Sensor* criar_sensor(int id, char* tipo, char* subtipo, float valor);
void insere_sensor(Dispositivo* dispositivo, Sensor* novo);
void remove_sensor(Dispositivo* dispositivo, int id);
void listar_sensores(Dispositivo* dispositivo);
void tipo_validos(char* tipo_sensor);
void subtipo_validos(char* subtipo_sensor);
Dispositivo* opera_sensores(Dispositivo* lista);

#endif
