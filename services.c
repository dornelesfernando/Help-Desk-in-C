#include "services.h"

// ====================================================================== HEAP
void replace(Call *a, Call *b) {
    Call temp = *a;
    *a = *b;
    *b = temp;
}

CallHeap* create_call_list_heap(int capacity) {
    
    CallHeap* call_list = (CallHeap*)malloc(sizeof(CallHeap*));
    
    if (call_list == NULL) return NULL;
    
    call_list->data = (Call*)malloc(capacity * sizeof(Call));
    call_list->capacity = capacity;
    call_list->size = 0;
    
    return call_list;
}

void heap_insert (CallHeap *call, Call data) {
    if (call->size == call->capacity) {
        printf("Overflow do heap\n");
        return;
    }
    
    call->size++;
    int index = call->size - 1;
    call->data[index] = data;
    tidying_up(call, index);
}

void tidying_up(CallHeap *call, int index) {
    if (index == 0) return;

    int father_index = (index - 1) / 2;

    while (index > 0 && get_priority_int(call->data[index].priority) > get_priority_int(call->data[father_index].priority)) {
        replace(&call->data[index], &call->data[father_index]);
        index = father_index;
        father_index = (index - 1) / 2;
    }
}

// ====================================================================== FIFO
CallFIFO* create_call_list_fifo(int capacity) {
    
    CallFIFO* call_list = (CallFIFO*)malloc(sizeof(CallFIFO*));
    
    if (call_list == NULL) return NULL;
    
    call_list->data = (Call*)malloc(capacity * sizeof(Call));
    call_list->capacity = capacity;
    call_list->size = 0;
    call_list->front = 0;
    call_list->tail = -1;

    return call_list;
}

void fifo_enqueue(CallFIFO *call, Call data) {
    if (call->size == call->capacity) {
        printf("Overflow da fifo\n");
        return;
    }
    
    call->size++;
    call->data[call->tail] = data;
    call->tail = (call->tail + 1) % call->capacity;
}

// =================================================================== Service
CallService *create_call_list_service() {
    CallService *call_list = (CallService*) malloc(sizeof(CallService));
    
    if (call_list == NULL) return NULL;
    
    call_list->head = NULL;
    call_list->tail = NULL;
    call_list->size = 0;
    
    return call_list;
}

void concat_call_list(CallHeap *call_list_heap[], CallFIFO *call_list_fifo[]) {
    
}

int login(int logado) {
    
    if(logado) {
        return 1;
    } else {

        const char USER[] = "admin";
        const char PASS[] = "admin123";
    
        char user_in[64];
        char pass_in[64];
    
        printf("Usuário: ");
        scanf("%63s", user_in);  // lê string (até 63 chars + '\0')
    
        printf("Senha: ");
        scanf("%63s", pass_in);  // lê string (até 63 chars + '\0')
    
        if (strcmp(user_in, USER) == 0 && strcmp(pass_in, PASS) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

// void liberar_call_list(Call *call_list[], int call_list_control) {
//     for (int i = 0; i < call_list_control; i++) {
//         free(call_list[i]);
//     }
// }

void clean_buffer_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int test_cancel(char* input) {
    if (strcmp(input, "!q") == 0) return 1;
    return 0;
}

const char* get_status_char(StatusEnum s) {
    switch (s) {
        case ABERTO:           return "Aberto";
        case EM_ANDAMENTO:     return "Em Andamento";
        case RESOLVIDO:        return "Resolvido";
        case FECHADO:          return "Fechado";
        default:               return "Desconhecido";
    }
}

const char* get_priority_char(PriorityEnum p) {
    switch (p) {
        case BAIXA:   return "Baixa";
        case MEDIA:   return "Média";
        case ALTA:    return "Alta";
        case URGENTE: return "Urgente";
        default:      return "Desconhecida";
    }
}

const int get_priority_int(PriorityEnum p) {
    switch (p) {
        case BAIXA:   return 0;
        case MEDIA:   return 1;
        case ALTA:    return 2;
        case URGENTE: return 3;
        default:      return -1;
    }
}