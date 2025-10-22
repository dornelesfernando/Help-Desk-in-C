#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h> 

#include "menu.h"
#include "logs.h"
#include "structs.h"

// Códigos ANSI para cores
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"
#define YELLOW      "\033[33m"
#define CYAN        "\033[36m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"

void print_calls(Call *call_data, char **logs) {
    char log_message[128];
    snprintf(log_message, sizeof(log_message), "Listando chamado ID: %d.", call_data->id);
    adicionar_log_dinamico(logs, log_message);
    
    // Buffer para formatar as datas
    char data_str[100];
    struct tm *tm_info;

    if (call_data == NULL) {
        printf(RED BOLD "Erro: chamado não encontrado (NULL).\n" RESET);
        return;
    }
    
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
    printf("%s\n", call_data->desc);

    if (strcmp(call_data->solution, "") != 0) {
        printf(GREEN "\n--- Solução Aplicada --------------------------------------\n" RESET);
        printf(GREEN "%s\n" RESET, call_data->solution);
    }

    line();
}

