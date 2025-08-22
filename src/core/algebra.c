#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algebra.h"

float **criaIdentidade4d()
{
    float **matriz = (float **)malloc(4 * sizeof(float *));
    for (int i = 0; i < 4; i++)
    {
        matriz[i] = (float *)calloc(4, sizeof(float));
        matriz[i][i] = 1.0f;
    }

    return matriz;
}

void imprimeMatriz4dDBG(float **matriz)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%.4f ", matriz[i][j]);
        printf("\n");
    }
}

float *multMatriz4dPonto(float **matriz, float *ponto)
{
    float *resultado = (float *)calloc(4, sizeof(float));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            resultado[i] += matriz[i][j] * ponto[j];
    }

    return resultado;
}

void multMatriz4d(float **matrizA, float **matrizB)
{
    float matrizC[4][4] = {0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            matrizB[i][j] = matrizC[i][j];
    }
}

float **criaMatrizRotacao(char eixo, float angulo)
{
    float **matriz = criaIdentidade4d();
    float c = cos(angulo);
    float s = sin(angulo);

    switch (eixo)
    {
    case 'X':
        matriz[1][1] = c;
        matriz[1][2] = -s;
        matriz[2][1] = s;
        matriz[2][2] = c;
        break;
    case 'Y':
        matriz[0][0] = c;
        matriz[0][2] = s;
        matriz[2][0] = -s;
        matriz[2][2] = c;
        break;
    case 'Z':
        matriz[0][0] = c;
        matriz[0][1] = -s;
        matriz[1][0] = s;
        matriz[1][1] = c;
        break;
    }

    return matriz;
}

Vetor normaliza(Vetor v) {
    double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    if (magnitude == 0) {
        Vetor zeroVector = {0, 0, 0, 0};
        return zeroVector;
    }

    Vetor result;
    result.x = v.x / magnitude;
    result.y = v.y / magnitude;
    result.z = v.z / magnitude;

    return result;
}

Vetor somaVetor(Vetor v1, Vetor v2) {
    Vetor resultado;
    resultado.x = v1.x + v2.x;
    resultado.y = v1.y + v2.y;
    resultado.z = v1.z + v2.z;
    return resultado;
}

Vetor produtoVetorial(Vetor v1, Vetor v2) {
    Vetor result;

    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;

    return result;
}

Vetor escalaVetor(Vetor v, float escalar) {
    Vetor resultado;
    resultado.x = v.x * escalar;
    resultado.y = v.y * escalar;
    resultado.z = v.z * escalar;

    return resultado;
}

double produtoEscalar(Vetor v1, Vetor v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vetor subtraiVetor(Vetor v1, Vetor v2) {
    Vetor result;

    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;

    return result;
}

Vetor rotacionaVetor(Vetor v, Vetor eixo, float angulo)
{
    // Normaliza o eixo de rotação
    eixo = normaliza(eixo);

    // Converte o ângulo de graus para radianos
    float rad = angulo * (3.14 / 180.0f);

    Vetor parte1 = escalaVetor(v, cos(rad));
    
    Vetor parte2 = escalaVetor(produtoVetorial(eixo, v), sin(rad));
    
    Vetor parte3 = escalaVetor(eixo, produtoEscalar(eixo, v) * (1 - cos(rad)));

    Vetor resultado = somaVetor(somaVetor(parte1, parte2), parte3);

    return resultado;
}

void limpaMatriz(float **matriz)
{
    for (int i = 0; i < 4; i++)
        free(matriz[i]);
    free(matriz);
}
