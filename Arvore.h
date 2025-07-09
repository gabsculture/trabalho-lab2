#ifndef ARVORES_H
#define ARVORES_H
#include "estruturas.h"
#include <stdbool.h>

NoArvore* plantar_arvore(Valor** vetor, int inicio, int fim);
void desmatar_arvore(NoArvore* raiz);
#endif
