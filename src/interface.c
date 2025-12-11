#include "interface.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


/*
 * Por enquanto, os menus de Clientes, Produtos e Pedidos
 * são apenas "placeholders" para testar a integração.
 * Depois você pode implementar o CRUD completo aqui.
 */

static void lerString(int y, int x, char *buffer, int tamanho) {
    mvprintw(y, x, "> ");
    echo();
    getnstr(buffer, tamanho - 1);
    noecho();
}

static int lerInt(int y, int x) {
    char buffer[16];
    mvprintw(y, x, "> ");
    echo();
    getnstr(buffer, 15);
    noecho();
    return atoi(buffer);
}


void mostrarMenuClientes(ListaClientes *clientes) {
    int opcao;

    do {
        clear();
        mvprintw(1, 2, "=== Manter Clientes ===");
        mvprintw(3, 4, "1 - Cadastrar cliente");
        mvprintw(4, 4, "2 - Remover cliente");
        mvprintw(5, 4, "3 - Consultar cliente");
        mvprintw(6, 4, "4 - Listar clientes");
        mvprintw(8, 4, "0 - Voltar");
        mvprintw(10, 2, "Escolha uma opcao: ");
        refresh();

        opcao = getch();

        switch (opcao) {

        case '1': { // Cadastrar
            Cliente c;
            c.id = nextIdCliente(clientes);

            clear();
            mvprintw(1, 2, "=== Cadastrar Cliente ===");

            mvprintw(3, 2, "Nome");
            lerString(3, 8, c.nome, NOME_MAX);

            mvprintw(4, 2, "CPF");
            lerString(4, 8, c.cpf, CPF_MAX);

            mvprintw(5, 2, "Telefone");
            lerString(5, 12, c.telefone, TELEFONE_MAX);

            adicionarCliente(clientes, &c);

            mvprintw(7, 2, "Cliente cadastrado com sucesso! ID = %d", c.id);
            mvprintw(9, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '2': { // Remover
            clear();
            mvprintw(1, 2, "=== Remover Cliente ===");
            mvprintw(3, 2, "Informe o ID do cliente");
            int id = lerInt(3, 28);

            if (removerClienteById(clientes, id) == 0)
                mvprintw(5, 2, "Cliente removido com sucesso!");
            else
                mvprintw(5, 2, "Cliente nao encontrado!");

            mvprintw(7, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '3': { // Consultar
            clear();
            mvprintw(1, 2, "=== Consultar Cliente ===");
            mvprintw(3, 2, "Informe o ID do cliente");
            int id = lerInt(3, 28);

            Cliente *c = buscarClienteById(clientes, id);
            if (c) {
                mvprintw(5, 2, "ID: %d", c->id);
                mvprintw(6, 2, "Nome: %s", c->nome);
                mvprintw(7, 2, "CPF: %s", c->cpf);
                mvprintw(8, 2, "Telefone: %s", c->telefone);
            } else {
                mvprintw(5, 2, "Cliente nao encontrado!");
            }

            mvprintw(10, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '4': { // Listar
            clear();
            mvprintw(1, 2, "=== Lista de Clientes ===");

            int y = 3;
            for (int i = 0; i < clientes->size; i++) {
                Cliente *c = &clientes->data[i];
                mvprintw(y++, 2, "ID:%d | %s | %s | %s",
                          c->id, c->nome, c->cpf, c->telefone);
            }

            if (clientes->size == 0)
                mvprintw(3, 2, "Nenhum cliente cadastrado.");

            mvprintw(y + 2, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '0':
            break;

        default:
            mvprintw(12, 2, "Opcao invalida!");
            refresh();
            getch();
        }

    } while (opcao != '0');
}


void mostrarMenuProdutos(ListaProdutos *produtos) {
    int opcao;

    do {
        clear();
        mvprintw(1, 2, "=== Manter Produtos ===");
        mvprintw(3, 4, "1 - Cadastrar produto");
        mvprintw(4, 4, "2 - Remover produto");
        mvprintw(5, 4, "3 - Consultar produto");
        mvprintw(6, 4, "4 - Listar produtos");
        mvprintw(8, 4, "0 - Voltar");
        mvprintw(10, 2, "Escolha uma opcao: ");
        refresh();

        opcao = getch();

        switch (opcao) {

        case '1': { // Cadastrar
            Produto p;
            p.id = nextIdProduto(produtos);

            clear();
            mvprintw(1, 2, "=== Cadastrar Produto ===");

            mvprintw(3, 2, "Nome");
            lerString(3, 8, p.nome, PROD_NOME_MAX);

            mvprintw(4, 2, "Preco");
            char bufPreco[20];
            lerString(4, 9, bufPreco, 20);
            p.preco = atof(bufPreco);

            mvprintw(5, 2, "Estoque");
            p.estoque = lerInt(5, 11);

            adicionarProduto(produtos, &p);

            mvprintw(7, 2, "Produto cadastrado com sucesso! ID = %d", p.id);
            mvprintw(9, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '2': { // Remover
            clear();
            mvprintw(1, 2, "=== Remover Produto ===");
            mvprintw(3, 2, "Informe o ID do produto");
            int id = lerInt(3, 28);

            if (removerProdutoById(produtos, id) == 0)
                mvprintw(5, 2, "Produto removido com sucesso!");
            else
                mvprintw(5, 2, "Produto nao encontrado!");

            mvprintw(7, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '3': { // Consultar
            clear();
            mvprintw(1, 2, "=== Consultar Produto ===");
            mvprintw(3, 2, "Informe o ID do produto");
            int id = lerInt(3, 28);

            Produto *p = buscarProdutoById(produtos, id);
            if (p) {
                mvprintw(5, 2, "ID: %d", p->id);
                mvprintw(6, 2, "Nome: %s", p->nome);
                mvprintw(7, 2, "Preco: %.2f", p->preco);
                mvprintw(8, 2, "Estoque: %d", p->estoque);
            } else {
                mvprintw(5, 2, "Produto nao encontrado!");
            }

            mvprintw(10, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '4': { // Listar
            clear();
            mvprintw(1, 2, "=== Lista de Produtos ===");

            int y = 3;
            for (int i = 0; i < produtos->size; i++) {
                Produto *p = &produtos->data[i];
                mvprintw(y++, 2, "ID:%d | %s | R$ %.2f | Estoque:%d",
                         p->id, p->nome, p->preco, p->estoque);
            }

            if (produtos->size == 0)
                mvprintw(3, 2, "Nenhum produto cadastrado.");

            mvprintw(y + 2, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '0':
            break;

        default:
            mvprintw(12, 2, "Opcao invalida!");
            refresh();
            getch();
        }

    } while (opcao != '0');
}


void mostrarMenuPedidos(ListaPedidos *pedidos) {
    int opcao;

    do {
        clear();
        mvprintw(1, 2, "=== Manter Pedidos ===");
        mvprintw(3, 4, "1 - Cadastrar pedido");
        mvprintw(4, 4, "2 - Remover pedido");
        mvprintw(5, 4, "3 - Consultar pedido");
        mvprintw(6, 4, "4 - Listar pedidos");
        mvprintw(8, 4, "0 - Voltar");
        mvprintw(10, 2, "Escolha uma opcao: ");
        refresh();

        opcao = getch();

        switch (opcao) {

        case '1': { // Cadastrar pedido
            Pedido p;
            p.id = pedidos->size + 1;   // simples e suficiente
            p.qtdItens = 0;
            strcpy(p.status, "Aberto");

            clear();
            mvprintw(1, 2, "=== Cadastrar Pedido ===");

            mvprintw(3, 2, "ID do cliente");
            p.clienteId = lerInt(3, 18);

            char resp;
            do {
                mvprintw(5 + p.qtdItens, 2, "ID do produto");
                p.itens[p.qtdItens].produtoId = lerInt(5 + p.qtdItens, 18);

                mvprintw(6 + p.qtdItens, 2, "Quantidade");
                p.itens[p.qtdItens].quantidade = lerInt(6 + p.qtdItens, 18);

                p.qtdItens++;

                mvprintw(8 + p.qtdItens, 2, "Adicionar outro produto? (s/n)");
                resp = getch();

            } while ((resp == 's' || resp == 'S') && p.qtdItens < MAX_ITENS_PEDIDO);

            adicionarPedido(pedidos, &p);

            mvprintw(10 + p.qtdItens, 2, "Pedido cadastrado com sucesso!");
            mvprintw(12 + p.qtdItens, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '2': { // Remover pedido
            clear();
            mvprintw(1, 2, "=== Remover Pedido ===");
            mvprintw(3, 2, "Informe o ID do pedido");
            int id = lerInt(3, 22);

            if (removerPedidoById(pedidos, id) == 0)
                mvprintw(5, 2, "Pedido removido com sucesso!");
            else
                mvprintw(5, 2, "Pedido nao encontrado!");

            mvprintw(7, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '3': { // Consultar pedido
            clear();
            mvprintw(1, 2, "=== Consultar Pedido ===");
            mvprintw(3, 2, "Informe o ID do pedido");
            int id = lerInt(3, 22);

            Pedido *p = buscarPedidoById(pedidos, id);
            if (p) {
                mvprintw(5, 2, "Pedido ID: %d", p->id);
                mvprintw(6, 2, "Cliente ID: %d", p->clienteId);
                mvprintw(7, 2, "Status: %s", p->status);

                int y = 9;
                for (int i = 0; i < p->qtdItens; i++) {
                    mvprintw(y++, 4, "Produto %d | Qtd %d",
                             p->itens[i].produtoId,
                             p->itens[i].quantidade);
                }
            } else {
                mvprintw(5, 2, "Pedido nao encontrado!");
            }

            mvprintw(12, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '4': { // Listar pedidos
            clear();
            mvprintw(1, 2, "=== Lista de Pedidos ===");

            int y = 3;
            for (int i = 0; i < pedidos->size; i++) {
                Pedido *p = &pedidos->data[i];
                mvprintw(y++, 2, "Pedido %d | Cliente %d | Itens %d",
                         p->id, p->clienteId, p->qtdItens);
            }

            if (pedidos->size == 0)
                mvprintw(3, 2, "Nenhum pedido cadastrado.");

            mvprintw(y + 2, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '0':
            break;

        default:
            mvprintw(12, 2, "Opcao invalida!");
            refresh();
            getch();
        }

    } while (opcao != '0');
}


void mostrarMenuPrincipal(ListaClientes *clientes, ListaProdutos *produtos, ListaPedidos *pedidos) {
    int opcao;

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE); // permite usar setas, etc.

    do {
        clear();
        mvprintw(1, 2, "=== Sistema de Controle de Pedidos ===");
        mvprintw(3, 4, "1 - Manter Clientes");
        mvprintw(4, 4, "2 - Manter Produtos");
        mvprintw(5, 4, "3 - Manter Pedidos");
        mvprintw(7, 4, "0 - Sair");
        mvprintw(9, 2, "Escolha uma opcao: ");
        refresh();

        opcao = getch();

        switch (opcao) {
            case '1':
                mostrarMenuClientes(clientes);
                break;
            case '2':
                mostrarMenuProdutos(produtos);
                break;
            case '3':
                mostrarMenuPedidos(pedidos);
                break;
            case '0':
                break;
            default:
                mvprintw(11, 2, "Opcao invalida! Pressione qualquer tecla...");
                refresh();
                getch();
                break;
        }

    } while (opcao != '0');

    endwin();
}
