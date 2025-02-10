# Gerenciamento de Pacientes
O programa consiste na simulação de num sistema simplificado de gerenciamento dos pacientes de uma clínica.

As funcionalidades do sistema se resumem a:
- Consulta de pacientes
- Atualização de pacientes
- Remoção de pacientes
- Cadastro de pacientes
- Visualização dos pacientes cadastrados
<br><br>

Como Instalar e Executar o Projeto
----------------------------------
1. Abra o terminal e clone o repositório em seu desktop: 
```cd
git clone https://github.com/lari-ms/TrabED.git
```
2. Copie e cole o caminho em que o repositorio foi salvo:
```
cd <caminho do repositorio>
```

3. Para compilar o código e executar o programa, digite a linha abaixo:
```cd
make
```
<br>

## [COLOCAR PRINTS DE EXEMPLO?]



## Estrutura do Projeto
- `src\main.c` - Arquivo principal (...)
- `src\paciente.c` - Funções de gerenciamento de pacientes
- `src\bd_paciente.c` - Funções de manipulação da lista de pacientes
- `src\paciente.c` - Funções de gerenciamento de pacientes
- `src\utils.c` - Funções auxiliares
- `include` - Pasta com headers das funções nos arquivos .c
- `db_paciente.csv` - Banco de dados com os pacientes
- `Makefile`
- `README.md`


## TADs utilizados
#### Node
Cada nó (Node) representa um elemento da lista encadeada. Cada nó é composto de três campos:
- Ponteiro para o **nó anterior** (`anterior`)
- Ponteiro para o **próximo nó** (`proximo`)
- Ponteiro para um **Paciente** (`info_paciente`)

```c
typedef struct node_lista {
    struct node_lista *anterior;  // Ponteiro para o nó seguinte
    struct node_lista *proximo;   // Próximo nó
    Paciente *info_paciente;      // Informações do paciente
} Node;
```


#### Lista
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


#### Paciente
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
<br>


## Principais funções de manipulação (da lista?)

Recebe uma lista de pacientes e exibe seu conteúdo
```C
void imprimir_lista(Lista *lista);
//Saída: 
//  ID    CPF                        Nome                 Idade       Data_Cadastro
//  2     987.654.321-00      Paciente 1          30            2024-12-02
//  6     354.624.978-06      Paciente 2          50            2024-07-10
```

#
Cria um novo paciente com os dados fornecidos.
```C
Paciente* cria_paciente(char* cpf, char *nome, int idade, char *data_cadastro, Lista* lista_pacientes)
```
Retorna um TAD Paciente<br><br>



## **[...]**