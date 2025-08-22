#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "objeto.h"
#include "algebra.h"

tObjeto3d *carregaObjeto(const char *nomeArquivo)
{
    FILE *arquivoObj = fopen(nomeArquivo, "r");
    if (!arquivoObj)
    {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    tObjeto3d *novoObjeto = (tObjeto3d *)malloc(sizeof(tObjeto3d));
    fscanf(arquivoObj, "%d", &(novoObjeto->nPontos));

    novoObjeto->pontos = (float **)malloc(novoObjeto->nPontos * sizeof(float *));
    for (int i = 0; i < novoObjeto->nPontos; i++)
    {
        novoObjeto->pontos[i] = (float *)malloc(4 * sizeof(float));
        fscanf(arquivoObj, "%f %f %f", &(novoObjeto->pontos[i][0]), &(novoObjeto->pontos[i][1]), &(novoObjeto->pontos[i][2]));
        novoObjeto->pontos[i][3] = 1;
    }

    fscanf(arquivoObj, "%d", &(novoObjeto->nArestas));
    novoObjeto->arestas = (int **)malloc(novoObjeto->nArestas * sizeof(int *));
    for (int i = 0; i < novoObjeto->nArestas; i++)
    {
        novoObjeto->arestas[i] = (int *)malloc(2 * sizeof(int));
        fscanf(arquivoObj, "%d %d", &(novoObjeto->arestas[i][0]), &(novoObjeto->arestas[i][1]));
    }

    novoObjeto->modelMatrix = criaIdentidade4d();
    fclose(arquivoObj);
    return novoObjeto;
}

void escalaObjeto(tObjeto3d *objeto, float scale)
{
    static float escala = 1.0;

    if (scale == 1.0)
    {
        escala = 1.0;
        return;
    }

    if (escala < 0.1 && scale < 0)
        return;
    if (escala > 1.5 && scale > 0)
        return;

    escala += scale;

    float **matrizEscala = criaIdentidade4d();

    matrizEscala[0][0] = 1 + scale;
    matrizEscala[1][1] = 1 + scale;
    matrizEscala[2][2] = 1 + scale;

    multMatriz4d(matrizEscala, objeto->modelMatrix);
    limpaMatriz(matrizEscala);
}

void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ)
{
    float **matrizTranslacao = criaIdentidade4d();

    matrizTranslacao[0][3] += transX;
    matrizTranslacao[1][3] += transY;
    matrizTranslacao[2][3] += transZ;

    multMatriz4d(matrizTranslacao, objeto->modelMatrix);
}

void rotacionaObjeto(tObjeto3d *objeto, char eixo, float angulo)
{
    float **matrizRotacao = criaMatrizRotacao(eixo, angulo * M_PI / 180.0);
    multMatriz4d(matrizRotacao, objeto->modelMatrix);
    limpaMatriz(matrizRotacao);
}

void resetaObjeto(tObjeto3d *obj)
{
    limpaMatriz(obj->modelMatrix);
    obj->modelMatrix = criaIdentidade4d();
}

void imprimeObjetoDBG(tObjeto3d *objeto)
{
    if (!objeto)
    {
        printf("ERRO: Objeto nulo!\n");
        return;
    }

    printf("Pontos:\n");
    for (int i = 0; i < objeto->nPontos; i++)
        printf(" [%d] - (%8.4f, %8.4f, %8.4f)\n", i + 1, objeto->pontos[i][0], objeto->pontos[i][1], objeto->pontos[i][2]);

    printf("Arestas\n");
    for (int i = 0; i < objeto->nArestas; i++)
        printf(" [%d] - (%3d, %3d)\n", i + 1, objeto->arestas[i][0], objeto->arestas[i][1]);
}

void desalocaObjetos(tObjeto3d **objetos, int count)
{
    if (!objetos)
    {
        perror("Erro: array de objetos nulo");
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        if (objetos[i]) // Check if the object is not null
        {
            for (int i = 0; i < objetos[i]->nPontos; i++)
                free(objetos[i]->pontos[i]);
            free(objetos[i]->pontos);

            for (int i = 0; i < objetos[i]->nArestas; i++)
                free(objetos[i]->arestas[i]);
            free(objetos[i]->arestas);

            limpaMatriz(objetos[i]->modelMatrix);
            free(objetos[i]);
        }
    }

    free(objetos); // Free the array of pointers
}