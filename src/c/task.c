#include "task.h"

/**
 * @brief Initialise une nouvelle tâche avec les paramètres donnés.
 *
 * @param ID Identifiant de la tâche.
 * @param R Date de début au plus tôt de la tâche.
 * @param P Durée opératoire de la tâche.
 * @param W Poids de la tâche.
 * @return T_TASK Une tâche initialisée avec les valeurs fournies.
 */
T_TASK * new_task(unsigned int ID,unsigned int R,unsigned int P,unsigned int W)
{
    T_TASK *task = (T_TASK *)malloc(sizeof(T_TASK));
    task->ID = ID;
    task->R = R;
    task->W = W;
    task->P = P;
    return task;
}

/**
 * @brief Crée une copie d'une tâche existante.
 *
 * @param task Pointeur vers la tâche à copier.
 * @return T_TASK Une copie de la tâche spécifiée.
 */
T_TASK * copy_task(T_TASK * task)
{
    return new_task(task->ID,task->R,task->P,task->W);
}

/**
 * @brief Affiche les informations d'une tâche.
 *
 * @param task Pointeur vers la tâche à afficher.
 */
void print_task(T_TASK * task)
{
    printf("Task [ID: %u] -> Ready: %u, Processing: %u, Weight: %u",task->ID, task->R, task->P, task->W);
}
