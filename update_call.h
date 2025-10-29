#ifndef UPDATE_CALL_H
#define UPDATE_CALL_H

#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "logs.h"
#include "services.h"
#include "structs.h"

void update_call(CallService *call_list, CallHeap *call_list_heap, CallFIFO *call_list_fifo, int selected_id, int login_control, int cancel_control, char **logs);
#endif // UPDATE_CALL_H
