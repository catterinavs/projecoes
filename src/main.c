#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "objeto.h"
#include "tela.h"
#include "algebra.h"
#include "projecao.h"

//desenha um objeto na tela
void desenhaObjetoTela(SDL_Renderer *renderer, float **matrizProj, tObjeto3d *objeto){
    // Aloca espaço para os pontos projetados
    float **pontosProj = (float **)malloc(objeto->nPontos * sizeof(float*));
    for(int i=0; i<objeto->nPontos; i++) pontosProj[i] = (float*)malloc(4 * sizeof(float));

    // Para cada ponto, aplica modelMatrix e depois matrizProj
    for(int i=0; i<objeto->nPontos; i++){
        float ponto[4] = {objeto->pontos[i][0], objeto->pontos[i][1], objeto->pontos[i][2], 1.0f};
        float *pontoModel = multMatriz4dPonto(objeto->modelMatrix, ponto);
        float *pontoProj = multMatriz4dPonto(matrizProj, pontoModel);
        // Divisão por w
        for(int j=0; j<3; j++) pontosProj[i][j] = pontoProj[j] / (pontoProj[3] != 0 ? pontoProj[3] : 1.0f);
        pontosProj[i][3] = 1.0f;
        free(pontoModel);
        free(pontoProj);
    }

    // Desenha as arestas
    for(int i=0; i<objeto->nArestas; i++){
        int idx1 = objeto->arestas[i][0];
        int idx2 = objeto->arestas[i][1];
        desenhaArestaTela(renderer, pontosProj[idx1], pontosProj[idx2]);
    }

    for(int i=0; i<objeto->nPontos; i++) free(pontosProj[i]);
    free(pontosProj);
}


int main( int argc, char * argv[] ){

    if (SDL_Init( SDL_INIT_EVERYTHING) < 0){
        printf("SDL não inicializou! SDL Erro: %s\n", SDL_GetError());
    }

    SDL_Window *window = criaTela("Transformações 3D");

    if(window == NULL){
        printf("SDL não criou a janela! SDL Erro: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event windowEvent;

    tObjeto3d *obj = carregaObjeto("src/objs/cubo.txt");
    imprimeObjetoDBG(obj);

    while(true){ {

        if( SDL_PollEvent(&windowEvent)){
            if(windowEvent.type == SDL_QUIT){
                break;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //ESCREVA AQUI O SEU PROGRAMA
        // Parâmetros da projeção
        float fov = 3.1415926f / 3.0f; // 60 graus
        float aspect = 800.0f / 600.0f;
        float near = 0.1f;
        float far = 100.0f;
        float **matrizProj = (float **)malloc(4 * sizeof(float *));
        for(int i=0; i<4; i++) matrizProj[i] = (float *)malloc(4 * sizeof(float));
        criaMatrizProjecaoPerspectiva(matrizProj, fov, aspect, near, far);
        desenhaObjetoTela(renderer, matrizProj, obj);
        for(int i=0; i<4; i++) free(matrizProj[i]);
        free(matrizProj);

        SDL_RenderPresent(renderer);
    }

    desalocaTela(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}