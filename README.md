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


## Estrutura do Projeto
- `src\main.c` - Arquivo principal (...)
- `src\arquivo.c` - Funções de manipulação do arquivo csv
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
    char Data_cadastro[11]; // Formato dd/mm/aaaa
} Paciente;
```
<br>


## Principais funções de manipulação (da lista?)

Recebe uma lista de pacientes e exibe seu conteúdo
```C
void imprimir_lista(Lista *lista);
//Saída: 
//  ID    CPF                 Nome                Idade         Data_Cadastro
//  2     987.654.321-00      Paciente 1          30            2024/12/02
//  6     354.624.978-06      Paciente 2          50            2024/07/10
```
## Exemplos de Execução

### Menu Principal
```
=====================
    MENU PRINCIPAL   
=====================
1 - Cadastrar paciente
2 - Consultar paciente
3 - Remover paciente
4 - Atualizar paciente
5 - Imprimir Lista
Q - Sair
=====================
Escolha uma opcao: 
```

### Cadastro de Paciente
```
Digite o CPF do paciente: 12345678901
Digite o nome do paciente: João Silva
Digite a idade do paciente: 30
Digite a data de cadastro do paciente (dd/mm/yyyy): 01/01/2023
Paciente cadastrado com sucesso!
```

### Consulta de Paciente
```
Escolha o modo de consulta:
1 - por nome
2 - por CPF
3 - retornar ao menu principal

1
Digite o nome
João

ID: 1
CPF: 123.456.789-01
Nome: João Silva
Idade: 30
Data de Cadastro: 01/01/2023
-------------------------------
```

### Atualização de Paciente
```
Digite o ID do paciente a ser atualizado:

1
Digite o novo valor para os campos CPF (apenas digitos), Nome, Idade e Data de Cadastro,
ou '-' para manter o valor atual.

Novo CPF: -
Novo Nome: João Pedro Silva
Nova Idade: -
Nova Data de Cadastro: -

Confirme os novos valores:

ID: 1
CPF: 123.456.789-01
Nome: João Pedro Silva
Idade: 30
Data de Cadastro: 01/01/2023
-------------------------------

Deseja confirmar as alteracoes? (S/N)
S
Alteracoes confirmadas.
```

### Remoção de Paciente
```
Digite o ID do paciente a ser excluido:

1

Tem certeza de que deseja excluir o registro abaixo? (S/N)

ID: 1
CPF: 123.456.789-01
Nome: João Pedro Silva
Idade: 30
Data de Cadastro: 01/01/2023
-------------------------------

S
Registro removido com sucesso.
```

### Impressão da Lista de Pacientes
```
ID    CPF                 Nome                Idade         Data_Cadastro
2     987.654.321-00      Paciente 1          30            2024/12/02
6     354.624.978-06      Paciente 2          50            2024/07/10
```