#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "..\include\paciente.h"
#include "..\include\bd_paciente.h"
#include "..\include\utils.h"

Paciente* cria_paciente(char* cpf, char *nome, int idade, char *data_cadastro, Lista* lista_pacientes){
    Paciente *ptr_novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    
    

    int cpf_valido = valida_cpf(cpf);
    if (!cpf_valido){
        printf("CPF inválido!\n");
        free(ptr_novo_paciente);
        return NULL;
    }

    sprintf(ptr_novo_paciente->Cpf, "%.3s.%.3s.%.3s-%.3s", cpf, cpf+3, cpf+6, cpf+9);
    if (consulta_cpf(ptr_novo_paciente->Cpf, lista_pacientes) != NULL){//se nao houver nenhum cpf cadastrado
        printf("CPF já cadastrado!");
        return NULL;
    }
    
    if (strlen(data_cadastro) < 11) {
        strcpy(ptr_novo_paciente->Data_cadastro, data_cadastro);
    } else {
        printf("Formato de data inválido!\n");
        free(ptr_novo_paciente);
        return NULL;
    }

    ptr_novo_paciente->Idade = idade;
    strcpy(ptr_novo_paciente->Nome, nome);
    ptr_novo_paciente->Id = ++lista_pacientes->qtd;

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
        printf("Paciente não registrado\n");
    }
}

Paciente* consulta_cpf(char* cpf, Lista *lista){
    char cpf_formatado[15];
    if (strlen(cpf)<14){
        sprintf(cpf_formatado, "%.3s.%.3s.%.3s-%.3s", cpf, cpf+3, cpf+6, cpf+9);
    } else {
        strcpy(cpf_formatado, cpf);
    }
    
    //printf("cpf: %s  |  cpf formatado: %s", cpf, cpf_formatado);
    /*if (lista->qtd == 0){
        printf("Lista vazia\n");
        return;
    }*/
    Node *node = lista->primeiro;

    while(node != NULL){
        //printf("\ndentro do while:\n %s != %s", cpf_formatado, node->info_paciente->Cpf);
        if (strcmp(node->info_paciente->Cpf, cpf_formatado)==0){
            //printf("entrou no if");
            return node->info_paciente;
        }
        node = node->proximo;
    }
    //printf("CPF nao registrado\n");
    return NULL;
}

Lista* consulta_nome(char* nome, Lista *lista){
    Lista *pacientes_encontrados = cria_lista_pacientes();
    Node *node = lista->primeiro;

    while(node != NULL){
        if (strstr(node->info_paciente->Nome, nome) != NULL){
            int id_original = node->info_paciente->Id;
            inserir_paciente_lista(node->info_paciente, pacientes_encontrados);
            node->info_paciente->Id = id_original;
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

int consultar_paciente(Lista *lista_pacientes){//retorna 0 nao houver erro ou -1 se houver excecao
    printf("escolha o modo de consulta:\n1 - por nome\n2 - por cpf\n3 - retornar ao menu principal\n\n");
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
            return -1;
        }
        imprimir_lista(pacientes_encontrados);
        free(pacientes_encontrados);

    // Busca por CPF
    } else if (modo_busca == 2){
        char cpf[11];
        printf("Digite o CPF:\n\n");
        scanf("%s", cpf);

        if (!valida_cpf(cpf)){
            printf("CPF inválido.\n\n");
            return -1;
        }

        Paciente *paciente_encontrado = consulta_cpf(cpf, lista_pacientes);
        if (paciente_encontrado == NULL){
            printf("CPF nao registrado.\n\n");
            return -1;
        }

        imprime_paciente(paciente_encontrado);
        free(paciente_encontrado);
        return 0;

    }else if (modo_busca == 3){
        return -1;
    } else {
        
        return -1;
    }
    return 0; //deu tudo certo
    }


void remover_paciente(Lista *lista){
    if (consultar_paciente(lista)!=0){//verifica excecoes
        printf("\nOperacao cancelada.\n\n");
        return;
        
    }
    printf("Digite o ID do paciente a ser excluído:\n\n");
    char id_str[10];
    int id;
    scanf("%s", id_str); 
    id = atoi(id_str);

    Paciente *paciente = consulta_id(id ,lista);
    if (paciente == NULL) {//caso o ID não seja encontrado, cancela a atualização
        //printf("Paciente com ID %d não encontrado.\n", id);
        return;
    }

    Node *node = lista->primeiro;

    //busca a id escolhida
    while (node != NULL){
        if (node->info_paciente->Id == id){

            printf("\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n\n");
            imprime_paciente(node->info_paciente); printf("\n");
            char remover; //char encerrar = 'N';
            scanf("%c", &remover);
            if (toupper(remover) == 'N'){
                return;
            } else if(toupper(remover) == 'S'){
                
            //se node for o primeiro elemento da lista
            if (node == lista->primeiro){
                //printf("\nentrou no segundo if\n");
                lista->primeiro = node->proximo;
                //printf("executou a linha depois do segundo if\n");
                //se tiver proximo elemento
                if (node->proximo != NULL){
                    //printf("entrou no terceiro if\n");
                    lista->primeiro->anterior = NULL;
                    //printf("executou a linha depois do terceiro if\n");
                }
            }
            //se o node for o ultimo elemento da lista
            if (node == lista->ultimo){
                //printf("\nentrou no quarto if\n");
                lista->ultimo = node->anterior;
                //se tiver elemento anterior
                if (lista->ultimo != NULL){
                    lista->ultimo->proximo = NULL;
                }
            }

            //se ele estiver entre dois elementos
            if (node->anterior != NULL && node->proximo != NULL) {
                //printf("\nentrou no ultimo if\n");
                node->anterior->proximo = node->proximo;
                node->proximo->anterior = node->anterior;
            }

            
            free(node->info_paciente);
            free(node);

            printf("\nRegistro removido com sucesso.\n");
            return;
            } else {
                printf("Opção inválida.\n");
                return;
            }
        }
        node = node->proximo;
    }
    return;
}    


void atualizar_paciente(Lista *lista){
    if (consultar_paciente(lista)!=0){
        printf("\nOperacao cancelada.\n\n");
        return;        
    }

    imprimir_lista(lista);
    printf("Digite o ID do paciente a ser atualizado:\n\n");
    int id;
    scanf("%d", &id); 

    Paciente *paciente = consulta_id(id ,lista);
    if (paciente == NULL) {//caso o ID não seja encontrado, cancela a atualização
        printf("Paciente com ID %d não encontrado.\n", id);
        return;
    }

    Paciente *paciente_atualizado = (Paciente*)malloc(sizeof(Paciente));
    paciente_atualizado->Id = paciente->Id;
    paciente_atualizado->Idade = paciente->Idade;
    strcpy(paciente_atualizado->Cpf, paciente->Cpf);
    strcpy(paciente_atualizado->Nome, paciente->Nome);
    strcpy(paciente_atualizado->Data_cadastro, paciente->Data_cadastro);

    printf("\n\n");
    printf("Digite o novo valor para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro,");
    printf("separados por espaços (para manter o valor atual de um campo, digite '-'):\n\n");

    char novo_cpf[15]; char novo_nome[101]; char nova_idade[4]; char nova_data_cadastro[11];
    scanf("%s", novo_cpf);
    scanf("%s", novo_nome);
    scanf("%s", nova_idade);
    scanf("%s", nova_data_cadastro);

    if (strcmp(novo_cpf, "-") != 0){
        char cpf_formatado[15];
        sprintf(cpf_formatado, "%.3s.%.3s.%.3s-%.3s", novo_cpf, novo_cpf+3, novo_cpf+6, novo_cpf+9);
        if (!valida_cpf(novo_cpf)){
            printf("CPF inválido!\n");
        }
        else if (consulta_cpf(novo_cpf, lista) != NULL){//se o novo cpf ja estiver cadastrado
            printf("CPF já cadastrado!\n");
        }
        else{
            strcpy(paciente_atualizado->Cpf, cpf_formatado);
        }
    }
    
    if (strcmp(novo_nome, "-") != 0){
        if (!contemNumero(novo_nome)){
            strcpy(paciente_atualizado->Nome, novo_nome);
        } else {
            printf("Formato de nome inválido!\n");
        }
    }

    if (strcmp(nova_data_cadastro, "-") != 0) {
        if (strlen(nova_data_cadastro) < 11) {
            strcpy(paciente_atualizado->Data_cadastro, nova_data_cadastro);
        } else {
            printf("Formato de data inválido!\n");
        }
    }

    if (strcmp(nova_idade, "-") != 0){
        paciente_atualizado->Idade = atoi(nova_idade);
    }

    printf("Confirme os novos valores:\n\n");
    imprime_paciente(paciente_atualizado);

    printf("Deseja confirmar as alterações? (S/N)\n\n");
    char confirmar;
    scanf(" %c", &confirmar);
    if (toupper(confirmar) == 'S'){
        printf("Alterações confirmadas.\n");
        *paciente = *paciente_atualizado;
    } else {
        printf("Alterações canceladas.\n");
    }

    free(paciente_atualizado);
}
