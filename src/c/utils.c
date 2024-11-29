#include "utils.h"

void init_rand()
{
    srand(time(NULL));
}

int get_rand(unsigned int max)
{
    return rand()%max;
}
