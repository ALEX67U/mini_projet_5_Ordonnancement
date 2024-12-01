#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_rand();

int get_rand(unsigned int max);

void fisherYatesShuffle(unsigned int * array, int n) ;

unsigned int absolu(int x) ;
#endif // UTILS_H_INCLUDED
