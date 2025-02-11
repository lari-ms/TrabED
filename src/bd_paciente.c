#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Adicionado para toupper
#include "bd_paciente.h"
#include "paciente.h"
#include "utils.h" // Adicionado para valida_cpf

Lista* cria_lista_pacientes(){
    Lista *ptr_nova_lista = (Lista *)malloc(sizeof(Lista));//aloca memoria para lista e retorna ponteiro para ela
    ptr_nova_lista->primeiro = NULL;
    ptr_nova_lista->ultimo = NULL;
    ptr_nova_lista->qtd = 0;

    return ptr_nova_lista; //retorna o PONTEIRO pra lista
}

void imprimir_lista(Lista *lista){
    printf("\n%-5s %-15s %-60s %-7s %-15s", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    for (Node *node = lista->primeiro; node != NULL; node=node->proximo){
        printf("\n%-5d %-15s %-60s %-7d %-15s",
        node->info_paciente->Id,
        node->info_paciente->Cpf,
        node->info_paciente->Nome,
        node->info_paciente->Idade,
        node->info_paciente->Data_cadastro);
    }
    printf("\n");
}

void inserir_paciente_lista(Paciente *paciente, Lista *lista_pacientes){
    // Verifica se o CPF já existe na lista
    if (consulta_cpf(paciente->Cpf, lista_pacientes) != NULL) {
        printf("CPF já cadastrado! Operação cancelada.\n");
        return;
    }

    // Criando novo nó
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
    lista_pacientes->qtd++; // Incrementa a quantidade de pacientes na lista
}

void remover_paciente(Lista *lista){
    Lista *pacientes_encontrados = consultar_paciente(lista);
    if (pacientes_encontrados == NULL) {
        return;
    }
    printf("Digite o ID do paciente a ser excluido:\n\n");
    char id_str[10];
    int id;
    scanf("%s", id_str); 
    id = atoi(id_str);

    Paciente *paciente = consulta_id(id, pacientes_encontrados);
    if (paciente == NULL) {//caso o ID não seja encontrado, cancela a atualização
        printf("ID invalido.\n");
        free(pacientes_encontrados);
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
                free(pacientes_encontrados);
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
            lista->qtd--; // Decrementa a quantidade de pacientes na lista
            free(pacientes_encontrados);
            return;
            } else {
                printf("Opcao invalida.\n");
                free(pacientes_encontrados);
                return;
            }
        }
        node = node->proximo;
    }
}

int lista_vazia(Lista *lista){
    return (lista->primeiro == NULL && lista->ultimo == NULL);
}

Lista* consultar_paciente(Lista *lista_pacientes){
    printf("Escolha o modo de consulta:\n1 - por nome\n2 - por CPF\n3 - retornar ao menu principal\n\n");
    int modo_busca;
    scanf("%d", &modo_busca);

    Lista *pacientes_encontrados = cria_lista_pacientes();

    // Busca por nome
    if (modo_busca == 1){
        char nome[100];
        printf("Digite o nome\n\n");
        getchar(); // Limpa o buffer do teclado
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha
        printf("\n");
        pacientes_encontrados = consulta_nome(nome, lista_pacientes);
        if (lista_vazia(pacientes_encontrados)){
            printf("Nenhum paciente foi encontrado.\n\n");
            free(pacientes_encontrados);
            return NULL;
        }
        imprimir_lista(pacientes_encontrados);

    // Busca por CPF
    } else if (modo_busca == 2){
        char cpf[12];
        printf("Digite o CPF:\n\n");
        scanf("%s", cpf);

        if (!valida_cpf(cpf)){
            printf("CPF invalido.\n\n");
            return NULL;
        }

        Paciente *paciente_encontrado = consulta_cpf(cpf, lista_pacientes);
        if (paciente_encontrado == NULL){
            printf("Nenhum paciente foi encontrado.\n\n");
            return NULL;
        }

        inserir_paciente_lista(paciente_encontrado, pacientes_encontrados);
        imprime_paciente(paciente_encontrado);

    } else if (modo_busca == 3){
        free(pacientes_encontrados);
        return NULL;
    } else {
        printf("Opcao invalida.\n");
        free(pacientes_encontrados);
        return NULL;
    }

    return pacientes_encontrados;
}

void cadastrar_paciente(Lista *lista_pacientes){

    char cpf[15], nome[100], data_cadastro[11];
    int idade;
    printf("Digite o CPF do paciente: ");
    scanf("%s", cpf);
    printf("Digite o nome do paciente: ");
    getchar(); // Limpa o buffer do teclado
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha
    printf("Digite a idade do paciente: ");
    scanf("%d", &idade);
    printf("Digite a data de cadastro do paciente (dd/mm/yyyy): ");
    getchar();
    fgets(data_cadastro, sizeof(data_cadastro), stdin);
    data_cadastro[strcspn(data_cadastro, "\n")] = '\0';

    Paciente *novo_paciente = cria_paciente(cpf, nome, idade, data_cadastro, lista_pacientes);
    
    if (novo_paciente != NULL) {
        inserir_paciente_lista(novo_paciente, lista_pacientes);
        printf("Paciente cadastrado com sucesso!\n");
    }
    else{
        printf("Erro ao cadastrar paciente.\n");
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


