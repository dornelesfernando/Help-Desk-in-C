#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "menu.h"
#include "services.h"

// Códigos ANSI para cores
#define RESET       "\033[0m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"
#define CYAN        "\033[36m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"

Call* open_call(int *id_control) {

    char email[100];
    int email_control = 0;
    int scanf_control = 0;
    int level = 0;
    int level_control = 0;
    
    Call* new_call_data;
    
    new_call_data = (Call*) malloc(sizeof(Call));
    
    if (new_call_data == NULL) {
        printf(RED "ERRO CRITICO: Falha ao alocar memoria para o chamado!\n" RESET);
        return NULL;
    }
    
    (*id_control)++;
    new_call_data->id = *id_control;
    new_call_data->status = ABERTO;
    new_call_data->created_at = time(NULL);
    
    header(0);
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
    printf(CYAN   "     3) " MAGENTA "Urgente\n" RESET);
    line();
   
    printf(CYAN  " [1] " RED "--> " RESET);
    scanf(" %99[^\n]", new_call_data->name);

    do {
        printf(CYAN  " [2] " RED "--> " RESET);
        scanf(" %99[^\n]", email);
    
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

    printf(CYAN  " [3] " RED "--> " RESET);
    scanf(" %149[^\n]", new_call_data->title);
    
    printf(CYAN  " [4] " RED "--> " RESET);
    scanf(" %1023[^\n]", new_call_data->desc);
    
    
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
    
    pre_log();
    printf(GREEN "Chamado ID:" CYAN " %d " GREEN "criado com sucesso!\n" RESET, new_call_data->id);
    return new_call_data; 
}