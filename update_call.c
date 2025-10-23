#include "update_call.h"

void update_call(Call *call_data, int login_control, char **logs) {
    while (1) {
        int index = 0;
        int index_control = 0;
        int scanf_control = 0;
        int status = 0;
        int priority_control = 0;
        int priority = 0;
        char email[100];
        int email_control = 0;
        
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
        printf("  DETALHES DO CHAMADO ID: " YELLOW "%d" RESET "\n", call_data->id);
        line();
        
        printf(YELLOW " [%d] " CYAN "Título:     " RESET BOLD "%s\n" RESET, ++index, call_data->title);
        
        if (login_control) {
            printf(YELLOW " [%d] " CYAN "Status:     " RESET "%s\n", ++index, get_status_styled(call_data->status));
        }
        
        printf(YELLOW " [%d] " CYAN "Prioridade: " RESET "%s\n", ++index, get_priority_styled(call_data->priority));
        
        if (login_control) {
            if (strcmp(call_data->name_func, "") == 0) {
                printf(CYAN " Atribuído a: " RESET "Nenhum técnico atribuído\n");
            } else {
                printf(YELLOW " [%d] " CYAN "Atribuído a: " RESET YELLOW "%s\n", ++index, call_data->name_func);
            }
        }
    
        printf(MAGENTA "\n--- Solicitante " "-------------------------------------------\n" RESET);
        printf(YELLOW " [%d] " CYAN "Nome:       " RESET "%s\n", ++index, call_data->name);
        printf(YELLOW " [%d] " CYAN "Email:      " RESET "%s\n", ++index, call_data->email);
        
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
        printf(YELLOW " [%d] " RESET "%s\n", ++index, call_data->desc);
    
        if (login_control) {
            if (strcmp(call_data->solution, "") != 0) {
                printf(GREEN "\n--- Solução Aplicada --------------------------------------\n" RESET);
                printf(YELLOW " [%d] " GREEN "%s\n" RESET, ++index, call_data->solution);
            }
        }
        
        line();
        printf(RED " [9] " YELLOW "Retornar ao menu\n" RESET);
        line();
        
        do {
            printf(YELLOW "\n  --> Digite o índex da informação que deseja alterar: " RESET);
            scanf_control = scanf("%d", &index_control);
            
            if (scanf_control) if (index_control == 9) return;
    
            if (scanf_control == 1 && index_control > 0 && index_control <= index) {
                if(login_control) {
                    switch (index_control) {
                        case 1:
                            printf(CYAN  " [1] " RED "--> " RESET);
                            scanf(" %149[^\n]", call_data->title);
                            break;
                        case 2:
                            printf(CYAN   "     0) " YELLOW "Aberto" RESET);
                            printf(CYAN   "     1) " BLUE "Em Andamento" RESET);
                            printf(CYAN   "     2) " GREEN "Resolvido" RESET);
                            printf(CYAN   "     3) " BOLD "Fechado" RESET);
                            
                            do {
                                printf(CYAN  "\n [2] " RED "--> " RESET);
                                scanf_control = scanf("%d", &status);
                                
                                //Verifica status
                                if (scanf_control == 1 && status >= 0 && status <= 3) {
                                    switch (status) {
                                        case 0:
                                            call_data->status = ABERTO;
                                            break;
                                        case 1:
                                            call_data->status = EM_ANDAMENTO;
                                            break;
                                        case 2:
                                            call_data->status = RESOLVIDO;
                                            break;
                                        case 3:
                                            call_data->status = FECHADO;
                                            break;
                                        default:
                                            call_data->status = ABERTO;
                                            break;
                                    }
                                    priority_control = 1;
                                } else {
                                    printf(RED  " --> Status inválido\n" RESET);
                                }
                                
                                clean_buffer_stdin();
                            } while (!(scanf_control == 1 && status >= 0 && status <= 3));
                            adicionar_log_dinamico(logs, "Status validado!");
                            break;
                        case 3:
                            printf(CYAN   "     0) " BLUE "Baixa" RESET);
                            printf(CYAN   "     1) " YELLOW "Média" RESET);
                            printf(CYAN   "     2) " RED "Alta" RESET);
                            printf(CYAN   "     3) " BOLD RED "Urgente" RESET);
                            
                            do {
                                printf(CYAN  "\n [3] " RED "--> " RESET);
                                scanf_control = scanf("%d", &priority);
                                
                                //Verifica priority
                                if (scanf_control == 1 && priority >= 0 && priority <= 3) {
                                    switch (priority) {
                                        case 0:
                                            call_data->priority = BAIXA;
                                            break;
                                        case 1:
                                            call_data->priority = MEDIA;
                                            break;
                                        case 2:
                                            call_data->priority = ALTA;
                                            break;
                                        case 3:
                                            call_data->priority = URGENTE;
                                            break;
                                        default:
                                            call_data->priority = BAIXA;
                                            break;
                                    }
                                    priority_control = 1;
                                } else {
                                    printf(RED  " --> priority inválido\n" RESET);
                                }
                                
                                clean_buffer_stdin();
                            } while (!(scanf_control && priority_control));
                            adicionar_log_dinamico(logs, "priority validado!");
                            break;
                        case 4:
                            printf(CYAN  " [4] " RED "--> " RESET);
                            scanf(" %99[^\n]", call_data->name_func);
                            break;
                        case 5:
                            printf(CYAN  " [5] " RED "--> " RESET);
                            scanf(" %99[^\n]", call_data->name);
                            break;
                        case 6:
                            do {
                                printf(CYAN  " [6] " RED "--> " RESET);
                                scanf(" %99[^\n]", email);
    
                                char* arroba = strchr(email, '@');
                                char* dot = strchr(email, '.');
                                
                                //Verifica email
                                if (!(arroba == NULL || dot == NULL)) {
                                    strcpy(call_data->email, email);
                                    email_control = 1;
                                } else {
                                    printf(RED  " --> Email inválido\n" RESET);
                                }
                            } while(!email_control);
                            adicionar_log_dinamico(logs, "Email validado");
                            break;
                        case 7:
                            printf(CYAN  " [7] " RED "--> " RESET);
                            scanf(" %1023[^\n]", call_data->desc);
                            break;
                        case 8:
                            printf(CYAN  " [8] " RED "--> " RESET);
                            scanf(" %1023[^\n]", call_data->solution);
                            break;
                    }
                } else {
                    switch (index_control) {
                        case 1:
                            
                            printf(CYAN  " [1] " RED "--> " RESET);
                            scanf(" %149[^\n]", call_data->title);
                            break;
                        case 2:
                            do {
                                printf(CYAN   "     0) " BLUE "Baixa" RESET);
                                printf(CYAN   "     1) " YELLOW "Média" RESET);
                                printf(CYAN   "     2) " RED "Alta" RESET);
                                printf(CYAN   "     3) " BOLD RED "Urgente\n" RESET);
                                
                                printf(CYAN  " [2] " RED "--> " RESET);
                                scanf_control = scanf("%d", &priority);
                                
                                //Verifica priority
                                if (scanf_control == 1 && priority >= 0 && priority <= 3) {
                                    switch (priority) {
                                        case 0:
                                            call_data->priority = BAIXA;
                                            break;
                                        case 1:
                                            call_data->priority = MEDIA;
                                            break;
                                        case 2:
                                            call_data->priority = ALTA;
                                            break;
                                        case 3:
                                            call_data->priority = URGENTE;
                                            break;
                                        default:
                                            call_data->priority = BAIXA;
                                            break;
                                    }
                                    priority_control = 1;
                                } else {
                                    printf(RED  " --> priority inválido\n" RESET);
                                }
                                
                                clean_buffer_stdin();
                            } while (!(scanf_control && priority_control));
                            adicionar_log_dinamico(logs, "priority validado!");
                            break;
                        case 3:
                            printf(CYAN  " [3] " RED "--> " RESET);
                            scanf(" %99[^\n]", call_data->name);
                            break;
                        case 4:
                            do {
                                printf(CYAN  " [4] " RED "--> " RESET);
                                scanf(" %99[^\n]", email);
    
                                char* arroba = strchr(email, '@');
                                char* dot = strchr(email, '.');
                                
                                //Verifica email
                                if (!(arroba == NULL || dot == NULL)) {
                                    strcpy(call_data->email, email);
                                    email_control = 1;
                                } else {
                                    printf(RED  " --> Email inválido\n" RESET);
                                }
                            } while(!email_control);
                            adicionar_log_dinamico(logs, "Email validado");
                            break;
                        case 5:
                            printf(CYAN  " [5] " RED "--> " RESET);
                            scanf(" %1023[^\n]", call_data->desc);
                            break;
                    }
                }
            } else {
                printf(RED  " --> Index inválido\n" RESET);
            }
            
        } while (!(scanf_control && index_control > 0 && index_control <= index));
        
        clear();
    }
}