#include "services.h"

void replace(Call *a, Call *b) {
    Call temp = *a;
    *a = *b;
    *b = temp;
}

// ====================================================================== HEAP
CallHeap* create_call_list_heap(int capacity) {
    
    CallHeap* call_list = (CallHeap*)malloc(sizeof(CallHeap));
    
    if (call_list == NULL) return NULL;
    
    call_list->data = (Call*)malloc(capacity * sizeof(Call));
    call_list->capacity = capacity;
    call_list->size = 0;
    
    return call_list;
}

void heap_insert(CallHeap *call, Call data) {
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
    
    CallFIFO* call_list = (CallFIFO*)malloc(sizeof(CallFIFO));
    
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
    
    call->tail = (call->tail + 1) % call->capacity;
    call->data[call->tail] = data;
    call->size++;
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

CallService *concat_call_list(CallHeap *call_list_heap, CallFIFO *call_list_fifo) {
    
    CallService *call_list_service = create_call_list_service();
    if (call_list_service == NULL) {
       printf("Falha ao criar call_list_service");
        return NULL;
    }
    
    if(call_list_fifo != NULL && call_list_fifo->size > 0) {
        // Adiciona os valores da FIFO    
        for (int i = 0; i < call_list_fifo->size; i++) {
            int index = (call_list_fifo->front + i) % call_list_fifo->capacity;
            
            Call *originalCall = &call_list_fifo->data[index];

            Call *newCall = (Call*) malloc(sizeof(Call));
            if (newCall == NULL) {
                perror("Falha ao alocar copia (FIFO)");
                continue; 
            }
            memcpy(newCall, originalCall, sizeof(Call));

            insert_at_end_service(call_list_service, newCall);
        }
    }
    
    if(call_list_heap != NULL && call_list_heap->size > 0) {
        for (int i = 0; i < call_list_heap->size; i++) {
            Call *originalCall = &call_list_heap->data[i];
            
            Call *newCall = (Call*) malloc(sizeof(Call));
            if (newCall == NULL) {
                perror("Falha ao alocar copia (Heap)");
                continue;
            }
            memcpy(newCall, originalCall, sizeof(Call));
            
            insert_at_end_service(call_list_service, newCall);
        }
    }
    
    return call_list_service;
}

void insert_at_end_service(CallService *call_list_service, Call *call) {
    if (call_list_service == NULL || call == NULL) return;

    CallNode *newNode = (CallNode*) malloc(sizeof(CallNode));
    if (newNode == NULL) {
        perror("Falha ao alocar no");
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

void free_list_service(CallService *call_list) {
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
    printf("Lista liberada da memoria.\n");
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