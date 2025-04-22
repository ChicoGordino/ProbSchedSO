#ifndef FCFS_H
#define FCFS_H

#include "../process.h"

// Devolve o índice do próximo processo a ser executado, ou -1 se nenhum estiver pronto
int fcfs_next(ProcessList* pl, int clock);

#endif
