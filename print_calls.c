#include "print_calls.h"

void print_calls(CallService *call_list, int selected_id, char **logs) {
    char log_msg[128];
    
    CallNode *current_node = call_list->head;
    Call *call_data = NULL;

    while (current_node != NULL) {
        if (current_node->data->id == selected_id) {
            call_data = current_node->data;
            break;
        }

        current_node = current_node->next;
    }
    
    if (call_data == NULL) {
        printf(RED BOLD "Erro: chamado com ID %d não encontrado.\n" RESET, selected_id);
        snprintf(log_msg, sizeof(log_msg), "Tentativa de visualizar ID %d falhou (nao encontrado).", selected_id);
        adicionar_log_dinamico(logs, log_msg);
        return;
    }
    snprintf(log_msg, sizeof(log_msg), "Chamado ID %d localizado.", selected_id);
    adicionar_log_dinamico(logs, log_msg);
    
    char log_message[128];
    snprintf(log_message, sizeof(log_message), "Listando chamado ID: %d.", call_data->id);
    adicionar_log_dinamico(logs, log_message);
    
    // Buffer para formatar as datas
    char data_str[100];
    struct tm *tm_info;
    
    header();
    line();
    printf("  DETALHES DO CHAMADO ID: " YELLOW "%d" RESET "\n", call_data->id);
    line();
    
    printf(CYAN " Título:     " RESET BOLD "%s\n" RESET, call_data->title);
    printf(CYAN " Status:     " RESET "%s\n", get_status_styled(call_data->status));
    printf(CYAN " Prioridade: " RESET "%s\n", get_priority_styled(call_data->priority));
    
    if (strcmp(call_data->name_func, "") == 0) {
        printf(CYAN " Atribuído a: " RESET "Nenhum técnico atribuído\n");
    } else {
        printf(CYAN " Atribuído a: " RESET YELLOW "%s\n", call_data->name_func);
    }

    printf(MAGENTA "\n--- Solicitante " "-------------------------------------------\n" RESET);
    printf(CYAN " Nome:       " RESET "%s\n", call_data->name);
    printf(CYAN " Email:      " RESET "%s\n", call_data->email);
    
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
        printf(CYAN " Fechado em: " RESET BOLD "%s\n" RESET, data_str);
    }

    printf(MAGENTA "\n--- Descrição do Problema ---------------------------------\n" RESET);
    printf(" %s\n", call_data->desc);

    if (strcmp(call_data->solution, "") != 0) {
        printf(GREEN "\n--- Solução Aplicada --------------------------------------\n" RESET);
        printf(GREEN " %s\n" RESET, call_data->solution);
    }

    line();
}
