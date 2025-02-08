#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bd_paciente.h"
#include "../include/paciente.h"

#define MAX_LINHA 256

// Declaração da função arq_criar_paciente
Paciente* arq_criar_paciente(int id, const char *cpf, const char *nome, int idade, const char *data_cadastro);

void cadastrar_paciente(Lista *lista_pacientes){
    char cpf[15], nome[100], data_cadastro[11];
    int idade;
    printf("Digite o CPF do paciente: ");
    scanf("%s", cpf);
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    printf("Digite a idade do paciente: ");
    scanf("%d", &idade);
    printf("Digite a data de cadastro do paciente: ");
    scanf("%s", data_cadastro);
    int id = lista_pacientes->qtd + 1; // Assuming id is the next available id
    Paciente *novo_paciente = arq_criar_paciente(id, cpf, nome, idade, data_cadastro);
    inserir_paciente_lista(novo_paciente, lista_pacientes);
}

void arq_inserir_lista(Lista *lista, FILE *arquivo){
    fprintf(arquivo, "id,cpf,nome,idade,data_cadastro\n");
    for (Node *node = lista->primeiro; node != NULL; node=node->proximo){
        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
        node->info_paciente->id,
        node->info_paciente->cpf,
        node->info_paciente->nome,
        node->info_paciente->idade,
        node->info_paciente->data_cadastro);
    }
}

Paciente* arq_criar_paciente(int id, const char *cpf, const char *nome, int idade, const char *data_cadastro) {
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
/*
int main(){
    Lista *lista_teste = arq_ler_pacientes("C:/Users/bield/Documents/Gabriel/ED_Projeto/TrabED/database/bd_paciente.csv");
    if (lista_teste == NULL){
        return 1;
    }
    imprimir_lista(lista_teste);
    cadastrar_paciente(lista_teste);

    FILE *arquivo = fopen("C:/Users/bield/Documents/Gabriel/ED_Projeto/TrabED/database/bd_paciente.csv", "w");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    arq_inserir_lista(lista_teste, arquivo);
    fclose(arquivo);

    return 0;
}
*/