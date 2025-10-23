#include "services.h"

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
            return 1;
        } else {
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

int test_cancel(char* input) {
    if (strcmp(input, "!q") == 0) return 1;
    return 0;
}

const char* get_status_char(StatusEnum s) {
    switch (s) {
        case ABERTO:           return "Aberto";
        case EM_ANDAMENTO:     return "Em Andamento";
        case RESOLVIDO:        return "Resolvido";
        case FECHADO:          return "Fechado";
        default:               return "Desconhecido";
    }
}

const char* get_priority_char(PriorityEnum p) {
    switch (p) {
        case BAIXA:   return "Baixa";
        case MEDIA:   return "Média";
        case ALTA:    return "Alta";
        case URGENTE: return "Urgente";
        default:      return "Desconhecida";
    }
}