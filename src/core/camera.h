#include <algebra.h>

#ifndef _tCam
#define _tCam
typedef struct tCam
{
    Vetor posicao;
    Vetor foco;
    Vetor cima;
    float **viewMatrix;
} tCamera;
#endif

#ifndef _tProj
#define _tProj
typedef struct _tProj
{
    int tipo;
    float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;
    float **projectionMatrix;
} tProj;
#endif

tCamera *criaCamera();

void defineCamera(tCamera *camera);

void rotacionaCamera(tCamera *camera, float angle, Vetor eixo);

tProj* criaProjecao(int tipo, float left, float right, float top, float bottom, float near, float far);

void defineProjecao(tProj *proj);

void desalocaCamera(tCamera *camera);

void desalocaProjecao(tProj *proj);