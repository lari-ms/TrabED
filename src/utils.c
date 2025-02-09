#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/utils.h"

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

void exibe_menu(){
    printf("HealthSys\n\n1 - Consultar paciente\n2 - Atualizar paciente\n3 - Remover paciente\n4 - Inserir paciente\n5 - Imprimir lista de pacientes\nQ- Sair\n\n");
}

int contemNumero(const char* str) {
    while (*str) {
        if (isdigit(*str)) {
            return 1;//retorna 1 se nao houver numero
        }
        str++;
    }
    return 0;//retorna 0 se houver numero
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