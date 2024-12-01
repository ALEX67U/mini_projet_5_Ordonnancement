#include "machine.h"

/**
 * @brief Initialise une nouvelle machine avec des tâches.
 *
 * @param ID Identifiant de la machine.
 * @param n Nombre de tâches initiales.
 * @param j Tableau de pointeurs vers les tâches.
 * @return T_MACHINE La machine initialisée.
 */
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

/**
 * @brief Crée une machine vide sans tâches.
 *
 * @param ID Identifiant de la machine.
 * @return T_MACHINE La machine vide initialisée.
 */
T_MACHINE new_machine(unsigned int ID)
{
    T_MACHINE M;

    M.ID = ID;
    M.n = 0; // Le nombre de tâches
    M.j = NULL; // Les tâches sur la machine
    M.Cj = NULL;

    return M;
}

/**
 * @brief Retourne la date de fin d'exécution de la dernière tâche sur la machine.
 *
 * @param machine Pointeur vers la machine.
 * @return unsigned int Date de fin de la dernière tâche.
 */
unsigned int get_end_machine(T_MACHINE *machine)
{
    if(machine->n == 0)
        return 0;
    return machine->Cj[machine->n - 1];
}

/**
 * @brief Calcule la somme pondérée des dates de fin des tâches sur la machine.
 *
 * @param machine Pointeur vers la machine.
 * @return unsigned int Somme pondérée des dates de fin.
 */
unsigned int get_weighted_sum_machine(T_MACHINE *machine)
{
    unsigned int sum = 0;
    for(int i = 0; i < machine->n; i++)
        sum += (*machine->j[i]).W*machine->Cj[i];
    return sum;
}

/**
 * @brief Ajoute une tâche à une machine et met à jour ses données.
 *
 * @param task Pointeur vers la tâche à ajouter.
 * @param machine Pointeur vers la machine cible.
 */
void add_task_machine(T_TASK *task, T_MACHINE *machine)
{
    machine->j = (T_TASK **) realloc(machine->j, (machine->n + 1) * sizeof(T_TASK *));
    machine->Cj = (unsigned int *) realloc(machine->Cj, (machine->n + 1) * sizeof(unsigned int));
    machine->j[machine->n] = task;
    machine->n++;
    update_machine(machine);
}

/**
 * @brief Libère la mémoire allouée à une machine.
 *
 * @param machine Pointeur vers la machine.
 */
void free_machine(T_MACHINE * machine)
{
    free(machine->j);
    free(machine->Cj);
}

/**
 * @brief Met à jour les dates de fin des tâches sur une machine.
 *
 * @param machine Pointeur vers la machine.
 */
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

/**
 * @brief Ajuste les dates de fin pour garantir l'absence d'attente entre tâches.
 *
 * @param machine Pointeur vers la machine.
 */
void no_wait_machine(T_MACHINE * machine)
{
    if(machine->n > 1)
        for(int i = machine->n - 2; i >= 0; i--)
            machine->Cj[i] = machine->Cj[i + 1] - (*machine->j[i + 1]).P;
}

/**
 * @brief Affiche les détails d'une machine, y compris ses tâches et leurs dates de fin.
 *
 * @param machine Pointeur vers la machine.
 */
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

/**
 * @brief Génère une visualisation textuelle des tâches exécutées sur une machine.
 *
 * @param machine Pointeur vers la machine.
 */
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
