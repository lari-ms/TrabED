#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

int verifica_cpf(char* cpf){ //1 - valido   | 0 - invalido
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
        return 0;
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
        printf("verificador2 = %d  |  algarismo 11: %d\n", verificador2, (cpf[10])-'0');

        return (cpf[10])-'0' == verificador2;
    }

}


/*
int main(){

    char cpf[12];
    scanf("%s", &cpf);
    printf("%s\n", cpf);
    int valido = verifica_cpf(cpf);
    printf("%s: %d\n", cpf, valido);

    return 0;
}
*/