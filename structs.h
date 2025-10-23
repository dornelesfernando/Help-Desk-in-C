#ifndef STRUCTS_H
#define STRUCTS_H

#include <time.h>

typedef struct {
    int call_id;
    int is_logged_in;
    int last_opened_call_id;
    int input_status;
    int selected_call_id;
    int returned_call_id;
    int priority_filter;
    int status_filter;
    int call_list_size;
    int call_list_index;
    int request_log;

    char log_message[128];
} MainParams;

typedef struct {
	int *dados;
	int capacidade;
	int tamanho;
} FilaPrioridadeMaxima;

// Defile the status
typedef enum {
    ABERTO,
    EM_ANDAMENTO,
    RESOLVIDO,
    FECHADO
} StatusEnum;

// Define the priority
typedef enum {
    BAIXA,
    MEDIA,
    ALTA,
    URGENTE
} PriorityEnum;


typedef struct {

    // --- Identificação ---
    int id;

    // --- Quem ---
    char name[100];
    char email[100];

    // --- O Quê ---
    char title[150];
    char desc[1024];

    // --- Como ---
    StatusEnum status;
    PriorityEnum priority;
    char name_func[100];

    // --- Quando ---
    time_t created_at;
    time_t updated_at;
    time_t data_fechamento;

    // --- Resolução ---
    char solution[1024];

} Call;

#endif // STRUCTS_H
