#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ensureCapacityClientes(ListaClientes *l) {
    if (l->size >= l->capacity) {
        int newCap = l->capacity == 0 ? 8 : l->capacity * 2;
        Cliente *tmp = realloc(l->data, newCap * sizeof(Cliente));
        if (!tmp) {
            fprintf(stderr, "ERRO: realloc clientes\n");
            exit(EXIT_FAILURE);
        }
        l->data = tmp;
        l->capacity = newCap;
    }
}

void initClientes(ListaClientes *l) {
    l->data = NULL;
    l->size = 0;
    l->capacity = 0;
}

void freeClientes(ListaClientes *l) {
    free(l->data);
    l->data = NULL;
    l->size = 0;
    l->capacity = 0;
}

int adicionarCliente(ListaClientes *l, const Cliente *c) {
    ensureCapacityClientes(l);
    l->data[l->size++] = *c;
    return 0;
}

int removerClienteById(ListaClientes *l, int id) {
    for (int i = 0; i < l->size; ++i) {
        if (l->data[i].id == id) {
            memmove(&l->data[i], &l->data[i+1], (l->size - i - 1) * sizeof(Cliente));
            l->size--;
            return 0;
        }
    }
    return -1;
}

Cliente *buscarClienteById(ListaClientes *l, int id) {
    for (int i = 0; i < l->size; ++i) {
        if (l->data[i].id == id) return &l->data[i];
    }
    return NULL;
}

void listarClientes(ListaClientes *l) {
    printf("=== Lista de Clientes (%d) ===\n", l->size);
    for (int i = 0; i < l->size; ++i) {
        Cliente *c = &l->data[i];
        printf("id=%d | nome=\"%s\" | cpf=%s | tel=%s\n", c->id, c->nome, c->cpf, c->telefone);
    }
}

/* retorna próximo id (max + 1) */
int nextIdCliente(ListaClientes *l) {
    int mx = 0;
    for (int i = 0; i < l->size; ++i) if (l->data[i].id > mx) mx = l->data[i].id;
    return mx + 1;
}

int carregarClientesCSV(ListaClientes *l, const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
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

int salvarClientesCSV(ListaClientes *l, const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    for (int i = 0; i < l->size; ++i) {
        Cliente *c = &l->data[i];
        fprintf(f, "%d;%s;%s;%s\n", c->id, c->nome, c->cpf, c->telefone);
    }
    fclose(f);
    return 0;
}
