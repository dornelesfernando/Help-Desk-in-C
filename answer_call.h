#ifndef ANSWER_CALL_H
#define ANSWER_CALL_H

    #include <stdio.h>
    #include <ctype.h>
    
    #include "menu.h"
    #include "logs.h"
    #include "services.h"
    #include "structs.h"
    #include "list_func.h"
    
    int answer_call(CallHeap *call_list_heap, CallFIFO *call_list_fifo, CallService *call_history, CallService *call_suspend, Arv *arv_items, Arv *arv_func, char **logs);
    int answer_call_tecnic(CallService *call_history, CallService *call_suspend, Arv *arv_items, Arv *arv_tec, const char *nome_usuario_logado, char **logs);   

#endif // ANSWER_CALL_H