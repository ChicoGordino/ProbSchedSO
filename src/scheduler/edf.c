#include "edf.h"

// Função que determina o próximo processo a ser executado com base no algoritmo EDF (Earliest Deadline First).
// Recebe uma lista de processos (lista), o número de processos (n) e o clock atual (clock).
int edfNext(ProcessoEDF* lista, int n, int clock) {
    int idx = -1; 
    int menorDeadline = 1e9; 
    (void)clock; 

    // Itera sobre todos os processos na lista.
    for (int i = 0; i < n; i++) {
        // Verifica se o processo ainda tem tempo restante para execução.
        if (lista[i].restante > 0) {
            // Verifica se o deadline absoluto do processo é menor que o menor deadline encontrado até agora.
            if (lista[i].deadlineAbsoluto < menorDeadline) {
                menorDeadline = lista[i].deadlineAbsoluto;
                idx = i; 
            }
        }
    }

    return idx;
}
