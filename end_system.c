#include <stdio.h>
#include <stdlib.h>

#include "end_system.h"
#include "services.h"
#include "logs.h"
#include "structs.h"

void end_system(FilaPrioridadeMaxima *fila, char *logs, Call *call_list[], int call_list_control) {
    liberar_fila(fila);
    liberar_logs(logs);
    liberar_call_list(call_list, call_list_control);
}

