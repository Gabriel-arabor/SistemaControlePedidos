#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ensureCapacityProdutos(ListaProdutos *l) {
    if (l->size >= l->capacity) {
        int newCap = l->capacity == 0 ? 8 : l->capacity * 2;
        Produto *tmp = realloc(l->data, newCap * sizeof(Produto));
        if (!tmp) { fprintf(stderr, "ERRO: realloc produtos\n"); exit(EXIT_FAILURE); }
        l->data = tmp; l->capacity = newCap;
    }
}

void initProdutos(ListaProdutos *l) { l->data = NULL; l->size = 0; l->capacity = 0; }
void freeProdutos(ListaProdutos *l) { free(l->data); l->data = NULL; l->size = l->capacity = 0; }

int adicionarProduto(ListaProdutos *l, const Produto *p) {
    ensureCapacityProdutos(l);
    l->data[l->size++] = *p;
    return 0;
}

int removerProdutoById(ListaProdutos *l, int id) {
    for (int i=0;i<l->size;i++) {
        if (l->data[i].id == id) {
            memmove(&l->data[i], &l->data[i+1], (l->size - i -1)*sizeof(Produto));
            l->size--;
            return 0;
        }
    }
    return -1;
}

Produto *buscarProdutoById(ListaProdutos *l, int id) {
    for (int i=0;i<l->size;i++) if (l->data[i].id == id) return &l->data[i];
    return NULL;
}

void listarProdutos(ListaProdutos *l) {
    printf("=== Produtos (%d) ===\n", l->size);
    for (int i=0;i<l->size;i++) {
        Produto *p = &l->data[i];
        printf("id=%d | %s | preco=%.2f | estoque=%d\n", p->id, p->nome, p->preco, p->estoque);
    }
}

int nextIdProduto(ListaProdutos *l) {
    int mx=0;
    for (int i=0;i<l->size;i++) if (l->data[i].id>mx) mx = l->data[i].id;
    return mx+1;
}

int carregarProdutosCSV(ListaProdutos *l, const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
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

int salvarProdutosCSV(ListaProdutos *l, const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    for (int i=0;i<l->size;i++) {
        Produto *p = &l->data[i];
        fprintf(f, "%d;%s;%.2f;%d\n", p->id, p->nome, p->preco, p->estoque);
    }
    fclose(f);
    return 0;
}
