#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logs.h"

// Códigos ANSI para cores
#define RESET       "\033[0m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"

void adicionar_log_dinamico(char **logs, char *novo_log) {
    size_t tamanho_atual = (*logs == NULL) ? 0 : strlen(*logs);
    size_t tamanho_novo_log = strlen(novo_log);
    
    //                                                           "|0" ";"
    size_t novo_tamanho_total = tamanho_atual + tamanho_novo_log + 1 + 1;
    
    char *temp = (char*)realloc(*logs, novo_tamanho_total);
    
    //Verifica a alocação
    if (temp == NULL) {
        printf(RED "ERRO: Falha na realocação de memória. Log não adicionado.\n" RESET);
        return;
    }
    
    // Transfere
    *logs = temp;
    
    // primeira adição
    if (tamanho_atual == 0) {
        (*logs)[0] = '\0';
    }
    
    // Adiciona log no fim
    strcat(*logs, novo_log);
    strcat(*logs, ";");
}

void liberar_logs(char *logs) {
    if (logs != NULL) {
        free(logs);
        logs = NULL;
    }
}

void print_logs(char *logs) {
    printf("%s", logs); 
    
    printf("\n"); 
}
