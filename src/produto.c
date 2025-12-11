#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ensureCapacityProdutos(ListaProdutos *l) 
{
    if (l->tamanho >= l->capacidade) 
    {
        int novoTamanho = l->capacidade == 0 ? 8 : l->capacidade * 2;
        Produto *tmp = realloc(l->vet_produtos, novoTamanho * sizeof(Produto));
        if (!tmp) { fprintf(stderr, "ERRO: realloc produtos\n"); exit(EXIT_FAILURE); }
        l->vet_produtos = tmp; l->capacidade = novoTamanho;
    }
}

void initProdutos(ListaProdutos *l) { l->vet_produtos = NULL; l->tamanho = 0; l->capacidade = 0; }
void freeProdutos(ListaProdutos *l) { free(l->vet_produtos); l->vet_produtos = NULL; l->tamanho = l->capacidade = 0; }

int adicionarProduto(ListaProdutos *l, const Produto *p) 
{
    ensureCapacityProdutos(l);
    l->vet_produtos[l->tamanho++] = *p;
    return 0;
}

int removerProdutoById(ListaProdutos *l, int id) 
{
    for (int i=0;i<l->tamanho;i++) {
        if (l->vet_produtos[i].id == id) 
        {
            memmove(&l->vet_produtos[i], &l->vet_produtos[i+1], (l->tamanho - i -1)*sizeof(Produto));
            l->tamanho--;
            return 0;
        }
    }
    return -1;
}

Produto *buscarProdutoById(ListaProdutos *l, int id) 
{
    for (int i=0;i<l->tamanho;i++) if (l->vet_produtos[i].id == id) return &l->vet_produtos[i];
    return NULL;
}

void listarProdutos(ListaProdutos *l) 
{
    printf("=== Produtos (%d) ===\n", l->tamanho);
    for (int i=0;i<l->tamanho;i++) 
    {
        Produto *p = &l->vet_produtos[i];
        printf("id=%d | %s | preco=%.2f | estoque=%d\n", p->id, p->nome, p->preco, p->estoque);
    }
}

int nextIdProduto(ListaProdutos *l) 
{
    int mx=0;
    for (int i=0;i<l->tamanho;i++) if (l->vet_produtos[i].id>mx) mx = l->vet_produtos[i].id;
    return mx+1;
}

int carregarProdutosCSV(ListaProdutos *l, const char *path) 
{
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char line[512];
    while (fgets(line, sizeof(line), f)) 
    {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0]==0) continue;
        char *tok = strtok(line, ";");
        Produto p;
        if (!tok) continue;
        p.id = atoi(tok);
        tok = strtok(NULL, ";"); if (!tok) continue;
        strncpy(p.nome, tok, PROD_NOME_MAX-1); p.nome[PROD_NOME_MAX-1]=0;
        tok = strtok(NULL, ";"); if (!tok) p.preco = 0.0f; else p.preco = atof(tok);
        tok = strtok(NULL, ";"); if (!tok) p.estoque = 0; else p.estoque = atoi(tok);
        adicionarProduto(l, &p);
    }
    fclose(f);
    return 0;
}

int salvarProdutosCSV(ListaProdutos *l, const char *path) 
{
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    for (int i=0;i<l->tamanho;i++) 
    {
        Produto *p = &l->vet_produtos[i];
        fprintf(f, "%d;%s;%.2f;%d\n", p->id, p->nome, p->preco, p->estoque);
    }
    fclose(f);
    return 0;
}
