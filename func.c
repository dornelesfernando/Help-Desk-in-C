#include "func.h"

#include "func.h"

void add_func(Arv *arv_func, char **logs) {
    char name[100];
    
    header();
    printf(GREEN " - Cadastrando técnico.\n" RESET);
    line();
    printf("  Por favor, preencha os seguintes dados:\n");
    
    do {
        printf(GREEN  "    [1] " RESET "Digite o nome do funcionário\n");
        line();
        
        printf(CYAN  " [1] " RED "--> " RESET);
        
        if (scanf(" %99[^\n]", name) != 1) {
            printf(RED "Erro na leitura. Tente novamente.\n" RESET);
            clean_buffer_stdin();
            continue;
        }
        clean_buffer_stdin();

        if (strlen(name) == 0) {
            printf(RED "O nome do funcionário não pode ser vazio. Tente novamente.\n" RESET);
            continue;
        }
        
        break;
    } while(1);

    ArvNo *novo_no = create_employee_node(name, logs);

    if (novo_no == NULL) {
        adicionar_log_dinamico(logs, "Falha na criação do nó de funcionário. Abortando inserção.");
        return;
    }

    arv_func->raiz = insert_func_node(arv_func->raiz, novo_no, logs);

    if (arv_func->raiz != NULL && novo_no->datas != NULL) {
        printf(GREEN "Técnico %s cadastrado com sucesso!\n" RESET, name);
    }
}