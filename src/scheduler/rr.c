#include "rr.h"

// Round Robin simples com última posição conhecida
int rr_next(ProcessList* pl, int clock, int* ultima_exec) {
    int n = pl->count;
    for (int i = 1; i <= n; i++) {
        int idx = (*ultima_exec + i) % n;

        if (pl->list[idx].remaining_time > 0 && pl->list[idx].arrival_time <= clock) {
            *ultima_exec = idx;
            return idx;
        }
    }
    return -1;
}
