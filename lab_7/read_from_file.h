
#ifndef ROADS_READ_FROM_FILE_H
#define ROADS_READ_FROM_FILE_H

int** read_file(FILE *file, int *n, int *m);
void print_mas(int **matrix, int n, int m);
void export_to_dot(FILE *f, int **mtr, int size);

#endif //ROADS_READ_FROM_FILE_H
