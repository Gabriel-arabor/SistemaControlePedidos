#ifndef CLIENTE_H
#define CLIENTE_H

#include <stddef.h>

#define NOME_MAX 100
#define TELEFONE_MAX 30
#define CPF_MAX 20

typedef struct {
    int id;
    char nome[NOME_MAX];
    char cpf[CPF_MAX];
    char telefone[TELEFONE_MAX];
} Cliente;

typedef struct {
    Cliente *data;
    int size;
    int capacity;
} ListaClientes;

/* Funções */
void initClientes(ListaClientes *l);
void freeClientes(ListaClientes *l);
int carregarClientesCSV(ListaClientes *l, const char *path);
int salvarClientesCSV(ListaClientes *l, const char *path);
int adicionarCliente(ListaClientes *l, const Cliente *c);
int removerClienteById(ListaClientes *l, int id);
Cliente *buscarClienteById(ListaClientes *l, int id);
void listarClientes(ListaClientes *l);
int nextIdCliente(ListaClientes *l);

#endif
