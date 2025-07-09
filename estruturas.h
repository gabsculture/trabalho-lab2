#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct NoArvore {
    char timestamp[20];
    float valor;         
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct Valor {
    char timestamp[20];
    float valor;
    struct Valor *proximo;
    struct Valor *anterior;
} Valor;

typedef struct Lista {
    Valor *inicio;
    Valor *fim;
} Lista;

typedef struct Sensor {
    int id;
    char tipo[100];
    char subtipo[100];
    Valor* valores;
    int totalValores; 
    int capacidade;
    struct Sensor* proximo;
} Sensor;

typedef struct Dispositivo {
    int id;
    char descricao[100];
    char tipo[100];
    char status[100];
    Sensor* sensores;
    struct Dispositivo* proximo;
} Dispositivo;

typedef struct Evento {
    char descricao[100];
    char prioridade[10];
    float valor;
    Sensor* sensores;
    Dispositivo* dispositivos;
    struct Evento* proximo;
} Evento;

typedef struct Fila{
    Evento* inicio;
    Evento* fim;
    int tamanho;
} Fila;



#endif
