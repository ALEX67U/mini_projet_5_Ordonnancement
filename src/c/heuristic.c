#include "heuristic.h"

/**
 * @brief Applique une heuristique pour r�partir les t�ches entre plusieurs machines.
 *
 * @param m Nombre de machines.
 * @param n Nombre de t�ches.
 * @param tasks Tableau des t�ches.
 * @param comparator Fonction de comparaison pour trier les t�ches (par exemple, par temps de d�but, poids, etc.).
 * @return T_MACHINE* Tableau des machines avec les t�ches assign�es.
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
 * @brief Trie un tableau de t�ches en utilisant l'algorithme QuickSort.
 *
 * @param tasks Tableau des t�ches � trier.
 * @param low Indice de d�but du sous-tableau � trier.
 * @param high Indice de fin du sous-tableau � trier.
 * @param comparator Fonction de comparaison pour trier les t�ches.
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
 * @brief Partitionne un sous-tableau de t�ches autour d'un pivot pour le tri QuickSort.
 *
 * @param tasks Tableau des t�ches.
 * @param low Indice de d�but du sous-tableau � partitionner.
 * @param high Indice de fin du sous-tableau � partitionner.
 * @param comparator Fonction de comparaison des t�ches.
 * @return int L'indice du pivot apr�s partition.
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
 * @brief Comparateur pour trier les t�ches par date de d�but au plus t�t (R).
 *
 * @param T1 Pointeur vers la premi�re t�che.
 * @param T2 Pointeur vers la deuxi�me t�che.
 * @return true Si la date de d�but de T1 est ant�rieure � celle de T2.
 * @return false Sinon.
 */
bool H1_R(T_TASK * T1,T_TASK * T2)
{
    return T1->R < T2->R;
}

/**
 * @brief Comparateur pour trier les t�ches par poids (W) de mani�re d�croissante.
 *
 * @param T1 Pointeur vers la premi�re t�che.
 * @param T2 Pointeur vers la deuxi�me t�che.
 * @return true Si le poids de T1 est sup�rieur � celui de T2.
 * @return false Sinon.
 */
bool H2_W(T_TASK * T1,T_TASK * T2)
{
    return T1->W > T2->W;
}

/**
 * @brief Comparateur pour trier les t�ches par dur�e op�ratoire (P) croissante.
 *
 * @param T1 Pointeur vers la premi�re t�che.
 * @param T2 Pointeur vers la deuxi�me t�che.
 * @return true Si la dur�e op�ratoire de T1 est inf�rieure � celle de T2.
 * @return false Sinon.
 */
bool H3_P(T_TASK * T1,T_TASK * T2)
{
    return T1->P < T2->P;
}

/**
 * @brief Comparateur pour trier les t�ches par le ratio poids/dur�e (W/P) croissant.
 *
 * @param T1 Pointeur vers la premi�re t�che.
 * @param T2 Pointeur vers la deuxi�me t�che.
 * @return true Si le ratio W/P de T1 est inf�rieur � celui de T2.
 * @return false Sinon.
 */
bool H4_WP(T_TASK * T1,T_TASK * T2)
{
    //return (T1->W/(float)T1->P) > (T2->W/(float)T2->P);
    return ((float)T1->P/T1->W) < ((float)T2->P/T2->W);
}
