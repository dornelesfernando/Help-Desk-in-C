#include "answer_call.h"

// int answer_call(CallService *call_list, CallHeap *call_list_heap, CallFIFO *call_list_fifo, char **logs) {
    
//     // busca o nó
//     CallNode *current_node = call_list->head;
//     Call *call_data = NULL;

//     while (current_node != NULL) {
//         if (current_node->data->status != RESOLVIDO && current_node->data->status != FECHADO) {
//             call_data = current_node->data;
//             break;
//         }

//         current_node = current_node->next;
//     }
    
//     if (call_data == NULL) {
//         printf(RED BOLD "Erro: Nenhum chamado à ser atendido.\n" RESET);
//         adicionar_log_dinamico(logs, "Erro: Nenhum chamado à ser atendido.");
//         return 9999;
//     }
    
//     int search_control = 0;
//     char resposta_sn;
//     int scanf_control;
    
//     char log_message[128];
//     snprintf(log_message, sizeof(log_message), "Listando chamado ID: %d. para atendimento", call_data->id);
//     adicionar_log_dinamico(logs, log_message);
    
//     // Buffer para formatar as datas
//     char data_str[100];
//     struct tm *tm_info;

//     if (call_data == NULL) {
//         printf(RED BOLD "Erro: chamado não encontrado (NULL).\n" RESET);
//         return 9999;
//     }
    
//     header();
//     printf("  DETALHES DO CHAMADO ID: " YELLOW "%d" RESET " SENDO ATENDIDO\n", call_data->id);
//     line();
    
//     printf(CYAN "Título:     " RESET BOLD "%s\n" RESET, call_data->title);
    
//     printf(CYAN "Status:     " RESET "%s\n", get_status_styled(call_data->status));
    
//     printf(CYAN "Prioridade: " RESET "%s\n", get_priority_styled(call_data->priority));
    
//     if (strcmp(call_data->name_func, "") == 0) {
//         printf(CYAN " Atribuído a: " RESET "Nenhum técnico atribuído\n");
//     } else {
//         printf(CYAN "Atribuído a: " RESET YELLOW "%s\n", call_data->name_func);
//     }

//     printf(MAGENTA "\n--- Solicitante " "-------------------------------------------\n" RESET);
//     printf(CYAN "Nome:       " RESET "%s\n", call_data->name);
//     printf(CYAN "Email:      " RESET "%s\n", call_data->email);
    
//     printf(MAGENTA "\n--- Histórico ---------------------------------------------\n" RESET);
    
//     tm_info = localtime(&call_data->created_at);
//     strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
//     printf(CYAN " Criado em:  " RESET "%s\n", data_str);

//     if (call_data->updated_at > 0) {
//         tm_info = localtime(&call_data->updated_at);
//         strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
//         printf(CYAN " Atualizado: " RESET "%s\n", data_str);
//     }
    
//     if (call_data->data_fechamento > 0) {
//         tm_info = localtime(&call_data->data_fechamento);
//         strftime(data_str, sizeof(data_str), "%d/%m/%Y às %H:%M:%S", tm_info);
//         printf(CYAN " Fechado em: " RESET BOLD "%s\n", data_str);
//     }

//     printf(MAGENTA "\n--- Descrição do Problema ---------------------------------\n" RESET);
//     printf(RESET "%s\n", call_data->desc);

//     if (strcmp(call_data->solution, "") != 0) {
//         printf(GREEN "\n--- Solução Aplicada --------------------------------------\n" RESET);
//         printf(GREEN "%s\n" RESET, call_data->solution);
//     }
        
//     line();
//     printf(RED " [9] " YELLOW "Retornar ao menu\n" RESET);
//     line();
//     line();
//     printf(CYAN "\n Digite o seu nome: " RESET);
//     printf(YELLOW "\n  --> " RESET);
//     scanf(" %99[^\n]", call_data->name_func);
//     clean_buffer_stdin();
    
//     do {
//         printf(CYAN "\n Esse chamado está finalizado? (S/N)" RESET);
//         printf(CYAN "\n  --> " RESET);
//         scanf_control = scanf(" %c", &resposta_sn);
//         clean_buffer_stdin();
        
//         resposta_sn = toupper(resposta_sn);
    
//         if (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N')) {
//             printf(RED "Entrada inválida. Digite 'S' para Sim ou 'N' para Não.\n" RESET);
//         }
    
//     } while (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N'));
    
//     if (resposta_sn == 'S') {
//         printf(GREEN "\nPor favor, descreva a solução aplicada:" RESET);
//         printf(GREEN "\n  --> " RESET);
//         scanf(" %1023[^\n]", call_data->solution);
//         clean_buffer_stdin();
        
//         call_data->status = RESOLVIDO;
//         call_data->data_fechamento = time(NULL);
        
//         printf(GREEN "Chamado marcado como finalizado.\n" RESET);
    
//     } else {
//         call_data->status = EM_ANDAMENTO;
//         printf(YELLOW "O chamado não foi finalizado.\n" RESET);
//     }
    
//     call_data->updated_at = time(NULL);
    
//     // Atualiza o dado na sua fila raiz (fifo ou heap)
//     if (call_list_heap != NULL) {
//         for (int i = 0; i < call_list_heap->size; i++) {
//             if (call_list_heap->data[i].id == call_data->id) {
//                 call_list_heap->data[i] = *call_data;
//                 search_control = 1;
//                 break;
//             }
//         }
//     }

//     if (!search_control && call_list_fifo != NULL) {
//         for (int i = 0; i < call_list_fifo->size; i++) {
//             int index = (call_list_fifo->front + i) % call_list_fifo->capacity;
            
//             if (call_list_fifo->data[index].id == call_data->id) {
//                 call_list_fifo->data[i] = *call_data;
//                 break;
//             }
//         }
//     }
    
//     clear();
//     return call_data->id;
// }