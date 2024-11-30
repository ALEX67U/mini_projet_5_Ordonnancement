#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "machine.h"
#include "heuristic.h"
#include "genetic.h"
#include "utils.h"

T_TASK** load_tasks_from_file(const char *filename, unsigned int *num_tasks) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Compter le nombre de lignes dans le fichier pour déterminer le nombre de tâches
    unsigned int count = 0;
    while (!feof(file)) {
        int c = fgetc(file);
        if (c == '\n') {
            count++;
        }
    }
    rewind(file);  // Revenir au début du fichier pour la lecture

    // Allouer de la mémoire pour un tableau de pointeurs vers des tâches
    T_TASK **tasks = (T_TASK **)malloc(count * sizeof(T_TASK *));
    if (tasks == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les tâches.\n");
        exit(EXIT_FAILURE);
    }

    // Lire les tâches et allouer de la mémoire pour chacune d'elles
    unsigned int i = 0;
    while (i < count) {
        // Variables temporaires pour stocker les données lues
        unsigned int tmpID, tmpR, tmpW, tmpP;

        // Lire une ligne avec fscanf et stocker les valeurs dans les variables temporaires
        if (fscanf(file, "%u %u %u %u", &tmpID, &tmpR, &tmpP, &tmpW) == 4) {
            // Allouer de la mémoire pour la tâche avant de remplir ses champs
            tasks[i] = new_task(tmpID, tmpR, tmpP, tmpW);
            i++;
        } else {
            break;  // Si une ligne est mal formatée ou manque des données, on arrête la lecture
        }
    }

    *num_tasks = count;  // Retourner le nombre de tâches lues
    fclose(file);  // Fermer le fichier

    return tasks;
}


int main(int argc, char *argv[])
{
    // Valeurs par défaut pour les paramètres
    int m = 2;     // Nombre de machines
    int p = 100;   // Taille de la population
    int g = 100;   // Nombre de générations

    // Vérification des arguments passés en ligne de commande
    if (argc > 1)
    {
        m = atoi(argv[1]);  // m (machines)
    }
    if (argc > 3)
    {
        p = atoi(argv[3]);  // p (taille de la population)
    }
    if (argc > 4)
    {
        g = atoi(argv[4]);  // g (nombre de générations)
    }
    init_rand();

    unsigned int num_tasks = 0;
    // Charger les tâches depuis le fichier
    T_TASK ** TASKS = load_tasks_from_file("tasks.txt", &num_tasks);

    // Afficher les tâches lues
    for (unsigned int i = 0; i < num_tasks; i++) {
        printf("Tache %u: R = %u, W = %u, P = %u\n", TASKS[i]->ID, TASKS[i]->R, TASKS[i]->W, TASKS[i]->P);
    }

    T_MACHINE * M ;

    printf("==================== heuristique 1 ====================");
    M = heuristic(m,num_tasks,TASKS,H1_R);
    print_machine(&M[0]);
    print_machine(&M[1]);
//    chart_machine(&M[0]);
//    chart_machine(&M[1]);

    T_SOLUTION S1 = init_new_solution(2,num_tasks,M);

    free_machine(&M[0]);
    free_machine(&M[1]);
    free(M);

    printf("==================== heuristique 2 ====================");
    M = heuristic(m,num_tasks,TASKS,H2_W);
    print_machine(&M[0]);
    print_machine(&M[1]);
//    chart_machine(&M[0]);
//    chart_machine(&M[1]);

    T_SOLUTION S2 = init_new_solution(2,num_tasks,M);

    free_machine(&M[0]);
    free_machine(&M[1]);
    free(M);

    printf("==================== heuristique 3 ====================");
    M = heuristic(m,num_tasks,TASKS,H3_P);
    print_machine(&M[0]);
    print_machine(&M[1]);
//    chart_machine(&M[0]);
//    chart_machine(&M[1]);

    T_SOLUTION S3 = init_new_solution(2,num_tasks,M);

    free_machine(&M[0]);
    free_machine(&M[1]);
    free(M);

    printf("==================== heuristique 4 ====================");
    M = heuristic(m,num_tasks,TASKS,H4_WP);
    print_machine(&M[0]);
    print_machine(&M[1]);
//    chart_machine(&M[0]);
//    chart_machine(&M[1]);

    T_SOLUTION S4 = init_new_solution(2,num_tasks,M);

    free_machine(&M[0]);
    free_machine(&M[1]);
    free(M);

    printf("==================== Codage ====================");

    print_solution(&S1);
    printf("evaluation H1 = %d\n",evaluate_solution(&S1,TASKS));

    print_solution(&S2);
    printf("evaluation H2 = %d\n",evaluate_solution(&S2,TASKS));

    print_solution(&S3);
    printf("evaluation H3 = %d\n",evaluate_solution(&S3,TASKS));

    print_solution(&S4);
    printf("evaluation H4 = %d\n",evaluate_solution(&S4,TASKS));

    printf("==================== Mutation ====================");
    T_SOLUTION SM = mutation_solution(&S1);
    print_solution(&SM);
    printf("evaluation Mutation H1 = %d\n",evaluate_solution(&SM,TASKS));
    free_solution(&SM);

    printf("==================== Croisement ====================");

    T_SOLUTION * SC = crossover_solution(&S2,&S4);
    print_solution(&SC[0]);
    printf("evaluation croisement H2 et H4 (1) = %d\n",evaluate_solution(&SC[0],TASKS));
    print_solution(&SC[1]);
    printf("evaluation croisement H2 et H4 (2) = %d\n",evaluate_solution(&SC[1],TASKS));

    printf("==================== Genetic Algorithm ====================\n");

    // Exécution de l'algorithme génétique avec les paramètres
    genetic_algorithm(m, num_tasks, p, g, TASKS, NULL);

    free_solution(&S1);
    free_solution(&S2);
    free_solution(&S3);
    free_solution(&S4);
    free_solution(&SC[0]);
    free_solution(&SC[1]);
    free(SC);

    for (unsigned int i = 0; i < num_tasks; i++) {
        free(TASKS);  // Libérer chaque tâche allouée
    }
    free(TASKS);  // Libérer le tableau de pointeurs
    return 0;
}
