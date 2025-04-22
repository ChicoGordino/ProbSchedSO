#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"


ProcessList gerar_processos(int n, int seed) {
    ProcessList pl;
    pl.count = n;
    pl.list = malloc(sizeof(Process) * n);

    srand(seed);

    int tempo_chegada = 0;
    for (int i = 0; i < n; i++) {
        pl.list[i].id = i + 1;

        double chegada_exp = gerar_exponencial(0.5); // λ pequeno = mais espaçado
        tempo_chegada += (int)(chegada_exp + 0.5);
        pl.list[i].arrival_time = tempo_chegada;

        double burst_normal = gerar_normal(6.0, 2.0);
        int burst = (int)(burst_normal + 0.5);
        if (burst < 1) burst = 1;
        if (burst > 20) burst = 20; // Limitar o burst time
        pl.list[i].burst_time = burst;

        pl.list[i].remaining_time = burst;
        pl.list[i].priority = rand() % 10;
        pl.list[i].deadline = tempo_chegada + 20 + rand() % 10;

        pl.list[i].start_time = -1;
        pl.list[i].finish_time = -1;
        pl.list[i].waiting_time = 0;
    }

    return pl;
}

void libertar_processos(ProcessList pl) {
    if (pl.list != NULL) {
        free(pl.list);
    }
}
