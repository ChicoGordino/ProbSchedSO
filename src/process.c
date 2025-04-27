#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"


// Função para gerar uma lista de processos com base no número de processos (n) e uma seed para o gerador de números aleatórios
ProcessList gerarProcessos(int n, int seed) {
    ProcessList pl;
    pl.count = n; 
    pl.list = malloc(sizeof(Process) * n); 

    srand(seed); // Inicializa o gerador de números aleatórios com a seed fornecida

    int tempoChegada = 0;
    for (int i = 0; i < n; i++) {
        pl.list[i].id = i + 1; 

        // Gera o tempo de chegada com base numa distribuição exponencial
        double chegadaExp = gerarExponencial(0.5); 
        tempoChegada += (int)(chegadaExp + 0.5); 
        pl.list[i].arrivalTime = tempoChegada;

        // Gera o burst time com base numa distribuição normal
        double burstNormal = gerarNormal(6.0, 2.0);
        int burst = (int)(burstNormal + 0.5); 
        if (burst < 1) burst = 1; 
        if (burst > 20) burst = 20; // Limita o burst time a um máximo de 20
        pl.list[i].burstTime = burst;

        pl.list[i].remainingTime = burst;
        pl.list[i].priority = rand() % 10; 
        pl.list[i].deadline = tempoChegada + 20 + rand() % 10; 

        // Inicializa os tempos de início, fim e espera
        pl.list[i].startTime = -1;
        pl.list[i].finishTime = -1;
        pl.list[i].waitingTime = 0;
    }

    return pl;
}

void libertarProcessos(ProcessList pl) {
    if (pl.list != NULL) {
        free(pl.list);
    }
}
