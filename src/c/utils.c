#include "utils.h"

/**
 * @brief Initialise le g�n�rateur de nombres al�atoires.
 */
void init_rand()
{
    srand(time(NULL));
}

/**
 * @brief G�n�re un entier al�atoire dans l'intervalle [0, max).
 *
 * @param max La valeur maximale (non incluse).
 * @return Un entier al�atoire entre 0 et max - 1.
 */
int get_rand(unsigned int max)
{
    return rand()%max;
}

/**
 * @brief M�lange un tableau d'entiers.
 *
 * @param array Tableau � m�langer.
 * @param n Taille du tableau.
 */
void fisherYatesShuffle(unsigned int * array, int n)
{
    for (int i = n - 1; i > 0; i--) {
        int j = get_rand(i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
