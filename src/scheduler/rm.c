#include "rm.h"

int rm_next(ProcessoPeriodico* lista, int n, int clock) {
    int idx = -1;
    int melhor_prioridade = 1e9;
    (void)clock; // Para evitar aviso de variável não utilizada
    for (int i = 0; i < n; i++) {
        if (lista[i].restante > 0) {
            if (lista[i].periodo < melhor_prioridade) {
                melhor_prioridade = lista[i].periodo;
                idx = i;
            }
        }
    }

    return idx;
}

