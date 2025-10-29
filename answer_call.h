#ifndef ANSWER_CALL_H
#define ANSWER_CALL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "menu.h"
#include "logs.h"
#include "services.h"
#include "structs.h"

int answer_call(CallService *call_list, CallHeap *call_list_heap, CallFIFO *call_list_fifo, char **logs);
#endif // ANSWER_CALL_H
