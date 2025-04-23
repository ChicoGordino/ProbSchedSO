#include "simulation.h"
#include "scheduler/fcfs.h"
#include "scheduler/rr.h"
#include "scheduler/sjf.h"
#include "scheduler/priority.h"
#include "scheduler/priority_preemptive.h"
#include "scheduler/rm.h"
#include "scheduler/edf.h"
#include <string.h>
#include <stdio.h>

void simular(Config cfg) {
    ProcessList pl = gerar_processos(cfg.num_processos, cfg.seed);

    int clock = 0;
    int completos = 0;
    int ultima_exec = -1;
    int processo_anterior = -1;
    int tempo_ocupado = 0;

    printf("\n[SIMULAÇÃO %s INICIADA]\n", cfg.algoritmo);

    while (completos < pl.count) {
        int idx = -1;

        if (strcmp(cfg.algoritmo, "fcfs") == 0) {
            idx = fcfs_next(&pl, clock);
        } else if (strcmp(cfg.algoritmo, "rr") == 0) {
            idx = rr_next(&pl, clock, &ultima_exec);
        } else if (strcmp(cfg.algoritmo, "sjf") == 0) {
            idx = sjf_next(&pl, clock);
        } else if (strcmp(cfg.algoritmo, "priority") == 0) {
            idx = priority_next(&pl, clock);
        } else if (strcmp(cfg.algoritmo, "priorityp") == 0) {
            idx = priority_preemptive_next(&pl, clock);

            if (idx != processo_anterior && processo_anterior != -1 &&
                pl.list[processo_anterior].remaining_time > 0) {
                printf("Processo %d (prioridade %d) interrompido por processo %d (prioridade %d) em t=%d\n",
                       pl.list[processo_anterior].id, pl.list[processo_anterior].priority,
                       pl.list[idx].id, pl.list[idx].priority, clock);
            }

            processo_anterior = idx;
        } else {
            printf("Algoritmo desconhecido: %s\n", cfg.algoritmo);
            break;
        }

        if (idx == -1) {
            clock++;
            continue;
        }

        Process* p = &pl.list[idx];

        if (p->start_time == -1)
            p->start_time = clock;

        int exec_time = 1;
        if (strcmp(cfg.algoritmo, "rr") == 0) {
            exec_time = (p->remaining_time < cfg.quantum) ? p->remaining_time : cfg.quantum;
        } else if (strcmp(cfg.algoritmo, "priorityp") != 0) {
            exec_time = p->remaining_time;
        }

        for (int i = 0; i < exec_time; i++) {
            p->remaining_time--;
            if (strcmp(cfg.algoritmo, "priority") == 0 || strcmp(cfg.algoritmo, "priorityp") == 0) {
                printf("Processo %d (prioridade %d) executado de t=%d até t=%d (resta %d)\n",
                       p->id, p->priority, clock, clock + 1, p->remaining_time);
            } else {
                printf("Processo %d executado de t=%d até t=%d (resta %d)\n",
                       p->id, clock, clock + 1, p->remaining_time);
            }

            clock++;
            tempo_ocupado++;

            if (p->remaining_time == 0) {
                p->finish_time = clock;
                p->waiting_time = p->start_time - p->arrival_time;
                completos++;
                break;
            }

            if (strcmp(cfg.algoritmo, "priorityp") == 0)
                break;
        }
    }

    // Estatísticas
    printf("\n[ESTATÍSTICAS]\n");
    int total_wait = 0, total_turnaround = 0;

    for (int i = 0; i < pl.count; i++) {
        int turnaround = pl.list[i].finish_time - pl.list[i].arrival_time;
        total_wait += pl.list[i].waiting_time;
        total_turnaround += turnaround;

        if (strcmp(cfg.algoritmo, "priority") == 0 || strcmp(cfg.algoritmo, "priorityp") == 0) {
            printf("P%d -> Espera: %d | Turnaround: %d | Prioridade: %d\n",
                   pl.list[i].id, pl.list[i].waiting_time, turnaround, pl.list[i].priority);
        } else {
            printf("P%d -> Espera: %d | Turnaround: %d\n",
                   pl.list[i].id, pl.list[i].waiting_time, turnaround);
        }
    }

    printf("\nTempo médio de espera: %.2f\n", total_wait / (float)pl.count);
    printf("Tempo médio de turnaround: %.2f\n", total_turnaround / (float)pl.count);

    float utilizacao_cpu = (tempo_ocupado / (float)clock) * 100;
    float throughput = (pl.count / (float)clock);

    printf("Utilização da CPU: %.2f%%\n", utilizacao_cpu);
    printf("Throughput: %.2f processos/unidade de tempo\n", throughput);

    libertar_processos(pl);
}




void simular_rm() {
    int clock = 0;
    int tempo_total = 100;
    int tempo_ocupado = 0;

    ProcessoPeriodico lista[] = {
        {1, 5, 1, 0, 5, 0, 0, 0},
        {2, 10, 2, 0, 10, 0, 0, 0},
        {3, 20, 4, 0, 20, 0, 0, 0}
    };
    int n = 3;

    int deadlines_falhadas[n];
    for (int i = 0; i < n; i++) deadlines_falhadas[i] = 0;

    printf("\n[SIMULAÇÃO Rate Monotonic INICIADA]\n");

    while (clock < tempo_total) {
        for (int i = 0; i < n; i++) {
            if (clock == lista[i].proxima_ativacao) {
                if (lista[i].restante > 0) {
                    printf("Deadline falhada para processo %d em t=%d\n", lista[i].id, clock);
                    deadlines_falhadas[i]++;
                }
                lista[i].restante = lista[i].burst;
                lista[i].proxima_ativacao += lista[i].periodo;
                printf("Processo %d ativado em t=%d (restante = %d)\n", lista[i].id, clock, lista[i].restante);
            }
        }

        int idx = rm_next(lista, n, clock);

        if (idx == -1) {
            clock++;
            continue;
        }

        lista[idx].restante--;
        tempo_ocupado++;
        printf("Processo %d executado em t=%d (resta %d)\n", lista[idx].id, clock, lista[idx].restante);

        if (lista[idx].restante == 0) {
            lista[idx].instancias_executadas++;
        }

        clock++;
    }

    // Estatísticas
    printf("\n[ESTATÍSTICAS]\n");
    int total_completas = 0;
    for (int i = 0; i < n; i++) {
        total_completas += lista[i].instancias_executadas;
        printf("P%d -> Instâncias completadas: %d | Deadlines falhadas: %d\n",
               lista[i].id, lista[i].instancias_executadas, deadlines_falhadas[i]);
    }

    float utilizacao_cpu = (tempo_ocupado / (float)tempo_total) * 100;
    float throughput = total_completas / (float)tempo_total;

    printf("\nUtilização da CPU: %.2f%%\n", utilizacao_cpu);
    printf("Throughput: %.2f processos/unidade de tempo\n", throughput);
}

void simular_edf() {
    int clock = 0;
    int tempo_total = 100;
    int tempo_ocupado = 0;

    ProcessoEDF lista[] = {
        {1, 5, 1, 5, 0, 0, 0, 0},
        {2, 10, 2, 10, 0, 0, 0, 0},
        {3, 20, 4, 20, 0, 0, 0, 0}
    };
    int n = 3;

    int deadlines_falhadas[n];
    for (int i = 0; i < n; i++) deadlines_falhadas[i] = 0;

    printf("\n[SIMULAÇÃO EDF INICIADA]\n");

    while (clock < tempo_total) {
        for (int i = 0; i < n; i++) {
            if (clock == lista[i].proxima_ativacao) {
                if (lista[i].restante > 0) {
                    printf("Deadline falhada para processo %d em t=%d\n", lista[i].id, clock);
                    deadlines_falhadas[i]++;
                }

                lista[i].restante = lista[i].burst;
                lista[i].deadline_absoluto = clock + lista[i].deadline;
                lista[i].proxima_ativacao += lista[i].periodo;

                printf("Processo %d ativado em t=%d (restante = %d, deadline_abs = %d)\n",
                       lista[i].id, clock, lista[i].restante, lista[i].deadline_absoluto);
            }
        }

        int idx = edf_next(lista, n, clock);

        if (idx == -1) {
            clock++;
            continue;
        }

        lista[idx].restante--;
        tempo_ocupado++;
        printf("Processo %d executado em t=%d (resta %d)\n", lista[idx].id, clock, lista[idx].restante);

        if (lista[idx].restante == 0) {
            lista[idx].instancias_executadas++;
        }

        clock++;
    }

    printf("\n[ESTATÍSTICAS]\n");
    int total_completas = 0;
    for (int i = 0; i < n; i++) {
        total_completas += lista[i].instancias_executadas;
        printf("P%d -> Instâncias completadas: %d | Deadlines falhadas: %d\n",
               lista[i].id, lista[i].instancias_executadas, deadlines_falhadas[i]);
    }

    float utilizacao_cpu = (tempo_ocupado / (float)tempo_total) * 100;
    float throughput = total_completas / (float)tempo_total;

    printf("\nUtilização da CPU: %.2f%%\n", utilizacao_cpu);
    printf("Throughput: %.2f processos/unidade de tempo\n", throughput);
}






