#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLOSED_ROADS 3

#include "close_roads.h"
#include "matrix.h"
#include "read_from_file.h"

//Задана система двусторонних дорог.
//Определить, можно ли, закрыв какие-нибудь три дороги, добиться того,
//чтобы из города А нельзя было попасть в город В.

unsigned long int tick(void)
{
    unsigned long int d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}


int main()
{
    unsigned long int time_b, time_e, time_res;
    FILE *file = fopen("file.txt", "r");
    int n, m;
    int **matrix = read_file(file, &n, &m);
    print_mas(matrix, n, m);
    printf("\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == 1)
                matrix[j][i] = 1;

    file = fopen("graph.gv","w");
    export_to_dot(file, matrix, n);
    fclose(file);
    printf("\n");

    time_b = tick();
    roads(matrix, n);
    time_e = tick();
    time_res = time_e - time_b;
    printf("Time: %8ld", time_res);
    free(matrix);

    return 0;
}
