#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Cria uma matriz de projeção perspectiva simples
void criaMatrizProjecaoPerspectiva(float **matriz, float fov, float aspect, float near, float far) {
    float f = 1.0f / tanf(fov / 2.0f);
    matriz[0][0] = f / aspect;
    matriz[0][1] = 0.0f;
    matriz[0][2] = 0.0f;
    matriz[0][3] = 0.0f;

    matriz[1][0] = 0.0f;
    matriz[1][1] = f;
    matriz[1][2] = 0.0f;
    matriz[1][3] = 0.0f;

    matriz[2][0] = 0.0f;
    matriz[2][1] = 0.0f;
    matriz[2][2] = (far + near) / (near - far);
    matriz[2][3] = (2 * far * near) / (near - far);

    matriz[3][0] = 0.0f;
    matriz[3][1] = 0.0f;
    matriz[3][2] = -1.0f;
    matriz[3][3] = 0.0f;
}
