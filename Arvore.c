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
    for (int i = 1; i <= meio && valor != NULL; i++) {
        valor = valor->proximo;
    }
    if (valor == NULL) return NULL;

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
    clock_t inicio = clock();  // começa a medir o tempo

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

void prepara_plantacao(Dispositivo* lista){
    if (lista == NULL) {
        printf("Erro: Lista de dispositivos vazia.\n");
        return;
    }
    Sensor* sensor = lista->sensores;
    if (sensor == NULL || sensor->valores == NULL) {
        printf("Erro: Sensor ou valores não inicializados.\n");
        return;
    }
    int fim = 0;
    Valor* atual = sensor->valores;
    while (atual != NULL) {
        fim++;
        atual = atual->proximo;
    }
    if (fim == 0) {
        printf("Nenhum valor para montar árvore.\n");
        return;
    }
    Valor** vetor = malloc(fim * sizeof(Valor*));
    atual = sensor->valores;
    while (atual && atual->anterior != NULL)
        atual = atual->anterior;
    for (int i = 0; i < fim && atual != NULL; i++) {
        vetor[i] = atual;
        atual = atual->proximo;
    }
    NoArvore* raiz = plantar_arvore_por_vetor(vetor, 0, fim - 1);

    int op;
    char timestamp[30];
    do {
        printf("1 - Mostrar Árvore\n");
        printf("2 - Buscar dado na árvore\n");
        printf("3 - Sair\n\nOpcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                mostrar_arvore(raiz);
                break;
            case 2:
                printf("digite o timestamp que deseja buscar: ");
                scanf(" %[^\n]", timestamp);
                buscar_timestamp_arvore(raiz, timestamp);
                break;
            case 3:
                printf("saindo da árvore...\n");
                break;
            default:
                printf("opção inválida!\n");
        }
    } while (op != 3);

    desmatar_arvore(raiz);
    free(vetor);
}
