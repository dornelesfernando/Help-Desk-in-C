#include "init_system.h"

void init_system(MainParams *params, char **logs) {
    
//     // logs
//     params->log_message[128];

//     // call list
//     params-> call_list_size = 100;
//     params->call_list_index = 0;
    params->call_id = 0;

//     // id's
    params->last_opened_call_id = 0;
//     params->selected_call_id = 0;
//     params->returned_call_id = 0;

    // controlers
    params->is_logged_in = 0;
//     params->input_status = 0;
//     params->request_log = 0;
    
//     // filters
//     params->priority_filter = 9;
//     params->status_filter = 9;

    adicionar_log_dinamico(logs, "Parâmetros carregados.");
}

