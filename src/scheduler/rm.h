#ifndef RM_H
#define RM_H

typedef struct {
    int id;
    int periodo;
    int burst;
    int prioridade;
    int deadline;
    int proximaAtivacao;
    int restante;
    int instanciasExecutadas;
} ProcessoPeriodico;

int rmNext(ProcessoPeriodico* lista, int n, int clock);

#endif
