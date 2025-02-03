typedef struct paciente Paciente;
typedef struct node_lista Node;
typedef struct lista_pacientes Lista;

Lista* cria_lista_pacientes();
void inserir_paciente(int cpf, char *nome, int idade, char data_cadastro, Lista *lista_pacientes);
void imprimir_lista(Lista *lista);



void valida_cpf(char *cpf);