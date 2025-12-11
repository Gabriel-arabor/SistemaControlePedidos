#include <stdio.h>
#include <stdlib.h>

#include "cliente.h"
#include "produto.h"
#include "pedido.h"
#include "interface.h"

int main(void) {
    ListaClientes clientes;
    ListaProdutos produtos;
    ListaPedidos pedidos;

    initClientes(&clientes);
    initProdutos(&produtos);
    initPedidos(&pedidos);

    carregarClientesCSV(&clientes, "data/Clientes.csv");
    carregarProdutosCSV(&produtos, "data/Produtos.csv");
    carregarPedidosCSV(&pedidos, "data/Pedidos.csv");

    mostrarMenuPrincipal(&clientes, &produtos, &pedidos);

    /* ao sair, salvar tudo */
    salvarClientesCSV(&clientes, "data/Clientes.csv");
    salvarProdutosCSV(&produtos, "data/Produtos.csv");
    salvarPedidosCSV(&pedidos, "data/Pedidos.csv");

    freeClientes(&clientes);
    freeProdutos(&produtos);
    freePedidos(&pedidos);
    return 0;
}
