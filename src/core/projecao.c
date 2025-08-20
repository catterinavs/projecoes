#include <stdlib.h>
#include <math.h>
#include "projecao.h"
#include "algebra.h"

tProjecao3d *criaProjecao() {
    tProjecao3d *proj = (tProjecao3d*)malloc(sizeof(tProjecao3d));
    proj->projectionMatrix = (float**)malloc(4 * sizeof(float*));
    for(int i=0;i<4;i++) proj->projectionMatrix[i] = (float*)calloc(4, sizeof(float));
    criaIdentidade4d(proj->projectionMatrix);
    return proj;
}

void defineProjecao(tProjecao3d *proj, float left, float right, float top, float bottom, float near, float far) {
    proj->left = left; proj->right = right; proj->top = top; proj->bottom = bottom; proj->near = near; proj->far = far;
    float **m = proj->projectionMatrix;
    // Matriz de projeção perspectiva (frustum)
    m[0][0] = (2*near)/(right-left);
    m[0][1] = 0;
    m[0][2] = (right+left)/(right-left);
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = (2*near)/(top-bottom);
    m[1][2] = (top+bottom)/(top-bottom);
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = -(far+near)/(far-near);
    m[2][3] = -(2*far*near)/(far-near);
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = -1;
    m[3][3] = 0;
}

void desalocaProjecao(tProjecao3d *proj) {
    if(!proj) return;
    for(int i=0;i<4;i++) free(proj->projectionMatrix[i]);
    free(proj->projectionMatrix);
    free(proj);
}
