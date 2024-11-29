#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "machine.h"
#include "heuristic.h"
#include "genetic.h"

int main()
{
    T_TASK T1 = new_task(1, 2, 4, 3);
    T_TASK T2 = new_task(2, 1, 3, 5);
    T_TASK T3 = new_task(3, 4, 2, 2);
    T_TASK T4 = new_task(4, 3, 1, 4);
    T_TASK T5 = new_task(5, 0, 5, 1);
    T_TASK T6 = new_task(6, 10, 6, 8);

    T_TASK * TASKS[] = {&T1,&T2,&T3,&T4,&T5,&T6};
    T_MACHINE * M ;

    M = heuristic(2,6,TASKS,H1_R);
    print_machine(&M[0]);
    print_machine(&M[1]);
    chart_machine(&M[0]);
    chart_machine(&M[1]);

    free_machine(&M[0]);
    free_machine(&M[1]);

    M = heuristic(2,6,TASKS,H2_W);
    print_machine(&M[0]);
    print_machine(&M[1]);
    chart_machine(&M[0]);
    chart_machine(&M[1]);

    free_machine(&M[0]);
    free_machine(&M[1]);

    M = heuristic(2,6,TASKS,H3_P);
    print_machine(&M[0]);
    print_machine(&M[1]);
    chart_machine(&M[0]);
    chart_machine(&M[1]);

    free_machine(&M[0]);
    free_machine(&M[1]);

    M = heuristic(2,6,TASKS,H4_WP);
    print_machine(&M[0]);
    print_machine(&M[1]);
    chart_machine(&M[0]);
    chart_machine(&M[1]);

    T_SOLUTION S = init_new_solution(2,6,M);
    print_solution(&S);

    printf("evaluation = %d\n",evaluate_solution(&S,TASKS));

    free_solution(&S);
    free_machine(&M[0]);
    free_machine(&M[1]);
    free(M);

    return 0;
}
