#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

NoArvore* plantar_arvore(Valor** vetor, int inicio, int fim) {
    if (inicio > fim) return NULL;

    int meio = (inicio + fim) / 2;

    NoArvore* no = malloc(sizeof(NoArvore));
    if (no == NULL) {
        printf("erro alocacao meoria\n");
        return NULL;
    }

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

int contar_valores(Dispositivo* lista) {
    int contador = 0;
    Sensor* sensor = lista->sensores;
    while (sensor != NULL) {
        Valor* valor = sensor->valores;
        while (valor != NULL) {
            contador++;
            valor = valor->proximo;
        }
        sensor = sensor->proximo;
    }
    return contador;
}

void lista_para_vetor(Valor* lista, Valor** vetor) {
    int i = 0;
    Valor* atual = lista;
    while (atual && atual->anterior != NULL)
        atual = atual->anterior;
    while (atual != NULL) {
        vetor[i++] = atual;
        atual = atual->proximo;
    }
}

void mostrar_arvore(NoArvore* raiz) {
    if (raiz == NULL) return;
    mostrar_arvore(raiz->esquerda);
    printf("Timestamp: %s | Valor: %.2f\n", raiz->timestamp, raiz->valor);
    mostrar_arvore(raiz->direita);
}

float buscar_timestamp_arvore(NoArvore* raiz, char* timestamp) {
    clock_t inicio = clock();

    char timestamp_limpo[30];
    strncpy(timestamp_limpo, timestamp, sizeof(timestamp_limpo));
    timestamp_limpo[sizeof(timestamp_limpo) - 1] = '\0';
    strtok(timestamp_limpo, "\n");

    NoArvore* atual = raiz;
    while (atual != NULL) {
        int cmp = strcmp(timestamp_limpo, atual->timestamp);
        if (cmp == 0) {
            clock_t fim = clock();  // fim da medição
            double tempo_ms = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC;
            printf("valor encontrado: %.2f\n", atual->valor);
            printf("timestamp: %s\n", atual->timestamp);
            printf("tempo de busca: %.4f ms\n", tempo_ms);
            return atual->valor;
        } else if (cmp < 0) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    clock_t fim = clock();
    double tempo_ms = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC;

    printf("timestamp não encontrado!\n");
    printf("tempo de busca: %.4f ms\n", tempo_ms);
    return -1.0;
}

NoArvore* plantar_arvore_por_vetor(Valor** vetor, int inicio, int fim) {
    if (inicio > fim) return NULL;

    int meio = (inicio + fim) / 2;
    NoArvore* no = malloc(sizeof(NoArvore));

    strcpy(no->timestamp, vetor[meio]->timestamp);
    no->valor = vetor[meio]->valor;
    no->esquerda = plantar_arvore_por_vetor(vetor, inicio, meio - 1);
    no->direita = plantar_arvore_por_vetor(vetor, meio + 1, fim);

    return no;
}

void prepara_plantacao(Dispositivo* lista) {
    if (lista == NULL) {
        printf("nao ha dipsositivos.\n");
        return;
    }

    int fim = contar_valores(lista);
    if (fim == 0) {
        printf("nao ha valores.\n");
        return;
    }

    Valor** vetor = malloc(fim * sizeof(Valor*));
    if (vetor == NULL) {
        printf("erro.\n");
        return;
    }

    int i = 0;
    Dispositivo* d = lista;
    while (d != NULL) {
        Sensor* s = d->sensores;
        while (s != NULL) {
            Valor* v = s->valores;

            while (v && v->anterior != NULL)
                v = v->anterior;

            while (v != NULL && i < fim) {
                vetor[i++] = v;
                v = v->proximo;
            }

            s = s->proximo;
        }
        d = d->proximo;
    }

    for (int j = 0; j < fim - 1; j++) {
        for (int k = j + 1; k < fim; k++) {
            if (strcmp(vetor[j]->timestamp, vetor[k]->timestamp) > 0) {
                Valor* temp = vetor[j];
                vetor[j] = vetor[k];
                vetor[k] = temp;
            }
        }
    }

    NoArvore* raiz = plantar_arvore(vetor, 0, fim - 1);
    int op;
    char timestamp[30];
    do {
        printf("1 - mostrar arvore\n");
        printf("2 - muscar dado na árvore\n");
        printf("3 - sair\n\nOpcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                mostrar_arvore(raiz);
                break;
            case 2:
                printf("busque por timestamp ");
                scanf(" %[^\n]", timestamp);
                buscar_timestamp_arvore(raiz, timestamp);
                break;
            case 3:
                printf("saindo...\n");
                break;
            default:
                printf("opcao invalida!\n");
        }
    } while (op != 3);

    desmatar_arvore(raiz);
    free(vetor);
}
