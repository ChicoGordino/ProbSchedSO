#ifndef RM_H
#define RM_H

typedef struct {
    int id;
    int periodo;
    int burst;
    int prioridade;
    int deadline;
    int proxima_ativacao;
    int restante;
    int instancias_executadas;
} ProcessoPeriodico;

int rm_next(ProcessoPeriodico* lista, int n, int clock);

#endif
