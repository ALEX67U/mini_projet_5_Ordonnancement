#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "machine.h"
#include "heuristic.h"

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

    T_TASK * TASK_H2_M1[] = {&T6,&T4,&T3};
    T_TASK * TASK_H2_M2[] = {&T2,&T1,&T5};

    T_MACHINE M1 = init_new_machine(1,3,TASK_H2_M1);
    T_MACHINE M2 = init_new_machine(2,3,TASK_H2_M2);
    print_machine(&M1);
    print_machine(&M2);
    chart_machine(&M1);
    chart_machine(&M2);

//    M = heuristic(2,6,TASKS,H1_R);
//    print_machine(&M[0]);
//    print_machine(&M[1]);
//    chart_machine(&M[0]);
//    chart_machine(&M[1]);
//
    M = heuristic(2,6,TASKS,H2_W);
    print_machine(&M[0]);
    print_machine(&M[1]);
    chart_machine(&M[0]);
    chart_machine(&M[1]);
//
//    M = heuristic(2,6,TASKS,H3_P);
//    print_machine(&M[0]);
//    print_machine(&M[1]);
//    chart_machine(&M[0]);
//    chart_machine(&M[1]);
//
//    M = heuristic(2,6,TASKS,H4_WP);
//    print_machine(&M[0]);
//    print_machine(&M[1]);
//    chart_machine(&M[0]);
//    chart_machine(&M[1]);

    return 0;
}
