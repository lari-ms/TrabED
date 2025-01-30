/*

operacoes basicas

consultar paciente
atualizar paciente
remover paciente
inserir paciente
imprimir lista de pacientes
sair (encerrar o programa)

*/


/*

structs - tipos

paciente{
    id - int
    cpf - str
    nome
    idade
    data_cadastro
}

*/

/*
outras funcoes auxiliares

ler arquivo csv
escrever no arquivo csv
*/

#include "BDPaciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct paciente{
    int Id;
    char *Cpf;
    char *Nome;
    int Idade;
    char *Data_cadastro;
};

struct node_lista{
    Node *anterior;
    Node *proximo;
    Paciente *info_paciente;
};

struct lista_pacientes{
    Node *primeiro;
    Node *ultimo;
    int qtd;

};

void carregar_csv(FILE *file, char *path){
    file = fopen(*path, "r");
    if (file == NULL){
        printf("Não foi carregar abrir o arquivo.\n");
    } else {
        printf("Arquivo carregado com sucesso!");
    }

    //// transformar todos os pacientes registrados em objetos paciente e oassar pra lista?
}

char* ler_paciente_bd(FILE *bd){ // retorna um ponteiro para uma string com o conteudo da linha
    char buffer[1000];
    fgets(buffer, 1000, bd);
    return buffer;

}

Lista* cria_lista_pacientes(){
    Lista *ptr_nova_lista = (Lista *)malloc(sizeof(Lista));//aloca memoria para lista e retorna ponteiro para ela
    ptr_nova_lista->primeiro = NULL;
    ptr_nova_lista->ultimo = NULL;
    ptr_nova_lista ->qtd = 0;

    return ptr_nova_lista; //retorna o PONTEIRO pra lista
}


void inserir_paciente(int cpf, char *nome, int idade, char data_cadastro, Lista *lista_pacientes){
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
