#ifndef ITEMS_H
#define ITEMS_H

    // #include <stdio.h>
    // #include <ctype.h>
    
    // #include "menu.h"
    // #include "logs.h"
    #include "services.h"
    #include "structs.h"
    
    void add_items(Arv * arv_items, CallService* call_suspend, CallHeap *call_list_heap, char **logs);

#endif // ITEMS_H