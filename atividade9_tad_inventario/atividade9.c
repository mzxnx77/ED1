#include "raylib.h"
#include "entidade.h"
#include "inventario.h"

#include <stdio.h>
#include <stdbool.h>

#define LARGURA_TELA 1000
#define ALTURA_TELA 650
#define CAPACIDADE_INVENTARIO 32

static bool adicionarEntidade(Inventario *inv, TipoEntidade tipo,
                              float x, float y) {
    Entidade *e = entidadeCriar(tipo, x, y);
    if (e == NULL) {
        return false;
    }

    if (!inventarioAdicionar(inv, e)) {
        entidadeDestruir(e);
        return false;
    }

    return true;
}

int main(void) {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Exercicio 9 - TAD Inventario Opaco");
    SetTargetFPS(60);

    Inventario *inventario = inventarioCriar(CAPACIDADE_INVENTARIO);
    if (inventario == NULL) {
        CloseWindow();
        return 1;
    }

    /* O jogador é colocado no índice zero. */
    if (!adicionarEntidade(inventario, ENTIDADE_JOGADOR, 80, 300)) {
        inventarioDestruir(inventario);
        CloseWindow();
        return 1;
    }

    /* Cria inimigos e itens de exemplo. */
    const Vector2 posInimigos[] = {
        {300, 120}, {470, 210}, {680, 120},
        {820, 350}, {540, 470}, {260, 500}
    };

    const Vector2 posItens[] = {
        {190, 130}, {390, 350}, {600, 300},
        {760, 200}, {870, 520}, {120, 520},
        {700, 480}, {420, 100}
    };

    for (int i = 0; i < (int)(sizeof(posInimigos) / sizeof(posInimigos[0])); i++) {
        if (!adicionarEntidade(inventario, ENTIDADE_INIMIGO,
                               posInimigos[i].x, posInimigos[i].y)) {
            inventarioDestruir(inventario);
            CloseWindow();
            return 1;
        }
    }

    for (int i = 0; i < (int)(sizeof(posItens) / sizeof(posItens[0])); i++) {
        if (!adicionarEntidade(inventario, ENTIDADE_ITEM,
                               posItens[i].x, posItens[i].y)) {
            inventarioDestruir(inventario);
            CloseWindow();
            return 1;
        }
    }

    int pontuacao = 0;
    int vidas = 3;
    bool fimDeJogo = false;
    char textoItens[80];
    char textoPontuacao[80];
    char textoVidas[80];
    char textoTotal[80];

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Entidade *jogador = inventarioObter(inventario, 0);

        if (!fimDeJogo && jogador != NULL) {
            float dx = 0.0f;
            float dy = 0.0f;

            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dx -= 1.0f;
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += 1.0f;
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dy -= 1.0f;
            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dy += 1.0f;

            /* Normaliza movimento diagonal para não andar mais rápido. */
            if (dx != 0.0f && dy != 0.0f) {
                dx *= 0.70710678f;
                dy *= 0.70710678f;
            }

            jogador->area.x += dx * jogador->velocidade * dt;
            jogador->area.y += dy * jogador->velocidade * dt;

            if (jogador->area.x < 0) jogador->area.x = 0;
            if (jogador->area.y < 70) jogador->area.y = 70;
            if (jogador->area.x + jogador->area.width > LARGURA_TELA)
                jogador->area.x = LARGURA_TELA - jogador->area.width;
            if (jogador->area.y + jogador->area.height > ALTURA_TELA)
                jogador->area.y = ALTURA_TELA - jogador->area.height;

            /* Percorre pela interface pública. A remoção troca pelo último,
               por isso o índice só avança quando não há remoção. */
            int i = 1;
            while (i < inventarioTotal(inventario)) {
                Entidade *e = inventarioObter(inventario, i);

                if (e != NULL && entidadeColidiu(jogador, e)) {
                    if (e->tipo == ENTIDADE_ITEM) {
                        pontuacao += 10;
                        inventarioRemover(inventario, i);
                        continue;
                    }

                    if (e->tipo == ENTIDADE_INIMIGO) {
                        vidas--;
                        inventarioRemover(inventario, i);
                        if (vidas <= 0) {
                            fimDeJogo = true;
                        }
                        continue;
                    }
                }

                i++;
            }
        }

        int itensRestantes =
            inventarioContarPorTipo(inventario, ENTIDADE_ITEM);

        snprintf(textoItens, sizeof(textoItens),
                 "Itens restantes: %d", itensRestantes);
        snprintf(textoPontuacao, sizeof(textoPontuacao),
                 "Pontos: %d", pontuacao);
        snprintf(textoVidas, sizeof(textoVidas),
                 "Vidas: %d", vidas);
        snprintf(textoTotal, sizeof(textoTotal),
                 "Entidades no inventario: %d", inventarioTotal(inventario));

        BeginDrawing();
        ClearBackground((Color){24, 28, 38, 255});

        DrawRectangle(0, 0, LARGURA_TELA, 60, (Color){15, 18, 26, 255});
        DrawText("EXERCICIO 9 - TAD: INVENTARIO OPACO", 20, 10, 24, RAYWHITE);
        DrawText("Mover: WASD ou setas | Colete os itens dourados", 20, 38, 15, LIGHTGRAY);

        /* O main acessa entidades por inventarioObter, nunca os campos
           internos do Inventario. */
        for (int i = 0; i < inventarioTotal(inventario); i++) {
            entidadeDesenhar(inventarioObter(inventario, i));
        }

        DrawText(textoItens, 20, 75, 20, GOLD);
        DrawText(textoPontuacao, 20, 100, 20, RAYWHITE);
        DrawText(textoVidas, 20, 125, 20, RED);
        DrawText(textoTotal, 20, 150, 18, LIGHTGRAY);

        /* Exercício 1: aviso usando apenas a interface pública. */
        if (inventarioEstaCheio(inventario)) {
            DrawRectangle(280, 75, 440, 42, MAROON);
            DrawText("AVISO: INVENTARIO CHEIO!", 300, 85, 22, RAYWHITE);
        }

        if (fimDeJogo) {
            DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA,
                          (Color){0, 0, 0, 190});
            DrawText("FIM DE JOGO", 350, 260, 42, RED);
            DrawText("Feche a janela para sair.", 365, 320, 22, RAYWHITE);
        } else if (itensRestantes == 0) {
            DrawText("Todos os itens foram coletados!", 300, 610, 22, GREEN);
        }

        EndDrawing();
    }

    inventarioDestruir(inventario);
    CloseWindow();
    return 0;
}
