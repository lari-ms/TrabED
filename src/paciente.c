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

Paciente* consulta_cpf(char* cpf, Lista *lista){
    char cpf_formatado[15];
    if (strlen(cpf)<14){
        sprintf(cpf_formatado, "%.3s.%.3s.%.3s-%.3s", cpf, cpf+3, cpf+6, cpf+9);
    } else {
        strcpy(cpf_formatado, cpf);
    }
    
    Node *node = lista->primeiro;

    while(node != NULL){
        if (strcmp(node->info_paciente->Cpf, cpf_formatado)==0){
            return node->info_paciente;
        }
        node = node->proximo;
    }
    return NULL;
}

Lista* consulta_nome(char* nome, Lista *lista){
    Lista *pacientes_encontrados = cria_lista_pacientes();
    Node *node = lista->primeiro;

    while(node != NULL){
        if (strstr(node->info_paciente->Nome, nome) != NULL){
            inserir_paciente_lista(node->info_paciente, pacientes_encontrados);
        }
        node = node->proximo;
    }

    return pacientes_encontrados;
}

Paciente* consulta_id(int id, Lista *lista){
    Node *node = lista->primeiro;

    while (node != NULL){
        if (node->info_paciente->Id == id){
            return node->info_paciente;
        }
        node = node->proximo;
    }
    printf("Nenhum paciente encontrado.\n\n");
    return NULL;
}

void consultar_paciente(Lista *lista_pacientes){
    printf("Escolha o modo de consulta:\n1 - por nome\n2 - por CPF\n3 - retornar ao menu principal\n\n");
    int modo_busca;
    scanf("%d", &modo_busca);

    // Busca por nome
    if (modo_busca == 1){
        char nome[100];
        printf("Digite o nome\n\n");
        scanf("%s", nome);
        printf("\n");
        Lista *pacientes_encontrados = consulta_nome(nome, lista_pacientes);
        if (lista_vazia(pacientes_encontrados)){
            printf("Nenhum paciente foi encontrado.\n\n");
            free(pacientes_encontrados);
            return;
        }
        imprimir_lista(pacientes_encontrados);
        free(pacientes_encontrados);

    // Busca por CPF
    } else if (modo_busca == 2){
        char cpf[12];
        printf("Digite o CPF:\n\n");
        scanf("%s", cpf);

        if (!valida_cpf(cpf)){
            printf("CPF invalido.\n\n");
            return;
        }

        Paciente *paciente_encontrado = consulta_cpf(cpf, lista_pacientes);
        if (paciente_encontrado == NULL){
            printf("Nenhum paciente foi encontrado.\n\n");
            return;
        }

        imprime_paciente(paciente_encontrado);

    } else if (modo_busca == 3){
        return;
    } else {
        printf("Opcao invalida.\n");
        return;
    }
}

void remover_paciente(Lista *lista){
    consultar_paciente(lista);
    printf("Digite o ID do paciente a ser excluido:\n\n");
    char id_str[10];
    int id;
    scanf("%s", id_str); 
    id = atoi(id_str);

    Paciente *paciente = consulta_id(id ,lista);
    if (paciente == NULL) {//caso o ID não seja encontrado, cancela a atualização
        return;
    }

    Node *node = lista->primeiro;

    //busca a id escolhida
    while (node != NULL){
        if (node->info_paciente->Id == id){

            printf("\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n\n");
            imprime_paciente(node->info_paciente); printf("\n");
            char remover; //char encerrar = 'N';
            scanf(" %c", &remover);
            if (toupper(remover) == 'N'){
                return;
            } else if(toupper(remover) == 'S'){
                
            //se node for o primeiro elemento da lista
            if (node == lista->primeiro){
                lista->primeiro = node->proximo;
                //se tiver proximo elemento
                if (node->proximo != NULL){
                    lista->primeiro->anterior = NULL;
                }
            }
            //se o node for o ultimo elemento da lista
            if (node == lista->ultimo){
                lista->ultimo = node->anterior;
                //se tiver elemento anterior
                if (lista->ultimo != NULL){
                    lista->ultimo->proximo = NULL;
                }
            }

            //se ele estiver entre dois elementos
            if (node->anterior != NULL && node->proximo != NULL) {
                node->anterior->proximo = node->proximo;
                node->proximo->anterior = node->anterior;
            }

            free(node->info_paciente);
            free(node);

            printf("\nRegistro removido com sucesso.\n");
            return;
            } else {
                printf("Opcao invalida.\n");
                return;
            }
        }
        node = node->proximo;
    }
}

void atualizar_paciente(Lista *lista){
    consultar_paciente(lista);
    imprimir_lista(lista);
    printf("Digite o ID do paciente a ser atualizado:\n\n");
    int id;
    scanf("%d", &id); 

    Paciente *paciente = consulta_id(id ,lista);
    if (paciente == NULL) {//caso o ID não seja encontrado, cancela a atualização
        printf("Paciente com ID %d nao encontrado.\n", id);
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
            return;
        }
        else if (consulta_cpf(novo_cpf, lista) != NULL){//se o novo cpf ja estiver cadastrado
            printf("CPF ja cadastrado!\n");
            free(paciente_atualizado);
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
                return;
            }
        }
        paciente_atualizado->Idade = atoi(nova_idade);
    }

    if (strcmp(nova_idade, "-") != 0){
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
}

void cadastrar_paciente(Lista *lista_pacientes){
    char cpf[15], nome[100], data_cadastro[11];
    int idade;
    printf("Digite o CPF do paciente: ");
    scanf("%s", cpf);
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    printf("Digite a idade do paciente: ");
    scanf("%d", &idade);
    printf("Digite a data de cadastro do paciente (dd/mm/yyyy): ");
    scanf("%s", data_cadastro);

    Paciente *novo_paciente = cria_paciente(cpf, nome, idade, data_cadastro, lista_pacientes);
    
    if (novo_paciente != NULL) {
        inserir_paciente_lista(novo_paciente, lista_pacientes);
        printf("Paciente cadastrado com sucesso!\n");
    }
    else{
        printf("Erro ao cadastrar paciente.\n");
    }
}