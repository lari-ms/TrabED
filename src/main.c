#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\include\paciente.h"
#include "..\include\bd_paciente.h"
#include "..\include\utils.h"
#include "..\include\arquivo.h"

int main(){

    //carregar o arquivo etc
    //criar a lista com os pacientes do arquivo
    const char *nome_arq = "database\\bd_paciente.csv";
    Lista *lista_pacientes = arq_ler_pacientes(nome_arq);
    printf("atualizando pacientes:\n");
    atualizar_paciente(lista_pacientes);
    printf("lista atualizada:\n");
    imprimir_lista(lista_pacientes);
    printf("removendo pacientes:\n");
    remover_paciente(lista_pacientes);
    arq_inserir_lista(lista_pacientes, nome_arq);

    return 0;
}


/*
char opcao;

while (toupper(opcao) != "Q"){
    //implementar menu
}
*/
