#ifndef SERVICES_H
#define SERVICES_H

#include "structs.h"

// Função para criar uma fila de prioridade máxima
FilaPrioridadeMaxima* criar_fila_prioridade_maxima(int capacidade, char **logs);

// Função para liberar a memória alocada para a fila de prioridade máxima
void liberar_fila(FilaPrioridadeMaxima *fila);

int login(int logado);

void liberar_call_list(Call *call_list[], int call_list_control);

void clean_buffer_stdin();

int test_cancel(char* input);

const char* get_status_char(StatusEnum s);
const char* get_priority_char(PriorityEnum p);

#endif // SERVICES_H
