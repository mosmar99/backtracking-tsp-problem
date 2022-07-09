#include <stdlib.h>
#include <string.h>
 
static void swap(unsigned int *a, unsigned int *b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}
 
static void traveling_salesman_recursive(const unsigned int **adjmat, unsigned int order, 
        unsigned int *best_tour, unsigned int *best_tour_cost, unsigned int *partial_tour,
        unsigned int *partial_tour_cost, unsigned int level)
{
    if (level == order - 1) {
        /* Add last two edges to complete the tour */
        unsigned int tour_cost = *partial_tour_cost 
                + adjmat[partial_tour[order - 2]][partial_tour[order - 1]]
                + adjmat[partial_tour[order - 1]][0];
        if (*best_tour_cost == 0 || tour_cost < *best_tour_cost) {
            /* Best tour so far */
            memcpy(best_tour, partial_tour, order * sizeof(unsigned int));
            *best_tour_cost = tour_cost;
        }
    }
    else {
        unsigned int i;
        for (i = level; i < order; i++) {
            if (*best_tour_cost == 0
                || *partial_tour_cost + adjmat[partial_tour[level - 1]][partial_tour[i]]
                    < *best_tour_cost)
            {  
                /* Next permutation */
                swap(&partial_tour[level], &partial_tour[i]);
                unsigned int cost = adjmat[partial_tour[level - 1]][partial_tour[level]];
                *partial_tour_cost += cost;
                traveling_salesman_recursive(adjmat, order, best_tour, best_tour_cost,
                        partial_tour, partial_tour_cost, level + 1);
                *partial_tour_cost -= cost;
                swap(&partial_tour[level], &partial_tour[i]);
            }
        }
    }
}
 
unsigned int traveling_salesman(const unsigned int **adjmat, unsigned int order, 
        unsigned int **best_tour)
{
    unsigned int i;
    unsigned int best_tour_cost = 0;
    unsigned int partial_tour_cost = 0;
    unsigned int *partial_tour = malloc(order * sizeof(unsigned int));
    *best_tour = malloc(order * sizeof(unsigned int));
    if (partial_tour == NULL || *best_tour == NULL) {
        free(partial_tour);
        free(*best_tour);
        *best_tour = NULL;
        return 0;
    }        
    for (i = 0; i < order; i++) {
        partial_tour[i] = i;
    }
    traveling_salesman_recursive(adjmat, order, *best_tour, &best_tour_cost, partial_tour, 
            &partial_tour_cost, 1);
    free(partial_tour);
    return best_tour_cost;
}

#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    // http://www.martinbroadhurst.com/traveling-salesman-problem-using-backtracking-in-c.html
    unsigned int r1[] = {0, 5, 7, 9, 10};
    unsigned int r2[] = {4, 0, 11, 3, 7};
    unsigned int r3[] = {3, 1, 0, 4, 5};
    unsigned int r4[] = {6, 5, 7, 0, 11} ;
    unsigned int r5[] = {13, 2, 8, 3, 0} ;
    const size_t order = 5; /* Vertices */
    const unsigned int *adjmat[] = { r1, r2, r3, r4, r5 };
    unsigned int *best_tour;
    unsigned int cost = traveling_salesman(adjmat, order, &best_tour);
    unsigned int i;
    printf("Best tour cost: %u\n", cost);
    printf("Vertices:\n");
    for (i = 0; i < order; i++) {
        printf("%u ", best_tour[i]);
    }
    putchar('\n');
    printf("Edge weights:\n");
    for (i = 0; i < order - 1; i++) {
        printf("%u ", adjmat[best_tour[i]][best_tour[i + 1]]);
    }
    printf("%u\n", adjmat[best_tour[order - 1]][0]);
    free(best_tour);
    return 0;
}