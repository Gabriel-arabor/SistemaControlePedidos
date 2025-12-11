#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void teste_de_capacidade_lista_clientes(ListaClientes *l) //testa a capacidade para ver se há lugar no vetor.
{
    if (l->quantos_existem >= l->capacidade) 
    {
        int novoTamanho = l->capacidade == 0 ? 8 : l->capacidade * 2;
        Cliente *tmp = realloc(l->vet_clientes, novoTamanho * sizeof(Cliente));
        if (!tmp) 
        {
            fprintf(stderr, "ERRO: realloc clientes\n");
            exit(EXIT_FAILURE);
        }
        l->vet_clientes = tmp;
        l->capacidade = novoTamanho;
    }
}

void initClientes(ListaClientes *l) //função para inicializar a lista vazia
{
    l->vet_clientes = NULL;
    l->quantos_existem = 0;
    l->capacidade = 0;
}

void freeClientes(ListaClientes *l) //liberar a memória usada pela lista ao final do prog
{
    free(l->vet_clientes);
    l->vet_clientes = NULL;
    l->quantos_existem = 0;
    l->capacidade = 0;
}

int adicionarCliente(ListaClientes *l, const Cliente *c) //adiciona o cliente na próxima posição
{
    teste_de_capacidade_lista_clientes(l);
    l->vet_clientes[l->quantos_existem++] = *c;
    return 0;
}

int removerClienteById(ListaClientes *l, int id) //recebe a lista do vetor e o id e faz a remoção
{
    for (int i = 0; i < l->quantos_existem; ++i) 
    {
        if (l->vet_clientes[i].id == id) //achou??
        {
            //a lista n pode ter buracos
            memmove(&l->vet_clientes[i], &l->vet_clientes[i+1], (l->quantos_existem - i - 1) * sizeof(Cliente));
            //algo como:
            //for (int j = i; j < l->qtd - 1; j++) 
            //{
                //l->vet_clientes[j] = l->vet_clientes[j + 1];
            //}

            l->quantos_existem--;
            return 0;
        }
    }
    return -1; //não achou
}

Cliente *buscarClienteById(ListaClientes *l, int id) 
{
    for (int i = 0; i < l->quantos_existem; ++i) 
    {
        if (l->vet_clientes[i].id == id) return &l->vet_clientes[i];
    }
    return NULL;
}

void listarClientes(ListaClientes *l) //servia antes do ncurses 
{
    printf("=== Lista de Clientes (%d) ===\n", l->quantos_existem);
    for (int i = 0; i < l->quantos_existem; ++i) 
    {
        Cliente *c = &l->vet_clientes[i];
        printf("id=%d | nome=\"%s\" | cpf=%s | tel=%s\n", c->id, c->nome, c->cpf, c->telefone);
    }
}

/* retorna próximo id (max + 1) */
int ProximoIdCliente(ListaClientes *l) //entrega sempre o proximo id usado
{
    int mx = 0;
    for (int i = 0; i < l->quantos_existem; ++i) if (l->vet_clientes[i].id > mx) mx = l->vet_clientes[i].id;
    return mx + 1;
}

int carregarClientesCSV(ListaClientes *l, const char *path) //Lê clientes do arquivo CSV e os coloca na lista.
{
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char line[512];
    while (fgets(line, sizeof(line), f)) 
    {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0] == '\0') continue;
        // id;nome;cpf;telefone
        char *p = line;
        char *tok;

        tok = strtok(p, ";");
        if (!tok) continue;
        Cliente c;
        c.id = atoi(tok);

        tok = strtok(NULL, ";");
        if (!tok) continue;
        strncpy(c.nome, tok, NOME_MAX-1); c.nome[NOME_MAX-1] = '\0';

        tok = strtok(NULL, ";");
        if (!tok) c.cpf[0]=0; else { strncpy(c.cpf, tok, CPF_MAX-1); c.cpf[CPF_MAX-1]=0; }

        tok = strtok(NULL, ";");
        if (!tok) c.telefone[0]=0; else { strncpy(c.telefone, tok, TELEFONE_MAX-1); c.telefone[TELEFONE_MAX-1]=0; }

        adicionarCliente(l, &c);
    }
    fclose(f);
    return 0;
}

int salvarClientesCSV(ListaClientes *l, const char *path) //Grava todos os clientes da lista no CSV.
{
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    for (int i = 0; i < l->quantos_existem; ++i) 
    {
        Cliente *c = &l->vet_clientes[i];
        fprintf(f, "%d;%s;%s;%s\n", c->id, c->nome, c->cpf, c->telefone);
    }
    fclose(f);
    return 0;
}
