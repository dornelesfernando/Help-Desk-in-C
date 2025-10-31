#ifndef PRINT_CALLS_H
#define PRINT_CALLS_H

    #include <stdio.h>
    
    #include "menu.h"
    #include "logs.h"
    #include "structs.h"
    
    void print_calls(CallService *call_data, int selected_id, char **logs);

#endif // PRINT_CALLS_H
