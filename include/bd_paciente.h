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

Lista* cria_lista_pacientes();
void imprimir_lista(Lista *lista);
int tamanho_lista(Lista *lista);
void inserir_paciente_lista(Paciente *paciente, Lista *lista_pacientes);
#endif