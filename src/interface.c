#include "interface.h"
#include <ncurses.h>
#include <stdlib.h>


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
    clear();
    mvprintw(1, 2, "=== Menu de Produtos ===");
    mvprintw(3, 4, "Total de produtos carregados: %d", produtos->size);
    mvprintw(5, 2, "Pressione qualquer tecla para voltar...");
    refresh();
    getch();
}

void mostrarMenuPedidos(ListaPedidos *pedidos) {
    clear();
    mvprintw(1, 2, "=== Menu de Pedidos ===");
    mvprintw(3, 4, "Total de pedidos carregados: %d", pedidos->size);
    mvprintw(5, 2, "Pressione qualquer tecla para voltar...");
    refresh();
    getch();
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
