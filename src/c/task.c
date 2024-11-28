#include "task.h"

T_TASK new_task(unsigned int ID,unsigned int R,unsigned int P,unsigned int W)
{
    T_TASK T;
    T.ID = ID; // num�ro de la tache j
    T.R = R; // Date de d�but au plus t�t, de la t�che j.
    T.P = P; // La dur�e op�ratoire de la t�che j.
    T.W = W; // Le poids de la t�che j.

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
