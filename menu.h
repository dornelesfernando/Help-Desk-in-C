#ifndef MENU_H
#define MENU_H

#include "structs.h"

void clear();
void line();
void ascii_logo();
void header();
void footer();
void menu_inicial();
void menu_administrador();
void menu(int perm);
void pre_log();     
const char* get_status_styled(StatusEnum s);
const char* get_priority_styled(PriorityEnum p);

#endif // MENU_H
