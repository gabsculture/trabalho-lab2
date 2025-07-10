#ifndef ARVORES_H
#define ARVORES_H
#include "estruturas.h"
#include <stdbool.h>

NoArvore* plantar_arvore(Dispositivo* lista, int inicio, int fim);
void desmatar_arvore(NoArvore* raiz);
int contar_valores(Valor* lista);
void lista_para_vetor(Valor* lista, Valor** vetor);
void mostrar_arvore(NoArvore* raiz);
void prepara_plantacao(Dispositivo* lista);

#endif
