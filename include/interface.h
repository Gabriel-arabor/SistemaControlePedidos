#ifndef INTERFACE_H
#define INTERFACE_H

#include "cliente.h"
#include "produto.h"
#include "pedido.h"

void mostrarMenuPrincipal(ListaClientes *clientes, ListaProdutos *produtos, ListaPedidos *pedidos);
void mostrarMenuClientes(ListaClientes *clientes);
void mostrarMenuProdutos(ListaProdutos *produtos);
void mostrarMenuPedidos(ListaPedidos *pedidos);

#endif
