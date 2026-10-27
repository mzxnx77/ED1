#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdbool.h>
#include "entidade.h"

/* Tipo opaco: os campos internos só existem em inventario.c. */
typedef struct inventario Inventario;

Inventario *inventarioCriar(int capacidade);
void inventarioDestruir(Inventario *inv);

bool inventarioAdicionar(Inventario *inv, Entidade *e);
void inventarioRemover(Inventario *inv, int indice);

Entidade *inventarioObter(Inventario *inv, int indice);
int inventarioTotal(Inventario *inv);

/* Exercício 1 */
bool inventarioEstaCheio(Inventario *inv);

/* Exercício 2 */
int inventarioContarPorTipo(Inventario *inv, TipoEntidade tipo);

#endif
