#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include"input.h"
#include"menu.h"
#include"multiplication.h"
#include"print.h"
#include"struct.h"
#include"efficient.h"

int ** hand_input(int *size, int *count)
{
	setlocale(LC_ALL, "Russian");
	int error = 1;
	int str, col, num;
	printf("\nEnter the size of the matrix: ");
	while (error == 1)
	{
		while (scanf("%d", size) == 0)
		{
			printf("Input error\nEnter the size of the matrix: ");
			clean_stdin();
		}
		if (*size < 1)
			printf("Invalid size\nEnter the size of the matrix: ");
		else
			error = 0;
	}
	int ** matrix = (int**)calloc((*size), sizeof(int*));
	if (matrix != NULL)
	{
		int i = 0;
		for (; i < *size; i++)
		{
			matrix[i] = (int*)calloc((*size), sizeof(int));
			if (matrix[i] == NULL)
			{
				free_mtr(matrix, *size);
			}
		}
	}

	error = 1;
	printf("Enter the number of nonzero elements: ");
	while (error == 1)
	{
		while (scanf("%d", count) == 0)
		{
			printf("Input error\nEnter the number of nonzero elements: ");
			clean_stdin();
		}
		if (*count < 0)
			printf("Invalid amount\nEnter the number of nonzero elements: ");
		else
			error = 0;
	}
	for (int i = 0; i<*count; i++)
	{
		error = 1;
		printf("Enter line number: ");
		while (error == 1)
		{
			while (scanf("%d", &str) == 0)
			{
				printf("Input error\nEnter the line number: ");
				clean_stdin();
			}
			if (str < 0 || str > *size - 1)
				printf("Input error\nEnter the line number: ");
			else
				error = 0;
		}
		error = 1;
		printf("Enter the column number: ");
		while (error == 1)
		{
			while (scanf("%d", &col) == 0)
			{
				printf("Input error\nEnter the column number: ");
				clean_stdin();
			}
			if (col < 0 || col > *size - 1)
				printf("Invalid size\nEnter the column number: ");
			else
				error = 0;
		}
		error = 1;
		printf("Insert the number: ");
		while (scanf("%d", &num) == 0)
		{
			printf("Input error\nInsert the number: ");
			clean_stdin();
		}
		printf("\n");
		matrix[str][col] = num;
	}
	return matrix;
}

int ** file_input(int *size, int *count)
{
	//setlocale(LC_ALL, "Russian");
	FILE *f = fopen("C:/Users/User/Desktop/matrix.txt", "r");
	int str, col, num;
	fscanf(f, "%d %d\n", size, count);
	int ** matrix = (int**)calloc((*size), sizeof(int*));
	if (matrix != NULL)
	{
		int i = 0;
		for (; i < *size; i++)
		{
			matrix[i] = (int*)calloc((*size), sizeof(int));
			if (matrix[i] == NULL)
			{
				free_mtr(matrix, *size);
			}
		}
	}
	for (int i = 0; i<*count; i++)
	{
		fscanf(f, "%d %d %d\n", &str, &col, &num);
		matrix[str][col] = num;
	}
	fclose(f);
	return matrix;
}

void inputing(int **mtr, int size, int count, int *A, int *IA, int *JA)
{
	//printf("%d", mtr[size-1][size - 1]);
	int s, flag = 0;
	JA[size] = count;
	s = count - 1;
	for (int i = size - 1; i >= 0; i--)
	{
		flag = 0;
		for (int j = size - 1; j >= 0; j--)
		{
			//if (s > size)
				//printf("ooops!");
			if (mtr[j][i] != 0)
			{
				A[s] = mtr[j][i];
				IA[s] = j;
				JA[i] = s;
				flag = 1;
				s--;
			}
		}
		if (flag == 0)
			JA[i] = JA[i + 1];
	}
}