#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct 
{
    char nome[100];
    char cpf[15];
    char cnpj[20];
    int tipo; 
} Cliente;

void inserirCliente();
void listarClientes();
void removerCliente();
int validarCPF(const char *cpf);
int validarCNPJ(const char *cnpj);

#endif
