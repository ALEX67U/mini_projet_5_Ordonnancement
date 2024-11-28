#ifndef HEURISTIC_H_INCLUDED
#define HEURISTIC_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include "task.h"
#include "machine.h"

T_MACHINE * heuristic(unsigned int m, unsigned int n, T_TASK ** arr, bool (*comparator)(T_TASK*, T_TASK*));

void quickSort(T_TASK ** arr, int low, int high, bool (*comparator)(T_TASK*, T_TASK*));
int partition(T_TASK ** arr, int low, int high, bool (*comparator)(T_TASK*, T_TASK*));

bool H1_R(T_TASK * T1,T_TASK * T2);
bool H2_W(T_TASK * T1,T_TASK * T2);
bool H3_P(T_TASK * T1,T_TASK * T2);
bool H4_WP(T_TASK * T1,T_TASK * T2);

#endif // HEURISTIC_H_INCLUDED
