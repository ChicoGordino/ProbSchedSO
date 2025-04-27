#ifndef PROCESS_H
#define PROCESS_H
#include "utils.h"


typedef struct {
    int id;
    int arrivalTime; 
    int burstTime;      
    int remainingTime; 
    int priority;       
    int deadline;        
    
    int startTime;      
    int finishTime;     
    int waitingTime;    
} Process;

typedef struct {
    Process* list;
    int count;
} ProcessList;

ProcessList gerarProcessos(int n, int seed);
void libertarProcessos(ProcessList pl);

#endif
