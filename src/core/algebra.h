#include <stdio.h>

#ifndef _Vetor
#define _Vetor
typedef struct Vetor
{
    float x;
    float y;
    float z;
    float w;
} Vetor;
#endif

// Ajusta valores de um matriz 4d para uma matriz identidade
float **criaIdentidade4d();

// Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz);

// Multiplica uma matriz 4d por um ponto
float *multMatriz4dPonto(float **matriz, float *ponto);

// Multiplica duas matrizes 4d salvando o resultado na segunda matriz
void multMatriz4d(float **matrizA, float **matrizB);

float **criaMatrizRotacao(char eixo, float angulo);

Vetor normaliza(Vetor v);

Vetor somaVetor(Vetor v1, Vetor v2);

Vetor produtoVetorial(Vetor v1, Vetor v2);

Vetor escalaVetor(Vetor v, float escalar);

double produtoEscalar(Vetor v1, Vetor v2);

Vetor subtraiVetor(Vetor v1, Vetor v2);

Vetor rotacionaVetor(Vetor v, Vetor eixo, float angulo);

void limpaMatriz(float **matriz);