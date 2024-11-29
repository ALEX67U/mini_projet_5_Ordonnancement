#include "genetic.h"

T_SOLUTION init_new_solution(unsigned int m, unsigned int n, T_MACHINE * machines)
{
    T_SOLUTION S;
    S.n = n;
    S.m = m;

    S.codage = (unsigned int *) malloc (size_solution(&S) * sizeof(unsigned int));
    int k = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < machines[i].n; j++)
        {
            S.codage[k] = machines[i].j[j]->ID;
            k++;
        }
        S.codage[n + i] = machines[i].n;
    }
    return S;
}

T_TASK *find_task_by_id(T_TASK **tasks, int task_id) {
    for (int t = 0; tasks[t] != NULL; t++)
    {
        if (tasks[t]->ID == task_id)
        {
            return tasks[t];
        }
    }
    return NULL;
}

unsigned int evaluate_solution(T_SOLUTION * solution , T_TASK ** tasks)
{
    T_MACHINE M[solution->m];
    for(int i = 0; i < solution->m; i++)
        M[i] = new_machine(i);

    int k = solution->n;
    int j = 0;
    for (int i = 0; i < solution->n; i++)
    {
        if((solution->codage[k] + j) == i)
        {
            k++;
            j += solution->codage[k];
        }

        // Recherche de la tâche
        T_TASK * current_task = find_task_by_id(tasks, solution->codage[i]);

        if (current_task == NULL)
        {
            printf("%d ",solution->codage[i]);
            fprintf(stderr, "Erreur : tâche avec ID %d introuvable.\n", solution->codage[i]);
            continue;
        }

        add_task_machine(current_task, &M[k - solution->n]);

    }

    unsigned int sum = 0;

    for (int i = 0; i < solution->m; i++)
    {
        sum += get_weighted_sum_machine(&M[i]);
    }

    return sum;
}

void free_solution(T_SOLUTION * solution)
{
    free(solution->codage);
}

int size_solution(T_SOLUTION * solution)
{
    return (solution->n + solution->m - 1);
}

void print_solution(T_SOLUTION * solution)
{
    unsigned int size = size_solution(solution);
    printf("\nSolution size (%u) : ", size);
    int k = solution->n;
    int j = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if(solution->n == i)
            printf("|| ");
        if((solution->codage[k] + j) == i)
        {
            printf("| ");
            k++;
            j += solution->codage[k];
        }
        printf("%u ", solution->codage[i]);
    }
}
