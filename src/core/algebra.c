#include <stdio.h>

//Ajusta valores de um matriz 4d para uma matriz identidade
void criaIdentidade4d(float **novaMatriz) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            novaMatriz[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

//Imprime uma matriz 4d no terminal
void imprimeMatriz4dDBG(float **matriz){

}

//Multiplica uma matriz 4d por um ponto
float *multMatriz4dPonto(float **matriz, float *ponto){
    float *res = (float*)malloc(4 * sizeof(float));
    for(int i=0; i<4; i++){
        res[i] = 0.0f;
        for(int j=0; j<4; j++){
            res[i] += matriz[i][j] * ponto[j];
        }
    }
    return res;
}

//Multiplica duas matrizes 4d salvando o resultado na segunda matriz
void multMatriz4d(float **matrizA, float **matrizB){

}