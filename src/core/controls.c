#include "algebra.h"
#include "camera.h"
#include "objeto.h"
#include "controls.h"

// Função para processar eventos de teclado
void processaInput(tCamera *camera, tObjeto3d *cubo)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    float speed = 0.1f;

    if (state[SDL_SCANCODE_R])
        resetaObjeto(cubo);

    if (state[SDL_SCANCODE_KP_PLUS])
        escalaObjeto(cubo, 0.02f);

    if (state[SDL_SCANCODE_KP_MINUS])
        escalaObjeto(cubo, -0.02f);

    if (state[SDL_SCANCODE_LCTRL])
    {
        if (state[SDL_SCANCODE_LEFT])
            rotacionaCamera(camera, -speed, camera->cima);

        if (state[SDL_SCANCODE_RIGHT])
            rotacionaCamera(camera, speed, camera->cima);
    }
    else
    {
        if (state[SDL_SCANCODE_W])
            moveCameraForward(camera, speed);

        if (state[SDL_SCANCODE_S]) {
            camera->posicao.z -= speed;
            camera->foco.z -= speed;
        }

        if (state[SDL_SCANCODE_A]){
            camera->posicao.z += speed;
            camera->foco.z += speed;
        }

        if (state[SDL_SCANCODE_D]) {
            camera->posicao.z -= speed;
            camera->foco.z -= speed;
        }

        if (state[SDL_SCANCODE_UP])
            camera->posicao.y += speed; // Move a câmera para cima

        if (state[SDL_SCANCODE_DOWN])
            camera->posicao.y -= speed; // Move a câmera para baixo

        if (state[SDL_SCANCODE_RIGHT])
            camera->posicao.x += speed; // Move a câmera para cima

        if (state[SDL_SCANCODE_LEFT])
            camera->posicao.x -= speed; // Move a câmera para baixo
    }

    defineCamera(camera);
}

void moveCameraForward(tCamera *camera, float speed)
{
    // Calcula a direção entre a câmera e o ponto de foco
    Vetor forward = normaliza(subtraiVetor(camera->foco, camera->posicao));

    // Move a posição e o foco da câmera na direção calculada
    camera->posicao = somaVetor(camera->posicao, escalaVetor(forward, speed));
    camera->foco = somaVetor(camera->foco, escalaVetor(forward, speed));
}

void moveCameraBackwards(tCamera *camera, float speed)
{
    camera->posicao.z -= speed;
    camera->foco.z -= speed;
}
