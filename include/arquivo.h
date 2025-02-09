#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "paciente.h"
#include "bd_paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void arq_inserir_lista(Lista *lista, FILE *arquivo);
void cadastrar_paciente(Lista *lista_pacientes);
Paciente* arq_criar_paciente(int id, const char *cpf, const char *nome, int idade, const char *data_cadastro);
Lista* arq_ler_pacientes(const char *nome_arquivo);
#endif
