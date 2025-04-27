#ifndef EDF_H
#define EDF_H

typedef struct {
    int id;
    int periodo;
    int burst;
    int deadline;
    int proximaAtivacao;
    int restante;
    int deadlineAbsoluto;
    int instanciasExecutadas;
} ProcessoEDF;

int edfNext(ProcessoEDF* lista, int n, int clock);

#endif
