#include "main.h"

int main() {
    // Inicia sistema de logs
    char *logs = NULL;
    adicionar_log_dinamico(&logs, "Controle de logs inicializado.");
    
    // Parâmetros do sistema
    MainParams params;
    init_system(&params, &logs);
    
    // Inicializa fila Heap e Fifo
    CallHeap *call_list_heap = create_call_list_heap(10);
    CallFIFO *call_list_fifo = create_call_list_fifo(10);

    // ======================= MAIN =======================
    adicionar_log_dinamico(&logs, "Sistema inicializado com sucesso.");
    int opcao;
    do {
        header();
        menu(params.is_logged_in);
        
        do {
            params.input_status = scanf("%d", &opcao);
            clean_buffer_stdin();
            
            if(!params.input_status) printf(RED "Digite apenas números.\n" YELLOW "Selecione uma opção: " RESET);
            
        } while (!params.input_status);
        
        // Menus
        clear();
        pre_log();
        if (params.is_logged_in) {
            switch (opcao) {
                case 1: 
                    printf(GREEN "Atendendo chamado...\n" RESET);
                    adicionar_log_dinamico(&logs, "Atendendo chamado.");
                    break;
                case 2: 
                    printf(GREEN "Cancelando chamado...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Cancelando chamado.");
                    break;
                case 3: 
                    printf(GREEN "Listando chamados para atualização chamado...\n" RESET);
                    adicionar_log_dinamico(&logs, "Listando chamados para atualização chamado.");
                    
                    // params.selected_call_id = list_calls(call_list, params.call_list_index, 9, 9, 1, &logs);
                    // clear();
                    
                    // if (params.selected_call_id == 9999) {
                    //     printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    //     adicionar_log_dinamico(&logs, "Não há chamados cadastrados no sistema.");
                    // } else {
                    //     printf(GREEN "Atualizando chamado...\n" RESET); 
                    //     adicionar_log_dinamico(&logs, "Atualizando chamado.");
                    //     update_call(call_list[params.selected_call_id - 1], params.is_logged_in, &logs);
                    // }
                    
                    // clear();
                    printf(GREEN "Chamado atualizado com sucesso!\n" RESET);
                    adicionar_log_dinamico(&logs, "Chamado atualizado com sucesso.");
                    break;
                case 7:
                    print_logs(logs);
                    line();
                    
                    printf("\n\nPressione ENTER para voltar ao menu...");
                    getchar();
                    
                    clear();
                    break;
                case 8: 
                    params.is_logged_in = 0; 
                    
                    clear();
                    printf(GREEN "Abrindo menu do principal...\n" RESET);
                    adicionar_log_dinamico(&logs, "Abrindo menu do principal.");
                    break;
                case 9: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Saindo do sistema.");
                    break;
                default: 
                    printf(RED "Opção inválida.\n" RESET); 
                    adicionar_log_dinamico(&logs, "Opção inválida.");
                    break;
            }
        } else {
            switch (opcao) {
                case 1: 
                    printf(GREEN "Abrindo chamado...\n" RESET);
                    adicionar_log_dinamico(&logs, "Abrindo chamado.");
                    Call* call_list_pointer = open_call(&params.call_id, &logs);
                    clear();
                    
                    pre_log();
                    if (call_list_pointer != NULL) {
                        if(call_list_pointer->priority == BAIXA) {
                            fifo_enqueue(call_list_fifo, *call_list_pointer);
                            
                            printf(GREEN "Chamado ID:" CYAN " %d " GREEN "criado com sucesso! Adicionado à fila FIFO\n" RESET, call_list_pointer->id);
                        
                            snprintf(params.log_message, sizeof(params.log_message), "Chamado ID: %d criado com sucesso. Adicionado à fila FIFO.", call_list_pointer->id);
                            adicionar_log_dinamico(&logs, params.log_message);
                        } else {
                            heap_insert(call_list_heap, *call_list_pointer);
                            
                            printf(GREEN "Chamado ID:" CYAN " %d " GREEN "criado com sucesso! Adicionado à fila heap\n" RESET, call_list_pointer->id);
                        
                            snprintf(params.log_message, sizeof(params.log_message), "Chamado ID: %d criado com sucesso. Adicionado à fila heap.", call_list_pointer->id);
                            adicionar_log_dinamico(&logs, params.log_message);
                        }
                        
                        params.last_opened_call_id = call_list_pointer->id;
                        
                        free(call_list_pointer);
                    } else {
                        printf(RED "Operação cancelada pelo usuário\n" RESET);
                        adicionar_log_dinamico(&logs, "Operação cancelada pelo usuário.");
                    }
                    
                    printf("\n\nPressione ENTER para voltar ao menu...");
                    getchar();
                    
                    break;
                case 2: 
                    // params.selected_call_id = list_calls(call_list, params.call_list_index, 9, 9, 1, &logs);
                    // clear();
                    
                    // if (params.selected_call_id == 9999) {
                    //     printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    //     adicionar_log_dinamico(&logs, "Não há chamados cadastrados no sistema");
                        
                    //     printf("\n\nPressione ENTER para voltar ao menu...");
                    //     getchar();
                    // } else {
                    //     printf(GREEN "Atualizando chamado...\n" RESET); 
                    //     adicionar_log_dinamico(&logs, "Atualizando chamado.");
                        
                    //     update_call(call_list[params.selected_call_id - 1], 0, &logs);
                    // }
                    
                    clear();
                    printf(GREEN "Chamado atualizado com sucesso!\n" RESET);
                    adicionar_log_dinamico(&logs, "Chamado atualizado com sucesso.");
                    break;
                case 3:
                    // printf(GREEN "Mostrando todos os chamados...\n" RESET); 
                    // adicionar_log_dinamico(&logs, "Mostrando todos os chamados.");
                    
                    // params.returned_call_id = list_calls(call_list, params.call_list_index, 9, 9, 0, &logs);
                    
                    // if (params.returned_call_id == 9999) {
                    //     clear();
                    //     pre_log();
                    //     printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    //     adicionar_log_dinamico(&logs, "Não há chamados cadastrados no sistema.");
                        
                    //     printf("\n\nPressione ENTER para voltar ao menu...");
                    //     getchar();
                    // } else {
                    //     printf("\nPressione ENTER para voltar ao menu...");
                    //     getchar();
                    // }
                    // clear();
                     
                    break;
                case 4: 
                    // printf(GREEN "Mostrando lista de baixa prioridade (normal)...\n" RESET); 
                    // adicionar_log_dinamico(&logs, "Mostrando lista de baixa prioridade (normal).");
                    
                    // params.returned_call_id = list_calls(call_list, params.call_list_index, 1, 9, 0, &logs);
                    
                    // if (params.returned_call_id == 9999) {
                    //     clear();
                    //     pre_log();
                    //     printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    //     adicionar_log_dinamico(&logs, "Não há chamados cadastrados no sistema.");
                        
                    //     printf("\n\nPressione ENTER para voltar ao menu...");
                    //     getchar();
                    // } else {
                    //     printf("\nPressione ENTER para voltar ao menu...");
                    //     getchar();
                    // }
                    // clear();
                    
                    break;
                case 5:
                    // select_parameter(&params.priority_filter, &params.status_filter);
                    // clear();
                    
                    // printf(GREEN "Mostrando lista por prioridades e status selecionado...\n" RESET); 
                    // printf("%d", params.call_list_index);
                    // params.returned_call_id = list_calls(call_list, params.call_list_index, params.priority_filter, params.status_filter, 0, &logs);
                    
                    // if (params.returned_call_id == 9999) {
                    //     clear();
                    //     pre_log();
                    //     printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    //     adicionar_log_dinamico(&logs, "Não há chamados cadastrados no sistema.");
                        
                    //     printf("\n\nPressione ENTER para voltar ao menu...");
                    //     getchar();
                    // } else {
                    //     printf("\nPressione ENTER para voltar ao menu...");
                    //     getchar();
                    // }
                    
                    // clear();
                    break;
                case 6:
                    // if (params.last_opened_call_id) {
                    //     printf(GREEN "Mostrando último chamado aberto...\n" RESET);
                    //     adicionar_log_dinamico(&logs, "Mostrando último chamado aberto.");
                        
                    //     print_calls(call_list[params.last_opened_call_id - 1], &logs);
                        
                    // } else {
                    //     printf(RED "Não há último chamado aberto.\n" RESET);
                    //     adicionar_log_dinamico(&logs, "Não há último chamado aberto.");
                    // }
                    
                    // printf("\nPressione ENTER para voltar ao menu...");
                    // getchar(); 
                    
                    // clear();
                    break;
                case 7:
                    printf(GREEN "Mostrando logs do sistema...\n" RESET);
                    adicionar_log_dinamico(&logs, "Mostrando logs do sistema.");
                    
                    print_logs(logs);
                    line();
                    
                    printf("\n\nPressione ENTER para voltar ao menu...");
                    getchar();
                    
                    clear();
                    break;
                case 8: 
                    printf(GREEN "Abrindo menu do administrador...\n" RESET);
                    adicionar_log_dinamico(&logs, "Abrindo menu do administrador.");
                    
                    params.is_logged_in = login(params.is_logged_in);
                    
                    clear();
                    
                    pre_log();
                    if (params.is_logged_in) {
                        printf(GREEN "Login realizado com sucesso!\n" RESET);
                        adicionar_log_dinamico(&logs, "Login realizado com sucesso.");
                    } else {
                        printf(RED "Falha ao fazer login.\n" RESET);
                        adicionar_log_dinamico(&logs, "Falha ao fazer login.");
                    }
                    break;
                case 9: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Saindo do sistema.");
                    break;
                default: 
                    printf(RED "Opção inválida.\n" RESET); 
                    adicionar_log_dinamico(&logs, "Opção inválida.");
                    break;
            }
        }
    } while (opcao != 9);
    
    line();
    
    printf("Deseja ler os log's ao encerrar o sistema?\n[1] - Sim \n[0] - Não\n"); 
    printf(YELLOW " --> " RESET); 
    scanf("%d", &params.request_log);
    clean_buffer_stdin();
    
    clear();
    
    if (params.request_log) {
        pre_log();
        print_logs(logs);
        line();
        
        printf("Pressione ENTER para finalizar o programa...");
        getchar();
        clear();
    }
    
    // end_system(logs, call_list, params.call_list_index);
    header();

    printf("\n");
    footer();
    return 0;
}