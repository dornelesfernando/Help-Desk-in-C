#include "answer_call.h"

int answer_call(CallHeap *call_list_heap, CallFIFO *call_list_fifo, CallService *call_history, CallService *call_suspend, Arv *arv_items, Arv *arv_func, char **logs) {
    char log_msg[128];
    int current_call_search_control = 0;
    int search_control = 0;
    char resposta_sn;
    int scanf_control = 0;
    int suspend_control = 0;
    Call *call_data = NULL;
    
    // Buffer para formatar as datas
    char data_str[100];
    struct tm *tm_info;
    
    header();
    
    // Verifica chamados suspensos
    if(call_suspend->size > 0) {
        int reativados = reativar_chamados_suspensos(arv_items, call_suspend, call_list_heap, logs);
        
        if (reativados > 0) {
            printf(GREEN "\n  >>> ATENÇÃO: %d Chamado(s) Suspenso(s) foram reativados e \nretornaram à fila de prioridade! <<<\n" RESET, reativados);
        } else {
            printf(BOLD RED "\n  Nenhum chamado suspenso pôde ser reativado.\n" RESET);
        }
    }
    
    if (call_list_heap == NULL && call_list_fifo == NULL) {
        printf(RED BOLD "  Erro: Nenhum chamado à ser atendido.\n" RESET);
        adicionar_log_dinamico(logs, "Erro: Nenhum chamado à ser atendido.");
        return 9999;
    }
    
    if (arv_func == NULL || arv_func->raiz == NULL) {
        printf(BOLD RED "  Nenhum funcionário cadastrado no sistema.\n" RESET);
        return 9999;
    }

    do {
        if (call_list_heap != NULL) {
    		for (int i = 0; i < call_list_heap->size; i++) {
    		    call_data = &call_list_heap->data[i];
    		    current_call_search_control = 1;
    		    break;
    		}
    	}
    
    	if (!current_call_search_control && call_list_fifo != NULL) {
    	    call_data = &call_list_fifo->data[call_list_fifo->front];
    	}
    	
    	if (call_data == NULL) {
            printf(RED BOLD "  Erro: Nenhum chamado à ser atendido.\n" RESET);
            adicionar_log_dinamico(logs, "  Erro: Nenhum chamado à ser atendido.");
            return 9999;
        }
    	
    	if (call_data->item != NONE && call_data->qtd_item > 0) {
            
            const char *nome_item_necessario = get_item_char(call_data->item);
            ArvNo *no_item_estoque = buscar_item(arv_items->raiz, nome_item_necessario);
            
            printf(YELLOW "\n --- Verificando Estoque ---\n" RESET);
            
            if (no_item_estoque != NULL && no_item_estoque->qtd >= call_data->qtd_item) {
                printf(GREEN " Estoque OK: Item '%s' (%d) disponível. Atendimento pode prosseguir.\n" RESET, 
                       nome_item_necessario, no_item_estoque->qtd);
                suspend_control = 0;
                
            } else {
                
                int qtd_disponivel = (no_item_estoque != NULL) ? no_item_estoque->qtd : 0;
                printf(RED " Estoque INSUFICIENTE: Item '%s' (Necessário: %d | Disponível: %d).\n" RESET, 
                       nome_item_necessario, call_data->qtd_item, qtd_disponivel);
                
                printf(RED BOLD " Chamado será marcado para suspensão.\n" RESET);
                suspend_control = 1;
            }
            
            line();
        } else {
            suspend_control = 0;
        }
        
        if(suspend_control) {
            call_data->status = SUSPENSO;
            Call *newCall = (Call*) malloc(sizeof(Call));
            
            memcpy(newCall, call_data, sizeof(Call));
            
            insert_at_end_service(call_suspend, newCall, logs);
            adicionar_log_dinamico(logs, "Chamado adicionado à lista de chamados suspensos.");
            free(newCall);
            
            if (call_list_heap != NULL) {
        		for (int i = 0; i < call_list_heap->size; i++) {
        			if (call_list_heap->data[i].id == call_data->id) {
        				heap_remove(call_list_heap, logs);
        				adicionar_log_dinamico(logs, "Chamado removido da lista Heap.");
        				search_control = 1;
        				call_data = NULL;
        				break;
        			}
        		}
        	}
        
        	if (!search_control && call_list_fifo != NULL) {
        		for (int i = 0; i < call_list_fifo->size; i++) {
        			int index = (call_list_fifo->front + i) % call_list_fifo->capacity;
        			if (call_list_fifo->data[index].id == call_data->id) {
        				fifo_dequeue(call_list_fifo, logs);
        				adicionar_log_dinamico(logs, "Chamado removido da fila FIFO.");
        				call_data = NULL;
        				break;
        			}
        		}
        	}
        	
        	enter();
        	clear();
            pre_log();
            printf("Selecionando próximo chamado da fila\n");
            header();
        }
    } while (call_data == NULL);
    
    const char *nome_item = get_item_char(call_data->item);
    
    snprintf(log_msg, sizeof(log_msg), "Listando chamado ID: %d para atendimento", call_data->id);
    adicionar_log_dinamico(logs, log_msg);

    printf("  DETALHES DO CHAMADO ID: " YELLOW "%d" RESET " SENDO ATENDIDO\n", call_data->id);
    line();
    
    printf(CYAN "Título:     " RESET BOLD "%s\n" RESET, call_data->title);
    
    printf(CYAN "Status:     " RESET "%s\n", get_status_styled(call_data->status));
    
    printf(CYAN "Prioridade: " RESET "%s\n", get_priority_styled(call_data->priority));
    
    if (strcmp(call_data->name_func, "") == 0) {
        printf(CYAN " Atribuído a: " RESET "Nenhum técnico atribuído\n");
    } else {
        printf(CYAN "Atribuído a: " RESET YELLOW "%s\n", call_data->name_func);
    }

    printf(MAGENTA "\n--- Solicitante " "-------------------------------------------\n" RESET);
    printf(CYAN "Nome:       " RESET "%s\n", call_data->name);
    printf(CYAN "Email:      " RESET "%s\n", call_data->email);
    
    printf(MAGENTA "\n--- Histórico ---------------------------------------------\n" RESET);
    
    tm_info = localtime(&call_data->created_at);
    strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
    printf(CYAN " Criado em:  " RESET "%s\n", data_str);

    if (call_data->updated_at > 0) {
        tm_info = localtime(&call_data->updated_at);
        strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
        printf(CYAN " Atualizado: " RESET "%s\n", data_str);
    }
    
    if (call_data->data_fechamento > 0) {
        tm_info = localtime(&call_data->data_fechamento);
        strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
        printf(CYAN " Fechado em: " RESET BOLD "%s\n", data_str);
    }

    printf(MAGENTA "\n--- Descrição do Problema ---------------------------------\n" RESET);
    printf(RESET "%s\n", call_data->desc);

    if (strcmp(call_data->solution, "") != 0) {
        printf(GREEN "\n--- Solução Aplicada --------------------------------------\n" RESET);
        printf(GREEN "%s\n" RESET, call_data->solution);
    }
        
    line();
    printf(RED " [9] " YELLOW "Retornar ao menu\n" RESET);
    line();
    line();
    
    char nome_tecnico_temp[100];
    ArvNo *no_tecnico_encontrado = NULL;
    int nome_valido = 0;

    printf(CYAN "\n Técnicos Disponíveis no Sistema (Digite o nome para atribuir):" RESET);
    list_func(arv_func, logs); 
    
    do {
        printf(YELLOW "\n  --> Digite o NOME COMPLETO do técnico para atribuição \n(ou 9 para retornar): " RESET);
        scanf_control = scanf(" %99[^\n]", nome_tecnico_temp);
        clean_buffer_stdin();

        if (scanf_control != 1) {
            printf(RED "  - Erro de leitura. Tente novamente.\n" RESET);
            continue;
        }

        if (strcmp(nome_tecnico_temp, "9") == 0) {
            strcpy(call_data->name_func, "");
            printf(YELLOW "Atribuição de técnico cancelada.\n" RESET);
            nome_valido = 1;
            break;
        }

        no_tecnico_encontrado = buscar_funcionario_por_nome(arv_func->raiz, nome_tecnico_temp);

        if (no_tecnico_encontrado == NULL) {
            printf(RED "  - Técnico '%s' não encontrado no sistema. Tente novamente ou digite 9.\n" RESET, nome_tecnico_temp);
        } else {
            strcpy(call_data->name_func, no_tecnico_encontrado->name);
            printf(GREEN "Chamado atribuído a: %s\n" RESET, call_data->name_func);
            
            if (strcmp(call_data->name_func, "") != 0) {
                atribuir_chamado_a_tecnico(arv_func, call_data->name_func, call_data, logs);
                
                call_data->status = EM_ANDAMENTO;
            }
            
            nome_valido = 1;
        }

    } while (!nome_valido);
    
    do {
        printf(CYAN "\n Esse chamado está finalizado? (S/N)" RESET);
        printf(CYAN "\n  --> " RESET);
        scanf_control = scanf(" %c", &resposta_sn);
        clean_buffer_stdin();
        
        resposta_sn = toupper(resposta_sn);
    
        if (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N')) {
            printf(RED "Entrada inválida. Digite 'S' para Sim ou 'N' para Não.\n" RESET);
        }
    
    } while (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N'));
    
    if (resposta_sn == 'S') {
        printf(GREEN "\nPor favor, descreva a solução aplicada:" RESET);
        printf(GREEN "\n  --> " RESET);
        scanf(" %1023[^\n]", call_data->solution);
        clean_buffer_stdin();
        
        call_data->status = RESOLVIDO;
        call_data->data_fechamento = time(NULL);
        
        printf(GREEN "Chamado marcado como finalizado.\n" RESET);
        
        // Adiciona na call_history
        Call *newCall = (Call*) malloc(sizeof(Call));
        
        memcpy(newCall, call_data, sizeof(Call));
        
        insert_at_end_service(call_history, newCall, logs);
        decrement(arv_items->raiz, nome_item, call_data->qtd_item, logs);
        adicionar_log_dinamico(logs, "Chamado adicionado à lista history.");
        free(newCall);
    } else {
        call_data->status = EM_ANDAMENTO;
        printf(YELLOW "O chamado não foi finalizado.\n" RESET);
        
        if (suspend_control) {
            call_data->status = SUSPENSO;
            Call *newCall = (Call*) malloc(sizeof(Call));
            
            memcpy(newCall, call_data, sizeof(Call));
            
            insert_at_end_service(call_suspend, newCall, logs);
            adicionar_log_dinamico(logs, "Chamado adicionado à lista de chamados suspensos.");
            free(newCall);
        }
    }
    
    call_data->updated_at = time(NULL);
    
    // Atualiza o dado na sua fila raiz (fifo ou heap)
	if (call_list_heap != NULL) {
		for (int i = 0; i < call_list_heap->size; i++) {
			if (call_list_heap->data[i].id == call_data->id) {
				heap_remove(call_list_heap, logs);
				adicionar_log_dinamico(logs, "Chamado removido da lista Heap.");
				search_control = 1;
				break;
			}
		}
	}

	if (!search_control && call_list_fifo != NULL) {
		for (int i = 0; i < call_list_fifo->size; i++) {
			int index = (call_list_fifo->front + i) % call_list_fifo->capacity;
			if (call_list_fifo->data[index].id == call_data->id) {
				fifo_dequeue(call_list_fifo, logs);
				adicionar_log_dinamico(logs, "Chamado removido da fila FIFO.");
				break;
			}
		}
	}
    
    return call_data->id;
}

int answer_call_tecnic(CallService *call_history, CallService *call_suspend, Arv *arv_items, Arv *arv_tec, const char *nome_usuario_logado, char **logs) {
    char log_msg[128];
    char resposta_sn;
    int scanf_control = 0;
    int suspend_control = 0;
    Call *call_data = NULL;
    CallService *lista_pessoal_tecnico = NULL;
    
    char data_str[100];
    struct tm *tm_info;
    
    header();
    printf(BOLD CYAN "--- ATENDIMENTO DE CHAMADOS PESSOAIS ---\n" RESET);
    line();

    ArvNo *tecnico_no = buscar_funcionario_por_nome(arv_tec->raiz, nome_usuario_logado);

    if (tecnico_no == NULL) {
        printf(RED BOLD "ERRO: Nó do técnico logado não encontrado na árvore.\n" RESET);
        adicionar_log_dinamico(logs, "Erro: Técnico logado não encontrado na árvore para atendimento.");
        return 9999;
    }
    
    lista_pessoal_tecnico = tecnico_no->datas;

    if (lista_pessoal_tecnico == NULL || lista_pessoal_tecnico->head == NULL) {
        printf(RED BOLD "Nenhum chamado atribuído a você (%s) no momento.\n" RESET, nome_usuario_logado);
        adicionar_log_dinamico(logs, "Nenhum chamado atribuído ao técnico logado.");
        return 9999;
    }

    CallNode *primeiro_chamado_node = lista_pessoal_tecnico->head;
    call_data = primeiro_chamado_node->data;
    const char *nome_item_necessario = get_item_char(call_data->item);

    if (call_data->item != NONE && call_data->qtd_item > 0) {
        ArvNo *no_item_estoque = buscar_item(arv_items->raiz, nome_item_necessario);
        
        printf("\n--- Verificando Estoque ---\n");
        
        if (no_item_estoque == NULL || no_item_estoque->qtd < call_data->qtd_item) {
            
            int qtd_disponivel = (no_item_estoque != NULL) ? no_item_estoque->qtd : 0;
            printf(RED "Estoque INSUFICIENTE: Item '%s' (Necessário: %d | Disponível: %d).\n" RESET, 
                   nome_item_necessario, call_data->qtd_item, qtd_disponivel);
            
            printf(RED BOLD "Chamado será marcado para suspensão.\n" RESET);
            suspend_control = 1;
        } else {
            printf(GREEN "Estoque OK: Item '%s' (%d) disponível. Atendimento pode prosseguir.\n" RESET, 
                   nome_item_necessario, no_item_estoque->qtd);
        }
    } else {
        suspend_control = 0;
    }

    if (suspend_control) {
        call_data->status = SUSPENSO;
        
        Call *newCall = (Call*) malloc(sizeof(Call));
        if (newCall == NULL) return 9999;
        
        memcpy(newCall, call_data, sizeof(Call));
        insert_at_end_service(call_suspend, newCall, logs);
        adicionar_log_dinamico(logs, "Chamado adicionado à lista de chamados suspensos por falta de estoque.");
        free(newCall);

        remover_call_service(lista_pessoal_tecnico, call_data->id);
        
        printf(YELLOW BOLD "\nATENÇÃO: Chamado ID %d suspenso e removido da sua lista. Retornando ao menu.\n" RESET, call_data->id);
        return call_data->id;
    }
    
    snprintf(log_msg, sizeof(log_msg), "Atendendo chamado pessoal ID: %d", call_data->id);
    adicionar_log_dinamico(logs, log_msg);

    printf("  DETALHES DO CHAMADO ID: " YELLOW "%d" RESET " SENDO ATENDIDO\n", call_data->id);
    line();
    
    printf(CYAN "Título:     " RESET BOLD "%s\n" RESET, call_data->title);
    printf(CYAN "Status:     " RESET "%s\n", get_status_styled(call_data->status));
    printf(CYAN "Prioridade: " RESET "%s\n", get_priority_styled(call_data->priority));
    printf(CYAN "Atribuído a: " RESET YELLOW "%s\n", call_data->name_func);
    
    printf(MAGENTA "\n--- Solicitante " "-------------------------------------------\n" RESET);
    printf(CYAN "Nome:       " RESET "%s\n", call_data->name);
    printf(CYAN "Email:      " RESET "%s\n", call_data->email);
    
    printf(MAGENTA "\n--- Histórico ---------------------------------------------\n" RESET);
    
    tm_info = localtime(&call_data->created_at);
    strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
    printf(CYAN " Criado em:  " RESET "%s\n", data_str);

    if (call_data->updated_at > 0) {
        tm_info = localtime(&call_data->updated_at);
        strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
        printf(CYAN " Atualizado: " RESET "%s\n", data_str);
    }
    
    if (call_data->data_fechamento > 0) {
        tm_info = localtime(&call_data->data_fechamento);
        strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
        printf(CYAN " Fechado em: " RESET BOLD "%s\n", data_str);
    }

    printf(MAGENTA "\n--- Descrição do Problema ---------------------------------\n" RESET);
    printf(RESET "%s\n", call_data->desc);

    if (strcmp(call_data->solution, "") != 0) {
        printf(GREEN "\n--- Solução Aplicada --------------------------------------\n" RESET);
        printf(GREEN "%s\n" RESET, call_data->solution);
    }
    
    line();
    printf(RED " [9] " YELLOW "Retornar ao menu\n" RESET);
    line();
    line();
    
    strncpy(call_data->name_func, nome_usuario_logado, 99);
    call_data->name_func[99] = '\0';

    do {
        printf(CYAN "\n Esse chamado está finalizado? (S/N)" RESET);
        printf(CYAN "\n  --> " RESET);
        scanf_control = scanf(" %c", &resposta_sn);
        clean_buffer_stdin();
        
        resposta_sn = toupper(resposta_sn);
    
        if (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N')) {
            printf(RED "Entrada inválida. Digite 'S' para Sim ou 'N' para Não.\n" RESET);
        }
    
    } while (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N'));
    
    if (resposta_sn == 'S') {
        printf(GREEN "\nPor favor, descreva a solução aplicada:" RESET);
        printf(GREEN "\n  --> " RESET);
        scanf(" %1023[^\n]", call_data->solution);
        clean_buffer_stdin();
        
        call_data->status = RESOLVIDO;
        call_data->data_fechamento = time(NULL);
        
        printf(GREEN "Chamado marcado como finalizado.\n" RESET);
        
        decrement(arv_items->raiz, nome_item_necessario, call_data->qtd_item, logs);
        
        Call *newCall = (Call*) malloc(sizeof(Call));
        if (newCall == NULL) return 9999;
        
        memcpy(newCall, call_data, sizeof(Call));
        insert_at_end_service(call_history, newCall, logs);
        adicionar_log_dinamico(logs, "Chamado adicionado à lista history.");
        free(newCall);
        
        remover_call_service(lista_pessoal_tecnico, call_data->id);
    } else {
        call_data->status = EM_ANDAMENTO;
        printf(YELLOW "O chamado não foi finalizado e permanece na sua lista.\n" RESET);
    }
    
    call_data->updated_at = time(NULL);
    
    return call_data->id;
}