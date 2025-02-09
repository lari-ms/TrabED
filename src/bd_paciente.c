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

int tamanho_lista(Lista *lista){
    return lista->qtd;
}

void imprimir_lista(Lista *lista){
    printf("\nID    CPF          Nome                 Idade      Data_Cadastro");
    for (Node *node = lista->primeiro; node != NULL; node=node->proximo){
        printf("\n%d     %s          %s       %d      %s",
        node->info_paciente->Id,
        node->info_paciente->Cpf,
        node->info_paciente->Nome,
        node->info_paciente->Idade,
        node->info_paciente->Data_cadastro);
    }
    printf("\n\n");
}

void inserir_paciente_lista(Paciente *paciente, Lista *lista_pacientes){
    //criando novo nó
    Node *node = (Node*)malloc(sizeof(Node));
    node->info_paciente = paciente;
    
    if (lista_pacientes->qtd == 0){
        node->anterior = NULL;
        lista_pacientes->primeiro = node;
    } else{
        node->anterior = lista_pacientes->ultimo;
        lista_pacientes->ultimo->proximo = node;
    }
    node->proximo = NULL;
    lista_pacientes->ultimo = node;
    //node->info_paciente->Id = ++lista_pacientes->qtd;
    //printf("\nid: %d, quantidade de pacientes depois do novo cadastro: %d\n\n", node->info_paciente->Id, lista_pacientes->qtd);

}

int lista_vazia(Lista *lista){
    return (lista->primeiro == NULL && lista->ultimo == NULL);
}