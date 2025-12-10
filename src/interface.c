#ifdef _WIN32
#include <curses.h>   // PDCurses no Windows
#else
#include <ncurses.h>  // ncurses no Linux
#endif

#include "interface.h"
#include "cliente.h"
#include "produto.h"
#include "pedido.h"



void mostrarMenuClientes() {
    // placeholder
}

void mostrarMenuProdutos() {
    // placeholder
}

void mostrarMenuPedidos() {
    // placeholder
}

void mostrarMenuPrincipal() {
    initscr();              // inicia ncurses
    noecho();               // não ecoa teclas
    curs_set(FALSE);        // esconde cursor

    mvprintw(1, 2, "=== Sistema de Controle de Pedidos ===");
    mvprintw(3, 4, "1 - Clientes");
    mvprintw(4, 4, "2 - Produtos");
    mvprintw(5, 4, "3 - Pedidos");
    mvprintw(6, 4, "0 - Sair");

    mvprintw(8, 2, "Pressione qualquer tecla para sair...");
    refresh();
    getch();

    endwin();               // finaliza ncurses
}
