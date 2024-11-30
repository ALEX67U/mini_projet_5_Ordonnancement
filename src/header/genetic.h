#ifndef GENETIC_H_INCLUDED
#define GENETIC_H_INCLUDED

#include <stdbool.h>
#include "machine.h"
#include "heuristic.h"
#include "task.h"
#include "utils.h"

typedef struct {
    unsigned int n;
    unsigned int m;
    unsigned int * codage;
}T_SOLUTION;

T_SOLUTION init_new_solution(unsigned int m, unsigned int n, T_MACHINE * machines);
T_SOLUTION copy_solution(T_SOLUTION * solution);

void free_solution(T_SOLUTION * solution);
int size_solution(T_SOLUTION * solution);
unsigned int evaluate_solution(T_SOLUTION * solution , T_TASK ** tasks);

void print_solution(T_SOLUTION * solution);

T_SOLUTION mutation_solution(T_SOLUTION * solution);
T_SOLUTION * crossover_solution(T_SOLUTION * s1, T_SOLUTION * s2);

void genetic_algorithm(int m, int n, int p, int g, T_TASK **TASKS, T_SOLUTION * solution_h) ;

#endif // GENETIC_H_INCLUDED
