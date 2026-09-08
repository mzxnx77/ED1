#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA 800
#define ALTURA 600
#define TAM 40

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;

int **criarMatriz(int linhas, int colunas) {
    int **m = malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        m[i] = malloc(colunas * sizeof(int));

        for (int j = 0; j < colunas; j++) {
            m[i][j] = GetRandomValue(0, 1);
        }
    }

    return m;
}

void liberarMatriz(int **m, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(m[i]);
    }

    free(m);
}

void desenharMatriz(int **m, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if (m[i][j] == 1) {
                DrawRectangle(j * TAM, i * TAM, TAM - 2, TAM - 2,
                              (Color){20, 40, 70, 255});
            } else {
                DrawRectangle(j * TAM, i * TAM, TAM - 2, TAM - 2,
                              (Color){15, 30, 55, 255});
            }
        }
    }
}

void criarBola(Bola *b) {
    b->pos.x = GetRandomValue(30, LARGURA - 30);
    b->pos.y = GetRandomValue(30, ALTURA - 30);

    b->vel.x = GetRandomValue(-4, 4);
    b->vel.y = GetRandomValue(-4, 4);

    b->raio = GetRandomValue(10, 25);

    b->cor = (Color){
        GetRandomValue(100, 255),
        GetRandomValue(100, 255),
        GetRandomValue(100, 255),
        255
    };
}

void moverBola(Bola *b) {
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    if (b->pos.x < b->raio || b->pos.x > LARGURA - b->raio) {
        b->vel.x *= -1;
    }

    if (b->pos.y < b->raio || b->pos.y > ALTURA - b->raio) {
        b->vel.y *= -1;
    }
}

int main() {

    srand(time(NULL));

    InitWindow(LARGURA, ALTURA, "Bolas e Matriz");
    SetTargetFPS(60);

    int linhas = ALTURA / TAM;
    int colunas = LARGURA / TAM;

    int **matriz = criarMatriz(linhas, colunas);

    int quantidade = 5;

    Bola *bolas = malloc(quantidade * sizeof(Bola));

    for (int i = 0; i < quantidade; i++) {
        criarBola(&bolas[i]);
    }

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {

            quantidade++;

            bolas = realloc(bolas, quantidade * sizeof(Bola));

            criarBola(&bolas[quantidade - 1]);
        }

        if (IsKeyPressed(KEY_BACKSPACE) && quantidade > 0) {

            quantidade--;

            if (quantidade > 0) {
                bolas = realloc(bolas, quantidade * sizeof(Bola));
            } else {
                free(bolas);
                bolas = NULL;
            }
        }

        for (int i = 0; i < quantidade; i++) {
            moverBola(&bolas[i]);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        desenharMatriz(matriz, linhas, colunas);

        for (int i = 0; i < quantidade; i++) {
            DrawCircleV(bolas[i].pos, bolas[i].raio, bolas[i].cor);
        }

        DrawText(
            TextFormat("Bolas: %d", quantidade),
            10, 10, 20, WHITE
        );

        DrawText(
            "ESPACO adiciona | BACKSPACE remove",
            10, 35, 18, WHITE
        );

        EndDrawing();
    }

    free(bolas);
    liberarMatriz(matriz, linhas);

    CloseWindow();

    return 0;
}
