#include "main.h"

int main() {
    // Inicia sistema de logs
    char *logs = NULL;
    adicionar_log_dinamico(&logs, "Controle de logs inicializado.");
    
    #ifdef _WIN32
        if (_putenv_s("TZ", "BRT3") != 0) {
            printf(RED BOLD "Erro ao definir fuso horario.\n" RESET);
        }
    #else
        setenv("TZ", "BRT3", 1);
    #endif
    tzset();
    adicionar_log_dinamico(&logs, "Fuso horário definido.");
    
    // Parâmetros do sistema
    MainParams params;
    init_system(&params, &logs);
    
    // Inicializa fila Heap, Fifo e Service
    CallHeap *call_list_heap = create_call_list_heap(3, &logs);
    if (call_list_heap == NULL) {
        printf(RED BOLD "Erro ao inicializar lista Heap" RESET);
        print_logs(logs);
        return 0;
    }
    
    CallFIFO *call_list_fifo = create_call_list_fifo(3, &logs);
    if (call_list_fifo == NULL) {
        printf(RED BOLD "Erro ao inicializar lista FIFO" RESET);
        print_logs(logs);
        return 0;
    }
    
    CallService* call_service;
    
    CallService* call_history = create_call_list_service(&logs);
    if (call_history == NULL) {
        printf(RED BOLD "Erro ao inicializar lista history duplamente encadeada" RESET);
        print_logs(logs);
        return 0;
    }
    
    CallService* call_suspend = create_call_list_service(&logs);
    if (call_suspend == NULL) {
        printf(RED BOLD "Erro ao inicializar lista suspend duplamente encadeada" RESET);
        print_logs(logs);
        return 0;
    }
    
    // Arv de técnico
    Arv* arv_tec = create_tree();
    if (arv_tec == NULL) {
        printf(RED BOLD "Erro ao inicializar árvore de técnicos." RESET);
        print_logs(logs);
        return 0;
    }
    
    // Arv de itens
    Arv* arv_items = create_tree();
    if (arv_items == NULL) {
        printf(RED BOLD "Erro ao inicializar árvore de itens." RESET);
        print_logs(logs);
        return 0;
    }
    
    char nome_usuario_logado[100];
    
    // ======================= MAIN =======================
    adicionar_log_dinamico(&logs, "Sistema inicializado com sucesso.");
    int opcao;
    do {
        header();
        menu(params.is_logged_in);
        
        do {
            params.input_status = scanf("%d", &opcao);
            clean_buffer_stdin();
            
            if(!params.input_status) printf(RED "Digite apenas números.\n" YELLOW " Selecione uma opção: " RESET);
            
        } while (!params.input_status);

        // Menus
        clear();
        pre_log();
        if (params.is_logged_in == 1) {
            switch (opcao) {
                case 1: 
                    printf(GREEN "Atendendo o chamado com maior prioridade por ordem de chegada...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Atendendo o chamado com maior prioridade por ordem de chegada.");

                    if(call_service == NULL || call_service->size == 0) {
                        line();
                        printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                        adicionar_log_dinamico(&logs, "Não há chamados cadastrados no sistema");   
                    } else {
                        params.returned_call_id_aux = answer_call(call_list_heap, call_list_fifo, call_history, call_suspend, arv_items, arv_tec, &logs);
                    
                        if (params.returned_call_id_aux != 9999) params.returned_call_id = params.returned_call_id_aux;
                    }
                    
                    enter();
                    if (params.returned_call_id_aux != 9999) {
                        pre_log();
                        printf(GREEN "Chamado atendido com sucesso!\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado atendido com sucesso.");
                    }
                    break;
                case 2: 
                    printf(GREEN "Mostrando todos os chamados...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados.");
                    call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                    params.returned_call_id_aux = list_calls_service(call_service, 9, 9, 1, &logs);
                    
                    if(!params.returned_call_id_aux) params.returned_call_id_aux = list_calls_service(call_suspend, 9, 9, 0, &logs);
                    
                    if (params.returned_call_id_aux != 9999) params.returned_call_id = params.returned_call_id_aux;

                    if (params.returned_call_id_aux != 9999) {
                        adicionar_log_dinamico(&logs, "Cancelando chamado.");
                        
                        params.returned_call_id_aux = update_call(call_service, call_list_heap, call_list_fifo, call_history, call_suspend, arv_tec, params.returned_call_id, 1, 1, &logs);
                    }
                    
                    free_list_service(call_service, &logs);
                    enter();
                    if (params.returned_call_id_aux == 9998) {
                        pre_log();
                        printf(GREEN "Chamado cancelado com sucesso!\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado cancelado com sucesso.");
                    }
                    break;
                case 3: 
                    printf(GREEN "Mostrando todos os chamados...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados.");
                    call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                    params.returned_call_id_aux = list_calls_service(call_service, 9, 9, 1, &logs);
                    
                    if (params.returned_call_id_aux != 9999) params.returned_call_id = params.returned_call_id_aux;

                    if (params.returned_call_id_aux != 9999) {
                        clear();
                        pre_log();
                        printf(GREEN "Atualizando chamado...\n" RESET); 
                        adicionar_log_dinamico(&logs, "Atualizando chamado.");
                        
                        params.returned_call_id_aux = update_call(call_service, call_list_heap, call_list_fifo, call_history, call_suspend, arv_tec, params.returned_call_id, 1, 0, &logs);
                    
                        if (params.returned_call_id_aux != 9997) params.last_opened_call_id = params.returned_call_id_aux;
                    }
                    
                    if (params.returned_call_id_aux == 9997) {
                        line();
                        printf(RED "Chamado não pode atualizado pois está fechado/resolvido.\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado não pode atualizado pois está fechado/resolvido.");
                    }
                    
                    free_list_service(call_service, &logs);
                    enter();
                    if (params.returned_call_id_aux != 9999 && params.returned_call_id_aux != 9997) {
                        pre_log();
                        printf(GREEN "Chamado atualizado com sucesso!\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado atualizado com sucesso.");
                    }
                    break;
                case 4:
                    printf(GREEN "Mostrando todos os chamados...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados.");
                    
                    call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                    list_calls_service(call_service, 9, 9, 0, &logs);
                     
                    free_list_service(call_service, &logs);  
                    enter();
                    break;
                case 5:
                    printf(GREEN "Mostrando todos os chamados no histórico...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados no histórico.");
                    
                    list_calls_service(call_history, 9, 9, 0, &logs);
                    enter();
                    break;
                case 6:
                    printf(GREEN "Mostrando todos os chamados suspensos...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados suspensos.");
                    
                    list_calls_service(call_suspend, 9, 9, 0, &logs);
                    enter();
                    break;
                case 7:
                    printf(GREEN "Cadastrando funcionário...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Cadastrando funcionário.");
                    
                    add_func(arv_tec, &logs);
                    
                    enter();
                    break;
                case 8:
                    printf(GREEN "Cadastrando/adicionando itens ao estoque...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Cadastrando/adicionando itens ao estoque.");
                    
                    add_items(arv_items, call_suspend, call_list_heap, &logs);
                    
                    enter();
                    break;
                case 9:
                    printf(GREEN "Visualizando funcionários cadastrados...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Visualizando funcionários cadastrados.");
                    
                    list_func(arv_tec, &logs);
                    
                    enter();
                    break;
                case 10:
                    printf(GREEN "Visualizando itens em estoque...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Visualizando itens em estoque.");
                    
                    list_items(arv_items, &logs);
                    
                    enter();
                    break;
                case 17:
                    printf(GREEN "Mostrando logs do sistema...\n" RESET);
                    adicionar_log_dinamico(&logs, "Mostrando logs do sistema.");
                    
                    print_logs(logs);
                    line();
                    
                    enter();
                    break;
                case 18: 
                    params.is_logged_in = 0; 
                    
                    printf(GREEN "Abrindo menu principal...\n" RESET);
                    adicionar_log_dinamico(&logs, "Abrindo menu principal.");
                    break;
                case 99: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Saindo do sistema.");
                    break;
                default: 
                    printf(RED "Opção inválida.\n" RESET); 
                    adicionar_log_dinamico(&logs, "Opção inválida.");
                    break;
            }
        } else if (params.is_logged_in == 2) {
            switch (opcao) {
                case 1: 
                    printf(GREEN "Atendendo o chamado com maior prioridade por ordem de chegada (tecnico)...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Atendendo o chamado com maior prioridade por ordem de chegada (tecnico).");

                    if(call_service == NULL || call_service->size == 0) {
                        line();
                        printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                        adicionar_log_dinamico(&logs, "Não há chamados cadastrados no sistema");   
                    } else {
                        printf(GREEN "Atendendo chamado...\n" RESET);
                        adicionar_log_dinamico(&logs, "Atendendo chamado.");
                        
                        params.returned_call_id_aux = answer_call_tecnic(call_history, call_suspend, arv_items, arv_tec, nome_usuario_logado, &logs);
                    
                        if (params.returned_call_id_aux != 9999) params.returned_call_id = params.returned_call_id_aux;
                    }
                    
                    enter();
                    if (params.returned_call_id_aux != 9999) {
                        pre_log();
                        printf(GREEN "Chamado atendido com sucesso!\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado atendido com sucesso.");
                    }
                    break;
                case 2: 
                    printf(GREEN "Mostrando todos os chamados atrelados ao funcionário...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados atrelados ao funcionário.");
                    call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                    
                    ArvNo *tecnico_no = buscar_funcionario_por_nome(arv_tec->raiz, nome_usuario_logado);
                    CallService *lista_pessoal = tecnico_no->datas;
                    params.returned_call_id_aux = list_calls_tecnic_service(lista_pessoal, 9, 9, 1, &logs);
                    
                    if (params.returned_call_id_aux != 9999) params.returned_call_id = params.returned_call_id_aux;

                    if (params.returned_call_id_aux != 9999) {
                        adicionar_log_dinamico(&logs, "Cancelando chamado.");
                        
                        params.returned_call_id_aux = update_call(call_service, call_list_heap, call_list_fifo, call_history, call_suspend, arv_tec, params.returned_call_id, 1, 1, &logs);
                    }
                    
                    free_list_service(call_service, &logs);
                    enter();
                    if (params.returned_call_id_aux == 9998) {
                        pre_log();
                        printf(GREEN "Chamado cancelado com sucesso!\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado cancelado com sucesso.");
                    }
                    break;
                case 17:
                    printf(GREEN "Mostrando logs do sistema...\n" RESET);
                    adicionar_log_dinamico(&logs, "Mostrando logs do sistema.");
                    
                    print_logs(logs);
                    line();
                    
                    enter();
                    break;
                case 18: 
                    params.is_logged_in = 0; 
                    
                    printf(GREEN "Abrindo menu principal...\n" RESET);
                    adicionar_log_dinamico(&logs, "Abrindo menu principal.");
                    break;
                case 99: 
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
                    
                    pre_log();
                    if (call_list_pointer != NULL) {
                        params.last_opened_call_id = call_list_pointer->id;
                        
                        if(call_list_pointer->priority == BAIXA) {
                            fifo_enqueue(call_list_fifo, *call_list_pointer, &logs);
                            
                            printf(GREEN "Chamado ID:" CYAN " %d " GREEN "criado com sucesso! Adicionado à fila FIFO\n" RESET, call_list_pointer->id);
                        
                            snprintf(params.log_message, sizeof(params.log_message), "Chamado ID: %d criado com sucesso. Adicionado à fila FIFO.", call_list_pointer->id);
                            adicionar_log_dinamico(&logs, params.log_message);
                        } else {
                            heap_insert(call_list_heap, *call_list_pointer, &logs);
                            
                            printf(GREEN "Chamado ID:" CYAN " %d " GREEN "criado com sucesso! Adicionado à fila heap\n" RESET, call_list_pointer->id);
                        
                            snprintf(params.log_message, sizeof(params.log_message), "Chamado ID: %d criado com sucesso. Adicionado à fila heap.", call_list_pointer->id);
                            adicionar_log_dinamico(&logs, params.log_message);
                        }
                    } else {
                        printf(RED "Operação cancelada pelo usuário\n" RESET);
                        adicionar_log_dinamico(&logs, "Operação cancelada pelo usuário.");
                    }
                    
                    free(call_list_pointer);
                    break;
                case 2: 
                    printf(GREEN "Mostrando todos os chamados...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados.");
                    call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                    params.returned_call_id_aux = list_calls_service(call_service, 9, 9, 1, &logs);
                    
                    if(!params.returned_call_id_aux) params.returned_call_id_aux = list_calls_service(call_suspend, 9, 9, 0, &logs);

                    if (params.returned_call_id_aux != 9999) params.returned_call_id = params.returned_call_id_aux;

                    if (params.returned_call_id_aux != 9999) {
                        clear();
                        pre_log();
                        printf(GREEN "Atualizando chamado...\n" RESET); 
                        adicionar_log_dinamico(&logs, "Atualizando chamado.");
                        
                        params.returned_call_id_aux = update_call(call_service, call_list_heap, call_list_fifo, call_history, call_suspend, arv_tec, params.returned_call_id, 0, 0, &logs);
                    
                        if (params.returned_call_id_aux != 9997) params.last_opened_call_id = params.returned_call_id_aux;
                    }
                    
                    if (params.returned_call_id_aux == 9997) {
                        line();
                        printf(RED "Chamado não pode atualizado pois está fechado/resolvido.\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado não pode atualizado pois está fechado/resolvido.");
                    }
                    
                    free_list_service(call_service, &logs);
                    enter();
                    if (params.returned_call_id_aux != 9999 && params.returned_call_id_aux != 9997) {
                        pre_log();
                        printf(GREEN "Chamado atualizado com sucesso!\n" RESET);
                        adicionar_log_dinamico(&logs, "Chamado atualizado com sucesso.");
                    } 
                    break;
                case 3:
                    printf(GREEN "Mostrando todos os chamados...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando todos os chamados.");
                    
                    call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                    list_calls_service(call_service, 9, 9, 0, &logs);
                        
                    free_list_service(call_service, &logs);
                    enter();
                    break;
                case 4: 
                    printf(GREEN "Mostrando lista de baixa prioridade (normal)...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando lista de baixa prioridade (normal).");
                    
                    call_service = concat_call_list(NULL, call_list_fifo, &logs);
                    list_calls_service(call_service, 9, 9, 0, &logs);
                    
                    free_list_service(call_service, &logs);
                    enter();
                    break;
                case 5:
                    printf(GREEN "Mostrando prioridades e status para seleção.\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando prioridades e status para seleção.");
                    select_parameter(&params.priority_filter, &params.status_filter, &logs);
                    clear();
                    
                    pre_log();
                    printf(GREEN "Mostrando lista por prioridades e status selecionado...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Mostrando lista por prioridades e status selecionado.");
                    
                    call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                    list_calls_service(call_service, params.priority_filter, params.status_filter, 0, &logs);
                    
                    free_list_service(call_service, &logs);
                    enter();
                    break;
                case 6:
                    if (params.last_opened_call_id) {
                        printf(GREEN "Mostrando último chamado aberto/atualizado...\n" RESET);
                        adicionar_log_dinamico(&logs, "Mostrando último chamado aberto/atualizado.");
                        
                        call_service = concat_call_list(call_list_heap, call_list_fifo, &logs);
                        print_calls(call_service, params.last_opened_call_id, &logs);
                        enter();
                    } else {
                        printf(RED "Não há último chamado aberto/atualizado.\n" RESET);
                        adicionar_log_dinamico(&logs, "Não há último chamado aberto/atualizado.");
                    }
                    
                    break;
                case 17:
                    printf(GREEN "Mostrando logs do sistema...\n" RESET);
                    adicionar_log_dinamico(&logs, "Mostrando logs do sistema.");
                    
                    print_logs(logs);
                    line();
                    
                    enter();
                    break;
                case 18: 
                    printf(GREEN "Abrindo menu do administrador...\n" RESET);
                    adicionar_log_dinamico(&logs, "Abrindo menu do administrador.");
                    
                    params.is_logged_in = login(params.is_logged_in, arv_tec, nome_usuario_logado, &logs);
                    
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
                case 99: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    adicionar_log_dinamico(&logs, "Saindo do sistema.");
                    break;
                default: 
                    printf(RED "Opção inválida.\n" RESET); 
                    adicionar_log_dinamico(&logs, "Opção inválida.");
                    break;
            }
        }
    } while (opcao != 99);
    
    if(call_list_heap != NULL) free_heap(call_list_heap, &logs);
    if(call_list_fifo != NULL) free_fifo(call_list_fifo, &logs);
    if(call_history != NULL) free_list_service(call_history, &logs);
    if(call_suspend != NULL) free_list_service(call_suspend, &logs);
    if(arv_tec != NULL) free_arv(arv_tec, &logs);
    if(arv_items != NULL) free_arv(arv_items, &logs);
    
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
    
    liberar_logs(logs);
    
    header();

    printf("\n");
    footer();
    return 0;
}