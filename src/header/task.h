#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <stdio.h>

typedef struct {
    unsigned int ID;// num�ro de la tache j
    unsigned int R; // Date de d�but au plus t�t, de la t�che j.
    unsigned int P; // La dur�e op�ratoire de la t�che j.
    unsigned int W; // Le poids de la t�che j.
} T_TASK;

T_TASK new_task(unsigned int ID,unsigned int R,unsigned int P,unsigned int W);

void print_task(T_TASK * task);

#endif // TASK_H_INCLUDED
