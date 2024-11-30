#include "utils.h"

/**
 * @brief Initialise le générateur de nombres aléatoires.
 */
void init_rand()
{
    srand(time(NULL));
}

/**
 * @brief Génère un entier aléatoire dans l'intervalle [0, max).
 *
 * @param max La valeur maximale (non incluse).
 * @return Un entier aléatoire entre 0 et max - 1.
 */
int get_rand(unsigned int max)
{
    return rand()%max;
}

/**
 * @brief Mélange un tableau d'entiers.
 *
 * @param array Tableau à mélanger.
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
