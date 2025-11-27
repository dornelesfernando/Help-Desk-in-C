#include "open_call.h"

Call* open_call(int *id_control, char **logs) {
    char email[100];
    int email_control = 0;
    int scanf_control = 0;
    int priority = 0;
    int item = 0;
    int qtd_item = 0;
    char resposta_sn;
    char log_msg[128];
    
    Call* new_call_data;
    
    new_call_data = (Call*) malloc(sizeof(Call));
    
    if (new_call_data == NULL) {
        printf(RED BOLD "Erro: Falha ao alocar memoria para o chamado!\n" RESET);
        adicionar_log_dinamico(logs, "Erro: Falha ao alocar memoria para o chamado.");
        return NULL;
    }
    adicionar_log_dinamico(logs, "Struct base do chamado inicializado.");
    
    (*id_control)++;
    new_call_data->id = *id_control;
    new_call_data->status = ABERTO;
    new_call_data->created_at = time(NULL);
    
    header();
    printf(GREEN " - Chamado ID:" CYAN " %d " GREEN "sendo criado.\n" RESET, new_call_data->id);
    line();
    printf("  Por favor, preencha os seguintes dados:\n");
    
    printf(GREEN  "   [1] " RESET "Digite seu nome\n");
    printf(GREEN  "   [2] " RESET "Digite seu email\n");
    printf(GREEN  "   [3] " RESET "Título do chamado\n");
    printf(GREEN  "   [4] " RESET "Motivo do chamado\n");
    printf(GREEN  "   [5] " RESET "Prioridade do chamado\n");
    printf(CYAN   "       0) " BLUE     "Baixa\n" RESET);
    printf(CYAN   "       1) " YELLOW   "Média\n" RESET);
    printf(CYAN   "       2) " RED      "Alta\n" RESET);
    printf(CYAN   "       3) " BOLD RED "Urgente\n" RESET);
    
    printf(GREEN  "   [6] " RESET "Item necessário\n");
    printf(CYAN   "       0) " BLUE "Nenhum   " RESET);
    printf(CYAN   "      1) " BLUE "Mouse       " RESET);
    printf(CYAN   "     2) " BLUE "Teclado\n" RESET);
    printf(CYAN   "       3) " BLUE "Cabo HDMI" RESET);
    printf(CYAN   "      4) " BLUE "Monitor     " RESET);
    printf(CYAN   "     5) " BLUE "Impressora\n" RESET);
    printf(CYAN   "       6) " BLUE "Notebook " RESET);
    printf(CYAN   "      7) " BLUE "Cabo de rede" RESET);
    printf(CYAN   "     8) " BLUE "Webcam\n" RESET);
    printf(CYAN   "       9) " BLUE "Fone de ouvido\n" RESET);
    printf(GREEN  "   [7] " RESET "Quantidade do item necessário\n");
    printf(RED    " \n   DIGITE \"" BLUE "!q" RED "\" PARA CANCELAR\n" RESET);
    line();
   
    printf(CYAN  " [1] " RED "--> " RESET);
    scanf(" %99[^\n]", new_call_data->name);
    if (test_cancel(new_call_data->name)) { 
        free(new_call_data); 
        (*id_control)--; 
        clear();
        return NULL; 
    }

    do {
        printf(CYAN  " [2] " RED "--> " RESET);
        scanf(" %99[^\n]", email);
        if (test_cancel(email)) { 
            free(new_call_data); 
            (*id_control)--; 
            clear();
            return NULL; 
        }
    
        char* arroba = strchr(email, '@');
        char* dot = strchr(email, '.');
        
        //Verifica email
        if (!(arroba == NULL || dot == NULL)) {
            strcpy(new_call_data->email, email);
            email_control = 1;
        } else {
            printf(RED  " --> Email inválido\n" RESET);
        }
    } while(!email_control);
    adicionar_log_dinamico(logs, "Email validado");

    printf(CYAN  " [3] " RED "--> " RESET);
    scanf(" %149[^\n]", new_call_data->title);
    if (test_cancel(new_call_data->title)) { 
        free(new_call_data); 
        (*id_control)--; 
        clear();
        return NULL; 
    }
    
    printf(CYAN  " [4] " RED "--> " RESET);
    scanf(" %1023[^\n]", new_call_data->desc);
    if (test_cancel(new_call_data->desc)) { 
        free(new_call_data); 
        (*id_control)--; 
        clear();
        return NULL; 
    }
    
    do {
        printf(CYAN  " [5] " RED "--> " RESET);
        scanf_control = scanf("%d", &priority);
        
        //Verifica a prioridade
        if (scanf_control == 1 && priority >= 0 && priority <= 3) {
            switch (priority) {
                case 0:  new_call_data->priority = BAIXA;   break;
                case 1:  new_call_data->priority = MEDIA;   break;
                case 2:  new_call_data->priority = ALTA;    break;
                case 3:  new_call_data->priority = URGENTE; break;
                default: new_call_data->priority = BAIXA;   break;
            }
        } else {
            printf(RED  " --> Priority inválido\n" RESET);
        }
        
        clean_buffer_stdin();
    } while (!(scanf_control == 1 && priority >= 0 && priority <= 3));
    adicionar_log_dinamico(logs, "Priority validado.");
    
    do {
        printf(CYAN  " [6] " RED "--> " RESET);
        scanf_control = scanf("%d", &item);
        
        //Verifica o item
        if (scanf_control == 1 && item >= 0 && item <= 9) {
            switch (item) {
                case 0:  new_call_data->item = NONE;        break;
                case 1:  new_call_data->item = MOUSE;       break;
                case 2:  new_call_data->item = KEYBOARD;    break;
                case 3:  new_call_data->item = CABO_HDMI;   break;
                case 4:  new_call_data->item = MONITOR;     break;
                case 5:  new_call_data->item = IMPRESSORA;  break;
                case 6:  new_call_data->item = NOTEBOOK;    break;
                case 7:  new_call_data->item = CABO_REDE;   break;
                case 8:  new_call_data->item = WEBCAM;      break;
                case 9:  new_call_data->item = HEADSET;     break;
                default: new_call_data->item = NONE;        break;
            }
        } else {
            printf(RED  " --> Item inválido\n" RESET);
        }

        clean_buffer_stdin();
    } while (!(scanf_control == 1 && item >= 0 && item <= 9));
    adicionar_log_dinamico(logs, "Item validado.");
    
    if (new_call_data->item != NONE) {
        snprintf(log_msg, sizeof(log_msg), "Item solicitado no chamado ID %d.", new_call_data->id);
        adicionar_log_dinamico(logs, log_msg);
        do {
            printf(CYAN  " [7] " RED "--> " RESET);
            scanf_control = scanf("%d", &qtd_item);
            
            if (qtd_item == 0) {
                do {
                    printf(RED  " --> Você informou um item no índice anterior. Tem certeza de que não deseja solicitá-lo mais? (S/N)\n" RESET);
                    printf(CYAN "\n  --> " RESET);
                    scanf_control = scanf(" %c", &resposta_sn);
                    clean_buffer_stdin();
                    
                    resposta_sn = toupper(resposta_sn);
                
                    if (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N')) {
                        printf(RED "Entrada inválida. Digite 'S' para Sim ou 'N' para Não.\n" RESET);
                    }
                } while (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N'));
                
                if (resposta_sn == 'S') {
                    new_call_data->item = NONE;
                    new_call_data->qtd_item = 0;
                    break;
                } else continue;
            } else if (qtd_item < 0) {
                printf(RED "A quantidade não pode ser um valor negativo.\n" RESET);
            } else if (qtd_item > 10) {
                printf(RED "Valor inserido acima do limite de solicitação (10).\n" RESET);
            } else new_call_data->qtd_item = qtd_item;
            
            clean_buffer_stdin();
        } while (!(scanf_control == 1 && (qtd_item > 0 && qtd_item <= 10) || new_call_data->item == NONE));
        adicionar_log_dinamico(logs, "Quantidade do item validado.");
    }

    clear();
    return new_call_data; 
}