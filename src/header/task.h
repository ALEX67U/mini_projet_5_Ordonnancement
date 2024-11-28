#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <stdio.h>

typedef struct {
    unsigned int ID;// numéro de la tache j
    unsigned int R; // Date de début au plus tôt, de la tâche j.
    unsigned int P; // La durée opératoire de la tâche j.
    unsigned int W; // Le poids de la tâche j.
} T_TASK;

T_TASK new_task(unsigned int ID,unsigned int R,unsigned int P,unsigned int W);

void print_task(T_TASK * task);

#endif // TASK_H_INCLUDED
