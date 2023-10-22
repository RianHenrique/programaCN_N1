#include <stdio.h>
#include <ctype.h>
#include "funcoes/funcoes.h"

int main() {
    char option;

    do {
        printf("\n\n\n");
        printf("*****ESCOLHA UMA OPÇÃO******\n");
        printf("     C - Conversão\n");
        printf("     S - Sistema Linear\n");
        printf("     E - Equação Algébrica\n");
        printf("     F - Finalizar\n");
        printf("****************************");
        printf("\n\n");

        printf("Digite a opção desejada: ");
        scanf(" %c", &option); // Lê a escolha do usuário
        printf("\n\n");

        option = tolower(option);

        switch (option) {
            case 'c':
                conversao();
                break;
            case 's':
                sistemaLinear();
                break;
            case 'e':
                equacaoAlgebrica();
                break;
            case 'f':
                printf("Finalizando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (option != 'f'); // Continue até que o usuário escolha 'F'

    return 0;
}
