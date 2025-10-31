#ifndef MENU_H
#define MENU_H

    #include <stdlib.h>
    #include <stdio.h>
    
    #include "structs.h"
    #include "config_ANSI.h"
    
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
    void enter();

#endif // MENU_H
