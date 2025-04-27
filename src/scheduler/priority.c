#include "priority.h"

// Função que determina o índice do próximo processo a ser executado com base na prioridade
int priorityNext(ProcessList* pl, int clock) {
    int idx = -1; 
    int melhorPrioridade = 1e9; 

    // Itera sobre a lista de processos
    for (int i = 0; i < pl->count; i++) {
        // Verifica se o processo ainda tem tempo restante e já chegou no tempo atual (clock)
        if (pl->list[i].remainingTime > 0 && pl->list[i].arrivalTime <= clock) {
            // Verifica se a prioridade do processo atual é melhor (menor valor)
            if (pl->list[i].priority < melhorPrioridade) {
                melhorPrioridade = pl->list[i].priority; 
                idx = i; 
            }
        }
    }

    return idx; 
}
