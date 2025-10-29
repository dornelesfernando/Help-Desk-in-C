#include "list_calls.h"

int list_calls_service(CallService *call_list, int priority, int status, int select_control, char **logs) {
    
    // Init params
    int scanf_control = 0;
    int selected_id = 0;
    int print_caunt = 0;
    char priority_name[20];
    char status_name[20];
    
    char log_message[128];

    if(call_list == NULL && call_list->size == 0) {
        return 9999;
    } else {
        if(priority == 9 && status == 9) {
            adicionar_log_dinamico(logs, "Listando todos os chamados");
        }else if(priority == 9) {
            snprintf(log_message, sizeof(log_message), "Listando chamados todas as prioridades e status %s\n", get_status_styled(status));
            adicionar_log_dinamico(logs, log_message);
        } else if(status == 9) {
            snprintf(log_message, sizeof(log_message), "Listando chamados de prioridade %s e todos os status\n", get_priority_styled(priority));
            adicionar_log_dinamico(logs, log_message);
        } else {
            snprintf(log_message, sizeof(log_message), "Listando chamados de prioridade %s e status %s\n", get_priority_styled(priority), get_status_styled(status));
            adicionar_log_dinamico(logs, log_message);
        }
    }

    header();
    line();
    
    // Converte o id para o dado
    switch(priority) {
        case 1:
            strcpy(priority_name, "Baixa");
            break;
        case 2:
            strcpy(priority_name, "Média");
            break;
        case 3:
            strcpy(priority_name, "Alta");
            break;
        case 4:
            strcpy(priority_name, "Urgente");
            break;
        default:
            strcpy(priority_name, "Todos");
            break;
    }
    
    switch(status) {
        case 1:
            strcpy(status_name, "Aberto");
            break;
        case 2:
            strcpy(status_name, "Em Andamento");
            break;
        case 3:
            strcpy(status_name, "Resolvido");
            break;
        case 4:
            strcpy(status_name, "Fechado");
            break;
        default:
            strcpy(status_name, "Todos");
            break;
    }
    
    CallNode *current_node = call_list->head;
    
    while (current_node != NULL) {
        Call *call_data = current_node->data;
        
        if (((!strcmp(get_priority_char(call_data->priority), priority_name)) || priority == 9) 
           && (!(strcmp(get_status_char(call_data->status), status_name)) || status == 9)) {
            
            printf(RED  " Id:                   " RESET BOLD "%d\n", call_data->id);
            printf(CYAN " Título:               " RESET BOLD "%s\n", call_data->title);
            
            if (call_data->desc && call_data->desc[0] != '\0') printf(CYAN " Descrição:            " RESET BOLD "%s\n", call_data->desc);
            
            printf(CYAN " Status:               " RESET "%s\n", get_status_styled(call_data->status));
            printf(CYAN " Prioridade:           " RESET "%s\n", get_priority_styled(call_data->priority));
            printf(CYAN " Nome do solicitante:  " RESET "%s\n", call_data->name);
            if (call_data->email && call_data->email[0] != '\0') printf(CYAN " Email do solicitante: " RESET "%s\n", call_data->email);
            if (call_data->name_func && call_data->name_func[0] != '\0') printf(CYAN " Nome do funcionário:  " RESET "%s\n", call_data->name_func);
            if (call_data->created_at) printf(CYAN " Criado em:            " RESET "%ld\n", call_data->created_at);
            if (call_data->updated_at) printf(CYAN " Atualizado em:        " RESET "%ld\n", call_data->updated_at);
            if (call_data->data_fechamento) printf(CYAN " Data de fechamento:   " RESET "%ld\n", call_data->data_fechamento);
            if (call_data->solution && call_data->solution[0] != '\0') printf(CYAN " Solution:             " RESET "%s\n", call_data->solution);
           
            line();
            
            print_caunt++;
        }
        
        current_node = current_node->next;
    } 
    
    if (print_caunt) {
        if (print_caunt == 1) {
            printf(GREEN "--> [%d]" YELLOW " chamado impresso.\n" RESET, print_caunt);
        } else {
            printf(GREEN "--> [%d]" YELLOW " chamados impressos.\n" RESET, print_caunt);
        }
    } else {
        printf(RED "Não há chamados para serem listados.\n" RESET);
    }

    if (select_control && print_caunt > 0) {
        int id_is_valid = 0;
        do {
            printf(YELLOW "Digite o Id do chamado que deseja atualizar: " RESET);
            scanf_control = scanf("%d", &selected_id);
            
            if(!scanf_control) {
                printf(RED "\nDigite apenas números.\n" RESET);
                id_is_valid = 0;
            } else {
                id_is_valid = 0;
                CallNode *temp_node = call_list->head;
                while (temp_node != NULL) {
                    if (temp_node->data->id == selected_id) {
                        id_is_valid = 1;
                        break;
                    }
                    temp_node = temp_node->next;
                }
                
                if (!id_is_valid) {
                    printf(RED "\nO chamado com ID %d nao existe.\n" RESET, selected_id);
                }
            }
            
            clean_buffer_stdin();
        } while (!scanf_control || !id_is_valid);
    }
    
    line();
    return selected_id;
}

void select_parameter(int *priority, int *status) {
    int selected_control = 0;
    int scanf_control = 0;
    
    header();
    line();
    
    printf(GREEN "  Seleione a prioridade do chamado que deseja consultar\n");
    printf(BLUE  "  [1] " GREEN    "Baixa\n"   RESET);
    printf(BLUE  "  [2] " YELLOW   "Média\n"   RESET);
    printf(BLUE  "  [3] " RED      "Alta\n"    RESET);
    printf(BLUE  "  [4] " BOLD RED "Urgente\n" RESET);
    printf(BLUE  "  [9] " MAGENTA  "Todos\n"   RESET);
    
    do {
        printf(YELLOW "\n  --> Digite a prioridade desejada: " RESET);
        scanf_control = scanf("%d", &selected_control);
        
        if(!(scanf_control)) {
            printf(RED "  - Digite apenas números.\n" RESET);
        } else if (!((selected_control >= 0 && selected_control <= 4) || selected_control == 9)) {
            printf(RED "  - A prioridade deve existir.\n" RESET);
        }
        
        clean_buffer_stdin();
    } while (!(((selected_control >= 0 && selected_control <= 4) || selected_control == 9) && scanf_control));
    
    *priority = selected_control;
    
    line();
    selected_control = 0;
    scanf_control = 0;
    
    printf(GREEN "  Seleione o status do chamado que deseja consultar\n");
    printf(BLUE  "  [1] " YELLOW  "Aberto\n"       RESET);
    printf(BLUE  "  [2] " BLUE    "Em Andamento\n" RESET);
    printf(BLUE  "  [3] " GREEN   "Resolvido\n"    RESET);
    printf(BLUE  "  [4] " BOLD    "Fechado\n"      RESET);
    printf(BLUE  "  [9] " MAGENTA "Todos\n"        RESET);
    
    do {
        printf(YELLOW "\n  --> Digite a prioridade desejada: " RESET);
        scanf_control = scanf("%d", &selected_control);
        
        if(!(scanf_control)) {
            printf(RED "  - Digite apenas números.\n" RESET);
        } else if (!((selected_control >= 0 && selected_control <= 4) || selected_control == 9)) {
            printf(RED "  - A prioridade deve existir.\n" RESET);
        }
        
        clean_buffer_stdin();
    } while (!(((selected_control >= 0 && selected_control <= 4) || selected_control == 9) && scanf_control));
    
    *status = selected_control;
    
    line();
    
    printf("\nPressione ENTER continuar...");
    getchar();
}

