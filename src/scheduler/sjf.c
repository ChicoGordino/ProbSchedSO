#include "sjf.h"

// Função que determina o índice do próximo processo a ser executado com base no algoritmo SJF (Shortest Job First).
// Recebe como parâmetros a lista de processos (ProcessList* pl) e o tempo atual (int clock).
int sjfNext(ProcessList* pl, int clock) {
    int idx = -1;
    int menorBurst = 1e9; 

    
    for (int i = 0; i < pl->count; i++) {
        // Verifica se o processo ainda tem tempo restante para executar e se já chegou (arrivalTime <= clock).
        if (pl->list[i].remainingTime > 0 && pl->list[i].arrivalTime <= clock) {
            // Se o tempo de burst do processo atual for menor que o menorBurst encontrado até agora:
            if (pl->list[i].burstTime < menorBurst) {
                menorBurst = pl->list[i].burstTime; 
                idx = i; 
            }
        }
    }

    return idx; 
}
