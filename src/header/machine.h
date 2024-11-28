#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "task.h"

typedef struct {
    unsigned int ID;// num�ro de la machine
    unsigned int n; // Le nombre de t�ches
    T_TASK ** j; // Les t�ches sur la machine
    unsigned int * Cj; // La date de fin d�ex�cution des t�ches j.


} T_MACHINE;

T_MACHINE init_new_machine(unsigned int ID, unsigned int n , T_TASK ** j);
T_MACHINE new_machine(unsigned int ID);

unsigned int get_end_machine(T_MACHINE *machine);

void add_task_machine(T_TASK *task, T_MACHINE *machine);
void free_machine(T_MACHINE * machine);
void update_machine(T_MACHINE * machine);
void no_wait_machine(T_MACHINE * machine);

void print_machine(T_MACHINE * machine);
void chart_machine(T_MACHINE * machine);

#endif // MACHINE_H_INCLUDED
