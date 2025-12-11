#include "pedido.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void testeDeCapacidadeListaPedidos(ListaPedidos *l) 
{
    if (l->tamanho >= l->capacidade) 
    {
        int novoTamanho = l->capacidade == 0 ? 8 : l->capacidade * 2;
        Pedido *tmp = realloc(l->lista_pedidos, novoTamanho * sizeof(Pedido));
        if (!tmp) { fprintf(stderr, "ERRO: realloc pedidos\n"); exit(EXIT_FAILURE); }
        l->lista_pedidos = tmp; l->capacidade = novoTamanho;
    }
}

void initPedidos(ListaPedidos *l) { l->lista_pedidos = NULL; l->tamanho = 0; l->capacidade = 0; }
void freePedidos(ListaPedidos *l) { free(l->lista_pedidos); l->lista_pedidos = NULL; l->tamanho = l->capacidade = 0; }

int adicionarPedido(ListaPedidos *l, const Pedido *p) 
{
    testeDeCapacidadeListaPedidos(l);
    l->lista_pedidos[l->tamanho++] = *p;
    return 0;
}

int removerPedidoById(ListaPedidos *l, int id) 
{
    for (int i=0;i<l->tamanho;i++) {
        if (l->lista_pedidos[i].id == id) 
        {
            memmove(&l->lista_pedidos[i], &l->lista_pedidos[i+1], (l->tamanho - i -1)*sizeof(Pedido));
            l->tamanho--;
            return 0;
        }
    }
    return -1;
}

Pedido *buscarPedidoById(ListaPedidos *l, int id) 
{
    for (int i=0;i<l->tamanho;i++) if (l->lista_pedidos[i].id==id) return &l->lista_pedidos[i];
    return NULL;
}

void listarPedidos(ListaPedidos *l) 
{
    printf("=== Pedidos (%d) ===\n", l->tamanho);
    for (int i=0;i<l->tamanho;i++) 
    {
        Pedido *p = &l->lista_pedidos[i];
        printf("id=%d | clienteId=%d | itens=%d | status=%s | total=%.2f\n",
               p->id, p->clienteId, p->qtdItens, p->status, p->total);
    }
}

float calcularTotalPedido(const Pedido *p, ListaProdutos *produtos) 
{
    float total = 0.0f;
    for (int i=0;i<p->qtdItens;i++) 
    {
        int pid = p->itens[i].produtoId;
        int qtd = p->itens[i].quantidade;
        Produto *prod = buscarProdutoById(produtos, pid);
        if (prod) total += prod->preco * qtd;
    }
    return total;
}

int carregarPedidosCSV(ListaPedidos *l, const char *path) 
{
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char line[2048];
    while (fgets(line, sizeof(line), f)) 
    {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0]==0) continue;
        char *p = line;
        char *tok = strtok(p, ";");
        if (!tok) continue;
        Pedido ped;
        ped.id = atoi(tok);

        tok = strtok(NULL, ";"); if (!tok) continue;
        ped.clienteId = atoi(tok);

        tok = strtok(NULL, ";"); if (!tok) continue;
        // parse itens
        ped.qtdItens = 0;
        char *items = tok;
        char *it = strtok(items, ",");
        while (it && ped.qtdItens < MAX_ITENS_PEDIDO) 
        {
            char *a = strtok(it, ":");
            char *b = strtok(NULL, ":");
            if (a && b) 
            {
                ped.itens[ped.qtdItens].produtoId = atoi(a);
                ped.itens[ped.qtdItens].quantidade = atoi(b);
                ped.qtdItens++;
            }
            it = strtok(NULL, ",");
        }

        tok = strtok(NULL, ";");
        if (tok) 
        {
            strncpy(ped.status, tok, STATUS_MAX-1);
            ped.status[STATUS_MAX-1]=0;
        } else ped.status[0]=0;

        ped.total = 0.0f; // será calculado quando necessário
        adicionarPedido(l, &ped);
    }
    fclose(f);
    return 0;
}

int salvarPedidosCSV(ListaPedidos *l, const char *path) 
{
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    for (int i=0;i<l->tamanho;i++) 
    {
        Pedido *p = &l->lista_pedidos[i];
        fprintf(f, "%d;%d;", p->id, p->clienteId);
        for (int j=0;j<p->qtdItens;j++) 
        {
            fprintf(f, "%d:%d", p->itens[j].produtoId, p->itens[j].quantidade);
            if (j < p->qtdItens-1) fprintf(f, ",");
        }
        fprintf(f, ";%s\n", p->status);
    }
    fclose(f);
    return 0;
}
