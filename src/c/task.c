#include "task.h"

/**
 * @brief Initialise une nouvelle t�che avec les param�tres donn�s.
 *
 * @param ID Identifiant de la t�che.
 * @param R Date de d�but au plus t�t de la t�che.
 * @param P Dur�e op�ratoire de la t�che.
 * @param W Poids de la t�che.
 * @return T_TASK Une t�che initialis�e avec les valeurs fournies.
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
 * @brief Cr�e une copie d'une t�che existante.
 *
 * @param task Pointeur vers la t�che � copier.
 * @return T_TASK Une copie de la t�che sp�cifi�e.
 */
T_TASK * copy_task(T_TASK * task)
{
    return new_task(task->ID,task->R,task->P,task->W);
}

/**
 * @brief Affiche les informations d'une t�che.
 *
 * @param task Pointeur vers la t�che � afficher.
 */
void print_task(T_TASK * task)
{
    printf("Task [ID: %u] -> Ready: %u, Processing: %u, Weight: %u",task->ID, task->R, task->P, task->W);
}
