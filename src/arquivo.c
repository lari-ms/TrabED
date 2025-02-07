#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bd_paciente.h"

#define MAX_LINHA 256

typedef struct Paciente {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
    struct Paciente *proximo;
} Paciente;

Paciente* criar_paciente(int id, const char *cpf, const char *nome, int idade, const char *data_cadastro) {
    Paciente *novo = (Paciente *)malloc(sizeof(Paciente));
    if (!novo) {
        perror("Erro ao alocar memória para paciente");
        return NULL;
    }
    novo->id = id;

    strncpy(novo->cpf, cpf, sizeof(novo->cpf) - 1);
    novo->cpf[sizeof(novo->cpf) - 1] = '\0';

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    novo->idade = idade;

    strncpy(novo->data_cadastro, data_cadastro, sizeof(novo->data_cadastro) - 1);
    novo->data_cadastro[sizeof(novo->data_cadastro) - 1] = '\0';

    novo->proximo = NULL;

    return novo;
}

void inserir_paciente(Lista *lista, Paciente *novo) {
   
    if(lista->primeiro == NULL){
        
        lista->primeiro = lista->ultimo = 
    }

}

Paciente *ler_pacientes(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    Paciente *lista = NULL;
    char linha[MAX_LINHA];
    while (fgets(linha, sizeof(linha), arquivo)) {
        int id, idade;
        char cpf[15], nome[100], data_cadastro[11];
        if (sscanf(linha, "%d,%14[^,],%99[^,],%d,%10[^,\n]", &id, cpf, nome, &idade, data_cadastro) == 5) {

            Paciente *novo = criar_paciente(id, cpf, nome, idade, data_cadastro);

            if (novo) {
                inserir_paciente(&lista, novo);
            }

        } else {
            fprintf(stderr, "Erro: linha inválida: %s", linha);
        }
    }
    fclose(arquivo);
    return lista;
}