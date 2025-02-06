#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BDPaciente.h"



void inserir_paciente(char* cpf, char *nome, int idade, char* data_cadastro, Lista *lista_pacientes, FILE *file){
    //criando novo paciente
    Paciente *ptr_novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    ptr_novo_paciente->Id = lista_pacientes->qtd++;
    printf("id: %d, quantidade de pacientes depois do novo cadastro: %d\n", ptr_novo_paciente->Id, lista_pacientes->qtd++);
    sprintf(ptr_novo_paciente->Cpf, "%.3s.%.3s.%.3s-%.2s", cpf, cpf+3, cpf+6, cpf+9);
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
    char *str = strcat()
    fputs("%s,%s,%d,%s", ptr_novo_paciente->Id, ptr_novo_paciente->);
    
}


/*
void main(){

    printf("HealthSys\n\n1 - Consultar paciente\n2 - Atualizar paciente\n3 - Reover paciente\n4 - Inserir paciente\n5 - Imprimir lista de pacientes\n Q - Sair\n\n");
    char acao;;
    scanf("%c", &acao);
    printf("acao escolhida pelo usuario: %c", acao);

    switch (acao)
    {
    case '1':
        char cpf[11];
        scanf("%s", cpf);
        consultar_paciente(char* cpf, char* nome);
        break;
    
    case '2':
        atualizar_paciente(int id);
        break;

    case '3':
        remover_paciente(int id);
        break;

    case '4':
        inserir_paciente(int cpf, char *nome, int idade, char data_cadastro, Lista *lista_pacientes);
        break;

    case '5':
        imprimir_lista(Lista *lista);
        break;
    
    case 'Q':
        void sair();
        break;
    
    default:
        printf("Escolha uma ação válida\n");
        break;
    }
}
*/

