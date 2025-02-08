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

    return ptr_novo_paciente;
}

void imprime_paciente(Paciente *paciente){
    if (paciente != NULL){
        printf("ID    CPF          Nome                 Idade      Data_Cadastro\n");
        printf("%d     %s          %s       %d      %s\n",
            paciente->Id,
            paciente->Cpf,
            paciente->Nome,
            paciente->Idade,
            paciente->Data_cadastro);
    } else {
        printf("paciente não registrado\n");
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
    printf("CPF nao registrado\n");
    return NULL;
}

Lista* consulta_nome(char* nome, Lista *lista){
    Lista *pacientes_encontrados = cria_lista_pacientes();
    Node *node = lista->primeiro;

    while(node != NULL){
        if (strstr(node->info_paciente->Nome, nome) != NULL){
            inserir_paciente_lista(node->info_paciente, pacientes_encontrados);
        }
        //imprime_paciente(node->info_paciente);
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
    printf("escolha o modo de consulta:\n1 - por nome\n2 - por cpf\n 3 - retornar ao menu principal\n\n");
    int modo_busca;
    scanf("%d", &modo_busca);

    //busca por nome
    if (modo_busca == 1){
        char nome[101];
        printf("Digite o nome\n\n");
        scanf("%s", nome);
        printf("\n");
        Lista *pacientes_encontrados = consulta_nome(nome, lista_pacientes);
        if (lista_vazia(pacientes_encontrados)){
            printf("Nenhum paciente foi encontrado.\n\n");
            return;
        }
        imprimir_lista(pacientes_encontrados);
        free(pacientes_encontrados);

    //busca por cpf
    } else if ( modo_busca == 2){
        char cpf[12];
        printf("Digite o CPF:\n\n");
        scanf("%s", cpf);

        if (!valida_cpf(cpf)){
            printf("CPF inválido.\n\n");
            return;
        }

        Paciente *paciente_encontrado = consulta_cpf(cpf, lista_pacientes);
        if (paciente_encontrado == NULL){
            printf("Nenhum paciente foi encontrado.\n\n");
            return;
        }

        imprime_paciente(paciente_encontrado);
        free(paciente_encontrado);
    
    }else if (modo_busca == 3){
        return;
    }
    
    }


void remover_paciente(int id, Lista *lista){

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
/*
Digite o novo valor para os campos CPF (apenas dígitos), Nome, Idade e
Data_Cadastro, separados por espaços (para manter o valor atual de um campo, digite ’-’):
*/
void atualizar_paciente(Paciente *paciente,
    char* novo_cpf,
    char* novo_nome,
    char* nova_idade,
    char* nova_data_cadastro,
    Lista *lista){
    if (strcmp(novo_cpf, '-') != 0){
        strcpy(paciente->Cpf,novo_cpf);
    }

    if (strcmp(novo_cpf, '-') != 0){
        char cpf_formatado[15];
        sprintf(cpf_formatado, "%.3s.%.3s.%.3s-%.3s", novo_cpf, novo_cpf+3, novo_cpf+6, novo_cpf+9);

        if (!novo_cpf){
            printf("CPF inválido!\n");
            return NULL;
        }
        
        else if (consulta_cpf(cpf_formatado, lista) != NULL){//se o novo cpf ja estiver cadastrado
            printf("CPF já cadastrado!");
            return NULL;
        }
        sprintf(paciente->Cpf, cpf_formatado);

    }if (strcmp(nova_data_cadastro, '-') != 0){
        if (strlen(nova_data_cadastro) < 11) {
            strcpy(paciente->Data_cadastro, nova_data_cadastro);
        } else {
            printf("Formato de data inválido!\n");
            return NULL;
        }

    }if (strcmp(nova_idade, '-') != 0){
        nova_idade = nova_idade - '0';
        paciente->Idade = nova_idade;
    }
}