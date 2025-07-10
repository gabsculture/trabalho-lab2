#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>




NoArvore* plantar_arvore(Dispositivo* lista, int inicio, int fim) {
    Valor* valor = lista->sensores->valores;
    if (inicio > fim) return NULL;

    int meio = (inicio + fim) / 2;

    NoArvore* no = malloc(sizeof(NoArvore));
    for (int i = 1; i <= meio; i++) {
        valor = valor->proximo;
    }
    strcpy(no->timestamp, valor->timestamp);
    no->valor = valor->valor;
    no->esquerda = plantar_arvore(lista, inicio, meio - 1);
    no->direita = plantar_arvore(lista, meio + 1, fim);

    return no;
}

void desmatar_arvore(NoArvore* raiz) {
    if (raiz == NULL) return;
    desmatar_arvore(raiz->esquerda);
    desmatar_arvore(raiz->direita);
    free(raiz);
}

int contar_valores(Dispositivo* lista) {
    int contador = 0;
    Valor* valor = lista->sensores->valores;
    while (lista->sensores->valores) {
        contador++;
         valor = valor->proximo;
    }
    return contador;
}

void lista_para_vetor(Valor* lista, Valor** vetor) { //Não sei se vai precisar
    int i = 0;
    while (lista) {
        vetor[i++] = lista;
        lista = lista->proximo;
    }
}

void mostrar_arvore(NoArvore* raiz) {
    if (raiz == NULL) return;
    mostrar_arvore(raiz->esquerda);
    printf("Timestamp: %s | Valor: %.2f\n", raiz->timestamp, raiz->valor);
    mostrar_arvore(raiz->direita);
}

float buscar_timestamp_arvore(NoArvore* raiz, char* timestamp) {
    clock_t inicio = clock();  // começa a medir o tempo

    NoArvore* atual = raiz;
    while (atual != NULL) {
        int cmp = strcmp(timestamp, atual->timestamp);
        if (cmp == 0) {
            clock_t fim = clock();  // fim da medição
            double tempo_ms = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC;
            printf("Valor encontrado: %.2f\n", atual->valor);
            printf("Timestamp: %s\n", atual->timestamp);
            printf("Tempo de busca: %.4f ms\n", tempo_ms);
            return atual->valor;
        } else if (cmp < 0) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    clock_t fim = clock();  // fim mesmo se não encontrar
    double tempo_ms = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC;

    printf("Timestamp não encontrado!\n");
    printf("Tempo de busca: %.4f ms\n", tempo_ms);
    return -1.0;

}

void prepara_plantacao(Dispositivo* lista){
    int fim = contar_valores(lista), op;
    char timestamp[20];

    NoArvore* NoArvore = plantar_arvore(lista, 1, fim);

    do{
      printf("\nQual das operações deseja fazer? \n\n1- Mostrar Arvore\n2 - Buscar dado na arvore\n3 - Sair\n\nOpcao: ");
      scanf("%d", &op);

      switch (op) {
        case 1:
          mostrar_arvore(NoArvore);
          break;
        case 2:
          printf("\nDigite o timestamp que deseja buscar: ");
          scanf("%s", timestamp);
          buscar_timestamp_arvore(NoArvore, timestamp);
          break;
        case 3:
          printf("\nSaindo!!");
          break;
        default:
          printf("\nOpcao invalida!\n");

      }
    }while(op != 3);

    desmatar_arvore(NoArvore);
}


