#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/paciente.h"
#include "../include/bd_paciente.h"
#include "../include/utils.h"

Paciente* cria_paciente(char* cpf, char *nome, int idade, char *data_cadastro, Lista* lista_pacientes){
    Paciente *ptr_novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    
    int cpf_valido = valida_cpf(cpf);
    if (!cpf_valido){
        printf("CPF invalido!\n");
        free(ptr_novo_paciente);
        return NULL;
    }

    sprintf(ptr_novo_paciente->Cpf, "%.3s.%.3s.%.3s-%.3s", cpf, cpf+3, cpf+6, cpf+9);
    if (consulta_cpf(ptr_novo_paciente->Cpf, lista_pacientes) != NULL){//se nao houver nenhum cpf cadastrado
        printf("CPF ja cadastrado!\n");
        free(ptr_novo_paciente);
        return NULL;
    }
    
    if (strlen(data_cadastro) == 10) {
        strcpy(ptr_novo_paciente->Data_cadastro, data_cadastro);
    } else {
        printf("Formato de data invalido!\n");
        free(ptr_novo_paciente);
        return NULL;
    }

    ptr_novo_paciente->Idade = idade;
    strcpy(ptr_novo_paciente->Nome, nome);

    if (lista_pacientes->ultimo != NULL) {
        ptr_novo_paciente->Id = lista_pacientes->ultimo->info_paciente->Id + 1;
    } else {
        ptr_novo_paciente->Id = 1;
    }

    return ptr_novo_paciente;
}

void imprime_paciente(Paciente *paciente){
    if (paciente != NULL){
        printf("ID: %d\n", paciente->Id);
        printf("CPF: %s\n", paciente->Cpf);
        printf("Nome: %s\n", paciente->Nome);
        printf("Idade: %d\n", paciente->Idade);
        printf("Data de Cadastro: %s\n", paciente->Data_cadastro);
        printf("-------------------------------\n");
    } else {
        printf("Paciente nao registrado\n");
    }
}

void atualizar_paciente(Lista *lista){
    Lista *pacientes_encontrados = consultar_paciente(lista);
    if (pacientes_encontrados == NULL) {
        return;
    }
    printf("Digite o ID do paciente a ser atualizado:\n\n");
    int id;
    scanf("%d", &id);

    Paciente *paciente = consulta_id(id, pacientes_encontrados);
    if (paciente == NULL) {//caso o ID não seja encontrado, cancela a atualização
        printf("ID invalido.\n");
        free(pacientes_encontrados);
        return;
    }

    Paciente *paciente_atualizado = (Paciente*)malloc(sizeof(Paciente));
    paciente_atualizado->Id = paciente->Id;
    paciente_atualizado->Idade = paciente->Idade;
    strcpy(paciente_atualizado->Cpf, paciente->Cpf);
    strcpy(paciente_atualizado->Nome, paciente->Nome);
    strcpy(paciente_atualizado->Data_cadastro, paciente->Data_cadastro);

    printf("\nDigite o novo valor para os campos CPF (apenas digitos), Nome, Idade e Data de Cadastro,\n");
    printf("ou '-' para manter o valor atual.\n\n");

    char novo_cpf[15]; char novo_nome[101]; char nova_idade[4]; char nova_data_cadastro[11];

    printf("Novo CPF: ");
    scanf("%s", novo_cpf);

    if (strcmp(novo_cpf, "-") != 0){
        char cpf_formatado[15];
        sprintf(cpf_formatado, "%.3s.%.3s.%.3s-%.3s", novo_cpf, novo_cpf+3, novo_cpf+6, novo_cpf+9);
        if (!valida_cpf(novo_cpf)){
            printf("CPF invalido!\n");
            free(paciente_atualizado);
            free(pacientes_encontrados);
            return;
        }
        else if (consulta_cpf(novo_cpf, lista) != NULL){//se o novo cpf ja estiver cadastrado
            printf("CPF ja cadastrado!\n");
            free(paciente_atualizado);
            free(pacientes_encontrados);
            return;
        }
        else{
            strcpy(paciente_atualizado->Cpf, cpf_formatado);
        }
    }

    printf("Novo Nome: ");
    scanf("%s", novo_nome);

    if (strcmp(novo_nome, "-") != 0){
        if (!contemNumero(novo_nome)){
            strcpy(paciente_atualizado->Nome, novo_nome);
        } else {
            printf("Formato de nome invalido!\n");
            free(paciente_atualizado);
            free(pacientes_encontrados);
            return;
        }
    }

    printf("Nova Idade: ");
    scanf("%s", nova_idade);

    if (strcmp(nova_idade, "-") != 0){
        for (int i = 0; i < strlen(nova_idade); i++) {
            if (!isdigit(nova_idade[i])) {
                printf("Formato de idade invalido!\n");
                free(paciente_atualizado);
                free(pacientes_encontrados);
                return;
            }
        }
        paciente_atualizado->Idade = atoi(nova_idade);
    }

    printf("Nova Data de Cadastro: ");
    scanf("%s", nova_data_cadastro);
    
    if (strcmp(nova_data_cadastro, "-") != 0) {
        if (strlen(nova_data_cadastro) == 10) {
            strcpy(paciente_atualizado->Data_cadastro, nova_data_cadastro);
        } else {
            printf("Formato de data invalido!\n");
            free(paciente_atualizado);
            free(pacientes_encontrados);
            return;
        }
    }  

    printf("Confirme os novos valores:\n\n");
    imprime_paciente(paciente_atualizado);

    printf("Deseja confirmar as alteracoes? (S/N)\n\n");
    char confirmar;
    scanf(" %c", &confirmar);
    if (toupper(confirmar) == 'S'){
        printf("Alteracoes confirmadas.\n");
        *paciente = *paciente_atualizado;
    } else {
        printf("Alteracoes canceladas.\n");
    }
    
    free(paciente_atualizado);
    free(pacientes_encontrados);
}




