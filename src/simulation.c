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
    ProcessList pl = gerarProcessos(cfg.numProcessos, cfg.seed);

    int clock = 0;
    int completos = 0;
    int ultimaExec = -1;
    int processoAnterior = -1;
    int tempoOcupado = 0;

    printf("\n[SIMULAÇÃO %s INICIADA]\n", cfg.algoritmo);

    while (completos < pl.count) {
        int idx = -1;

        if (strcmp(cfg.algoritmo, "fcfs") == 0) {
            idx = fcfsNext(&pl, clock);
        } else if (strcmp(cfg.algoritmo, "rr") == 0) {
            idx = rrNext(&pl, clock, &ultimaExec);
        } else if (strcmp(cfg.algoritmo, "sjf") == 0) {
            idx = sjfNext(&pl, clock);
        } else if (strcmp(cfg.algoritmo, "priority") == 0) {
            idx = priorityNext(&pl, clock);
        } else if (strcmp(cfg.algoritmo, "priorityp") == 0) {
            idx = priorityPreemptiveNext(&pl, clock);

            if (idx != processoAnterior && processoAnterior != -1 &&
                pl.list[processoAnterior].remainingTime > 0) {
                printf("Processo %d (prioridade %d) interrompido por processo %d (prioridade %d) em t=%d\n",
                       pl.list[processoAnterior].id, pl.list[processoAnterior].priority,
                       pl.list[idx].id, pl.list[idx].priority, clock);
            }

            processoAnterior = idx;
        } else {
            printf("Algoritmo desconhecido: %s\n", cfg.algoritmo);
            break;
        }

        if (idx == -1) {
            clock++;
            continue;
        }

        Process* p = &pl.list[idx];

        if (p->startTime == -1)
            p->startTime = clock;

        int execTime = 1;
        if (strcmp(cfg.algoritmo, "rr") == 0) {
            execTime = (p->remainingTime < cfg.quantum) ? p->remainingTime : cfg.quantum;
        } else if (strcmp(cfg.algoritmo, "priorityp") != 0) {
            execTime = p->remainingTime;
        }

        for (int i = 0; i < execTime; i++) {
            p->remainingTime--;
            if (strcmp(cfg.algoritmo, "priority") == 0 || strcmp(cfg.algoritmo, "priorityp") == 0) {
                printf("Processo %d (prioridade %d) executado de t=%d até t=%d (resta %d)\n",
                       p->id, p->priority, clock, clock + 1, p->remainingTime);
            } else {
                printf("Processo %d executado de t=%d até t=%d (resta %d)\n",
                       p->id, clock, clock + 1, p->remainingTime);
            }

            clock++;
            tempoOcupado++;

            if (p->remainingTime == 0) {
                p->finishTime = clock;
                p->waitingTime = p->startTime - p->arrivalTime;
                completos++;
                break;
            }

            if (strcmp(cfg.algoritmo, "priorityp") == 0)
                break;
        }
    }

    // Estatísticas
    printf("\n[ESTATÍSTICAS]\n");
    int totalWait = 0, totalTurnaround = 0;

    for (int i = 0; i < pl.count; i++) {
        int turnaround = pl.list[i].finishTime - pl.list[i].arrivalTime;
        totalWait += pl.list[i].waitingTime;
        totalTurnaround += turnaround;

        if (strcmp(cfg.algoritmo, "priority") == 0 || strcmp(cfg.algoritmo, "priorityp") == 0) {
            printf("P%d -> Espera: %d | Turnaround: %d | Prioridade: %d\n",
                   pl.list[i].id, pl.list[i].waitingTime, turnaround, pl.list[i].priority);
        } else {
            printf("P%d -> Espera: %d | Turnaround: %d\n",
                   pl.list[i].id, pl.list[i].waitingTime, turnaround);
        }
    }

    printf("\nTempo médio de espera: %.2f\n", totalWait / (float)pl.count);
    printf("Tempo médio de turnaround: %.2f\n", totalTurnaround / (float)pl.count);

    float utilizacaoCpu = (tempoOcupado / (float)clock) * 100;
    float throughput = (pl.count / (float)clock);

    printf("Utilização da CPU: %.2f%%\n", utilizacaoCpu);
    printf("Throughput: %.2f processos/unidade de tempo\n", throughput);

    libertarProcessos(pl);
}




void simularRM() {
    int clock = 0;
    int tempoTotal = 100;
    int tempoOcupado = 0;
    ProcessoPeriodico lista[] = {
        {1, 5, 1, 0, 5, 0, 0, 0},
        {2, 10, 2, 0, 10, 0, 0, 0},
        {3, 20, 4, 0, 20, 0, 0, 0}
    };
    int n = 3;

    int deadlinesFalhadas[n];
    for (int i = 0; i < n; i++) deadlinesFalhadas[i] = 0;

    printf("\n[SIMULAÇÃO RM INICIADA]\n");

    while (clock < tempoTotal) {
        for (int i = 0; i < n; i++) {
            if (clock == lista[i].proximaAtivacao) {
                if (lista[i].restante > 0) {
                    printf("Deadline falhada para processo %d em t=%d\n", lista[i].id, clock);
                    deadlinesFalhadas[i]++;
                }
                lista[i].restante = lista[i].burst;
                lista[i].proximaAtivacao += lista[i].periodo;
                printf("Processo %d ativado em t=%d (restante = %d)\n", lista[i].id, clock, lista[i].restante);
            }
        }

        int idx = rmNext(lista, n, clock);

        if (idx == -1) {
            clock++;
            continue;
        }

        lista[idx].restante--;
        tempoOcupado++;

        printf("Processo %d executado em t=%d (resta %d)\n", lista[idx].id, clock, lista[idx].restante);

        if (lista[idx].restante == 0) {
            lista[idx].instanciasExecutadas++;
        }

        clock++;
    }

    // Estatísticas
    printf("\n[ESTATÍSTICAS FINAIS]\n");
    int totalCompletadas = 0;
    for (int i = 0; i < n; i++) {
        totalCompletadas += lista[i].instanciasExecutadas;
        printf("P%d -> Instâncias completadas: %d | Deadlines falhadas: %d\n",
               lista[i].id, lista[i].instanciasExecutadas, deadlinesFalhadas[i]);
    }

    float utilizacaoCpu = (tempoOcupado / (float)tempoTotal) * 100.0;
    float throughput = totalCompletadas / (float)tempoTotal;

    printf("\nUtilização da CPU: %.2f%%\n", utilizacaoCpu);
    printf("Throughput: %.2f processos/unidade de tempo\n", throughput);
}

void simularEDF() {
    int clock = 0;
    int tempoTotal = 100;
    int tempoOcupado = 0;
    ProcessoEDF lista[] = {
        {1, 5, 1, 5, 0, 0, 0, 0},
        {2, 10, 2, 10, 0, 0, 0, 0},
        {3, 20, 4, 20, 0, 0, 0, 0}
    };
    int n = 3;

    int deadlinesFalhadas[n];
    for (int i = 0; i < n; i++) deadlinesFalhadas[i] = 0;

    printf("\n[SIMULAÇÃO EDF INICIADA]\n");

    while (clock < tempoTotal) {
        // Verifica se algum processo é ativado no instante atual
        for (int i = 0; i < n; i++) {
            if (clock == lista[i].proximaAtivacao) {
                // Se o processo anterior não foi concluído, regista uma deadline falhada
                if (lista[i].restante > 0) {
                    printf("Deadline falhada para processo %d em t=%d\n", lista[i].id, clock);
                    deadlinesFalhadas[i]++;
                }

                // Reativa o processo e atualiza os seus atributos
                lista[i].restante = lista[i].burst;
                lista[i].deadlineAbsoluto = clock + lista[i].deadline;
                lista[i].proximaAtivacao += lista[i].periodo;

                printf("Processo %d ativado em t=%d (restante = %d, deadline_abs = %d)\n",
                       lista[i].id, clock, lista[i].restante, lista[i].deadlineAbsoluto);
            }
        }

        // Determina o próximo processo a ser executado com base no algoritmo EDF
        int idx = edfNext(lista, n, clock);

    
        if (idx == -1) {
            clock++;
            continue;
        }

        // Executa o processo selecionado
        lista[idx].restante--;
        tempoOcupado++;
        printf("Processo %d executado em t=%d (resta %d)\n", lista[idx].id, clock, lista[idx].restante);

        // Se o processo foi concluído, incrementa o contador de instâncias executadas
        if (lista[idx].restante == 0) {
            lista[idx].instanciasExecutadas++;
        }

        clock++;
    }

    
    printf("\n[ESTATÍSTICAS]\n");
    int totalCompletas = 0;
    for (int i = 0; i < n; i++) {
        totalCompletas += lista[i].instanciasExecutadas;
        printf("P%d -> Instâncias completadas: %d | Deadlines falhadas: %d\n",
               lista[i].id, lista[i].instanciasExecutadas, deadlinesFalhadas[i]);
    }

    // Cálculo da utilização da CPU e throughput
    float utilizacaoCpu = (tempoOcupado / (float)tempoTotal) * 100;
    float throughput = totalCompletas / (float)tempoTotal;

    printf("\nUtilização da CPU: %.2f%%\n", utilizacaoCpu);
    printf("Throughput: %.2f processos/unidade de tempo\n", throughput);
}






