#include "rm.h"

// Função que determina o próximo processo a ser executado com base no algoritmo Rate-Monotonic (RM).
// Recebe uma lista de processos periódicos, o número de processos (n) e o clock atual (não utilizado nesta implementação).
int rmNext(ProcessoPeriodico* lista, int n, int clock) {
    int idx = -1; 
    int melhorPrioridade = 1e9; 
    (void)clock; 

    // Itera sobre a lista de processos para encontrar o de maior prioridade (menor período).
    for (int i = 0; i < n; i++) {
        if (lista[i].restante > 0) { 
            if (lista[i].periodo < melhorPrioridade) { 
                melhorPrioridade = lista[i].periodo; 
                idx = i; 
            }
        }
    }

    return idx; 
}

