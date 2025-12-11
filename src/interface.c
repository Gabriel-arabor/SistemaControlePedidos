#include "interface.h"
#include <ncurses.h>

/*
 * Por enquanto, os menus de Clientes, Produtos e Pedidos
 * são apenas "placeholders" para testar a integração.
 * Depois você pode implementar o CRUD completo aqui.
 */

void mostrarMenuClientes(ListaClientes *clientes) {
    clear();
    mvprintw(1, 2, "=== Menu de Clientes ===");
    mvprintw(3, 4, "Total de clientes carregados: %d", clientes->size);
    mvprintw(5, 2, "Pressione qualquer tecla para voltar...");
    refresh();
    getch();
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
