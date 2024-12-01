#include "heuristic.h"

/**
 * @brief Applique une heuristique pour répartir les tâches entre plusieurs machines.
 *
 * @param m Nombre de machines.
 * @param n Nombre de tâches.
 * @param tasks Tableau des tâches.
 * @param comparator Fonction de comparaison pour trier les tâches (par exemple, par temps de début, poids, etc.).
 * @return T_MACHINE* Tableau des machines avec les tâches assignées.
 */
T_MACHINE * heuristic(unsigned int m, unsigned int n, T_TASK ** tasks, bool (*comparator)(T_TASK*, T_TASK*))
{
    quickSort(tasks, 0, n - 1, comparator);
    T_MACHINE * M = (T_MACHINE *) malloc (m * sizeof(T_MACHINE));
    unsigned int machine;
    int min;
    int end;

    for(int i = 0; i < m; i++)
        M[i] = new_machine(i);

    for(int i = 0; i < n; i++)
    {
        int start_task = tasks[i]->R;
        machine = 0;
        min = INT_MAX;
        for(int j = 0; j < m; j++)
        {
            end = get_end_machine(&M[j]) - start_task;

            if(end == 0)
            {
                machine = j;
                break;
            }

            if(min > end)
            {
                min = end;
                machine = j;
            }
        }
        add_task_machine(tasks[i],&M[machine]);
    }
    return M;
}

/**
 * @brief Trie un tableau de tâches en utilisant l'algorithme QuickSort.
 *
 * @param tasks Tableau des tâches à trier.
 * @param low Indice de début du sous-tableau à trier.
 * @param high Indice de fin du sous-tableau à trier.
 * @param comparator Fonction de comparaison pour trier les tâches.
 */
void quickSort(T_TASK ** tasks, int low, int high, bool (*comparator)(T_TASK*, T_TASK*))
{
    if (low < high) {
        int pivotIndex = partition(tasks, low, high, comparator);
        quickSort(tasks, low, pivotIndex - 1, comparator);
        quickSort(tasks, pivotIndex + 1, high, comparator);
    }
}

/**
 * @brief Partitionne un sous-tableau de tâches autour d'un pivot pour le tri QuickSort.
 *
 * @param tasks Tableau des tâches.
 * @param low Indice de début du sous-tableau à partitionner.
 * @param high Indice de fin du sous-tableau à partitionner.
 * @param comparator Fonction de comparaison des tâches.
 * @return int L'indice du pivot après partition.
 */
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

/**
 * @brief Comparateur pour trier les tâches par date de début au plus tôt (R).
 *
 * @param T1 Pointeur vers la première tâche.
 * @param T2 Pointeur vers la deuxième tâche.
 * @return true Si la date de début de T1 est antérieure à celle de T2.
 * @return false Sinon.
 */
bool H1_R(T_TASK * T1,T_TASK * T2)
{
    return T1->R < T2->R;
}

/**
 * @brief Comparateur pour trier les tâches par poids (W) de manière décroissante.
 *
 * @param T1 Pointeur vers la première tâche.
 * @param T2 Pointeur vers la deuxième tâche.
 * @return true Si le poids de T1 est supérieur à celui de T2.
 * @return false Sinon.
 */
bool H2_W(T_TASK * T1,T_TASK * T2)
{
    return T1->W > T2->W;
}

/**
 * @brief Comparateur pour trier les tâches par durée opératoire (P) croissante.
 *
 * @param T1 Pointeur vers la première tâche.
 * @param T2 Pointeur vers la deuxième tâche.
 * @return true Si la durée opératoire de T1 est inférieure à celle de T2.
 * @return false Sinon.
 */
bool H3_P(T_TASK * T1,T_TASK * T2)
{
    return T1->P < T2->P;
}

/**
 * @brief Comparateur pour trier les tâches par le ratio poids/durée (W/P) croissant.
 *
 * @param T1 Pointeur vers la première tâche.
 * @param T2 Pointeur vers la deuxième tâche.
 * @return true Si le ratio W/P de T1 est inférieur à celui de T2.
 * @return false Sinon.
 */
bool H4_WP(T_TASK * T1,T_TASK * T2)
{
    //return (T1->W/(float)T1->P) > (T2->W/(float)T2->P);
    return ((float)T1->P/T1->W) < ((float)T2->P/T2->W);
}
