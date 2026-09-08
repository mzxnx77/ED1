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
    int **matriz = malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        matriz[i] = malloc(colunas * sizeof(int));

        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }

    free(matriz);
}

void desenharMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if (matriz[i][j] == 1) {
                DrawRectangle(
                    j * TAM,
                    i * TAM,
                    TAM,
                    TAM,
                    LIGHTGRAY
                );
            }

            DrawRectangleLines(
                j * TAM,
                i * TAM,
                TAM,
                TAM,
                DARKGRAY
            );
        }
    }
}

void criarBola(Bola *b) {
    b->pos.x = GetRandomValue(50, LARGURA - 50);
    b->pos.y = GetRandomValue(50, ALTURA - 50);

    b->vel.x = GetRandomValue(-3, 3);
    b->vel.y = GetRandomValue(-3, 3);

    b->raio = 10;
    b->cor = RED;
}

void atualizarBola(Bola *b) {
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    if (b->pos.x - b->raio < 0 ||
        b->pos.x + b->raio > LARGURA) {
        b->vel.x *= -1;
    }

    if (b->pos.y - b->raio < 0 ||
        b->pos.y + b->raio > ALTURA) {
        b->vel.y *= -1;
    }
}

int main() {

    InitWindow(LARGURA, ALTURA, "Atividade 2");
    SetTargetFPS(60);

    srand(time(NULL));

    int linhas = ALTURA / TAM;
    int colunas = LARGURA / TAM;

    int **matriz = criarMatriz(linhas, colunas);

    int quantidadeBolas = 12;

    Bola *bolas = malloc(quantidadeBolas * sizeof(Bola));

    for (int i = 0; i < quantidadeBolas; i++) {
        criarBola(&bolas[i]);
    }

    while (!WindowShouldClose()) {

        for (int i = 0; i < quantidadeBolas; i++) {

            atualizarBola(&bolas[i]);

            int coluna = bolas[i].pos.x / TAM;
            int linha = bolas[i].pos.y / TAM;

            if (linha >= 0 && linha < linhas &&
                coluna >= 0 && coluna < colunas) {

                matriz[linha][coluna] = 1;
            }
        }

        int visitadas = 0;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {

                if (matriz[i][j] == 1) {
                    visitadas++;
                }
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        desenharMatriz(matriz, linhas, colunas);

        for (int i = 0; i < quantidadeBolas; i++) {
            DrawCircleV(
                bolas[i].pos,
                bolas[i].raio,
                bolas[i].cor
            );
        }

        DrawText(
            TextFormat("Celulas visitadas: %d", visitadas),
            10, 10, 20, WHITE
        );

        DrawText(
            "Pressione ESC para sair",
            10, 35, 20, WHITE
        );

        EndDrawing();
    }

    free(bolas);

    liberarMatriz(matriz, linhas);

    CloseWindow();

    return 0;
}
