#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "cliente.h"
#include "produto.h"
#include "pedido.h"

void salvarClientesCSV();
void carregarClientesCSV();

void salvarProdutosCSV();
void carregarProdutosCSV();

void salvarPedidosCSV();
void carregarPedidosCSV();

#endif
