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

struct ListaDispositivos {
    int informacoes;
    struct lista* proximo;
};

typedef struct listaDispositivos ListaDispositivos;

ListaDispositivos* inicializa(void) {
    return NULL;
}

void insere_dispositivo(){

}

void remove_dispositivo(){

}

void atualizar_dispositivo(){

}

void buscar_dispositivo(){

}

void lista_de_dispositivos(){

}
bool validaDescricao (Dispositivo dispositivo) {
    
}

bool validaTIpo
int main(){
    int opicao;

    printf("\nDigite qual das opcoes deseja fazer:");
    printf("\n1 - Inserir dispositivo\n 2 - remover dispostivo\n 3 - Atualizar dispositivo\n 4 - Buscar dispositivo\n 5 - lista de dispositivos\n 6 - Sair\n Qual opcao deseja deseja? ");
    scanf("%d",&opicao); //le a opção do usuario

    while(opicao > 6 || opicao < 1){ //verifica se foi digitado uma opação valida
      printf("\nDigite uma opcao valida:");
      printf("1 - Inserir dispositivo\n 2 - remover dispostivo\n 3 - Atualizar dispositivo\n 4 - Buscar dispositivo\n 5 - lista de dispositivos\n 6 - Sair\n Qual opcao deseja deseja? ");
      scanf("%d",&opicao);
    }

    do{ //Direciona para as funções
        switch(opicao){
        case 1:
          insere_dispositivo();
          break;
        case 2:
          remove_dispositivo();
          break;
        case 3:
          atualizar_dispositivo();
          break;
        case 4:
          buscar_dispositivo();
          break;
        case 5:
          lista_de_dispositivos();
          break;
        default:
          break;
      }

      //após a verificação pede para o usuario escolher a proxima opção
      printf("\nDigite qual das opcoes deseja fazer:");
      printf("\n1 - Inserir dispositivo\n 2 - remover dispostivo\n 3 - Atualizar dispositivo\n 4 - Buscar dispositivo\n 5 - lista de dispositivos\n 6 - Sair\n Qual opcao deseja deseja? ");
      scanf("%d",&opicao);

      while(opicao > 6 || opicao < 1){
        printf("\nDigite uma opcao valida:");
        printf("1 - Inserir dispositivo\n 2 - remover dispostivo\n 3 - Atualizar dispositivo\n 4 - Buscar dispositivo\n 5 - lista de dispositivos\n 6 - Sair\n Qual opcao deseja deseja? ");
        scanf("%d",&opicao);
      }
    }while(opicao != 6);


    return 0;
}
