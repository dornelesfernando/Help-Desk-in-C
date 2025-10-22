#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "services.h"
#include "logs.h"

// Códigos ANSI para cores
#define RESET       "\033[0m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"


FilaPrioridadeMaxima* criar_fila_prioridade_maxima(int capacidade, int logs_control, char **logs) {
    FilaPrioridadeMaxima *fila = (FilaPrioridadeMaxima*)malloc(sizeof(FilaPrioridadeMaxima));
    fila->dados = (int*)malloc(capacidade * sizeof(int));
    fila->capacidade = capacidade;
    fila->tamanho = 0;
    
    if(logs_control) adicionar_log_dinamico(logs, "Fila Criada!");

    return fila;
}

void liberar_fila(FilaPrioridadeMaxima *fila) {
    free(fila->dados);
    free(fila);
    
    printf("Fila Liberada!\n");
}

int login(int logado) {
    
    if(logado) {
        return 1;
    } else {

        const char USER[] = "admin";
        const char PASS[] = "admin123";
    
        char user_in[64];
        char pass_in[64];
    
        printf("Usuário: ");
        scanf("%63s", user_in);  // lê string (até 63 chars + '\0')
    
        printf("Senha: ");
        scanf("%63s", pass_in);  // lê string (até 63 chars + '\0')
    
        if (strcmp(user_in, USER) == 0 && strcmp(pass_in, PASS) == 0) {
            printf(GREEN "Login realizado com sucesso!\n" RESET);
            return 1;
        } else {
            printf(RED "Falha ao fazer login.\n" RESET);
            return 0;
        }
    }
}

void liberar_call_list(Call *call_list[], int call_list_control) {
    for (int i = 0; i < call_list_control; i++) {
        free(call_list[i]);
    }
}

void clean_buffer_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}