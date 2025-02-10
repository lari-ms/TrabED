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
    if (strlen(cpf) != 11) {
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }    
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
    Lista *lista_pacientes = arq_ler_pacientes("C:/Users/bield/Documents/Gabriel/ED_Projeto/TrabED/database/bd_paciente.csv");
    printf("teste\n");    
    int opcao = 0;

    while(opcao != 5){

        printf("\n=====================\n");
        printf("    MENU PRINCIPAL   \n");
        printf("=====================\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Consultar paciente\n");
        printf("3 - Remover paciente\n");
        printf("4 - Atualizar paciente\n");
        printf("5 - Sair\n");
        printf("=====================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        printf("\n\n");

        switch (opcao){
            case 1:
                cadastrar_paciente(lista_pacientes);
                break;
            case 2:
                consultar_paciente(lista_pacientes);
                break;
            case 3:
                remover_paciente(lista_pacientes);
                break;
            case 4:
                atualizar_paciente(lista_pacientes);
                break;
            case 5:
                printf("Fim da execucao\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    arq_inserir_lista(lista_pacientes, "C:\\Users\\bield\\Documents\\Gabriel\\ED_Projeto\\TrabED\\database\\bd_paciente.csv");


}
