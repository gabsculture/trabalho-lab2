#include <stdio.h>
#include "Dispositivos.h"
#include "Sensores.h"
#include "Evento.h"
#include "Funcoes.h"
#include "Arvore.h"



int main() {
    Dispositivo* lista = inicializa();
    Fila *alta = cria();
    Fila *media = cria();
    Fila *baixa = cria();

    int opicao;


    do {
        printf("\nCom o que deseja mexer: \n1 - Dispositivos\n2 - Sensores\n3 - Eventos\n4 - Lista de valores de um sensor/atuador \n5 - Mostrar arvore de timestamp\n6 - Sair\n\nEscolha uma opção: ");
        scanf("%d", &opicao);

        switch (opicao) {
            case 1:
                lista = opera_dispositivos(lista); //faz as operações com dispositivos e retorna a lista atualizada
                break;
            case 2:
                lista = opera_sensores(lista); //faz as operações com sensores e retorna na lista atualizada
                break;
            case 3:
                opera_evento(lista, alta, media, baixa); //faz as operações com os eventos
                break;
            case 4:
                ordem_da_lista();
                break;
            case 5:
                prepara_plantacao(lista);
                break;
            case 6:
                printf("finalizado\n");
                break;
            default:
                printf("opição invalida!\n");
        }
    } while (opicao != 6);

    //libera as listas e as filas
    libera(lista);
    liberar_todas_filas(alta, media, baixa);

    //anular ponteiros após liberar
    lista = NULL;
    alta = media = baixa = NULL;

    return 0;
}
