#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "bd_paciente.h"
typedef struct lista_pacientes Lista;
Lista *arq_ler_pacientes(const char *nome_arquivo);
#endif
