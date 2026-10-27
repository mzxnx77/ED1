#include "entidade.h"
#include <stdlib.h>

Entidade *entidadeCriar(TipoEntidade tipo, float x, float y) {
    Entidade *e = malloc(sizeof(*e));
    if (e == NULL) {
        return NULL;
    }

    e->tipo = tipo;
    e->area.x = x;
    e->area.y = y;
    e->vida = 1;

    switch (tipo) {
        case ENTIDADE_JOGADOR:
            e->area.width = 34;
            e->area.height = 42;
            e->cor = BLUE;
            e->velocidade = 250.0f;
            e->vida = 3;
            break;
        case ENTIDADE_INIMIGO:
            e->area.width = 32;
            e->area.height = 32;
            e->cor = RED;
            e->velocidade = 0.0f;
            break;
        case ENTIDADE_ITEM:
            e->area.width = 18;
            e->area.height = 18;
            e->cor = GOLD;
            e->velocidade = 0.0f;
            break;
        default:
            free(e);
            return NULL;
    }

    return e;
}

bool entidadeColidiu(const Entidade *a, const Entidade *b) {
    if (a == NULL || b == NULL) {
        return false;
    }

    return CheckCollisionRecs(a->area, b->area);
}

void entidadeDesenhar(const Entidade *e) {
    if (e == NULL) {
        return;
    }

    if (e->tipo == ENTIDADE_ITEM) {
        DrawCircle(
            (int)(e->area.x + e->area.width / 2),
            (int)(e->area.y + e->area.height / 2),
            e->area.width / 2,
            e->cor
        );
    } else {
        DrawRectangleRec(e->area, e->cor);
        DrawRectangleLinesEx(e->area, 2.0f, DARKGRAY);
    }
}

void entidadeDestruir(Entidade *e) {
    free(e);
}
