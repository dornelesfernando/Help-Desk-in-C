#include <stdio.h>

#include <stdlib.h> // --- REMOVER NO PROJETO FINAL
#include <string.h> // --- REMOVER NO PROJETO FINAL

// Códigos ANSI para cores
#define RESET       "\033[0m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"
#define CYAN        "\033[36m"
#define YELLOW      "\033[33m"

#include "services.h"
#include "structs.h"
#include "menu.h"
#include "logs.h"

#include "init_system.h"
#include "end_system.h"
#include "open_call.h"
#include "print_calls.h"
#include "list_calls.h"
#include "update_call.h"

int main() {
    
    // Variáveis de log
    char *logs = NULL;
    char log_message[128];

    // int login_control = 0;
    // int logs_control = 0;
    // int last_call_oppened = 0;
    // int scanf_control = 0;
    // int selected_id = 0;
    // int returned_id = 0;
    // int priority_control = 9;
    // int status_control = 9;

    // Parâmetros do sistema
    Params params;
    
    init_system(&params);
    
    adicionar_log_dinamico(&logs, "Log's de inicialização:");
    adicionar_log_dinamico(&logs, "Parâmetros carregados");
    
    //Lista de chamados
    int call_list_size = 100;
    Call* call_list[call_list_size];
    int call_list_control = 0;
    
    snprintf(log_message, sizeof(log_message), "Lista de chamados inicializada com tamanho %d.", call_list_size);
    adicionar_log_dinamico(&logs, log_message);
    
    // Adiciona dados para teste ==================================================
    for (int i = 0; i < 3; i++) {
        Call* new_call_data = (Call*) malloc(sizeof(Call));
    
        if (new_call_data == NULL) {
            printf(RED "ERRO CRÍTICO: Falha ao alocar memória para o chamado %d!\n" RESET, i + 1);
            return 0;
        }
    
        params.id_control++;
        new_call_data->id = params.id_control;
        new_call_data->status = ABERTO;
    
        // preenche dados específicos de cada chamado
        if (i == 0) {
            strcpy(new_call_data->name,  "Chamado 1");
            strcpy(new_call_data->email, "email@01.com");
            strcpy(new_call_data->title, "Título de chamado 1");
            strcpy(new_call_data->desc,  "Uma descrição para o chamado 1");
            new_call_data->priority = BAIXA;
        } else if (i == 1) {
            strcpy(new_call_data->name,  "Chamado 2");
            strcpy(new_call_data->email, "email@02.com");
            strcpy(new_call_data->title, "Título de chamado 2");
            strcpy(new_call_data->desc,  "Uma descrição para o chamado 2");
            new_call_data->priority = MEDIA;
        } else {
            strcpy(new_call_data->name,  "Chamado 3");
            strcpy(new_call_data->email, "email@03.com");
            strcpy(new_call_data->title, "Título de chamado 3");
            strcpy(new_call_data->desc,  "Uma descrição para o chamado 3");
            new_call_data->priority = URGENTE;
        }
    
        call_list[call_list_control++] = new_call_data;
    }

    
    // ==============================================================================
    
    // init_system(Init parms);
    // init_system();
    
    FilaPrioridadeMaxima *fila = criar_fila_prioridade_maxima(10, &logs);
    
    // ======================= MAIN =======================
    adicionar_log_dinamico(&logs, "Sistema inicializado com sucesso!");
    int opcao;
    do {
        header();
        menu(login_control);
        
        do {
            scanf_control = scanf("%d", &opcao);
            clean_buffer_stdin();
            
            if(!scanf_control) printf(RED "Digite apenas números.\n" YELLOW "Selecione uma opção: " RESET);
            
        } while (!scanf_control);
        
        // Menus
        pre_log();
        if (login_control) {
            switch (opcao) {
                case 1: 
                    printf(GREEN "Atendendo chamado...\n" RESET);
                    break;
                case 2: 
                    printf(GREEN "Cancelando chamado...\n" RESET); 
                    break;
                case 3: 
                    clear();
                    selected_id = list_calls(call_list, call_list_control, 9, 9, 1, &logs);
                    clear();
                    
                    if (selected_id == 9999) {
                        printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    } else {
                        printf(GREEN "Atualizando chamado...\n" RESET); 
                        update_call(call_list[selected_id - 1], login_control, &logs);
                    }
                    
                    clear();
                    printf(GREEN "Chamado atualizado com sucesso!\n" RESET);
                    break;
                case 7:
                    clear();
                    print_logs(logs);
                    line();
                    break;
                case 8: 
                    clear();
                    printf(GREEN "Abrindo menu do principal...\n" RESET);
                    login_control = 0; 
                    break;
                case 9: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    break;
                default: 
                    clear();
                    printf(RED "Opção inválida!\n" RESET); 
                    break;
            }
        } else {
            switch (opcao) {
                case 1: 
                    printf(GREEN "Abrindo chamado...\n" RESET);
                    clear();
                    Call* call_list_pointer = open_call(&params.id_control, &logs);
                    clear();
                    
                    pre_log();
                    if (call_list_pointer != NULL) {
                        last_call_oppened = call_list_pointer->id;
                        call_list[call_list_control] = call_list_pointer;
                        call_list_control++;
                        printf(GREEN "Chamado ID:" CYAN " %d " GREEN "criado com sucesso!\n" RESET, call_list_pointer->id);
                        
                        snprintf(log_message, sizeof(log_message), "Chamado ID: %d criado com sucesso!", call_list_pointer->id);
                        adicionar_log_dinamico(&logs, log_message);
                    } else {
                        printf(RED "Operação cancelada pelo usuário\n" RESET);
                        adicionar_log_dinamico(&logs, "Operação cancelada pelo usuário");
                    }
                    break;
                case 2: 
                    clear();
                    selected_id = list_calls(call_list, call_list_control, 9, 9, 1, &logs);
                    clear();
                    
                    if (selected_id == 9999) {
                        printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    } else {
                        printf(GREEN "Atualizando chamado...\n" RESET); 
                        update_call(call_list[selected_id - 1], 0, &logs);
                    }
                    
                    clear();
                    printf(GREEN "Chamado atualizado com sucesso!\n" RESET);
                    break;
                case 3:
                    clear();
                    printf(GREEN "Mostrando todos os chamados...\n" RESET); 
                    returned_id = list_calls(call_list, call_list_control, 9, 9, 0, &logs);
                    
                    if (returned_id == 9999) {
                        clear();
                        pre_log();
                        printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                    } else {
                        printf("\nPressione ENTER para voltar ao menu...");
                        getchar();
                    }
                    clear();
                     
                    break;
                case 4: 
                    clear();
                    printf(GREEN "Mostrando lista de baixa prioridade (normal)...\n" RESET); 
                    returned_id = list_calls(call_list, call_list_control, 1, 9, 0, &logs);
                    
                    if (returned_id == 9999) {
                        clear();
                        pre_log();
                        printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                        
                        printf("\n\nPressione ENTER para voltar ao menu...");
                        getchar();
                    } else {
                        printf("\nPressione ENTER para voltar ao menu...");
                        getchar();
                    }
                    clear();
                    
                    break;
                case 5:
                    clear();
                    select_parameter(&priority_control, &status_control);
                    clear();
                    
                    printf(GREEN "Mostrando lista por prioridades e status selecionado...\n" RESET); 
                    printf("%d", call_list_control);
                    returned_id = list_calls(call_list, call_list_control, priority_control, status_control, 0, &logs);
                    
                    if (returned_id == 9999) {
                        clear();
                        pre_log();
                        printf(RED "Não há chamados cadastrados no sistema\n" RESET);
                        
                        printf("\n\nPressione ENTER para voltar ao menu...");
                        getchar();
                    } else {
                        printf("\nPressione ENTER para voltar ao menu...");
                        getchar();
                    }
                    
                    clear();
                    break;
                case 6:
                    clear();
                    if (last_call_oppened) {
                        printf(GREEN "Mostrando último chamado aberto...\n" RESET);
                        print_calls(call_list[last_call_oppened - 1], &logs);
                        
                        printf("\nPressione ENTER para voltar ao menu...");
                        getchar(); 
                        clear();
                    } else {
                        printf(RED "Não há último chamado aberto.\n" RESET);
                    }
                    break;
                case 7:
                    clear();
                    printf(GREEN "Mostrando logs do sistema...\n" RESET);
                    print_logs(logs);
                    line();
                    break;
                case 8: 
                    printf(GREEN "Abrindo menu do administrador...\n" RESET);
                    login_control = login(login_control);
                    
                    clear();
                    
                    pre_log();
                    if (login_control) {
                        printf(GREEN "Login realizado com sucesso!\n" RESET);
                    } else {
                        printf(RED "Falha ao fazer login.\n" RESET);
                    }
                    break;
                case 9: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    break;
                default: 
                    clear();
                    printf(RED "Opção inválida!\n" RESET); 
                    break;
            }
        }
    } while (opcao != 9);
    logs_control = 0;
    printf("Deseja ler os log's de encerramento do sistema?\n[1] - Sim \n[0] - Não\n"); 
    scanf("%d", &logs_control);
    
    clear();
    
    // Falta adicionar o controle de logs
    if(logs_control) {
        printf("Log's de saída:\n"); 
    }
    
    end_system(fila, logs, call_list, call_list_control);
    header();

    printf("\n");
    footer();
    return 0;
}


// int main() {

    // inserir(fila, 3);
    // inserir(fila, 5);
    // inserir(fila, 9);
    // inserir(fila, 1);
    // inserir(fila, 6);
    // inserir(fila, 9); // Inserção de valor duplicado

    // printf("Valor máximo: %d\n", extrair_maximo(fila));
    // printf("Valor máximo: %d\n", extrair_maximo(fila));
    // printf("Valor máximo: %d\n", extrair_maximo(fila));

// }
