#ifndef SERVICES_H
#define SERVICES_H

#include "structs.h"

// Função para criar uma fila de prioridade máxima
FilaPrioridadeMaxima* criar_fila_prioridade_maxima(int capacidade, int logs_control, char **logs);

// Função para liberar a memória alocada para a fila de prioridade máxima
void liberar_fila(FilaPrioridadeMaxima *fila);

int login(int logado);

void liberar_call_list(Call *call_list[], int call_list_control);

void clean_buffer_stdin();

#endif // SERVICES_H
