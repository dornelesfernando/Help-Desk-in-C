#ifndef SERVICES_H
#define SERVICES_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #include "structs.h"
    #include "logs.h"
    #include "menu.h"
    
    void replace(Call *a, Call *b);
    
    CallHeap* create_call_list_heap(int capacity, char **logs);
    void heap_insert (CallHeap *call, Call data, char **logs);
    void tidying_up(CallHeap *call, int index, char **logs);
    void heap_remove(CallHeap *call, char **logs);
    void tidying_down(CallHeap *call, char **logs);
    int expand_heep(CallHeap *call, char **logs);
    
    CallFIFO* create_call_list_fifo(int capacity, char **logs);
    void fifo_enqueue(CallFIFO *call, Call data, char **logs);
    void fifo_dequeue(CallFIFO *call, char **logs);
    int expand_fifo(CallFIFO *call, char **logs);
    
    CallService* create_call_list_service(char **logs);
    
    int login(int logado, Arv *arv_func, char *nome_logado, char **logs);
    void clean_buffer_stdin();
    int test_cancel(char* input);
    
    const char* get_status_char(StatusEnum s);
    const char* get_priority_char(PriorityEnum p);
    const int get_priority_int(PriorityEnum p);
    const char* get_item_char(ItemsEnum i);
    
    CallService *concat_call_list(CallHeap *call_list_heap, CallFIFO *call_list_fifo, char **logs);
    void insert_at_end_service(CallService *call_list_service, Call *call, char **logs);
    
    void free_list_service(CallService *call_list, char **logs);
    void free_heap(CallHeap *heap, char **logs);
    void free_fifo(CallFIFO *fifo, char **logs);
    void free_arv(Arv *arv, char **logs);

    Arv* create_tree();
    ArvNo* create_employee_node(const char* name, char **logs);
    ArvNo* insert_func_node(ArvNo *raiz, ArvNo *novo_no, char **logs);
    int atribuir_chamado_a_tecnico(Arv *arv_func, const char *nome_tecnico, Call *chamado, char **logs);
    ArvNo* insert_or_update(ArvNo *raiz, const char *item_name, int qtd, char **logs);
    ArvNo* decrement(ArvNo *raiz, const char *item_name, int qtd, char **logs);
    ArvNo* create_new_node(const char *item_name, int qtd);
    
    void exibir_itens_recursivo(ArvNo *no, char **logs);
    void exibir_funcionarios_recursivo(ArvNo *no, char **logs);
    ArvNo* buscar_item(ArvNo *raiz, const char *item_name);
    int remover_call_service(CallService *cs, int call_id);
    int reativar_chamados_suspensos(Arv *arv_items, CallService *call_suspend, CallHeap *call_list_heap, char **logs);
    ArvNo* buscar_funcionario_por_nome(ArvNo *raiz, const char *nome);
    int buscar_e_atualizar_lista_tecnico(ArvNo *raiz, Call *call_data, int selected_id, int cancel_control, char **logs);
    int buscar_chamado_na_arvore_tecnicos(ArvNo *raiz, int call_id, Call **chamado_ptr);

#endif // SERVICES_H
    