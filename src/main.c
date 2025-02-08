#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\include\paciente.h"
#include "..\include\bd_paciente.h"
#include "..\include\utils.h"

int main(){
    Lista *lista_pacientes = cria_lista_pacientes();
    char cpf[] = "18376163701";
    char cpf_errado[] = "18376163700";
    char nome[] = "lari a Lari";
    int idade = 60;
    char data[] = "06-05-2000";
    Paciente *paciente = cria_paciente(cpf, nome, idade, data, lista_pacientes);
    inserir_paciente_lista(paciente, lista_pacientes);
    //imprimir_lista(lista_pacientes);

    char cpf2[] = "01752563735";
    char cpf_errado2[] = "18376163700";
    char nome2[] = "lari a eu";
    int idade2 = 90;
    char data2[] = "06-05-2005";
    Paciente *paciente2 = cria_paciente(cpf2, nome2, idade2, data2, lista_pacientes);
    inserir_paciente_lista(paciente2, lista_pacientes);
    imprimir_lista(lista_pacientes);
    char nomeai[] = "a";
    Lista *encontrados = cria_lista_pacientes();
    remover_paciente(1, lista_pacientes);
    //imprimir_lista(lista_pacientes);

    consultar_paciente(lista_pacientes);
    char novo_cpf[]= "01752573766"; char novo_nome[] = "vovo"; char nova_idade[] = "-"; char nova_data[] = "-";
    atualizar_paciente(consulta_id(2, lista_pacientes), novo_cpf, novo_nome, nova_idade, nova_data, lista_pacientes);
    return 0;
}


/*
char opcao;

while (toupper(opcao) != "Q"){
    //implementar menu
}
*/
