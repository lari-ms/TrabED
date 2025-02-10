#ifndef PACIENTE_H
#define PACIENTE_H
typedef struct lista_pacientes Lista;

typedef struct paciente{
    int Id;
    char Cpf[15];
    char Nome[100];
    int Idade;
    char Data_cadastro[11];
} Paciente;


//Atualizações Paciente
Paciente* cria_paciente(char* cpf, char *nome, int idade, char *data_cadastro, Lista* lista_pacientes);
void atualizar_paciente(Lista *lista);

//Operações Paciente
void imprime_paciente(Paciente *paciente);

#endif