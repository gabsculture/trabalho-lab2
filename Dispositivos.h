#ifndef DISPOSITIVOS_H
#define DISPOSITIVOS_H

#include "estruturas.h"

Dispositivo* inicializa();
Dispositivo* opera_dispositivos(Dispositivo* lista);
void libera(Dispositivo* lista);

#endif
