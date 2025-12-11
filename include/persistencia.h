#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "cliente.h"
#include "produto.h"
#include "pedido.h"

// Funções de persistência centralizadas
int carregarClientesCSV(ListaClientes *l, const char *path);
int salvarClientesCSV(ListaClientes *l, const char *path);

int carregarProdutosCSV(ListaProdutos *l, const char *path);
int salvarProdutosCSV(ListaProdutos *l, const char *path);

int carregarPedidosCSV(ListaPedidos *l, const char *path);
int salvarPedidosCSV(ListaPedidos *l, const char *path);

#endif
