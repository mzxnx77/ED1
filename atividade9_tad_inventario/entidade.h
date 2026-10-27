#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "raylib.h"
#include <stdbool.h>

typedef enum {
    ENTIDADE_JOGADOR,
    ENTIDADE_INIMIGO,
    ENTIDADE_ITEM
} TipoEntidade;

/* A struct Entidade é visível: este é um módulo comum, não um TAD opaco. */
typedef struct {
    TipoEntidade tipo;
    Rectangle area;
    Color cor;
    float velocidade;
    int vida;
} Entidade;

Entidade *entidadeCriar(TipoEntidade tipo, float x, float y);
bool entidadeColidiu(const Entidade *a, const Entidade *b);
void entidadeDesenhar(const Entidade *e);
void entidadeDestruir(Entidade *e);

#endif
