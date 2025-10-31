#ifndef SERVICES_H
#define SERVICES_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #include "structs.h"
    #include "logs.h"
    
    void replace(Call *a, Call *b);
    
    CallHeap* create_call_list_heap(int capacity, char **logs);
    void heap_insert (CallHeap *call, Call data, char **logs);
    void tidying_up(CallHeap *call, int index, char **logs);
    int expand_heep(CallHeap *call, char **logs);
    
    CallFIFO* create_call_list_fifo(int capacity, char **logs); 
    void fifo_enqueue(CallFIFO *call, Call data, char **logs);
    int expand_fifo(CallFIFO *call, char **logs);
    
    CallService* create_call_list_service(char **logs);
    
    int login(int logado);
    void clean_buffer_stdin();
    int test_cancel(char* input);
    
    const char* get_status_char(StatusEnum s);
    const char* get_priority_char(PriorityEnum p);
    const int get_priority_int(PriorityEnum p);
    
    CallService *concat_call_list(CallHeap *call_list_heap, CallFIFO *call_list_fifo, char **logs);
    void insert_at_end_service(CallService *call_list_service, Call *call, char **logs);
    
    void free_list_service(CallService *call_list, char **logs);
    void free_heap(CallHeap *heap, char **logs);
    void free_fifo(CallFIFO *fifo, char **logs);

#endif // SERVICES_H
