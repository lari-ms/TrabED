#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\include\paciente.h"
#include "..\include\bd_paciente.h"
#include "..\include\utils.h"

Paciente* cria_paciente(char* cpf, char *nome, int idade, char data_cadastro, Lista* lista_pacientes){
    Paciente *ptr_novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    ptr_novo_paciente->Id = lista_pacientes->qtd++;
    printf("id: %d, quantidade de pacientes depois do novo cadastro: %d\n", ptr_novo_paciente->Id, lista_pacientes->qtd++);
    sprintf(ptr_novo_paciente->Cpf, "%.3s.%.3s.%.3s-%.3s", cpf, cpf+3, cpf+6, cpf+9);
    
    int cpf_valido = valida_cpf(ptr_novo_paciente->Cpf);

    ptr_novo_paciente->Idade = idade;
    ptr_novo_paciente->Nome = nome;
    ptr_novo_paciente->Data_cadastro = data_cadastro; //É OBRIGATORIO??

    return ptr_novo_paciente;
}

Lista* busca_paciente_cpf(char* cpf, Lista *lista){
    Lista *pacientes_encontrados = cria_lista_pacientes();
    Paciente *paciente = lista->primeiro;

    if (lista->qtd == 0){
        return NULL;
    }

    while(paciente != NULL){
        if (strcmp(paciente->Cpf, cpf)){
            inserir_paciente_lista(paciente, pacientes_encontrados);
        }
    }

    return pacientes_encontrados;
}

Lista* busca_paciente_nome(char* nome, Lista *lista){
    Lista *pacientes_encontrados = cria_lista_pacientes();
    Paciente *paciente = lista->primeiro;

    if (lista->qtd == 0){
        return NULL;
    }

    while(paciente != NULL){
        if (strstr(paciente->Nome, nome) != NULL){
            inserir_paciente_lista(paciente, pacientes_encontrados);
        }
    }

    return pacientes_encontrados;
}



Paciente* consultar_paciente(int modo_busca, Lista *lista_pacientes){
    switch (modo_busca)
    {
    case 1://nome
        char *cpf = "12345678900";

        Lista *resultado_busca = busca_paciente_cpf(cpf, lista_pacientes);
        break;
    
    case 2: //nome
        char *nome = "Mari";
        Lista *resultado_busca = busca_paciente_nome(nome, lista_pacientes);


    case 3: //voltar pro menu
        return;

    default:
        printf("Modo inválido");
        break; //chamar a funcao de novo?
    }
}
