#ifndef GENETIC_H_INCLUDED
#define GENETIC_H_INCLUDED

#include "machine.h"
#include "task.h"
#include "utils.h"

typedef struct {
    unsigned int n;
    unsigned int m;
    unsigned int * codage;
}T_SOLUTION;

T_SOLUTION init_new_solution(unsigned int m, unsigned int n, T_MACHINE * machines);

void free_solution(T_SOLUTION * solution);
int size_solution(T_SOLUTION * solution);
unsigned int evaluate_solution(T_SOLUTION * solution , T_TASK ** tasks);

void print_solution(T_SOLUTION * solution);

T_SOLUTION mutation_solution(T_SOLUTION * solution);

#endif // GENETIC_H_INCLUDED
