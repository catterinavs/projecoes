#include <stdio.h>
#include <SDL2/SDL.h>

#ifndef tObj
#define tObj

typedef struct _tObj
{
    int nPontos;
    int nArestas;
    float **pontos;
    int **arestas;
    float **modelMatrix;
} tObjeto3d;
#endif // tObj

extern float **matrizRotacaoX, **matrizRotacaoY, **matrizRotacaoZ;
// Lê as informações de um arquivo e as carrega num novo objeto alocado
tObjeto3d *carregaObjeto(const char *nomeArquivo);

// Altera a modelMatrix de um objeto para redimenciona-lo segundo os parâmetros escalaX, escalaY e escalaZ
void escalaObjeto(tObjeto3d *objeto, float escala);

// Altera a modelMatrix de um objeto para translada-lo segundo os parâmetros transX, transY e transZ
void transladaObjeto(tObjeto3d *objeto, float transX, float transY, float transZ);

// Altera a modelMatrix de um objeto para rotaciona-lo ao redor do eixo desejado segundo o angulo informado
void rotacionaObjeto(tObjeto3d *objeto, char eixo, float angulo);

//Reseta todas as alterações feitas no objeto
void resetaObjeto(tObjeto3d* obj);

// Imprime um objeto no terminal
void imprimeObjetoDBG(tObjeto3d *objeto);

// Desaloca os objetos
void desalocaObjetos(tObjeto3d **objetos, int count);
