#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int** create_matrix(int n, int m)
{
    int **pa = malloc(n*sizeof(int*)+n*m*sizeof(int));
    if (pa)
    {
        for (int i = 0; i<n; i++)
            pa[i] = (int*)((char*)pa + n*sizeof(int*) + i*m*sizeof(int));

        for (int i = 0; i < n; i++)
            for (int k = 0; k < m; k++)
                pa[i][k] = 0;
    }
    return pa;
}

void free_matrix(int **matrix)
{
    if (!matrix)
        free(matrix);
}

int** copy_matrix(int** matrix1, int n, int m)
{
    int **matrix2 = create_matrix(n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix2[i][j] = matrix1[i][j];

    return matrix2;
}
