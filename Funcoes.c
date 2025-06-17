#include "Funcoes.h"
#include "estruturas.h"
#include "Sensores.h"
#include "Dispositivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

FILE *arquivoCsv;

Valor* insere_valor(Valor *listaValor, float valor) { //insere o valor do sensor/atuador e insere o timestamp
    Valor *novo = (Valor*)malloc(sizeof(Valor));

    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return listaValor;
    }

    novo->valor = valor;
    pegaTempo(novo->timestamp, sizeof(novo->timestamp));
    novo->proximo = listaValor;
    novo->anterior = NULL;

    if (listaValor != NULL) {
        listaValor->anterior = novo;
    }
    return novo;  // novo passa a ser a nova cabeça da lista
}

Dispositivo* encontrarSensor(Dispositivo *listaDispositivos, int id_dispositivo, int id_sensor) {
    Dispositivo *atual = listaDispositivos;
    while (atual != NULL) {
        if (atual->id == id_dispositivo){
            while (atual->sensores != NULL) {
                if (atual->sensores->id == id_sensor) {
                    return atual;
                }
            }
        }
        atual = atual->proximo;
    }
    return NULL;
}

void printa_lista_crescente(int id_dispositivo, int id_sensor) {
    extern Dispositivo *listaDispositivos;

    Dispositivo *dispositivo = encontrarSensor(listaDispositivos, id_dispositivo, id_sensor);
    if (dispositivo == NULL) {
        printf("Sensor com ID %d não encontrado!\n", id_sensor);
        return;
    }

    Valor *atual = dispositivo->sensores->valores;
    if (atual == NULL) {
        printf("Nenhum valor registrado para o sensor %d\n", id_sensor);
        return;
    }

    // Encontrar o início da lista (caso não esteja no primeiro nó)
    while (atual->anterior != NULL) {
        atual = atual->anterior;
    }

    printf("\nValores do sensor %d em ordem crescente:\n", id_sensor);
    while (atual != NULL) {
        printf("Timestamp: %s, Valor: %.2f\n", atual->timestamp, atual->valor);
        atual = atual->proximo;
    }
}

void printa_lista_decrescente(int id_dispositivo, int id_sensor) {
    extern Dispositivo *listaDispositivos;

    Dispositivo *dispositivo = encontrarSensor(listaDispositivos, id_dispositivo, id_sensor);
    if (dispositivo == NULL) {
        printf("Sensor com ID %d não encontrado!\n", id_sensor);
        return;
    }

    Valor *atual = dispositivo->sensores->valores;
    if (atual == NULL) {
        printf("Nenhum valor registrado para o sensor %d\n", id_sensor);
        return;
    }

    // Encontrar o fim da lista
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }

    printf("\nValores do sensor %d em ordem decrescente:\n", id_sensor);
    while (atual != NULL) {
        printf("Timestamp: %s, Valor: %.2f\n", atual->timestamp, atual->valor);
        atual = atual->anterior;
    }
}

void ordem_da_lista() {
        int valor, id_sensor, id_dispositivo;
        do {
        printf("\nEm qual ordem deseja os valores?\n1 - Crescente\n2 - Descresente");
        scanf("%d", &valor);
        switch (valor) {
            case 1:
                printf("Digite o id do dispositivo: ");
                scanf("%d", &id_dispositivo);
                printf("Digite o id do sensor que deseja ver a lista de valores: ");
                scanf("%d", &id_sensor);
                printa_lista_crescente(id_dispositivo, id_sensor);
                break;
            case 2:
                printf("Digite o id do dispositivo: ");
                scanf("%d", &id_dispositivo);
                printf("Digite o id do sensor que deseja ver a lista de valores: ");
                scanf("%d", &id_sensor);
                printa_lista_decrescente(id_dispositivo, id_sensor);
                break;
            default:
                printf("Esse ordem não existe");
        }
    }while (valor != 1 && valor != 2);
}

void pegaTempo(char *buffer, int tamanho) {
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    strftime(buffer, tamanho, "%Y-%m-%d %H:%M:%S", tm_info);
}

void incluirTimeStamp(Sensor* sensor, float valor) {
    sensor->valores = insere_valor(sensor->valores, valor);
}


bool verificacsv(char *timestamp) {
    FILE *arquivo = fopen("arquivoCsv.csv", "r");

    if (arquivo == NULL) {
        return false;  // Se não existe, não há duplicata.
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char timestampArquivo[30];
        sscanf(linha, "%[^,],", timestampArquivo);

        if (strcmp(timestamp, timestampArquivo) == 0) {
            fclose(arquivo);
            return true;  // Já existe.
        }
    }

    fclose(arquivo);
    return false;
}

void exportacsv(Sensor* sensor, Dispositivo* dispositivo) {
    FILE *arquivo = fopen("arquivoCsv.csv", "a");

    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    Valor* atual = sensor->valores;

    // Ir até o início da lista
    while (atual && atual->anterior != NULL) {
        atual = atual->anterior;
    }

    while (atual != NULL) {
        if (!verificacsv(atual->timestamp)) {
            fprintf(arquivo, "%s,%d,%d,%.2f\n", atual->timestamp, dispositivo->id, sensor->id, atual->valor);
            printf("Exportado: %s,%d,%d,%.2f\n", atual->timestamp, dispositivo->id, sensor->id, atual->valor);
        } else {
            printf("Valor com timestamp %s já existe no CSV.\n", atual->timestamp);
        }
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void importacsv(Sensor* sensor, Dispositivo* dispositivo) {
    FILE *arquivo = fopen("arquivoCsv.csv", "r");

    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char timestamp[30];
        int dispositivoId, sensorId;
        float valor;

        sscanf(linha, "%[^,],%d,%d,%f", timestamp, &dispositivoId, &sensorId, &valor);

        if (sensor->id == sensorId) {
            // Verificar se timestamp já está na lista de valores
            Valor *temp = sensor->valores;
            bool existe = false;

            while (temp != NULL) {
                if (strcmp(temp->timestamp, timestamp) == 0) {
                    existe = true;
                    break;
                }
                temp = temp->proximo;
            }

            if (!existe) {
                Valor *novo = (Valor*)malloc(sizeof(Valor));
                strcpy(novo->timestamp, timestamp);
                novo->valor = valor;
                novo->proximo = sensor->valores;
                novo->anterior = NULL;

                if (sensor->valores != NULL) {
                    sensor->valores->anterior = novo;
                }
                sensor->valores = novo;

                printf("Importado: %s, %d, %d, %.2f\n", timestamp, dispositivoId, sensorId, valor);
            }
        }
    }
    fclose(arquivo);
}
void exportar_todos_csv(Dispositivo* lista) {
    Dispositivo* d = lista;
    while (d != NULL) {
        Sensor* s = d->sensores;
        while (s != NULL) {
            exportacsv(s, d);
            s = s->proximo;
        }
        d = d->proximo;
    }
}

void importar_todos_csv(Dispositivo* lista) {
    Dispositivo* d = lista;
    while (d != NULL) {
        Sensor* s = d->sensores;
        while (s != NULL) {
            importacsv(s, d);
            s = s->proximo;
        }
        d = d->proximo;
    }
}
