#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

NoArvore* plantar_arvore(Valor** vetor, int inicio, int fim) {
    if (inicio > fim) return NULL;

    int meio = (inicio + fim) / 2;

    NoArvore* no = malloc(sizeof(NoArvore));
    strcpy(no->timestamp, vetor[meio]->timestamp);
    no->valor = vetor[meio]->valor;
    no->esquerda = plantar_arvore(vetor, inicio, meio - 1);
    no->direita = plantar_arvore(vetor, meio + 1, fim);

    return no;
}
void desmatar_arvore(NoArvore* raiz) {
    if (raiz == NULL) return;
    desmatar_arvore(raiz->esquerda);
    desmatar_arvore(raiz->direita);
    free(raiz);
}
