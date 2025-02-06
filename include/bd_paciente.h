#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H
#include "paciente.h"
typedef struct paciente Paciente;

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

#endif