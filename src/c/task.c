#include "task.h"

T_TASK new_task(unsigned int ID,unsigned int R,unsigned int P,unsigned int W)
{
    T_TASK T;
    T.ID = ID; // numéro de la tache j
    T.R = R; // Date de début au plus tôt, de la tâche j.
    T.P = P; // La durée opératoire de la tâche j.
    T.W = W; // Le poids de la tâche j.

    return T;
}

T_TASK copy_task(T_TASK * task)
{
    return new_task(task->ID,task->R,task->P,task->W);
}

void print_task(T_TASK * task)
{
    printf("Task [ID: %u] -> Ready: %u, Processing: %u, Weight: %u",task->ID, task->R, task->P, task->W);
}
