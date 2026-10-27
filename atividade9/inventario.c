#include "inventario.h"
#include <stdlib.h>

struct inventario {
    Entidade **vetor;
    int total;
    int capacidade;
};

Inventario *inventarioCriar(int capacidade) {
    if (capacidade <= 0) return NULL;

    Inventario *inv = malloc(sizeof(*inv));
    if (inv == NULL) return NULL;

    inv->vetor = malloc((size_t)capacidade * sizeof(*inv->vetor));
    if (inv->vetor == NULL) {
        free(inv);
        return NULL;
    }

    inv->total = 0;
    inv->capacidade = capacidade;
    return inv;
}

void inventarioDestruir(Inventario *inv) {
    if (inv == NULL) return;

    for (int i = 0; i < inv->total; i++) {
        entidadeDestruir(inv->vetor[i]);
    }

    free(inv->vetor);
    free(inv);
}

bool inventarioAdicionar(Inventario *inv, Entidade *e) {
    if (inv == NULL || e == NULL || inv->total >= inv->capacidade)
        return false;

    inv->vetor[inv->total] = e;
    inv->total++;
    return true;
}

void inventarioRemover(Inventario *inv, int indice) {
    if (inv == NULL || indice < 0 || indice >= inv->total) return;

    entidadeDestruir(inv->vetor[indice]);
    inv->total--;

    if (indice < inv->total) {
        inv->vetor[indice] = inv->vetor[inv->total];
    }
    inv->vetor[inv->total] = NULL;
}

Entidade *inventarioObter(Inventario *inv, int indice) {
    if (inv == NULL || indice < 0 || indice >= inv->total) return NULL;
    return inv->vetor[indice];
}

int inventarioTotal(Inventario *inv) {
    if (inv == NULL) return 0;
    return inv->total;
}

/* Exercicio 1: verifica se o inventario esta cheio. */
bool inventarioEstaCheio(Inventario *inv) {
    if (inv == NULL) return false;
    return inv->total >= inv->capacidade;
}

/* Exercicio 2: conta quantas entidades existem de um tipo. */
int inventarioContarPorTipo(Inventario *inv, TipoEntidade tipo) {
    if (inv == NULL) return 0;

    int contador = 0;
    for (int i = 0; i < inv->total; i++) {
        Entidade *e = inv->vetor[i];
        if (e != NULL && e->tipo == tipo) {
            contador++;
        }
    }
    return contador;
}
