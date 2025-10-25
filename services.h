#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

void replace(Call *a, Call *b);

CallHeap* create_call_list_heap(int capacity);
void heap_insert (CallHeap *call, Call data);
void tidying_up(CallHeap *call, int index);

CallFIFO* create_call_list_fifo(int capacity);
void fifo_enqueue(CallFIFO *call, Call data);

CallService* create_call_list_service();

int login(int logado);
void liberar_call_list(Call *call_list[], int call_list_control);
void clean_buffer_stdin();
int test_cancel(char* input);

const char* get_status_char(StatusEnum s);
const char* get_priority_char(PriorityEnum p);
const int get_priority_int(PriorityEnum p);

#endif // SERVICES_H
