# TrabED
Sistema simplificado de gerenciamento de pacientes

## Estrutura do projeto
O projeto usa uma lista duplamente encadeada para armazenar e manipular pacientes.

### Estruturas de dados utilizadas
#### Estrutura  **Node**
Cada nó (Node) representa um elemento da lista encadeada. Cada nó é composto de três campos:
- Ponteiro para o **nó anterior** (`anterior`)
- Ponteiro para o **próximo nó** (`proximo`)
- Ponteiro para um **Paciente** (`info_paciente`)

```c
typedef struct node_lista {
    struct node_lista *anterior;  // Nó anterior
    struct node_lista *proximo;   // Próximo nó
    Paciente *info_paciente;      // Informações do paciente
} Node;
```


#### Estrutura  **Lista**
A estrutura **Lista** gerencia os nós. É composta de:
- Ponteiro para o **primeiro nó** (`primeiro`)
- Ponteiro para o **último nó** (`ultimo`)
- Inteiro **qtd**, representando o  número de elementos da lista (`qtd`)

```C
typedef struct lista_pacientes {
    Node *primeiro;  // Primeiro elemento da lista
    Node *ultimo;    // Último elemento da lista
    int qtd;         // Número de pacientes cadastrados
} Lista;
```


#### Estrutura **Paciente**
Representação dos pacientes cadastrados no sistema. É composta dos campos:
```C
typedef struct paciente {
    int Id;              // Identificador único do paciente
    char Cpf[15];        // Formato xxx.xxx.xxx-xx
    char Nome[101];          // Nome com máximo de 100 caracteres
    int Idade;           // Idade do paciente
    char Data_cadastro[11]; // Formato dd-mm-aaaa
} Paciente;
```