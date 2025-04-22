#include "priority.h"

int priority_next(ProcessList* pl, int clock) {
    int idx = -1;
    int melhor_prioridade = 1e9;

    for (int i = 0; i < pl->count; i++) {
        if (pl->list[i].remaining_time > 0 && pl->list[i].arrival_time <= clock) {
            if (pl->list[i].priority < melhor_prioridade) {
                melhor_prioridade = pl->list[i].priority;
                idx = i;
            }
        }
    }

    return idx;
}
