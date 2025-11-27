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
    
    adicionar_log_dinamico(logs, "Lista Heap organizada. (up)");
}

void heap_remove(CallHeap *call, char **logs) {
    if (call->size == 0) {
        adicionar_log_dinamico(logs, "Underflow do Heap. Fila esta vazia.");
        return;
    }
    
    int removed_id = call->data[0].id; 
    call->data[0] = call->data[call->size - 1];
    call->size--;
    
    if (call->size > 0) {
        tidying_down(call, logs);
    }
    tidying_down(call, logs);
    adicionar_log_dinamico(logs, "Chamado removido da lista Heap.");
}

void tidying_down(CallHeap *call, char **logs) {
    int index = 0;
    int did_swap = 0;

    while (1) {
        int largest = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;

        // Verifica se a esquerda existe e é >
        if (left_child < call->size && get_priority_int(call->data[left_child].priority) > get_priority_int(call->data[largest].priority)) {
            largest = left_child;
        }

        if (right_child < call->size && get_priority_int(call->data[right_child].priority) > get_priority_int(call->data[largest].priority)) {
            largest = right_child;
        }

        if (largest == index) {
            break; 
        }

        replace(&call->data[index], &call->data[largest]);
        index = largest;
        did_swap = 1;
    }

    if (did_swap) {
        adicionar_log_dinamico(logs, "Lista Heap organizada. (down)");
    }
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

void fifo_dequeue(CallFIFO *call, char **logs) {
    if (call->size == 0) {
        adicionar_log_dinamico(logs, "Underflow da FIFO. Fila esta vazia.");
        return;
    }
    
    Call removed_call = call->data[call->front];
    call->front = (call->front + 1) % call->capacity;
    call->size--;
    adicionar_log_dinamico(logs, "Chamado removido da fila FIFO.");
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
int login(int logado, Arv *arv_func, char *nome_logado, char **logs) {
    if (logado) {
        return logado;
    } else {
        header();
        const char ADMIN_USER[] = "admin";
        const char ADMIN_PASS[] = "admin123";
        
        char user_in[100]; 
        char pass_in[100];
        char expected_pass[105]; 
        char log_msg[128];

            printf( YELLOW "  LOGIN DE ACESSO\n" RESET);
        line();
        
        printf(GREEN "  Usuário: " RESET);
        scanf(" %99[^\n]", user_in);
        clean_buffer_stdin(); 
        
        printf(CYAN "  Senha: " RESET);
        scanf(" %99s", pass_in);
        
        if (strcmp(user_in, ADMIN_USER) == 0 && strcmp(pass_in, ADMIN_PASS) == 0) {
                printf(GREEN "\n  LOGIN BEM-SUCEDIDO. Bem-vindo(a), Administrador.\n" RESET);
                adicionar_log_dinamico(logs, "LOGIN BEM-SUCEDIDO. Bem-vindo(a), Administrador.");
            strncpy(nome_logado, ADMIN_USER, 99);
            nome_logado[99] = '\0';
            return 1;
        }

        if (arv_func == NULL || arv_func->raiz == NULL) {
                printf("\n  Erro: Usuário ou senha inválidos.\n");
                adicionar_log_dinamico(logs, "Erro: Usuário ou senha inválidos.");
            return 0;
        }

        ArvNo *tecnico = buscar_funcionario_por_nome(arv_func->raiz, user_in);

        if (tecnico != NULL) {
            snprintf(expected_pass, sizeof(expected_pass), "%s123", tecnico->name);
            
            if (strcmp(pass_in, expected_pass) == 0) {
                    printf(GREEN"\n  LOGIN BEM-SUCEDIDO. Bem-vindo(a), %s.\n" RESET, tecnico->name);
                    snprintf(log_msg, sizeof(log_msg), "LOGIN BEM-SUCEDIDO. Bem-vindo(a), %s.\n", tecnico->name);
                adicionar_log_dinamico(logs, log_msg);
                strncpy(nome_logado, tecnico->name, 99);
                nome_logado[99] = '\0';
                return 2;
            }
        }
        
            printf(BOLD RED "\n  Erro: Usuário ou senha inválidos.\n" RESET);
        nome_logado[0] = '\0'; 
        return 0;
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
        case ABERTO:       return "Aberto";
        case EM_ANDAMENTO: return "Em Andamento";
        case RESOLVIDO:    return "Resolvido";
        case CANCELADO:    return "Cancelado";
        case SUSPENSO:     return "Suspenso";
        default:           return "Desconhecido";
    }
}

const char* get_priority_char(PriorityEnum p) {
    switch (p) {
        case BAIXA:     return "Baixa";
        case MEDIA:     return "Média";
        case ALTA:      return "Alta";
        case URGENTE:   return "Urgente";
        case RETORNADO: return "Retornado";
        default:        return "Desconhecida";
    }
}

const int get_priority_int(PriorityEnum p) {
    switch (p) {
        case BAIXA:     return 0;
        case MEDIA:     return 1;
        case ALTA:      return 2;
        case URGENTE:   return 3;
        case RETORNADO: return 4;
        default:        return -1;
    }
}

const char* get_item_char(ItemsEnum i) {
    switch (i) {
        case NONE:       return "Nenhum";
        case MOUSE:      return "Mouse";
        case KEYBOARD:   return "Teclado";
        case CABO_HDMI:  return "Cabo HDMI";
        case MONITOR:    return "Monitor";
        case IMPRESSORA: return "Impressora";
        case NOTEBOOK:   return "Notebook";
        case CABO_REDE:  return "Cabo de rede";
        case WEBCAM:     return "Webcam";
        case HEADSET:    return "Fone de ouvido";
        default:         return "Nenhum";
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

void free_arv(Arv *arv, char **logs) {
    if (arv == NULL) return;

    free(arv);
    
    adicionar_log_dinamico(logs, "Arvore liberada.");
}

// tree
Arv* create_tree() {
    Arv* newTree = (Arv*) malloc(sizeof(Arv));
    if (newTree != NULL) {
        newTree->raiz = NULL;
    }
    return newTree;
}

ArvNo* create_employee_node(const char* name, char **logs) {
    ArvNo* newNode = (ArvNo*) malloc(sizeof(ArvNo));
    if (newNode == NULL) {
        adicionar_log_dinamico(logs, "Falha ao alocar no da arvore (funcionario).");
        return NULL;
    }
    
    strncpy(newNode->name, name, 99);
    newNode->name[99] = '\0';
    newNode->qtd = 0;
    
    newNode->datas = create_call_list_service(logs); 
    if (newNode->datas == NULL) {
         adicionar_log_dinamico(logs, "Falha ao alocar lista interna do funcionario.");
         free(newNode);
         return NULL;
    }
    
    newNode->left = NULL;
    newNode->right = NULL;
    
    adicionar_log_dinamico(logs, "Novo nó de funcionario criado.");
    return newNode;
}

ArvNo* insert_func_node(ArvNo *raiz, ArvNo *novo_no, char **logs) {
    if (raiz == NULL) {
        adicionar_log_dinamico(logs, "Nó de funcionário inserido com sucesso.");
        return novo_no;
    }
    
    int comparacao = strcmp(novo_no->name, raiz->name);

    if (comparacao < 0) {
        raiz->left = insert_func_node(raiz->left, novo_no, logs);
    } else if (comparacao > 0) {
        raiz->right = insert_func_node(raiz->right, novo_no, logs);
    } else {
        adicionar_log_dinamico(logs, "ERRO: Tentativa de inserir funcionário duplicado.");
        free(novo_no->datas);
        free(novo_no);
        return raiz;
    }

    return raiz;
}

int atribuir_chamado_a_tecnico(Arv *arv_func, const char *nome_tecnico, Call *chamado, char **logs) {
    if (arv_func == NULL || arv_func->raiz == NULL || chamado == NULL) {
        return 0;
    }

    ArvNo *tecnico = buscar_funcionario_por_nome(arv_func->raiz, nome_tecnico);

    if (tecnico == NULL) {
        adicionar_log_dinamico(logs, "Erro: Tentativa de atribuir chamado a técnico inexistente.");
        return 0;
    }

    Call *copia_chamado = (Call*) malloc(sizeof(Call));
    if (copia_chamado == NULL) {
        adicionar_log_dinamico(logs, "Erro: Falha ao alocar memória para cópia do chamado.");
        return 0;
    }
    memcpy(copia_chamado, chamado, sizeof(Call));
    
    insert_at_end_service(tecnico->datas, copia_chamado, logs); 

    char log_msg[128];
    snprintf(log_msg, sizeof(log_msg), "Chamado ID %d atribuído ao técnico %s.", chamado->id, nome_tecnico);
    adicionar_log_dinamico(logs, log_msg);

    return 1;
}

ArvNo* insert_or_update(ArvNo *raiz, const char *item_name, int qtd, char **logs) {
    if (raiz == NULL) {
        ArvNo *novo_no = create_new_node(item_name, qtd);
        return novo_no;
    }

    int comparacao = strcmp(item_name, raiz->name);

    if (comparacao == 0) {
        raiz->qtd += qtd;
        return raiz;
    }
    
    if (comparacao < 0) {
        raiz->left = insert_or_update(raiz->left, item_name, qtd, logs);
    } else {
        raiz->right = insert_or_update(raiz->right, item_name, qtd, logs);
    }

    return raiz;
}

ArvNo* decrement(ArvNo *raiz, const char *item_name, int qtd, char **logs) {
    if (raiz == NULL) return NULL;
    int comparacao = strcmp(item_name, raiz->name);

    if (comparacao == 0) {
        raiz->qtd -= qtd;
        return raiz;
    }
    
    if (comparacao < 0) {
        raiz->left = decrement(raiz->left, item_name, qtd, logs);
    } else {
        raiz->right = decrement(raiz->right, item_name, qtd, logs);
    }

    return raiz;
}

ArvNo* create_new_node(const char *item_name, int qtd) {
    ArvNo *novo = (ArvNo*)malloc(sizeof(ArvNo));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo nó.");
        return NULL;
    }
    
    strncpy(novo->name, item_name, 99);
    novo->name[99] = '\0';
    novo->qtd = qtd;
    novo->datas = NULL;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

void exibir_itens_recursivo(ArvNo *no, char **logs) {
    if (no == NULL) {
        return;
    }

    exibir_itens_recursivo(no->left, logs);

    printf("  -> %-15s | Quantidade: %d\n", no->name, no->qtd);

    exibir_itens_recursivo(no->right, logs);
}

void exibir_funcionarios_recursivo(ArvNo *no, char **logs) {
    if (no == NULL) {
        return;
    }

    exibir_funcionarios_recursivo(no->left, logs);

    printf("  -> Funcionário: %s\n", no->name);

    exibir_funcionarios_recursivo(no->right, logs);
}

int reativar_chamados_suspensos(Arv *arv_items, CallService *call_suspend, CallHeap *call_list_heap, char **logs) {
    if (call_suspend == NULL || call_suspend->head == NULL || arv_items == NULL) {
        return 0;
    }

    CallNode *atual = call_suspend->head;
    CallNode *proximo = NULL; 
    int reativados = 0;
    
    int *ids_a_remover = NULL;
    int max_removals = call_suspend->size; 
    int count_to_remove = 0;
    
    if (max_removals > 0) {
        ids_a_remover = (int*)malloc(sizeof(int) * max_removals);
        if (ids_a_remover == NULL) return 0;
    }
    
    while (atual != NULL) {
        proximo = atual->next; 
        
        Call *chamado = atual->data;
        const char *nome_item = get_item_char(chamado->item);

        ArvNo *no_item_estoque = buscar_item(arv_items->raiz, nome_item); 

        if (no_item_estoque != NULL && no_item_estoque->qtd >= chamado->qtd_item) {
            chamado->status = EM_ANDAMENTO; 
            chamado->priority = RETORNADO;
            
            heap_insert(call_list_heap, *chamado, logs);
            
            if (count_to_remove < max_removals) {
                ids_a_remover[count_to_remove++] = chamado->id;
            }

            pre_log();
            
            reativados++;
        }
        
        atual = proximo; 
    }
    
    for (int i = 0; i < count_to_remove; i++) {
        if (remover_call_service(call_suspend, ids_a_remover[i]) == 0) {
            printf(BOLD RED "  Falha ao remover chamado ID %d da lista suspensa." RESET);
            pre_log();
        }
    }

    if (ids_a_remover != NULL) {
        free(ids_a_remover);
    }

    return reativados;
}

ArvNo* buscar_item(ArvNo *raiz, const char *item_name) {
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(item_name, raiz->name);

    if (comparacao == 0) {
        return raiz;
    } else if (comparacao < 0) {
        return buscar_item(raiz->left, item_name);
    } else {
        return buscar_item(raiz->right, item_name);
    }
}

int remover_call_service(CallService *cs, int call_id) {
    if (cs == NULL || cs->head == NULL) {
        return 0;
    }

    CallNode *atual = cs->head;

    while (atual != NULL && atual->data->id != call_id) {
        atual = atual->next;
    }

    if (atual == NULL) {
        return 0;
    }
    
    if (atual->prev != NULL) {
        atual->prev->next = atual->next;
    } else {
        cs->head = atual->next;
    }

    if (atual->next != NULL) {
        atual->next->prev = atual->prev;
    } else {
        cs->tail = atual->prev;
    }
    
    free(atual);
    cs->size--;

    return 1;
}

ArvNo* buscar_funcionario_por_nome(ArvNo *raiz, const char *nome) {
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(nome, raiz->name);

    if (comparacao == 0) {
        return raiz;
    } else if (comparacao < 0) {
        return buscar_funcionario_por_nome(raiz->left, nome);
    } else {
        return buscar_funcionario_por_nome(raiz->right, nome);
    }
}

int buscar_e_atualizar_lista_tecnico(ArvNo *raiz, Call *call_data, int selected_id, int cancel_control, char **logs) {
    if (raiz == NULL) {
        return 0;
    }

    if (buscar_e_atualizar_lista_tecnico(raiz->left, call_data, selected_id, cancel_control, logs)) {
        return 1;
    }

    CallService *lista_tec = raiz->datas;
    if (lista_tec != NULL && lista_tec->head != NULL) {
        CallNode *current_node = lista_tec->head;
        while (current_node != NULL) {
            if (current_node->data->id == selected_id) {
                
                if (cancel_control) {
                    if (remover_call_service(lista_tec, selected_id)) { 
                        adicionar_log_dinamico(logs, "Chamado removido da lista pessoal do técnico.");
                    }
                } else {

                    *(current_node->data) = *call_data;
                    adicionar_log_dinamico(logs, "Chamado atualizado na lista pessoal do técnico.");
                }
                return 1;
            }
            current_node = current_node->next;
        }
    }

    if (buscar_e_atualizar_lista_tecnico(raiz->right, call_data, selected_id, cancel_control, logs)) {
        return 1;
    }

    return 0;
}

int buscar_chamado_na_arvore_tecnicos(ArvNo *raiz, int call_id, Call **chamado_ptr) {
    if (raiz == NULL || *chamado_ptr != NULL) {
        return *chamado_ptr != NULL;
    }

    if (buscar_chamado_na_arvore_tecnicos(raiz->left, call_id, chamado_ptr)) {
        return 1;
    }

    CallService *lista_tec = raiz->datas;
    if (lista_tec != NULL) {
        CallNode *current_node = lista_tec->head;
        while (current_node != NULL) {
            if (current_node->data->id == call_id) {
                *chamado_ptr = current_node->data;
                return 1;
            }
            current_node = current_node->next;
        }
    }

    if (buscar_chamado_na_arvore_tecnicos(raiz->right, call_id, chamado_ptr)) {
        return 1;
    }

    return 0;
}