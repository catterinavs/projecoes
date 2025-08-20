#ifndef PROJECAO_H
#define PROJECAO_H

typedef struct {
    float left, right, top, bottom, near, far;
    float **projectionMatrix; // 4x4
} tProjecao3d;

tProjecao3d *criaProjecao();
void defineProjecao(tProjecao3d *proj, float left, float right, float top, float bottom, float near, float far);
void desalocaProjecao(tProjecao3d *proj);

#endif
