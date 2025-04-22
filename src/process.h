#ifndef PROCESS_H
#define PROCESS_H
#include "utils.h"


typedef struct {
    int id;
    int arrival_time;    // Tempo de chegada
    int burst_time;      // Tempo de CPU necessário
    int remaining_time;  // Tempo restante de execução
    int priority;        // Prioridade (menor número = maior prioridade)
    int deadline;        // Para tempo real (EDF)
    
    int start_time;      // Tempo em que começou a ser executado
    int finish_time;     // Tempo em que terminou
    int waiting_time;    // Tempo total de espera
} Process;

typedef struct {
    Process* list;
    int count;
} ProcessList;

ProcessList gerar_processos(int n, int seed);
void libertar_processos(ProcessList pl);

#endif
