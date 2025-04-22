#include "sjf.h"

int sjf_next(ProcessList* pl, int clock) {
    int idx = -1;
    int menor_burst = 1e9;

    for (int i = 0; i < pl->count; i++) {
        if (pl->list[i].remaining_time > 0 && pl->list[i].arrival_time <= clock) {
            if (pl->list[i].burst_time < menor_burst) {
                menor_burst = pl->list[i].burst_time;
                idx = i;
            }
        }
    }

    return idx;
}
