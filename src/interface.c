#include "interface.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>



static void lerString(int y, int x, char *buffer, int tamanho)//função aux para fazer tipo  um scanf em ncuses
{
    mvprintw(y, x, "[____________________________]");
    move(y, x + 1);

    curs_set(TRUE);
    echo();

    getnstr(buffer, tamanho - 1);

    noecho();
    curs_set(FALSE);
}

static int lerInt(int y, int x)
{
    char buffer[16];

    mvprintw(y, x, "[________]");
    move(y, x + 1);

    curs_set(TRUE);
    echo();

    getnstr(buffer, 15);

    noecho();
    curs_set(FALSE);

    return atoi(buffer);
}

static char lerOpcaoMenu(int y, int x)
{
    char buffer[4];  

    mvprintw(y, x, "[ ]");
    move(y, x + 1);

    curs_set(TRUE);
    echo();

    getnstr(buffer, 2);

    noecho();
    curs_set(FALSE);

    return buffer[0];
}

void mostrarMenuClientes(ListaClientes *clientes)
{
    char opcao;

    do {
        clear();

        mvprintw(1, 2, "=== Manter Clientes ===");
        mvprintw(3, 4, "1 - Cadastrar cliente");
        mvprintw(4, 4, "2 - Remover cliente");
        mvprintw(5, 4, "3 - Consultar cliente");
        mvprintw(6, 4, "4 - Listar clientes");
        mvprintw(8, 4, "0 - Voltar");

        mvprintw(9, 2, "Escolha uma opcao:");
        opcao = lerOpcaoMenu(9, 22);


        switch (opcao)
        {
        case '1':   /* CADASTRAR */
        {
            Cliente c;
            c.id = ProximoIdCliente(clientes);

            clear();
            mvprintw(1, 2, "=== Cadastrar Cliente ===");

            mvprintw(3, 2, "Nome:");
            lerString(3, 12, c.nome, NOME_MAX);

            mvprintw(4, 2, "CPF:");
            lerString(4, 12, c.cpf, CPF_MAX);

            mvprintw(5, 2, "Telefone:");
            lerString(5, 14, c.telefone, TELEFONE_MAX);

            adicionarCliente(clientes, &c);

            mvprintw(7, 2, "Cliente cadastrado! ID = %d", c.id);
            mvprintw(9, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '2':   /* REMOVER */
        {
            clear();
            mvprintw(1, 2, "=== Remover Cliente ===");

            mvprintw(3, 2, "ID do cliente:");
            int id = lerInt(3, 18);

            if (removerClienteById(clientes, id) == 0)
                mvprintw(5, 2, "Removido com sucesso!");
            else
                mvprintw(5, 2, "Cliente nao encontrado!");

            mvprintw(7, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '3':   /* CONSULTAR */
        {
            clear();
            mvprintw(1, 2, "=== Consultar Cliente ===");

            mvprintw(3, 2, "ID do cliente:");
            int id = lerInt(3, 18);

            Cliente *c = buscarClienteById(clientes, id);

            if (c)
            {
                mvprintw(5, 2, "ID: %d", c->id);
                mvprintw(6, 2, "Nome: %s", c->nome);
                mvprintw(7, 2, "CPF: %s", c->cpf);
                mvprintw(8, 2, "Telefone: %s", c->telefone);
            }
            else
            {
                mvprintw(5, 2, "Cliente nao encontrado!");
            }

            mvprintw(12, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '4':   /* LISTAR */
        {
            clear();
            mvprintw(1, 2, "=== Lista de Clientes ===");

            if (clientes->quantos_existem == 0)
            {
                mvprintw(3, 2, "Nenhum cliente cadastrado.");
            }
            else
            {
                int y = 3;
                for (int i = 0; i < clientes->quantos_existem; i++)
                {
                    Cliente *c = &clientes->vet_clientes[i];
                    mvprintw(y++, 2, "ID:%d | %s | %s | %s",
                             c->id, c->nome, c->cpf, c->telefone);
                }
            }

            mvprintw(20, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }
        }

    } while (opcao != '0');
}


void mostrarMenuProdutos(ListaProdutos *produtos)
{
    char opcao;

    do {
        clear();

        mvprintw(1, 2, "=== Manter Produtos ===");
        mvprintw(3, 4, "1 - Cadastrar produto");
        mvprintw(4, 4, "2 - Remover produto");
        mvprintw(5, 4, "3 - Consultar produto");
        mvprintw(6, 4, "4 - Listar produtos");
        mvprintw(8, 4, "0 - Voltar");

        mvprintw(9, 2, "Escolha uma opcao:");
        opcao = lerOpcaoMenu(9, 22);

        switch (opcao)
        {
        case '1':   /* CADASTRAR */
        {
            Produto p;
            p.id = nextIdProduto(produtos);

            clear();
            mvprintw(1, 2, "=== Cadastrar Produto ===");

            mvprintw(3, 2, "Nome:");
            lerString(3, 12, p.nome, PROD_NOME_MAX);

            mvprintw(4, 2, "Preco:");
            char buf[20];
            lerString(4, 12, buf, 20);
            p.preco = atof(buf);

            mvprintw(5, 2, "Estoque:");
            p.estoque = lerInt(5, 14);

            adicionarProduto(produtos, &p);

            mvprintw(7, 2, "Produto cadastrado! ID = %d", p.id);
            mvprintw(9, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '2':   /* REMOVER */
        {
            clear();
            mvprintw(1, 2, "=== Remover Produto ===");

            mvprintw(3, 2, "ID:");
            int id = lerInt(3, 10);

            if (removerProdutoById(produtos, id) == 0)
                mvprintw(5, 2, "Removido!");
            else
                mvprintw(5, 2, "Nao encontrado!");

            mvprintw(7, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '3':   /* CONSULTAR */
        {
            clear();
            mvprintw(1, 2, "=== Consultar Produto ===");

            mvprintw(3, 2, "ID:");
            int id = lerInt(3, 10);

            Produto *p = buscarProdutoById(produtos, id);

            if (p)
            {
                mvprintw(5, 2, "ID: %d", p->id);
                mvprintw(6, 2, "Nome: %s", p->nome);
                mvprintw(7, 2, "Preco: %.2f", p->preco);
                mvprintw(8, 2, "Estoque: %d", p->estoque);
            }
            else
            {
                mvprintw(5, 2, "Nao encontrado!");
            }

            mvprintw(12, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }

        case '4':   /* LISTAR */
        {
            clear();
            mvprintw(1, 2, "=== Lista de Produtos ===");

            if (produtos->tamanho == 0)
            {
                mvprintw(3, 2, "Nenhum produto cadastrado.");
            }
            else
            {
                int y = 3;
                for (int i = 0; i < produtos->tamanho; i++)
                {
                    Produto *p = &produtos->vet_produtos[i];
                    mvprintw(y++, 2, "ID:%d | %s | R$ %.2f | Estoque:%d",
                             p->id, p->nome, p->preco, p->estoque);
                }
            }

            mvprintw(20, 2, "Pressione qualquer tecla...");
            refresh();
            getch();
            break;
        }
        }

    } while (opcao != '0');
}


void mostrarMenuPedidos(ListaPedidos *pedidos)
{
    char opcao;

    do {
        clear();

        mvprintw(1, 2, "=== Manter Pedidos ===");
        mvprintw(3, 4, "1 - Cadastrar pedido");
        mvprintw(4, 4, "2 - Remover pedido");
        mvprintw(5, 4, "3 - Consultar pedido");
        mvprintw(6, 4, "4 - Listar pedidos");
        mvprintw(8, 4, "0 - Voltar");

        mvprintw(9, 2, "Escolha uma opcao:");
        opcao = lerOpcaoMenu(9, 22);


        switch (opcao)
        {
        case '1':   /* CADASTRAR */
        {
            Pedido p;
            p.id = pedidos->tamanho + 1;
            p.qtdItens = 0;
            strcpy(p.status, "Aberto");

            clear();
            mvprintw(1, 2, "=== Cadastrar Pedido ===");

            mvprintw(3, 2, "ID do cliente:");
            p.clienteId = lerInt(3, 18);

            char resp;

            do {
                mvprintw(5 + p.qtdItens, 2, "ID do produto:");
                p.itens[p.qtdItens].produtoId = lerInt(5 + p.qtdItens, 18);

                mvprintw(6 + p.qtdItens, 2, "Quantidade:");
                p.itens[p.qtdItens].quantidade = lerInt(6 + p.qtdItens, 18);

                p.qtdItens++;

                mvprintw(8 + p.qtdItens, 2, "Adicionar outro item? (s/n)");
                refresh();
                resp = getch();

            } while ((resp == 's' || resp == 'S') && p.qtdItens < MAX_ITENS_PEDIDO);

            adicionarPedido(pedidos, &p);

            mvprintw(10 + p.qtdItens, 2, "Pedido cadastrado!");
            mvprintw(12 + p.qtdItens, 2, "Pressione tecla...");
            refresh();
            getch();
            break;
        }

        case '2':   /* REMOVER */
        {
            clear();
            mvprintw(1, 2, "=== Remover Pedido ===");

            mvprintw(3, 2, "ID:");
            int id = lerInt(3, 10);

            if (removerPedidoById(pedidos, id) == 0)
                mvprintw(5, 2, "Removido!");
            else
                mvprintw(5, 2, "Nao encontrado!");

            mvprintw(7, 2, "Pressione tecla...");
            refresh();
            getch();
            break;
        }

        case '3':   /* CONSULTAR */
        {
            clear();
            mvprintw(1, 2, "=== Consultar Pedido ===");

            mvprintw(3, 2, "ID:");
            int id = lerInt(3, 10);

            Pedido *p = buscarPedidoById(pedidos, id);

            if (p)
            {
                mvprintw(5, 2, "ID: %d", p->id);
                mvprintw(6, 2, "Cliente: %d", p->clienteId);
                mvprintw(7, 2, "Status: %s", p->status);

                int y = 9;
                for (int i = 0; i < p->qtdItens; i++)
                {
                    mvprintw(y++, 4, "Prod %d | Qtd %d",
                             p->itens[i].produtoId,
                             p->itens[i].quantidade);
                }
            }
            else
            {
                mvprintw(5, 2, "Pedido nao encontrado!");
            }

            mvprintw(15, 2, "Pressione tecla...");
            refresh();
            getch();
            break;
        }

        case '4':   /* LISTAR */
        {
            clear();
            mvprintw(1, 2, "=== Lista de Pedidos ===");

            if (pedidos->tamanho == 0)
            {
                mvprintw(3, 2, "Nenhum pedido cadastrado.");
            }
            else
            {
                int y = 3;
                for (int i = 0; i < pedidos->tamanho; i++)
                {
                    Pedido *p = &pedidos->lista_pedidos[i];
                    mvprintw(y++, 2, "Pedido %d | Cliente %d | Itens %d",
                             p->id, p->clienteId, p->qtdItens);
                }
            }

            mvprintw(20, 2, "Pressione tecla...");
            refresh();
            getch();
            break;
        }
        }

    } while (opcao != '0');
}


void mostrarMenuPrincipal(ListaClientes *clientes,
                          ListaProdutos *produtos,
                          ListaPedidos *pedidos)
{
    char opcao;

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    do {
        clear();

        mvprintw(1, 2, "=== Sistema de Controle de Pedidos ===");
        mvprintw(3, 4, "1 - Manter Clientes");
        mvprintw(4, 4, "2 - Manter Produtos");
        mvprintw(5, 4, "3 - Manter Pedidos");
        mvprintw(7, 4, "0 - Sair");

        mvprintw(9, 2, "Escolha uma opcao:");
        refresh();

        opcao = lerOpcaoMenu(9, 22);

        switch (opcao)
        {
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
            mvprintw(11, 2, "Opcao invalida!");
            refresh();
            getch();
            break;
        }

    } while (opcao != '0');

    endwin();
}
