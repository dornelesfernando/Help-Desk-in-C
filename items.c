    #include "func.h"

void add_items(Arv *arv_items, CallService* call_suspend, CallHeap *call_list_heap, char **logs) {
    int escolha;
    
    header();
    do {
        printf("  ADICIONAR ITENS AO ESTOQUE\n");
        line();
        printf(  YELLOW "  Selecione o Item Desejado:\n" RESET);
        
        printf(CYAN   "       0) " BLUE "Cancelar   " RESET);
        printf(CYAN   "      1) " BLUE "Mouse       " RESET);
        printf(CYAN   "     2) " BLUE "Teclado\n" RESET);
        printf(CYAN   "       3) " BLUE "Cabo HDMI" RESET);
        printf(CYAN   "      4) " BLUE "Monitor     " RESET);
        printf(CYAN   "     5) " BLUE "Impressora\n" RESET);
        printf(CYAN   "       6) " BLUE "Notebook " RESET);
        printf(CYAN   "      7) " BLUE "Cabo de rede" RESET);
        printf(CYAN   "     8) " BLUE "Webcam\n" RESET);
        printf(CYAN   "       9) " BLUE "Fone de ouvido\n" RESET);

        printf(CYAN "  Escolha (%d-%d ou 0 para cancelar): " RESET, MOUSE, HEADSET);
        
        if (scanf("%d", &escolha) != 1) {
            clear();
            pre_log();
            printf(BOLD RED "Entrada inválida (apenas números são permitidos). Tente novamente.\n" RESET);
            header();
            clean_buffer_stdin(); 
            escolha = -1;
            continue;
        }

        if (escolha < MOUSE || escolha > HEADSET) {
            if (escolha == 0) {
                printf("\nOperação cancelada.\n");
                clean_buffer_stdin();
            }
            clear();
            pre_log();
            printf(BOLD RED "Escolha fora do intervalo. Tente novamente.\n" RESET);
            header();
        }

    } while (escolha < MOUSE || escolha > HEADSET); 


    ItemsEnum item_selecionado = (ItemsEnum)escolha;
    const char *nome_item = get_item_char(item_selecionado);

    int quantidade;
    do {
        printf(CYAN "  Digite a quantidade a adicionar de %s (mín. 1): " RESET, nome_item);
        
        if (scanf("%d", &quantidade) != 1) {
            printf(BOLD RED "\nQuantidade inválida (apenas números inteiros positivos são permitidos). Tente novamente.\n" RESET);
            clean_buffer_stdin();
            quantidade = 0;
            continue;
        }
        
        if (quantidade <= 0) {
            printf(BOLD RED "\nA quantidade deve ser maior que zero. Tente novamente.\n" RESET);
        }

    } while (quantidade <= 0);

    arv_items->raiz = insert_or_update(arv_items->raiz, nome_item, quantidade, logs);

    if (arv_items->raiz != NULL) {
        printf("\nEstoque atualizado para %s (Adicionado: %d).\n", nome_item, quantidade);
        
        int reativados = reativar_chamados_suspensos(arv_items, call_suspend, call_list_heap, logs);
        
        if (reativados > 0) {
            printf(BOLD YELLOW "\n>>> ATENÇÃO: %d Chamado(s) Suspenso(s) foram reativados e retornaram à fila de prioridade! <<<\n" RESET, reativados);
        } else {
            printf(BOLD RED "\nNenhum chamado suspenso pôde ser reativado.\n" RESET);
        }
    } else {
        printf(BOLD RED "\nErro na operação de estoque.\n" RESET);
    }
    
    clean_buffer_stdin(); 
}