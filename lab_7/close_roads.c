#include <stdio.h>
#include <stdlib.h>

#include "close_roads.h"
#include "matrix.h"

void roads(int **matrix, int n)
{
    int h = 0;
    int is_naideno, impossible_to_reach = 0;
    char c = 'A';
    int **matrix_copy = copy_matrix(matrix, n, n);
    for (int i = 0; i < n*n; i++)
        for (int j = 0; j < n*n; j++)
            for (int k = 0; k < n*n; k++)
            {
                if (matrix_copy[i/n][i%n] && matrix_copy[j/n][j%n] && matrix_copy[k/n][k%n]
                    && i != j && j != k && i != k && i%n>i/n && j%n>j/n && k%n>k/n && k > j && j > i)
                {
                    h++;
                    matrix_copy[i/n][i%n] = 0;
                    matrix_copy[j/n][j%n] = 0;
                    matrix_copy[k/n][k%n] = 0;

                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                            if (matrix_copy[i][j] == 0)
                                matrix_copy[j][i] = 0;

                    //printf("Закрытые дороги: %c%c, %c%c, %c%c\n", c+i/n, c+i%n, c+j/n, c+j%n,c+k/n, c+k%n);
                    //printf("Closed roads: %c%c, %c%c, %c%c\n", c+i/n, c+i%n, c+j/n, c+j%n,c+k/n, c+k%n);
                    int mas[n];
                    for (int i = 0; i < n; i++)
                        mas[i] = 1;
//                    printf("Путь: ");
                    is_naideno = find_d(matrix_copy, n, 0, mas);
                    if (is_naideno)
                    {
                        //printf("Можно попасть в город B\n");
                        //printf("You can get to the city B\n");
                    }
                    else
                    {
                        printf("Closed roads: %c%c, %c%c, %c%c\n", c+i/n, c+i%n, c+j/n, c+j%n,c+k/n, c+k%n);
                        printf("!You can not get to the city B\n");
                        impossible_to_reach++;
                        printf("\n");
                    }

                    //printf("\n");

                    matrix_copy[i/n][i%n] = 1;
                    matrix_copy[j/n][j%n] = 1;
                    matrix_copy[k/n][k%n] = 1;

                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                            if (matrix_copy[i][j] == 1)
                                matrix_copy[j][i] = 1;

                }
            }
    //printf("Кол-во рассмотренных случаев: %d\n", h);
    //printf("Кол-во случаев, в которых нельзя попасть из города А в В: %d\n\n",
    //impossible_to_reach);
    printf("Number of cases reviewed: %d\n", h);
    printf("The number of cases in which you can not get from city A to B: %d\n\n",
           impossible_to_reach);
    free(matrix_copy);
}

int find_d(int **a, int n, int k, int* mas)
{

    if (k == 1)
    {
//        printf("B\n");
        return 1;
    }
    else
//        printf("%c -> ", k+'A');

        mas[k] = 0;
    for (int i = 0; i < n; i++)
        if (a[k][i] && mas[i])
            if (find_d(a, n, i, mas))
                return 1;

    return 0;
}
