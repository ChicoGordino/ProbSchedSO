#include "rr.h"


// Função para determinar o próximo processo a executar num escalonador Round-Robin
int rrNext(ProcessList* pl, int clock, int* ultimaExec) {
    int n = pl->count; 
    for (int i = 1; i <= n; i++) {
        
        int idx = (*ultimaExec + i) % n;

        // Verifica se o processo tem tempo de execução restante e já chegou
        if (pl->list[idx].remainingTime > 0 && pl->list[idx].arrivalTime <= clock) {
            *ultimaExec = idx; 
            return idx; 
        }
    }
    return -1; 
}
