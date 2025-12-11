#ifndef PEDIDO_H
#define PEDIDO_H

#include "produto.h"

#define STATUS_MAX 32
#define MAX_ITENS_PEDIDO 64

typedef struct {
    int produtoId;
    int quantidade;
} ItemPedido;

typedef struct {
    int id;
    int clienteId;
    ItemPedido itens[MAX_ITENS_PEDIDO];
    int qtdItens;
    char status[STATUS_MAX];
    float total;
} Pedido;

typedef struct {
    Pedido *lista_pedidos;
    int tamanho;
    int capacidade;
} ListaPedidos;

/* Funções */
void initPedidos(ListaPedidos *l);
void freePedidos(ListaPedidos *l);
int carregarPedidosCSV(ListaPedidos *l, const char *path);
int salvarPedidosCSV(ListaPedidos *l, const char *path);
int adicionarPedido(ListaPedidos *l, const Pedido *p);
int removerPedidoById(ListaPedidos *l, int id);
Pedido *buscarPedidoById(ListaPedidos *l, int id);
void listarPedidos(ListaPedidos *l);

/* Auxiliar */
float calcularTotalPedido(const Pedido *p, ListaProdutos *produtos);

#endif
