#include "open_call.h"

Call* open_call(int *id_control, char **logs) {
    adicionar_log_dinamico(logs, "Abrindo chamado...");

    char email[100];
    int email_control = 0;
    int scanf_control = 0;
    int level = 0;
    int level_control = 0;
    adicionar_log_dinamico(logs, "Parâmetros de criação de chamado inicializados");
    
    Call* new_call_data;
    
    new_call_data = (Call*) malloc(sizeof(Call));
    
    if (new_call_data == NULL) {
        printf(RED "ERRO CRITICO: Falha ao alocar memoria para o chamado!\n" RESET);
        return NULL;
    }
    adicionar_log_dinamico(logs, "Struct chamado inicializado");
    
    (*id_control)++;
    new_call_data->id = *id_control;
    new_call_data->status = ABERTO;
    new_call_data->created_at = time(NULL);
    
    header();
    printf(GREEN "- Chamado ID:" CYAN " %d " GREEN "sendo criado.\n" RESET, new_call_data->id);
    line();
    printf("Por favor, preencha os seguintes dados:\n");
    
    printf(GREEN  " [1] " RESET "Digite seu nome\n");
    printf(GREEN  " [2] " RESET "Digite seu email\n");
    printf(GREEN  " [3] " RESET "Título do chamado\n");
    printf(GREEN  " [4] " RESET "Motivo do chamado\n");
    printf(GREEN  " [5] " RESET "Prioridade do chamado\n");
    printf(CYAN   "     0) " BLUE "Baixa" RESET);
    printf(CYAN   "     1) " YELLOW "Média" RESET);
    printf(CYAN   "     2) " RED "Alta" RESET);
    printf(CYAN   "     3) " BOLD RED "Urgente\n" RESET);
    printf(RED    " \n DIGITE \"" BLUE "!q" RED "\" PARA CANCELAR\n" RESET);
    line();
   
    printf(CYAN  " [1] " RED "--> " RESET);
    scanf(" %99[^\n]", new_call_data->name);
    if (test_cancel(new_call_data->name)) { free(new_call_data); (*id_control)--; return NULL; }

    do {
        printf(CYAN  " [2] " RED "--> " RESET);
        scanf(" %99[^\n]", email);
        if (test_cancel(email)) { free(new_call_data); (*id_control)--; return NULL; }
    
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
    if (test_cancel(new_call_data->title)) { free(new_call_data); (*id_control)--; return NULL; }
    
    printf(CYAN  " [4] " RED "--> " RESET);
    scanf(" %1023[^\n]", new_call_data->desc);
    if (test_cancel(new_call_data->desc)) { free(new_call_data); (*id_control)--; return NULL; }
    
    do {
        printf(CYAN  " [5] " RED "--> " RESET);
        scanf_control = scanf("%d", &level);
        
        //Verifica level
        if (scanf_control == 1 && level >= 0 && level <= 3) {
            switch (level) {
                case 0:
                    new_call_data->priority = BAIXA;
                    break;
                case 1:
                    new_call_data->priority = MEDIA;
                    break;
                case 2:
                    new_call_data->priority = ALTA;
                    break;
                case 3:
                    new_call_data->priority = URGENTE;
                    break;
                default:
                    new_call_data->priority = BAIXA;
                    break;
            }
            level_control = 1;
        } else {
            printf(RED  " --> Level inválido\n" RESET);
        }
        
                clean_buffer_stdin();
    } while (!(scanf_control && level_control));
    adicionar_log_dinamico(logs, "Level validado!");

    return new_call_data; 
}