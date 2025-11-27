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
    if(perm == 1) {
        menu_administrador();
    } else if(perm == 2) {
        menu_tecnico();  
    } else {
        menu_inicial();
    }
}

void menu_inicial() {
    printf(BOLD "\n                       MENU PRINCIPAL\n" RESET);
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(GREEN  " [ 1] " RESET "Abrir chamado\n");
    printf(GREEN  " [ 2] " RESET "Atualizar chamado\n");
    printf(GREEN  " [ 3] " RESET "Ver todos os chamados em aberto\n");
    printf(GREEN  " [ 4] " RESET "Ver lista de baixa prioridade (normal)\n");
    printf(GREEN  " [ 5] " RESET "Ver lista por prioridade e status\n");
    printf(GREEN  " [ 6] " RESET "Ver ultimo chamado aberto/atualizado\n");
    printf(YELLOW " [17] " RESET "Visualizar log's\n");
    printf(CYAN   " [18] " RESET "Acessar menu do administrador\n");
    printf(RED    " [99] " RESET "Sair do sistema\n");
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(YELLOW " Selecione uma opção: " RESET);
}

void menu_administrador() {
    printf(BOLD "\n                       MENU ADMINISTRADOR\n" RESET);
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(GREEN  " [ 1] " RESET "Atender chamado\n");
    printf(GREEN  " [ 2] " RESET "Cancelar chamado\n");
    printf(GREEN  " [ 3] " RESET "Atualizar chamado\n");
    printf(GREEN  " [ 4] " RESET "Ver todos os chamados em aberto\n");
    printf(GREEN  " [ 5] " RESET "Ver todos os chamados no histórico\n");
    printf(GREEN  " [ 6] " RESET "Ver todos os chamados suspensos\n");
    printf(GREEN  " [ 7] " RESET "Cadastrar funcionário\n");
    printf(GREEN  " [ 8] " RESET "Cadastrar/Adicionar item\n");
    printf(GREEN  " [ 9] " RESET "Visualizar funcionários cadastrados\n");
    printf(GREEN  " [10] " RESET "Visualizar itens no estoque\n");
    printf(YELLOW " [17] " RESET "Visualizar log's\n");
    printf(CYAN   " [18] " RESET "Voltar ao menu principal\n");
    printf(RED    " [99] " RESET "Sair do sistema\n");
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(YELLOW " Selecione uma opção: " RESET);
}

void menu_tecnico() {
    printf(BOLD "\n                       MENU TÉCNICO\n" RESET);
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(GREEN  " [ 1] " RESET "Atender chamado\n");
    printf(GREEN  " [ 2] " RESET "Cancelar chamado\n");
    printf(YELLOW " [17] " RESET "Visualizar log's\n");
    printf(CYAN   " [18] " RESET "Voltar ao menu principal\n");
    printf(RED    " [99] " RESET "Sair do sistema\n");
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(YELLOW " Selecione uma opção: " RESET);
}

void pre_log() {
    line();
    printf(CYAN "LOG: " RESET);
}

const char* get_status_styled(StatusEnum s) {
    switch (s) {
        case ABERTO:       return YELLOW   "Aberto" RESET;
        case EM_ANDAMENTO: return BLUE     "Em Andamento" RESET;
        case RESOLVIDO:    return GREEN    "Resolvido" RESET;
        case CANCELADO:    return RED BOLD "Cancelado"   RESET;
        case SUSPENSO:     return BOLD     "Suspenso"   RESET;
        default:           return          "Desconhecido";
    }
}

const char* get_priority_styled(PriorityEnum p) {
    switch (p) {
        case BAIXA:     return GREEN   "Baixa"   RESET;
        case MEDIA:     return YELLOW  "Média"   RESET;
        case ALTA:      return RED     "Alta"    RESET;
        case URGENTE:   return BOLD RED "Urgente" RESET;
        case RETORNADO: return BOLD MAGENTA "Retornado" RESET;
        default:        return "Desconhecida";
    }
}

void enter() {
    printf("\n\n  Pressione ENTER para voltar ao menu...");
    getchar();
    clear();
}