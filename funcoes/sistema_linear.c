#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoes.h"


int sistemaLinear() {
    char nomeArquivo[100]; // Assume um limite de 100 caracteres para o nome do arquivo

    printf("Digite o nome do arquivo .txt que contem o sistema linear: ");
    scanf("%s", nomeArquivo);
    printf("\n\n\n");

    FILE *arquivo;
    int linhas, colunas;

    // Abra o arquivo para leitura
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro na leitura do arquivo!\n");
        return 1;
    }

    printf("\t  ***MATRIZ DIAGONAL***\n\n");

    // Leia o número de linhas
    fscanf(arquivo, "%d", &linhas);

    //Ajuste sabendo que um array inicia com 0
    colunas = linhas; // A última coluna é para os termos independentes
    linhas = linhas - 1; // pois em um array começa com 0 entao se tiver 3 linhas ficaria 2 => 0,1,2

    // Alocação dinâmica da matriz
    int *ordemColuna = (int *)malloc((colunas + 1) * sizeof(int));
    double **m = (double **)malloc((linhas + 1) * sizeof(double *));
    for (int i = 0; i <= linhas; i++) {
        m[i] = (double *)malloc((colunas +1) * sizeof(double));
    }

    // Preencha a matriz com os valores do arquivo
    for (int i = 0; i <= linhas; i++) {
        ordemColuna[i] = i + 1;
        for (int j = 0; j <= colunas; j++) {
            fscanf(arquivo, "%lf", &m[i][j]);
        }
    }

    // Feche o arquivo após a leitura
    fclose(arquivo);

    // aplicando metodo de jordan
    for (int i = 0; i <= linhas; i++ ) {

        if (m[i][i] == 0) {
            int j = i + 1;
            while (j <= (colunas - 1) && m[i][j] == 0) {
                j++;
            }
            if (j <= (colunas -1)) {
                for (int x = 0; x <= (linhas); x++) {
                    int aux = m[x][j]; //valor da coluna a direita para aux
                    m[x][j] = m[x][i]; //valor da coluna atual para a direita
                    m[x][i] = aux; //valor da coluna a direita para atual
                }
                //Altera ordem da coluna
                int aux = ordemColuna[j]; 
                ordemColuna[j] = ordemColuna[i];
                ordemColuna[i] = aux;
            }
        }


        if (m[i][i] != 0) {
            for (int x = 0; x <= linhas; x++){
                if (x != i) {
                    double mult = ((- m[x][i]) / m[i][i]);
                    for (int y = 0; y <= colunas; y++) {
                        m[x][y] = m[x][y] + mult * m[i][y];
                    }

                }
            }


        } else {
            for (int x = 0; x <= (linhas); x++) {
                    m[x][i] = 0;
                }
        }
    }

    // pegando os valores dos X
    for (int i =0; i <= linhas; i++) {

        if (fabs(m[i][i]) < 1e-10 && fabs(m[i][colunas]) > 1e-10) {
            
            //printa a matriz
            for (int i = 0; i <= linhas; i++) {
                for (int j = 0; j <= colunas; j++) {
                    printf("%.2lf\t", m[i][j]);
                }
                if (i != linhas) {
                    printf("\n");
                }
            }

            printf("(SL incompatível)\n"); 
            
            //libera memória alocada.
            for (int i = 0; i < linhas; i++) {
                free(m[i]);
            }
            free(m);


            return 1;
        }
    }

    // Printa matiz com os valores de X
    for (int i = 0; i <= linhas; i++) {

        double x;
        for (int j = 0; j <= colunas; j++) {
            printf("%.2lf\t", m[i][j]);
        }

        if (fabs(m[i][i]) < 1e-10 && fabs(m[i][colunas]) < 1e-10) {
            double x = 0;
            printf("X%d = %.2lf", ordemColuna[i], x);
            printf("   (Variável livre)\n");
        } else {
            double x = m[i][colunas]/m[i][i];
            printf("X%d = %.2lf\n", ordemColuna[i], x);
        }

    }

    //libera memória alocada.
    for (int i = 0; i < linhas; i++) {
        free(m[i]);
    }
    free(m);

    return 1;

}


