#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/utils.h"
#include "../include/bd_paciente.h"
#include "../include/paciente.h"
#include "../include/arquivo.h"



void limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


int contemNumero(const char* str){
    for (int i=0; i<strlen(str); i++){
        if (isdigit(str[i])){
            return 1;
        }
    }
    return 0;
}

int valida_cpf(char* cpf){ //0 - valido   | 1 - invalido
    int soma = 0;
    for (int index=0; index<9; index++){
        int m = 10-index;
        int algarismo = (cpf[index]) - '0';
        soma += m*algarismo;
    }
    
    int resto = soma % 11;
    int verificador1;
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

        int resto2 = soma2 % 11;
        int verificador2;
        if (resto2 < 2){
            verificador2 = 0;
        } else {
            verificador2 = 11-resto2;
        }

        return (cpf[10])-'0' == verificador2;
    }
}

void Menu(){
    printf("teste\n");
    Lista *lista_pacientes = cria_lista_pacientes();
    printf("teste\n");    
    int opcao = 0;

    while(opcao != 5){

        printf("\n=====================\n");
        printf("    MENU PRINCIPAL   \n");
        printf("=====================\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Consultar paciente\n");
        printf("3 - Atualizar paciente\n");
        printf("4 - Remover paciente\n");
        printf("5 - Sair\n");
        printf("=====================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                printf("teste 1");
                break;
            case 2:
                printf("teste 2");
                break;
            case 3:
                printf("teste 3");
                break;
            case 4:
                printf("teste 4");
                break;
            case 5:
                printf("Saindo aqui mano...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}
