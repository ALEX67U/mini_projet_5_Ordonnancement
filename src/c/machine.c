#include "machine.h"

T_MACHINE init_new_machine(unsigned int ID ,unsigned int n , T_TASK ** j)
{
    T_MACHINE M;

    M.ID = ID;
    M.n = n; // Le nombre de tâches
    M.j = j; // Les tâches sur la machine
    M.Cj = (unsigned int *) malloc (n * sizeof(unsigned int));
    update_machine(&M);

    return M;
}

T_MACHINE new_machine(unsigned int ID)
{
    T_MACHINE M;

    M.ID = ID;
    M.n = 0; // Le nombre de tâches
    M.j = NULL; // Les tâches sur la machine
    M.Cj = NULL;

    return M;
}

unsigned int get_end_machine(T_MACHINE *machine)
{
    return machine->Cj[machine->n - 1];
}

unsigned int get_weighted_sum_machine(T_MACHINE *machine)
{
    unsigned int sum = 0;
    for(int i = 0; i < machine->n; i++)
        sum += (*machine->j[i]).W*machine->Cj[i];
    return sum;
}


// Ajout d'une tâche à une machine (avec réallocation de mémoire)
void add_task_machine(T_TASK *task, T_MACHINE *machine)
{
    machine->j = (T_TASK **) realloc(machine->j, (machine->n + 1) * sizeof(T_TASK *));
    machine->Cj = (unsigned int *) realloc(machine->Cj, (machine->n + 1) * sizeof(unsigned int));
    machine->j[machine->n] = task;
    machine->n++;
    update_machine(machine);
}

void free_machine(T_MACHINE * machine)
{
    free(machine->j);
    free(machine->Cj);
}

void update_machine(T_MACHINE * machine)
{
    if(machine->n > 0)
    {
        machine->Cj[0] = (*machine->j[0]).P + (*machine->j[0]).R;
        for(int i = 1; i < machine->n; i++)
            if((*machine->j[i]).R > machine->Cj[i - 1])
                machine->Cj[i] = (*machine->j[i]).P + (*machine->j[i]).R;
            else
                machine->Cj[i] = (*machine->j[i]).P + machine->Cj[i - 1];
    }

    no_wait_machine(machine);
}

void no_wait_machine(T_MACHINE * machine)
{
    if(machine->n > 1)
        for(int i = machine->n - 2; i >= 0; i--)
            machine->Cj[i] = machine->Cj[i + 1] - (*machine->j[i + 1]).P;
}

void print_machine(T_MACHINE * machine)
{
    printf("\nMachine %d with %u tasks:", machine->ID, machine->n);
    for (unsigned int i = 0; i < machine->n; i++)
    {
        printf("\n\t");
        print_task(machine->j[i]);
        printf(", Completion: %u",machine->Cj[i]);
    }

    printf("\n\nWeighted sum of job execution end dates machine %u: %u\n",machine->ID, get_weighted_sum_machine(machine));
}

void chart_machine(T_MACHINE * machine)
{
    printf("\nVisualization of machine %d tasks:\n\t\n", machine->ID);

    unsigned int start = machine->Cj[0] - (*machine->j[0]).P;
    for (unsigned int i = 0; i < start; i++)
        printf("_");
    for (unsigned int i = 0; i < machine->n; i++)
    {
        for (unsigned int j = 0; j < ((*machine->j[i]).P); j++)
            printf("%d",(*machine->j[i]).ID);

    }
    printf("\n\nEnd machine %u: %u\n",machine->ID, get_end_machine(machine));
}
