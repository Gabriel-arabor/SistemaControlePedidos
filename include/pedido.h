#ifndef PEDIDO_H
#define PEDIDO_H

#include "cliente.h"
#include "produto.h"

typedef struct 
{
    int idPedido;
    Cliente cliente;
    Produto produtos[20];
    int qtdProdutos;
} Pedido;

void inserirPedido();
void listarPedidos();
void detalharPedido();

#endif
