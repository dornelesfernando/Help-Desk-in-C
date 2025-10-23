#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

int login(int logado);
void liberar_call_list(Call *call_list[], int call_list_control);
void clean_buffer_stdin();
int test_cancel(char* input);
const char* get_status_char(StatusEnum s);
const char* get_priority_char(PriorityEnum p);

#endif // SERVICES_H
