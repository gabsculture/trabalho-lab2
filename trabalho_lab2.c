#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char descricao[100];
    char tipo[100];
    char status[100];

} Dispositivo;


typedef struct{
    char tipo[100];

} Sensor;

void insere_dispositivo(Dispositivo *dispositivo){

}

void remove_dispositivo(Dispositivo *dispositivo){

}

void atualizar_dispositivo(Dispositivo *dispositivo){

}

void buscar_dispositivo(Dispositivo *dispositivo){

}

void lista_de_dispositivos(Dispositivo *dispositivo){

}

int main(){
    int opicao;

    printf("\nDigite qual das opcoes deseja fazer:");
    printf("1 - Inserir dispositivo\n 2 - remover dispostivo\n 3 - Atualizar dispositivo\n 4 - Buscar dispositivo\n 5 - lista de dispositivos\n 6 - Sair\n Qual opcao deseja deseja? ");
    scanf("%d",&opicao);

    while(opicao > 6 && opicao < 1){
      printf("\nDigite uma opcao valida:");
      printf("1 - Inserir dispositivo\n 2 - remover dispostivo\n 3 - Atualizar dispositivo\n 4 - Buscar dispositivo\n 5 - lista de dispositivos\n 6 - Sair\n Qual opcao deseja deseja? ");
      scanf("%d",&opicao);
    }

    do{
        switch(opicao){
        case 1:
          insere_dispositivo();
          break;
        case 2:
          remove_dispositivo();
          break;
        case 3:
          atuailar_dispositivos();
          break;
        case 4:
          buscar_dispositivos();
          break;
        case 5:
          lista_de_dispositivos();
          break;
        default:
          break;
      }
    }while(opicao != 6);


    return 0;
}
