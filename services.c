#include "services.h"

void replace(Call *a, Call *b) {
    Call temp = *a;
    *a = *b;
    *b = temp;
}

// // ====================================================================== HEAP
CallHeap* create_call_list_heap(int capacity, char **logs) {
    
    CallHeap* call_list = (CallHeap*)malloc(sizeof(CallHeap));
    
    if (call_list == NULL) {
        adicionar_log_dinamico(logs, "Falha ao criar lista Heap.");
        return NULL;
    }
    
    call_list->data = (Call*)malloc(capacity * sizeof(Call));
    call_list->capacity = capacity;
    call_list->size = 0;
    
    adicionar_log_dinamico(logs, "Lista Heap criada com sucesso.");
    return call_list;
}

void heap_insert(CallHeap *call, Call data, char **logs) {
    if (call->size == call->capacity) {
        adicionar_log_dinamico(logs, "Overflow do Heap. Tentando expandir.");
        
        int success = expand_heep(call, logs);
        if (!success) {
            adicionar_log_dinamico(logs, "Falha ao expandir. Falha ao inserir chamado.");
            return;
        }
    }
    
    call->size++;
    int index = call->size - 1;
    call->data[index] = data;
    tidying_up(call, index, logs);
    adicionar_log_dinamico(logs, "Chamado adicionado à lista Heap.");
}

void tidying_up(CallHeap *call, int index, char **logs) {
    if (index == 0) {
        adicionar_log_dinamico(logs, "Lista Heap não precisa ser organizada.");
        return;
    }
    
    int father_index = (index - 1) / 2;

    while (index > 0 && get_priority_int(call->data[index].priority) > get_priority_int(call->data[father_index].priority)) {
        replace(&call->data[index], &call->data[father_index]);
        index = father_index;
        father_index = (index - 1) / 2;
    }
    
    adicionar_log_dinamico(logs, "Lista Heap organizada.");
}

int expand_heep(CallHeap *call, char **logs) {
    int new_capacity = call->capacity + 1;
    
    Call *new_data = (Call*) realloc(call->data, new_capacity * sizeof(Call));
    
    if (new_data == NULL) {
        adicionar_log_dinamico(logs, "Falha ao expandir a lista Heap.");
        return 0;
    }
    
    call->data = new_data;
    call->capacity = new_capacity;
    
    char log_msg[128];
    snprintf(log_msg, sizeof(log_msg), "Lista Heap expandida com sucesso. Nova capacidade: %d", new_capacity);
    adicionar_log_dinamico(logs, log_msg);
    return 1;
}

// // ====================================================================== FIFO
CallFIFO* create_call_list_fifo(int capacity, char **logs) {
    CallFIFO* call_list = (CallFIFO*)malloc(sizeof(CallFIFO));
    
    if (call_list == NULL) {
        adicionar_log_dinamico(logs, "Falha ao criar lista FIFO.");
        return NULL;
    }
    
    call_list->data = (Call*)malloc(capacity * sizeof(Call));
    call_list->capacity = capacity;
    call_list->size = 0;
    call_list->front = 0;
    call_list->tail = -1;

    adicionar_log_dinamico(logs, "Lista FIFO criada com sucesso.");
    return call_list;
}

void fifo_enqueue(CallFIFO *call, Call data, char **logs) {
    if (call->size == call->capacity) {
        adicionar_log_dinamico(logs, "Overflow do FIFO. Tentando expandir.");
        
        int success = expand_fifo(call, logs);
        if (!success) {
            adicionar_log_dinamico(logs, "Falha ao expandir. Falha ao inserir chamado.");
            return;
        }
    }
    
    call->tail = (call->tail + 1) % call->capacity;
    call->data[call->tail] = data;
    call->size++;
    adicionar_log_dinamico(logs, "Chamado adicionado à fila FIFO.");
}

int expand_fifo(CallFIFO *call, char **logs) {
    int new_capacity = call->capacity + 1;
    
    Call *new_data = (Call*) realloc(call->data, new_capacity * sizeof(Call));
    
    if (new_data == NULL) {
        adicionar_log_dinamico(logs, "Falha ao expandir a fila FIFO.");
        return 0;
    }
    
    call->data = new_data;
    call->capacity = new_capacity;
    
    char log_msg[128];
    snprintf(log_msg, sizeof(log_msg), "Fila FIFO expandida com sucesso. Nova capacidade: %d", new_capacity);
    adicionar_log_dinamico(logs, log_msg);
    return 1;
}

// =================================================================== Service
CallService *create_call_list_service(char **logs) {
    CallService *call_list = (CallService*) malloc(sizeof(CallService));
    
    if (call_list == NULL) {
        adicionar_log_dinamico(logs, "Falha ao criar lista Service.");
        return NULL;
    }
    
    call_list->head = NULL;
    call_list->tail = NULL;
    call_list->size = 0;
    
    adicionar_log_dinamico(logs, "Lista Service criada com sucesso.");
    return call_list;
}

CallService *concat_call_list(CallHeap *call_list_heap, CallFIFO *call_list_fifo, char **logs) {
    
    CallService *call_list_service = create_call_list_service(logs);
    if (call_list_service == NULL) {
        printf("Falha ao criar lista Service");
        adicionar_log_dinamico(logs, "Falha ao criar lista Service.");
        return NULL;
    }
    
    if(call_list_heap != NULL && call_list_heap->size > 0) {
        for (int i = 0; i < call_list_heap->size; i++) {
            Call *originalCall = &call_list_heap->data[i];
            
            Call *newCall = (Call*) malloc(sizeof(Call));
            if (newCall == NULL) {
                printf("Falha ao alocar copia (Heap)");
                adicionar_log_dinamico(logs, "Falha ao alocar copia (Heap).");
                continue;
            }
            memcpy(newCall, originalCall, sizeof(Call));
            
            insert_at_end_service(call_list_service, newCall, logs);
        }
        
        adicionar_log_dinamico(logs, "Lista Heap adicionada à lista de serviço.");
    }
    
    
    if(call_list_fifo != NULL && call_list_fifo->size > 0) {
        // Adiciona os valores da FIFO    
        for (int i = 0; i < call_list_fifo->size; i++) {
            int index = (call_list_fifo->front + i) % call_list_fifo->capacity;
            
            Call *originalCall = &call_list_fifo->data[index];

            Call *newCall = (Call*) malloc(sizeof(Call));
            if (newCall == NULL) {
                printf("Falha ao alocar copia (FIFO)");
                adicionar_log_dinamico(logs, "Falha ao alocar copia (FIFO).");
                continue; 
            }
            memcpy(newCall, originalCall, sizeof(Call));

            insert_at_end_service(call_list_service, newCall, logs);
        }
        adicionar_log_dinamico(logs, "Fila FIFO adicionada à lista de serviço.");
    }
    
    return call_list_service;
}

void insert_at_end_service(CallService *call_list_service, Call *call, char **logs) {
    if (call_list_service == NULL || call == NULL) return;

    CallNode *newNode = (CallNode*) malloc(sizeof(CallNode));
    if (newNode == NULL) {
        printf("Falha ao alocar nó");
        adicionar_log_dinamico(logs, "Falha ao alocar nó.");
        return;
    }

    newNode->data = call;
    newNode->next = NULL;
    newNode->prev = call_list_service->tail;

    if (call_list_service->head == NULL) {
        call_list_service->head = newNode;
        call_list_service->tail = newNode;
    } else {
        call_list_service->tail->next = newNode;
        call_list_service->tail = newNode;
    }

    call_list_service->size++;
}

// login control
int login(int logado) {
    
    if(logado) {
        return 1;
    } else {

        const char USER[] = "admin";
        const char PASS[] = "admin123";
    
        char user_in[64];
        char pass_in[64];
    
        printf("Usuário: ");
        scanf("%63s", user_in);
    
        printf("Senha: ");
        scanf("%63s", pass_in);
    
        if (strcmp(user_in, USER) == 0 && strcmp(pass_in, PASS) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

void clean_buffer_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int test_cancel(char* input) {
    if (strcmp(input, "!q") == 0) return 1;
    return 0;
}

// Status and Priority
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

// Clean memory
void free_heap(CallHeap *heap, char **logs) {
    if (heap == NULL) return;

    if (heap->data != NULL) {
        free(heap->data);
        heap->data = NULL; 
    }

    free(heap);
    adicionar_log_dinamico(logs, "Lista Heap liberada.");
}

void free_fifo(CallFIFO *fifo, char **logs) {
    if (fifo == NULL) return;

    if (fifo->data != NULL) {
        free(fifo->data);
        fifo->data = NULL;
    }

    free(fifo);
    adicionar_log_dinamico(logs, "Fila FIFO liberada.");
}

void free_list_service(CallService *call_list, char **logs) {
    if (call_list == NULL) return;

    CallNode *current = call_list->head;
    CallNode *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;

        free(temp->data);
        free(temp);
    }

    free(call_list);
    adicionar_log_dinamico(logs, "Lista Service liberada.");
}