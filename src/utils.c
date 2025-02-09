#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/utils.h"
#include <bd_paciente.h>

int valida_cpf(char* cpf){ //0 - valido   | 1 - invalido
    int soma = 0;
    for (int index=0; index<9; index++){
        int m = 10-index;
        int algarismo = (cpf[index]) - '0';
        soma += m*algarismo;
    }
    
    int resto = soma% 11;
    int verificador1 ;
    if (resto < 2){
        verificador1 = 0;
    } else {
        verificador1 = 11-resto;
    }

    if ((cpf[9])-'0' != verificador1){
        return 1;
    } else {
        int soma2 = 0;
        for (int index=0; index<10; index++){
        int m = 11-index;
        int algarismo = (cpf[index]) - '0';
        soma2 += m*algarismo;
        }

        int resto = soma2% 11;
        int verificador2 ;
        if (resto < 2){
            verificador2 = 0;
        } else {
            verificador2 = 11-resto;
        
        }
        //printf("verificador2 = %d  |  algarismo 11: %d\n", verificador2, (cpf[10])-'0');

        return (cpf[10])-'0' == verificador2;
    }

}

void Menu(){

    Lista *lista_pacientes = arq_ler_pacientes("../bd_paciente.csv");
    
    printf("\n=====================\n");
    printf("    MENU PRINCIPAL   \n");
    printf("=====================\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Consultar paciente\n");
    printf("3 - Atualizar paciente\n");
    printf("4 - Remover paciente\n");
    printf("5 - Sair\n");
    printf("=====================\n");
    printf("Escolha uma opção: ");

    int opcao;

    while(1){
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            Paciente *novo_paciente = cria_paciente();
            inserir_paciente_lista(novo_paciente, lista_pacientes);
            break;
        case 2:
            consultar_paciente(lista_pacientes);
            break;
        case 3:
            atualizar_paciente(lista_pacientes);
            break;
        case 4:
            remover_paciente(lista_pacientes);
            break;
        case 5:
            arq_inserir_lista(lista_pacientes, "../bd_paciente.csv");
            return;
        default:
            printf("Opção inválida.\n");
            break;
        }
    }

}












/*
int main(){

    char cpf[12];
    scanf("%s", &cpf);
    printf("%s\n", cpf);
    int valido = valida_cpf(cpf);
    printf("%s: %d\n", cpf, valido);

    return 0;
}
*/