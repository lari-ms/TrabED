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

Paciente* cria_paciente(char* cpf, char *nome, int idade, char *data_cadastro, Lista* lista_pacientes);
void consultar_paciente(Lista *lista_pacientes);
void inserir_paciente_lista(Paciente *paciente, Lista *lista_pacientes);
Paciente* consulta_cpf(char* cpf, Lista *lista);
void remover_paciente(Lista *lista);
int lista_vazia(Lista *lista);
void atualizar_paciente(Lista *lista);
Paciente* consulta_id(int id, Lista *lista);
Lista* consulta_nome(char* nome, Lista *lista);
void imprime_paciente(Paciente *paciente);
void cadastrar_paciente(Lista *lista_pacientes);

#endif