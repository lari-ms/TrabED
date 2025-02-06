#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "bd_paciente.h"

void inserir_paciente(char* cpf, char *nome, int idade, char data_cadastro, Lista *lista_pacientes){
    //criando novo paciente
    Paciente *ptr_novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    ptr_novo_paciente->Id = lista_pacientes->qtd++;
    printf("id: %d, quantidade de pacientes depois do novo cadastro: %d\n", ptr_novo_paciente->Id, lista_pacientes->qtd++);
    sprintf(ptr_novo_paciente->Cpf, "%.3s.%.3s.%.3s-%.3s", cpf, cpf+3, cpf+6, cpf+9);
    //validar cpf
    ptr_novo_paciente->Idade = idade;
    ptr_novo_paciente->Nome = nome;
    ptr_novo_paciente->Data_cadastro = data_cadastro; //É OBRIGATORIO??

    //criando novo nó
    Node *node = (Node*)malloc(sizeof(Node));
    node->info_paciente = ptr_novo_paciente;
    
    if (lista_pacientes->qtd == 0){
        node->anterior = NULL;
        lista_pacientes->primeiro = node;
    } else{
        node->anterior = lista_pacientes->ultimo;
        lista_pacientes->ultimo->proximo = node;
    }
    node->proximo = NULL;
    lista_pacientes->ultimo = node;

    /////////// ADD REGISTRO DO PACIENTE NO ARQUIVO CSV
    
}