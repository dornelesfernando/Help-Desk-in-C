#ifndef LIST_CALLS_H
#define LIST_CALLS_H

#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "logs.h"
#include "structs.h"
#include "services.h"

int list_calls_service(CallService *call_list, int priority, int status, int select_control, char **logs);
void select_parameter(int *priority, int *status);

#endif // LIST_CALLS_H
