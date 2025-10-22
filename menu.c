#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

// Códigos ANSI para cores
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define CYAN        "\033[36m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define RED         "\033[31m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"

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



void header(int clear_control) {
    if(clear_control) clear();
    line();
    ascii_logo();
    printf(GREEN BOLD "                     SISTEMA HELP DESK\n" RESET);
    printf("\n");
    printf(YELLOW "- Bem-vindo ao sistema de ajuda técnica!\n" RESET);
    line();
}

void footer() {
    line();
    printf(MAGENTA "- Até a próxima!\n");
    printf("- Criado por: " CYAN "~Dorneles\n" RESET);
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
    printf(GREEN  " [2] " RESET "Verificar chamados\n");
    printf(GREEN  " [3] " RESET "Ver lista normal\n");
    printf(GREEN  " [4] " RESET "Ver lista de prioridade\n");
    printf(GREEN  " [5] " RESET "Ver ultimo chamado aberto\n");
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
    printf(GREEN  " [3] " RESET "Priorizar chamado\n");
    printf(CYAN   " [8] " RESET "Acessar menu do principal\n");
    printf(RED    " [9] " RESET "Sair do menu do administrador\n");
    printf(BLUE "-------------------------------------------------------------\n" RESET);
    printf(YELLOW "Selecione uma opção: " RESET);
}

void pre_log() {
    clear();
    line();
    printf(CYAN "LOG: " RESET);
}