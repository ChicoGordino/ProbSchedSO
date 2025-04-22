#include "priority_preemptive.h"

int priority_preemptive_next(ProcessList* pl, int clock) {
    int idx = -1;
    int melhor_prioridade = 1e9;

    for (int i = 0; i < pl->count; i++) {
        Process* p = &pl->list[i];

        if (p->arrival_time <= clock && p->remaining_time > 0) {
            if (p->priority < melhor_prioridade) {
                melhor_prioridade = p->priority;
                idx = i;
            }
        }
    }

    return idx;
}
