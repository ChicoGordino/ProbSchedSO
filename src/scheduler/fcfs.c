#include "fcfs.h"

int fcfs_next(ProcessList* pl, int clock) {
    int chosen = -1;
    int earliest = 1e9;

    for (int i = 0; i < pl->count; i++) {
        if (pl->list[i].remaining_time > 0 && pl->list[i].arrival_time <= clock) {
            if (pl->list[i].arrival_time < earliest) {
                earliest = pl->list[i].arrival_time;
                chosen = i;
            }
        }
    }

    return chosen;
}
