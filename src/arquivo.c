#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bd_paciente.h"
#include "../include/paciente.h"
#include "../include/arquivo.h"

#define MAX_LINHA 256

void arq_inserir_lista(Lista *lista, const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(arquivo, "id,cpf,nome,idade,data_cadastro\n");
    for (Node *node = lista->primeiro; node != NULL; node=node->proximo){
        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
        node->info_paciente->Id,
        node->info_paciente->Cpf,
        node->info_paciente->Nome,
        node->info_paciente->Idade,
        node->info_paciente->Data_cadastro);
    }
    fclose(arquivo); 
}

Paciente* arq_criar_paciente(int id, const char *cpf, const char *nome, int idade, const char *data_cadastro) {
    Paciente *novo = (Paciente *)malloc(sizeof(Paciente));
    if (!novo) {
        perror("Erro ao alocar memória para paciente");
        return NULL;
    }
    novo->Id = id;

    strncpy(novo->Cpf, cpf, sizeof(novo->Cpf) - 1);
    novo->Cpf[sizeof(novo->Cpf) - 1] = '\0';

    strncpy(novo->Nome, nome, sizeof(novo->Nome) - 1);
    novo->Nome[sizeof(novo->Nome) - 1] = '\0';

    novo->Idade = idade;

    strncpy(novo->Data_cadastro, data_cadastro, sizeof(novo->Data_cadastro) - 1);
    novo->Data_cadastro[sizeof(novo->Data_cadastro) - 1] = '\0';

    return novo;
}

Lista *arq_ler_pacientes(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    char linha[MAX_LINHA];
    Lista *lista = cria_lista_pacientes(); 

    fgets(linha, MAX_LINHA, arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        int id, idade;
        char cpf[15], nome[100], data_cadastro[11];
        if (sscanf(linha, "%d,%14[^,],%99[^,],%d,%10[^,\n]", &id, cpf, nome, &idade, data_cadastro) == 5) {
            Paciente *novo = arq_criar_paciente(id, cpf, nome, idade, data_cadastro);
            if (novo) {
                inserir_paciente_lista(novo, lista);
            }
        } else {
            fprintf(stderr, "Erro: linha inválida: %s", linha);
        }
    }

    fclose(arquivo);
    return lista;
}