#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include"input.h"
#include"menu.h"
#include"multiplication.h"
#include"print.h"
#include"struct.h"

void print_mtr(int **mtr, int size)
{
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
			printf("%6d ", mtr[i][j]);
		printf("\n");
	}
}

void print_mtr_raz(int *A, int *IA, int*JA, int count, int size)
{
	printf("A: ");
	for (int i = 0; i<count; i++)
		printf("%d ", A[i]);
	printf("\n");
	printf("IA: ");
	for (int i = 0; i<count; i++)
		printf("%d ", IA[i]);
	printf("\n");
	printf("JA: ");
	for (int i = 0; i<size + 1; i++)
		printf("%d ", JA[i]);
	printf("\n");
}

int * get_string(int size)
{
	setlocale(LC_ALL, "Russian");
	int num;
	int *string = (int*)calloc(size, sizeof(int));
	if (string != NULL)
	{
		printf("\nVector line: \n");
		
		printf("Input number of nonzero elements: ");
		int n, k;
		scanf("%d", &n);
		int error;
		for (int i = 0; i < n; i++)
		{
			printf("Enter index: ");
			while (scanf("%d", &k) == 0)
			{
				printf("Input error\nEnter index: ");
				clean_stdin();
			}
			if (k < 0 || k > size - 1)
				printf("Input error\nEnter index: ");
			else
				error = 0;

			printf("Insert the number: ");
			while (scanf("%d", &num) == 0)
			{
				printf("Input error\nInsert the number: ");
				clean_stdin();
			}
			string[k] = num;
		}

		/*for (int i = 0; i<size; i++)
		{
			printf("\nInput %d element: ", i);
			while (scanf("%d", &num) == 0)
			{
				printf("\nInput error\nInput %d element: ", i);
				clean_stdin();
			}
			string[i] = num;
		}*/

		return string;
	}
	else
		return NULL;
}