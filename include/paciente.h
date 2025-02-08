#ifndef PACIENTE_H
#define PACIENTE_H
typedef struct lista_pacientes Lista;

typedef struct Paciente {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
} Paciente;

//Paciente* cria_paciente(char *cpf, char *nome, int idade, char *data_cadastro, Lista* lista_pacientes);
Paciente* consultar_paciente(int modo_busca, Lista *lista_pacientes);
void inserir_paciente_lista(Paciente *paciente, Lista *lista_pacientes);
Paciente* busca_paciente_cpf(char* cpf, Lista *lista);
#endif