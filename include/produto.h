#ifndef PRODUTO_H
#define PRODUTO_H

#define PROD_NOME_MAX 100

typedef struct {
    int id;
    char nome[PROD_NOME_MAX];
    float preco;
    int estoque;
} Produto;

typedef struct {
    Produto *vet_produtos;
    int tamanho;
    int capacidade;
} ListaProdutos;

/* Funções */
void initProdutos(ListaProdutos *l);
void freeProdutos(ListaProdutos *l);
int carregarProdutosCSV(ListaProdutos *l, const char *path);
int salvarProdutosCSV(ListaProdutos *l, const char *path);
int adicionarProduto(ListaProdutos *l, const Produto *p);
int removerProdutoById(ListaProdutos *l, int id);
Produto *buscarProdutoById(ListaProdutos *l, int id);
void listarProdutos(ListaProdutos *l);
int nextIdProduto(ListaProdutos *l);

#endif
