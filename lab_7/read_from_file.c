#include <stdio.h>
#include <stdlib.h>

#include "read_from_file.h"
#include "close_roads.h"
#include "matrix.h"

int** read_file(FILE *file, int *n, int *m)
{
    int **matrix = NULL;
    fscanf(file,"%d %d\n", n, m);
    matrix = create_matrix(*n, *m);

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            fscanf(file, "%d", &matrix[i][j]);
    fclose(file);

    return matrix;
}

void print_mas(int **matrix, int n, int m)
{
    char c = 'A';
    for (int i = 0; i < n; i++, c++)
        printf("\t%c", c);
    printf("\n");
    for (int i = 0; i < n; i++, c++)
        printf("---------");
    printf("\n");
    c = 'A';
    for (int i = 0; i < n; i++)
    {
        printf("%c\t", c++);
        printf("|");
        for (int k = 0; k < m; k++)
        {
            printf("%d\t", matrix[i][k]);
            if (k != m - 1)
                printf("|");
        }
        printf("\n");
        for (int k = 0; k < m; k++)
            printf("---------");
        printf("\n");
    }
}

void export_to_dot(FILE *f, int **mtr, int size)
{
    fprintf(f, "graph my_graph {\n");
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (mtr[i][j] && i >= j)
                fprintf(f, "%c -- %c;\n", i+'A', j+'A');
    fprintf(f, "}\n");
}
