#ifndef EDF_H
#define EDF_H

typedef struct {
    int id;
    int periodo;
    int burst;
    int deadline;
    int proxima_ativacao;
    int restante;
    int deadline_absoluto;
    int instancias_executadas;
} ProcessoEDF;

int edf_next(ProcessoEDF* lista, int n, int clock);

#endif
