#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "simulation.h"
#include "scheduler/rm.h"
#include "scheduler/edf.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <ficheiro_configuracao>\n", argv[0]);
        return 1;
    }

    Config cfg = carregarConfig(argv[1]);
    if (!cfg.valido) {
        printf("Erro ao carregar configuração.\n");
        return 1;
    }

    // Se for o algoritmo RM (Rate Monotonic), chamamos função especial
    if (strcmp(cfg.algoritmo, "rm") == 0) {
        simularRM(); 
        
    }

    // Se for o algoritmo EDF (Earliest Deadline First), chamamos função especial
    else if (strcmp(cfg.algoritmo, "edf") == 0) {
        simularEDF();
        
    }
        
    else {
    // Para os restantes algoritmos (fcfs, rr, sjf, priority, priorityp)
    simular(cfg);
    }
    return 0;
}
