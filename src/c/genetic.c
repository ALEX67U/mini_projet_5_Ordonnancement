#include "genetic.h"

/**
 * @brief Initialise une nouvelle solution en assignant des t�ches aux machines
 *        selon un codage donn� bas� sur l'�tat actuel des machines.
 *
 * @param m Nombre de machines.
 * @param n Nombre de t�ches.
 * @param machines Tableau des machines avec leurs t�ches assign�es.
 * @return T_SOLUTION La solution initialis�e avec un codage de t�ches.
 */
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

/**
 * @brief Initialise une solution al�atoire en attribuant des t�ches aux machines
 *        apr�s un m�lange des identifiants des t�ches.
 *
 * @param m Nombre de machines.
 * @param n Nombre de t�ches.
 * @param TASKS Tableau des t�ches � distribuer.
 * @return T_SOLUTION La solution al�atoire g�n�r�e.
 */
T_SOLUTION init_alea_solution(unsigned int m, unsigned int n, T_TASK **TASKS)
{
    T_SOLUTION S;
    S.n = n;
    S.m = m;

    S.codage = (unsigned int *) malloc (size_solution(&S) * sizeof(unsigned int));

    for(int i = 0; i < n; i++)
    {
        S.codage[i] = TASKS[i]->ID;
    }

    fisherYatesShuffle(S.codage, n) ;

    int k = n;
    for(int i = 0; i < m; i++)
    {
        int size = get_rand(k);
        S.codage[n + i] = size;
        k -= size;
    }
    return S;
}

/**
 * @brief Cr�e une copie d'une solution existante.
 *
 * @param solution Pointeur vers la solution � copier.
 * @return T_SOLUTION La solution copi�e.
 */
T_SOLUTION copy_solution(T_SOLUTION * solution)
{
    T_SOLUTION S;
    S.n = solution->n;
    S.m = solution->m;
    S.codage = (unsigned int *) malloc (size_solution(&S) * sizeof(unsigned int));
    for (unsigned int i = 0; i < size_solution(solution); i++)
    {
        S.codage[i] = solution->codage[i];
    }
    return S;
}

/**
 * @brief Recherche une t�che par son identifiant dans un tableau de t�ches.
 *
 * @param tasks Tableau des t�ches.
 * @param task_id Identifiant de la t�che � rechercher.
 * @return T_TASK* Pointeur vers la t�che trouv�e, ou NULL si elle n'existe pas.
 */
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

/**
 * @brief �value la qualit� d'une solution en calculant la somme pond�r�e
 *        des co�ts des machines apr�s avoir assign� les t�ches.
 *
 * @param solution La solution � �valuer.
 * @param tasks Tableau des t�ches � utiliser dans l'�valuation.
 * @return unsigned int La somme pond�r�e des co�ts des machines.
 */
unsigned int evaluate_solution(T_SOLUTION * solution , T_TASK ** tasks)
{
    T_MACHINE M[solution->m];
    for(int i = 0; i < solution->m; i++)
        M[i] = new_machine(i);

    int k = solution->n;
    int m = 1;
    int j = 0;
    for (int i = 0; i < solution->n; i++)
    {
        if(((solution->codage[k] + j) == i) && (m < solution->m))
        {
            k++;
            m++;
            j += solution->codage[k];
        }

        // Recherche de la t�che
        T_TASK * current_task = find_task_by_id(tasks, solution->codage[i]);

        if (current_task == NULL)
        {
            printf("%d ",solution->codage[i]);
            fprintf(stderr, "Erreur : t�che avec ID %d introuvable.\n", solution->codage[i]);
            continue;
        }

        add_task_machine(current_task, &M[k - solution->n]);

    }

    unsigned int sum = 0;

    for (int i = 0; i < solution->m; i++)
    {
        sum += get_weighted_sum_machine(&M[i]);
        free_machine(&M[i]);
    }

    return sum;
}

/**
 * @brief Lib�re la m�moire allou�e pour une solution.
 *
 * @param solution La solution � lib�rer.
 */
void free_solution(T_SOLUTION * solution)
{
    free(solution->codage);
}

/**
 * @brief Calcule la taille d'une solution, c'est-�-dire le nombre total
 *        d'�l�ments dans le codage de la solution.
 *
 * @param solution La solution dont la taille doit �tre calcul�e.
 * @return int La taille de la solution.
 */
int size_solution(T_SOLUTION * solution)
{
    return (solution->n + solution->m - 1);
}

/**
 * @brief Affiche la solution sous forme lisible, y compris le codage des t�ches
 *        et la distribution des t�ches entre les machines.
 *
 * @param solution La solution � afficher.
 */
void print_solution(T_SOLUTION * solution)
{
    unsigned int size = size_solution(solution);
    printf("\nSolution size (%u) : ", size);
    int k = solution->n;
    int m = 1;
    int j = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if(solution->n == i)
            printf("|| ");

        if(((solution->codage[k] + j) == i) && (m < solution->m) && (solution->n > i))
        {
            printf("| ");
            k++;
            j += solution->codage[k];
        }
        printf("%u ", solution->codage[i]);
    }
}

/**
 * @brief Effectue une mutation sur une solution en permutant deux t�ches dans son codage.
 *
 * @param solution La solution � muter.
 * @return T_SOLUTION La solution apr�s mutation.
 */
T_SOLUTION mutation_solution(T_SOLUTION * solution)
{
    T_SOLUTION S = copy_solution(solution);
    int i = get_rand(solution->n);
    int j = get_rand(solution->n);

    if(i == j)
    j = (j+1)%solution->n;

    unsigned int tmp = S.codage[i];
    S.codage[i] = S.codage[j];
    S.codage[j] = tmp;

    return S;
}

/**
 * @brief R�alise un croisement entre deux solutions pour cr�er une nouvelle solution.
 *        Les deux solutions sont combin�es en fonction d'un point de croisement.
 *
 * @param s1 Premi�re solution � croiser.
 * @param s2 Deuxi�me solution � croiser.
 * @return T_SOLUTION* Tableau contenant les deux solutions enfants g�n�r�es.
 */
T_SOLUTION * crossover_solution(T_SOLUTION * s1, T_SOLUTION * s2)
{
    T_SOLUTION * S = (T_SOLUTION *) malloc (2 * sizeof(T_SOLUTION));
    S[0] = copy_solution(s1);
    S[1] = copy_solution(s2);
    int k = get_rand(s1->n);
    int k1 = k;
    int k2 = k;
    for (unsigned int i = 0; i < s1->n; i++)
    {
        for (unsigned int j = k; j < s1->n; j++)
        {
            if(s2->codage[i] == s1->codage[j])
            {
                S[0].codage[k1] = s2->codage[i];
                k1++;
            }
            if(s1->codage[i] == s2->codage[j])
            {
                S[1].codage[k2] = s1->codage[i];
                k2++;
            }
        }
    }

    for (unsigned int j = s1->n; j < size_solution(s1); j++)
    {
        S[0].codage[j] = s2->codage[j];
        S[1].codage[j] = s1->codage[j];
    }

    return S;
}

/**
 * @brief V�rifie si deux solutions sont identiques en comparant leurs codages.
 *
 * @param sol1 Premi�re solution � comparer.
 * @param sol2 Deuxi�me solution � comparer.
 * @return bool true si les solutions sont identiques, false sinon.
 */
bool is_same_solution(T_SOLUTION *sol1, T_SOLUTION *sol2)
{
    // Comparer les champs principaux de la solution
    if (size_solution(sol1) != size_solution(sol2))
        return false;

    for (int i = 0; i < size_solution(sol1); i++)
    {
        if (sol1->codage[i] != sol2->codage[i])
            return false;
    }

    return true;
}

/**
 * @brief Trie une population de solutions en fonction de leur "fitness" (�valuation),
 *        en utilisant un tri par s�lection sur les indices de la population.
 *
 * @param fitness Tableau des scores de fitness des solutions.
 * @param p Taille de la population.
 * @return int* Tableau des indices tri�s par ordre croissant de fitness.
 */
int *sort_population_by_fitness(unsigned int *fitness, int p)
{
    // Tableau d'indices
    int *indices = (int *)malloc(p * sizeof(int));
    for (int i = 0; i < p; i++)
    {
        indices[i] = i;
    }

    // Tri par fitness (ordre croissant) avec l'algorithme de tri par s�lection
    for (int i = 0; i < p - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < p; j++)
        {
            if (fitness[indices[j]] < fitness[indices[min_idx]])
            {
                min_idx = j;
            }
        }

        // �change des indices
        int temp = indices[i];
        indices[i] = indices[min_idx];
        indices[min_idx] = temp;
    }

    return indices;
}

/**
 * @brief Ex�cute l'algorithme g�n�tique pour r�soudre le probl�me, en simulant
 *        plusieurs g�n�rations de solutions, en utilisant des croisements, mutations
 *        et une s�lection par fitness.
 *
 * @param m Nombre de machines.
 * @param n Nombre de t�ches.
 * @param p Taille de la population.
 * @param g Nombre de g�n�rations � ex�cuter.
 * @param TASKS Tableau des t�ches � utiliser.
 * @param solution_h Solution heuristique initiale (optionnelle).
 */
void genetic_algorithm(int m, int n, int p, int g, T_TASK **TASKS, T_SOLUTION *solution_h)
{
    // Allouer dynamiquement la population
    T_SOLUTION *population = (T_SOLUTION *)malloc(p * sizeof(T_SOLUTION));
    int h = 0;

    if (solution_h != NULL)
    {
        population[0] = copy_solution(solution_h);
        h++;
    }

    // Initialiser la population
    for (int i = h; i < p; i++)
    {
        population[i] = init_alea_solution(m, n, TASKS);
    }

    // Pourcentage de population al�atoire (par exemple, 10 %)
    int random_count = p / 10;

    // Boucle sur les g�n�rations
    for (int generation = 0; generation < g; generation++)
    {
        // �valuer chaque solution
        unsigned int *fitness = (unsigned int *)malloc(p * sizeof(unsigned int));
        for (int i = 0; i < p; i++)
        {
            fitness[i] = evaluate_solution(&population[i], TASKS);
        }

        // Trier la population par fitness (croissant) en gardant les indices
        int *sorted_indices = sort_population_by_fitness(fitness, p);

        // Conserver les 10 % des meilleures solutions (uniques)
        int elite_count = p / 10; // 10 % de la population
        T_SOLUTION *elite_population = (T_SOLUTION *)malloc(elite_count * sizeof(T_SOLUTION));
        int elite_index = 0;

        for (int i = 0; i < p && elite_index < elite_count; i++)
        {
            bool is_duplicate = false;
            for (int j = 0; j < elite_index; j++)
            {
                if (is_same_solution(&population[sorted_indices[i]], &elite_population[j]))
                {
                    is_duplicate = true;
                    break;
                }
            }

            if (!is_duplicate)
            {
                elite_population[elite_index] = copy_solution(&population[sorted_indices[i]]);
                elite_index++;
            }
        }

        // Remplir la nouvelle population
        T_SOLUTION *new_population = (T_SOLUTION *)malloc(p * sizeof(T_SOLUTION));

        // Ajouter l'�lite dans la nouvelle population
        for (int i = 0; i < elite_index; i++)
        {
            new_population[i] = copy_solution(&elite_population[i]);
        }

        // G�n�rer des enfants par croisement et mutation
        for (int i = elite_index; i < p - random_count; i++)
        {
            int parent1 = get_rand(elite_index); // Choisir un parent parmi l'�lite
            int parent2 = get_rand(elite_index);

            // Croisement
            T_SOLUTION *offspring = crossover_solution(&elite_population[parent1], &elite_population[parent2]);

            // Mutation (probabilit� de 20 %)
            if (rand() % 100 < 20)
            {
                new_population[i] = mutation_solution(&offspring[0]);
            }
            else
            {
                new_population[i] = copy_solution(&offspring[0]);
            }

            free(offspring);
        }

        // Ajouter des solutions al�atoires pour diversifier la population
        for (int i = p - random_count; i < p; i++)
        {
            new_population[i] = init_alea_solution(m, n, TASKS);
        }

        // Remplacer l'ancienne population
        for (int i = 0; i < p; i++)
        {
            free_solution(&population[i]);
        }
        free(population);
        population = new_population;

        // Lib�rer les ressources de l'�lite
        for (int i = 0; i < elite_index; i++)
        {
            free_solution(&elite_population[i]);
        }
        free(elite_population);
        free(sorted_indices);
        free(fitness);

        // Afficher la meilleure solution
//        printf("\nGeneration %d:\n", generation + 1);
//        printf("Best solution of generation %d:\n", generation + 1);
//        print_solution(&population[0]);
//        printf(": evaluation = %u\n", evaluate_solution(&population[0], TASKS));
    }

    // Afficher la meilleure solution finale
    unsigned int final_best_fitness = evaluate_solution(&population[0], TASKS);
    printf("\nBest solution after %d generations:\n", g);
    print_solution(&population[0]);
    printf("Evaluation: %d\n", final_best_fitness);

    // Lib�rer les ressources
    for (int i = 0; i < p; i++)
    {
        free_solution(&population[i]);
    }
    free(population);
}

