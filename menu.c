#include "menu.h"

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void line() {
    printf(BLUE "=============================================================" RESET "\n");
}

void ascii_logo() {
    printf(CYAN BOLD);
    printf("   ___ ___         .__        ________                 __    \n");
    printf("  /   |   \\   ____ |  | ______\\______ \\   ____   _____|  | __\n");
    printf(" /    ~    \\_/ __ \\|  | \\____ \\|    |  \\_/ __ \\ /  ___/  |/ /\n");
    printf(" \\    Y    /\\  ___/|  |_|  |_> >    `   \\  ___/ \\___ \\|    < \n");
    printf("  \\___|_  /  \\___  >____/   __/_______  /\\___  >____   >__|_ \\ \n");
    printf("        \\/       \\/     |__|          \\/     \\/     \\/     \\/ \n");
    printf(RESET);
}

void header() {
    line();
    ascii_logo();
    printf(GREEN BOLD "                     SISTEMA HELP DESK\n" RESET);
    printf("\n");
    printf(YELLOW " - Bem-vindo ao sistema de ajuda técnica!\n" RESET);
    line();
}

void footer() {
    line();
    printf(MAGENTA " - Até a próxima!\n");
    printf(" - Criado por: " CYAN "~Dorneles\n" RESET);
    line();
}

void menu(int perm) {
    if(perm) {
        menu_administrador();
    } else {
        menu_inicial();
    }
}

void menu_inicial() {
    printf(BOLD "\n                       MENU PRINCIPAL\n" RESET);
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(GREEN  " [1] " RESET "Abrir chamado\n");
    printf(GREEN  " [2] " RESET "Atualizar chamado\n");
    printf(GREEN  " [3] " RESET "Ver todos os chamados\n");
    printf(GREEN  " [4] " RESET "Ver lista de baixa prioridade (normal)\n");
    printf(GREEN  " [5] " RESET "Ver lista por prioridade e status\n");
    printf(GREEN  " [6] " RESET "Ver ultimo chamado aberto\n");
    printf(YELLOW " [7] " RESET "Visualizar log's\n");
    printf(CYAN   " [8] " RESET "Acessar menu do administrador\n");
    printf(RED    " [9] " RESET "Sair do sistema\n");
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(YELLOW "Selecione uma opção: " RESET);
}

void menu_administrador() {
    printf(BOLD "\n                       MENU ADMINISTRADOR\n" RESET);
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(GREEN  " [1] " RESET "Atender chamado\n");
    printf(GREEN  " [2] " RESET "Cancelar chamado\n");
    printf(GREEN  " [3] " RESET "Atualizar chamado\n");
    printf(GREEN  " [4] " RESET "Ver todos os chamados\n");
    printf(YELLOW " [7] " RESET "Visualizar log's\n");
    printf(CYAN   " [8] " RESET "Voltar ao menu principal\n");
    printf(RED    " [9] " RESET "Sair do sistema\n");
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(YELLOW "Selecione uma opção: " RESET);
}

void pre_log() {
    line();
    printf(CYAN "LOG: " RESET);
}

const char* get_status_styled(StatusEnum s) {
    switch (s) {
        case ABERTO:           return YELLOW "Aberto" RESET;
        case EM_ANDAMENTO:     return BLUE   "Em Andamento" RESET;
        case RESOLVIDO:        return GREEN  "Resolvido" RESET;
        case FECHADO:          return BOLD   "Fechado"   RESET;
        default:               return "Desconhecido";
    }
}

const char* get_priority_styled(PriorityEnum p) {
    switch (p) {
        case BAIXA:   return GREEN   "Baixa"   RESET;
        case MEDIA:   return YELLOW  "Média"   RESET;
        case ALTA:    return RED     "Alta"    RESET;
        case URGENTE: return BOLD RED "Urgente" RESET;
        default:      return "Desconhecida";
    }
}

void enter() {
    printf("\n\nPressione ENTER para voltar ao menu...");
    getchar();
    clear();
}