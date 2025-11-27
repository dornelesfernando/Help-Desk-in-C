#include "list_func.h"

void list_func(Arv *arv_func, char **logs) {
    if (arv_func == NULL || arv_func->raiz == NULL) {
        printf("Nenhum funcionário cadastrado na árvore.\n");
        return;
    }

    printf("\n## Lista de Funcionários Cadastrados (Ordem Alfabética) ##\n");
    exibir_funcionarios_recursivo(arv_func->raiz, logs);
    printf("----------------------------------------------------------\n");
}