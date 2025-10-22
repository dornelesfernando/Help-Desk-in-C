#ifndef LIST_CALLS_H
#define LIST_CALLS_H

#include "structs.h"

int list_calls(Call *call_list[], int call_list_control, int priority, int status, int select_control, char **logs);
void select_parameter(int *priority, int *status);

#endif // LIST_CALLS_H
