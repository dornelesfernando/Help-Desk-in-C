#include "list_items.h"

void list_items(Arv *arv_items, char **logs) {
    if (arv_items == NULL || arv_items->raiz == NULL) {
        printf(BOLD RED "Nenhum item em estoque cadastrado na árvore.\n" RESET);
        return;
    }

    printf( YELLOW "\n Itens em Estoque e Quantidades ##\n" RESET);
    exibir_itens_recursivo(arv_items->raiz, logs);
    line();
}