// solving tsp using backtracking formulated as a decision problem, spring 2022
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define V 5 // vertices

int sum_all_weights(int** mat) {
    int sum = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = i; j < V; j++)
        {
            sum += mat[i][j];
        }
    }
    return sum;
}

int factorial(int n) {
    int f = 1;
    for (int c = 1; c <= n; c++) {
        f = f * c;
    }
    return f;
}

bool eNotInIdxs(int* vIdxs, int e) {
    for (int i = 0; i < V; i++)
    {
        if (vIdxs[i] == e)
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    // välj array som datastruktur, ty, TSP förutsätter ett en komplett graf, grafen är alltså dense

    int f1tr[V] = {0, 3, 5, 2, 7}; // from node 1 to rest of nodes
    int f2tr[V] = {3, 0, 1, 4, 6}; // from node 2 to rest of nodes
    int f3tr[V] = {5, 1, 0, 8, 10}; // from node 3 to rest of nodes
    int f4tr[V] = {2, 4, 8, 0, 9}; // from node 4 to rest of nodes
    int f5tr[V] = {7, 6, 10, 9, 0}; // from node 5 to rest of nodes
    int* adjMat[V] = {f1tr, f2tr, f3tr, f4tr, f5tr}; // adj matrix is created

    // forumlate as a decision problem, otherwise complexity will be n!, just as in exhaustive search
    int k_best = sum_all_weights(adjMat);

    int k_curr = 0;
    int startV = (rand() % V) + 1;
    int vIdxs[V] = {0};
    vIdxs[0] = startV; 
    int i = 0, minEdge = INT_MAX;
    while (k_curr < k_best)
    {
        if (vIdxs[5] != 0)
        {
            break;  
        }

        if (i >= factorial(V));
        {
            break;
        }
        
        for (int e = 0; e < V-1; e++)
        {
            if (adjMat[vIdxs[i]][e] < minEdge && eNotInIdxs(vIdxs, e))
            {
                minEdge = adjMat[vIdxs[i]][e];
                vIdxs[i] = e;
            }
            
        }
        minEdge = 0;
        i++;
    }



    return 0;
}