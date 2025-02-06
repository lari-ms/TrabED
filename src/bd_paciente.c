#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

Lista* cria_lista_pacientes(){
    Lista *ptr_nova_lista = (Lista *)malloc(sizeof(Lista));//aloca memoria para lista e retorna ponteiro para ela
    ptr_nova_lista->primeiro = NULL;
    ptr_nova_lista->ultimo = NULL;
    ptr_nova_lista ->qtd = 0;

    return ptr_nova_lista; //retorna o PONTEIRO pra lista
}

void imprimir_lista(Lista *lista){

    printf("Imprimindo lista de pacientes...\nID    CPF          Nome                 Idade      Data_Cadastro");
    for (Node *node = lista->primeiro; node != NULL; node=node->proximo){
        printf("%d     %s          %s       %d      %s",
        node->info_paciente->Id,
        node->info_paciente->Cpf,
        node->info_paciente->Nome,
        node->info_paciente->Idade,
        node->info_paciente->Data_cadastro);
    }
}