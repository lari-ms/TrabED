#ifndef UTILS_H
#define UTILS_H
#include "bd_paciente.h"

//Funções de interface	
void Menu();
void limpar_terminal();

//Funções de validação
int valida_cpf(char* cpf);
int contemNumero(const char* str);

#endif