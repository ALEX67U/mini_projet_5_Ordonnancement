#include "heuristic.h"

T_MACHINE * heuristic(unsigned int m, unsigned int n, T_TASK ** tasks, bool (*comparator)(T_TASK*, T_TASK*))
{
    quickSort(tasks, 0, n - 1, comparator);
    T_MACHINE * M = (T_MACHINE *) malloc (m * sizeof(T_MACHINE));
    unsigned int machine;
    unsigned int min;
    unsigned int end;

    for(int i = 0; i < m; i++)
        M[i] = new_machine(i);

    for(int i = 0; i < n; i++)
    {
        machine = 0;
        min = UINTMAX_MAX;
        for(int j = 0; j < m; j++)
        {
            if(M[j].n == 0)
            {
                machine = j;
                break;
            }

            end = get_end_machine(&M[j]);
            if(min >= end)
            {
                min = end;
                machine = j;
            }
        }
        add_task_machine(tasks[i],&M[machine]);
    }
    return M;
}

// Fonction de tri rapide (QuickSort)
void quickSort(T_TASK ** tasks, int low, int high, bool (*comparator)(T_TASK*, T_TASK*))
{
    if (low < high) {
        int pivotIndex = partition(tasks, low, high, comparator);
        quickSort(tasks, low, pivotIndex - 1, comparator);
        quickSort(tasks, pivotIndex + 1, high, comparator);
    }
}

int partition(T_TASK ** tasks, int low, int high, bool (*comparator)(T_TASK*, T_TASK*))
{
    T_TASK *pivot = tasks[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (comparator(tasks[j], pivot)) {
            i++;
            T_TASK *temp = tasks[i];
            tasks[i] = tasks[j];
            tasks[j] = temp;
        }
    }
    T_TASK *temp = tasks[i + 1];
    tasks[i + 1] = tasks[high];
    tasks[high] = temp;
    return (i + 1);
}

bool H1_R(T_TASK * T1,T_TASK * T2)
{
    return T1->R < T2->R;
}

bool H2_W(T_TASK * T1,T_TASK * T2)
{
    return T1->W > T2->W;
}

bool H3_P(T_TASK * T1,T_TASK * T2)
{
    return T1->P < T2->P;
}

bool H4_WP(T_TASK * T1,T_TASK * T2)
{
    return (T1->W/(float)T1->P) < (T2->W/(float)T2->P);
}
