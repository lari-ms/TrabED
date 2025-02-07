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
    if (busca_paciente_cpf(ptr_novo_paciente->Cpf, lista_pacientes) != NULL){//se nao houver nenhum cpf cadastrado
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

Paciente* busca_paciente_cpf(char* cpf, Lista *lista){
    
    if (lista->qtd == 0){
        return NULL;
    }
    Node *node = lista->primeiro;

    while(node != NULL){
        if (strcmp(node->info_paciente->Cpf, cpf)==0){
            return node->info_paciente;
        }
        node = node->proximo;
    }

    return NULL;
}

Lista* busca_paciente_nome(char* nome, Lista *lista){
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

/*Paciente* consultar_paciente(int modo_busca, Lista *lista_pacientes){
    switch (modo_busca)
    {
    case 1://nome
        char cpf;
        cpf[12] = "12345678900";

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

int main(){
    Lista *lista_pacientes = cria_lista_pacientes();
    char cpf[] = "18376163701";
    char cpf_errado[] = "18376163700";
    char nome[] = "lari a Lari";
    int idade = 60;
    char data[] = "06-05-200005";
    Paciente *paciente = cria_paciente(cpf, nome, idade, data, lista_pacientes);
    inserir_paciente_lista(paciente, lista_pacientes);
    imprimir_lista(lista_pacientes);

    return 0;
}
