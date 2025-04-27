#include "priority_preemptive.h"

// Função que determina o próximo processo a ser executado com base no escalonamento preemptivo por prioridade
int priorityPreemptiveNext(ProcessList* pl, int clock) {
    int idx = -1; 
    int melhorPrioridade = 1e9; 

    // Itera sobre a lista de processos
    for (int i = 0; i < pl->count; i++) {
        Process* p = &pl->list[i]; // Aponta para o processo atual

        // Verifica se o processo chegou e ainda tem tempo restante para executar
        if (p->arrivalTime <= clock && p->remainingTime > 0) {
            // Verifica se a prioridade do processo atual é melhor (menor valor)
            if (p->priority < melhorPrioridade) {
                melhorPrioridade = p->priority; 
                idx = i; 
            }
        }
    }

    return idx; 
}
