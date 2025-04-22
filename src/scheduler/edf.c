#include "edf.h"

int edf_next(ProcessoEDF* lista, int n, int clock) {
    int idx = -1;
    int menor_deadline = 1e9;
    (void)clock; // Para evitar aviso de variável não utilizada
    for (int i = 0; i < n; i++) {
        if (lista[i].restante > 0) {
            if (lista[i].deadline_absoluto < menor_deadline) {
                menor_deadline = lista[i].deadline_absoluto;
                idx = i;
            }
        }
    }

    return idx;
}
