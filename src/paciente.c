#include <stdio.h>
#include <stdlib.h>
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
    ptr_novo_paciente->Nome = strdup(nome);

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
    if (lista->qtd == 0){
        printf("Lista vazia\n");
        return;
    }
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
    return;
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

/*void consultar_paciente(int modo_busca, Lista *lista_pacientes){
    printf("escolha o modo de consulta:\n1 - por nome\n2 - por cpf\n 3 - retornar ao menu principal\n\n");
    modo_
    switch (modo_busca)
    {
    case 1://nome
        char cpf;
        //cpf[12] = "12345678900";

        Lista *resultado_busca = busca_paciente_cpf(cpf, lista_pacientes);
        break;
    
    case 2: //nome
        char nome[150] = "Mari";
        Lista *resultado_busca = busca_paciente_nome(nome, lista_pacientes);


    case 3: //voltar pro menu
        return;

    default:
        printf("Modo inválido");
        break; //chamar a funcao de novo?
    }
}*/

void remover_paciente(int id, Lista *lista){
    
    
    
    Node *node = lista->primeiro;

    //busca a id escolhida
    while (node != NULL){
        if (node->info_paciente->Id == id){

            printf("\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n\n");
            imprime_paciente(node->info_paciente); printf("\n");
            char remover; char encerrar = 'N';
            scanf("%c", &remover);
            if (remover == encerrar){
                return;
            }

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
        }
        node = node->proximo;
    }
    return;
}    