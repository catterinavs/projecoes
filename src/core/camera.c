#include <stdlib.h>
#include "algebra.h"
#include "camera.h"

tCamera *criaCamera()
{
    tCamera *camera = (tCamera *)malloc(sizeof(tCamera));

    camera->posicao.x = 0.0;
    camera->posicao.y = 0.0;
    camera->posicao.z = 1.0;

    camera->foco.x = 0.0;
    camera->foco.y = 0.0;
    camera->foco.z = 0.0;

    camera->cima.x = 0.0;
    camera->cima.y = 1.0;
    camera->cima.z = 0.0;

    camera->viewMatrix = criaIdentidade4d();

    defineCamera(camera);

    return camera;
}

void defineCamera(tCamera *camera)
{
    Vetor forward = normaliza(subtraiVetor(camera->foco, camera->posicao));
    Vetor right = normaliza(produtoVetorial(forward, camera->cima));
    Vetor up = produtoVetorial(right, forward); // Já está normalizado

    camera->viewMatrix[0][0] = right.x;
    camera->viewMatrix[0][1] = right.y;
    camera->viewMatrix[0][2] = right.z;
    camera->viewMatrix[0][3] = -produtoEscalar(right, camera->posicao);

    camera->viewMatrix[1][0] = up.x;
    camera->viewMatrix[1][1] = up.y;
    camera->viewMatrix[1][2] = up.z;
    camera->viewMatrix[1][3] = -produtoEscalar(up, camera->posicao);

    camera->viewMatrix[2][0] = -forward.x;
    camera->viewMatrix[2][1] = -forward.y;
    camera->viewMatrix[2][2] = -forward.z;
    camera->viewMatrix[2][3] = produtoEscalar(forward, camera->posicao);

    camera->viewMatrix[3][0] = 0;
    camera->viewMatrix[3][1] = 0;
    camera->viewMatrix[3][2] = 0;
    camera->viewMatrix[3][3] = 1;
}

void rotacionaCamera(tCamera *camera, float angle, Vetor eixo)
{
    // Get the direction vector (focus - position)
    Vetor direcao = subtraiVetor(camera->foco, camera->posicao);
    
    // Rotate the direction vector around the specified axis (e.g., camera->cima)
    direcao = rotacionaVetor(direcao, eixo, angle);
    
    // Update the camera's focus point
    camera->foco = somaVetor(camera->posicao, direcao);
}

tProj *criaProjecao(int tipo, float left, float right, float top, float bottom, float near, float far)
{
    tProj *proj = (tProj *)malloc(sizeof(tProj));

    proj->tipo = tipo;
    proj->left = left;
    proj->right = right;
    proj->top = top;
    proj->bottom = bottom;
    proj->near = near;
    proj->far = far;

    proj->projectionMatrix = (float **)malloc(4 * sizeof(float *));
    for (int i = 0; i < 4; i++)
    {
        proj->projectionMatrix[i] = (float *)malloc(4 * sizeof(float));
    }

    defineProjecao(proj);

    return proj;
}

void defineProjecao(tProj *proj)
{
    if (proj == NULL || proj->projectionMatrix == NULL)
        return;

    float left = proj->left;
    float right = proj->right;
    float top = proj->top;
    float bottom = proj->bottom;
    float near = proj->near;
    float far = proj->far;

    proj->projectionMatrix[0][0] = (2.0f * near) / (right - left);
    proj->projectionMatrix[0][1] = 0.0f;
    proj->projectionMatrix[0][2] = (right + left) / (right - left);
    proj->projectionMatrix[0][3] = 0.0f;

    proj->projectionMatrix[1][0] = 0.0f;
    proj->projectionMatrix[1][1] = (2.0f * near) / (top - bottom);
    proj->projectionMatrix[1][2] = (top + bottom) / (top - bottom);
    proj->projectionMatrix[1][3] = 0.0f;

    proj->projectionMatrix[2][0] = 0.0f;
    proj->projectionMatrix[2][1] = 0.0f;
    proj->projectionMatrix[2][2] = -(far + near) / (far - near);
    proj->projectionMatrix[2][3] = -(2.0f * far * near) / (far - near);

    proj->projectionMatrix[3][0] = 0.0f;
    proj->projectionMatrix[3][1] = 0.0f;
    proj->projectionMatrix[3][2] = -1.0f;
    proj->projectionMatrix[3][3] = 0.0f;
}

void desalocaCamera(tCamera *camera)
{
    if (camera == NULL)
        return;

    limpaMatriz(camera->viewMatrix);
    free(camera);
}

void desalocaProjecao(tProj *proj)
{
    if (proj == NULL)
        return;

    limpaMatriz(proj->projectionMatrix);

    free(proj);
}