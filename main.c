#include <stdio.h>

// Códigos ANSI para cores
#define RESET       "\033[0m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"

#include "services.h"
#include "menu.h"
#include "init_system.h"
#include "end_system.h"
#include "logs.h"
#include "open_call.h"

int main() {
    // transformar tudo isso em um struct chamado Init parms
    char *logs = NULL;
    int id_control = 0;
    int login_control = 0;
    int logs_control = 0;
    int clear_control = 1;
    int last_call_oppened = 0;
    
    //Lista de chamados
    Call* call_list[100];
    int call_list_control = 0;
    
    // init_system(Init parms);
    
    printf("Deseja ler os log's de inicialização do sistema?\n[1] - Sim \n[0] - Não\n"); 
    scanf("%d", &logs_control);
    
    // Controlador dos logs de inicialização
    if(logs_control) {
        clear_control = 0; // Evita que logs sejam apagados na criação do header
        adicionar_log_dinamico(&logs, "Log's de inicialização:");
    }

    // init_system();
    FilaPrioridadeMaxima *fila = criar_fila_prioridade_maxima(10, logs_control, &logs);
    
    print_logs(logs);
    
    // ======================= MAIN =======================
    int opcao;
    do {
        header(clear_control);
        menu(login_control);
        scanf("%d", &opcao);
        
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
                    printf(GREEN "Priorizando chamado...\n" RESET); 
                    break;
                case 8: 
                    printf(GREEN "Abrindo menu do principal...\n" RESET);
                    login_control = login(login_control);
                    clear_control = 0;
                    break;
                case 9: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    break;
                default: 
                    printf(RED "Opção inválida!\n" RESET); 
                    break;
            }
        } else {
            switch (opcao) {
                case 1: 
                    printf(GREEN "Abrindo chamado...\n" RESET);
                    Call* call_list_pointer = open_call(&id_control);
                    
                    last_call_oppened = call_list_pointer->id;
                    
                    if (call_list_pointer != NULL) {
                        call_list[call_list_control] = call_list_pointer;
                        call_list_control++;
                    }
                    
                    
                    break;
                case 2: 
                    printf(GREEN "Listando chamados...\n" RESET); 
                    break;
                case 3: 
                    printf(GREEN "Mostrando lista normal...\n" RESET); 
                    break;
                case 4:
                    printf(GREEN "Mostrando lista de prioridade...\n" RESET); 
                    break;
                case 5:
                    if (last_call_oppened) {
                        printf(GREEN "Mostrando último chamado aberto...\n" RESET);
                    } else {
                        printf(RED "Não há último chamado aberto.\n" RESET);
                    }
                    break;
                case 8: 
                    printf(GREEN "Abrindo menu do administrador...\n" RESET);
                    login_control = login(login_control);
                    clear_control = 0;
                    break;
                case 9: 
                    printf(GREEN "Saindo do sistema...\n" RESET); 
                    break;
                default: 
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
        clear_control = 1; // Evita que logs sejam apagados na criação do header
        printf("Log's de saída:\n"); 
    } else {
        clear_control = 0;
    }
    
    end_system(fila, logs, call_list, call_list_control);
    header(clear_control);

    
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
