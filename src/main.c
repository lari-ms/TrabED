#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\include\paciente.h"
#include "..\include\bd_paciente.h"
#include "..\include\utils.h"
#include "..\include\arquivo.h"

int main(){

    //carregar o arquivo etc
    //criar a lista com os pacientes do arquivo
    const char *nome_arq = "database\\bd_paciente.csv";
    Lista *lista_pacientes = arq_ler_pacientes(nome_arq);
    printf("%d", tamanho_lista(lista_pacientes));
    imprimir_lista(lista_pacientes);
   
    /*int run = 0;
    while(run==0){
        exibe_menu();
        char opcao_menu;
        scanf("%c", opcao_menu);
        switch (opcao_menu)
        {
        case '1':
            consultar_paciente()
            break;
        
        default:
            break;
        }

    }//fim do while
    */
    return 0;
}


/*
char opcao;

while (toupper(opcao) != "Q"){
    //implementar menu
}
*/
