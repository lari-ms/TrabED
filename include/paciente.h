#ifndef PACIENTE_H
#define PACIENTE_H
typedef struct lista_pacientes Lista;

typedef struct paciente{
    int Id;
    char *Cpf;
    char *Nome;
    int Idade;
    char *Data_cadastro;
} Paciente;

void consultar_paciente(int modo, Lista *lista_pacientes);
void inserir_paciente_lista(Paciente *paciente, Lista *lista_pacientes);

#endif