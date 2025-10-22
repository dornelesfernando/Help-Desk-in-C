// #include "fila_prioridade_maxima.h"
// #include <stdio.h>
// #include <stdlib.h>

// static void trocar(int *a, int *b) {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// static void arrumar_acima(FilaPrioridadeMaxima *fila, int indice) {
    
// }

// static void arrumar_abaixo(FilaPrioridadeMaxima *fila, int indice) {
    
// }
// void inserir(FilaPrioridadeMaxima *fila, int valor) {
//     if (fila->tamanho == fila->capacidade) {
//         printf("Overflow do heap\n");
//         return;
//     }

//     fila->tamanho++;
//     int indice = fila->tamanho - 1;
//     fila->dados[indice] = valor;
//     arrumar_acima(fila, indice);
// }

// int extrair_maximo(FilaPrioridadeMaxima *fila) {
//     if (fila->tamanho == 0) {
//         printf("Underflow do heap\n");
//         return -1;
//     }

//     int maximo = fila->dados[0];
//     fila->dados[0] = fila->dados[fila->tamanho - 1];
//     fila->tamanho--;
//     arrumar_abaixo(fila, 0);

//     return maximo;
// }