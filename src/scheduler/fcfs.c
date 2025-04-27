#include "fcfs.h"

// Função para selecionar o próximo processo a executar usando o algoritmo de escalonamento First-Come, First-Served (FCFS)
int fcfsNext(ProcessList* pl, int clock) {
    int escolhido = -1; 
    int maisCedo = 1e9; 

    for (int i = 0; i < pl->count; i++) {
        // Verificar se o processo tem tempo restante e já chegou até o tempo atual do relógio
        if (pl->list[i].remainingTime > 0 && pl->list[i].arrivalTime <= clock) {
            // Se o processo chegou mais cedo do que o atual mais cedo, atualizar o processo escolhido
            if (pl->list[i].arrivalTime < maisCedo) {
                maisCedo = pl->list[i].arrivalTime; 
                escolhido = i; 
            }
        }
    }

    return escolhido; 
}
