#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H
#include "paciente.h"
typedef struct Paciente paciente;

typedef struct node_lista{
    struct node_lista *anterior;
    struct node_lista *proximo;
    Paciente *info_paciente;
} Node;

typedef struct lista_pacientes{
    Node *primeiro;
    Node *ultimo;
    int qtd;

} Lista;

//Alterações Lista
Lista* cria_lista_pacientes();
void remover_paciente(Lista *lista);
void cadastrar_paciente(Lista *lista_pacientes);
void inserir_paciente_lista(Paciente *paciente, Lista *lista_pacientes);

//Operações Lista
Lista* consultar_paciente(Lista *lista_pacientes);
void imprimir_lista(Lista *lista);
int tamanho_lista(Lista *lista);
int lista_vazia(Lista *lista);

//Buscas Lista
Paciente* consulta_id(int id, Lista *lista);
Paciente* consulta_cpf(char* cpf, Lista *lista);
Lista* consulta_nome(char* nome, Lista *lista);

#endif