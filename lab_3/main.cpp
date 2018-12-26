#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include"input.h"
#include"menu.h"
#include"multiplication.h"
#include"print.h"
#include"struct.h"
#include"efficient.h"

int main(void)
{
	//setlocale(LC_ALL, "Russian");
	int error = 0;
	int choice;
	int ** matrix;
	int size = 0, count = 0;
	while ((choice = menu_1()) == -1);
	if (choice == 1)
	{
		matrix = hand_input(&size, &count);
		if (matrix == NULL)
			error = 1;
	}
	else if (choice == 2)
	{
		matrix = file_input(&size, &count);
		if (matrix == NULL)
			error = 1;
	}

	int *A = (int*)malloc(count * sizeof(int));
	if (A == NULL)
		error = 1;

	int *IA = (int*)malloc(count * sizeof(int));
	if (IA == NULL)
		error = 1;

	int *JA = (int*)malloc((size + 1) * sizeof(int));
	if (JA == NULL)
		error = 1;

	if (count != 0)
		inputing(matrix, size, count, A, IA, JA);

	while ((choice = menu_2()) != 0 && error == 0)
	{
		if (choice == 1)
		{
			if (count == 0)
				printf("There are no nozero elements in the matrix\n"); // n
			else
				error = mult_mtr_raz(A, IA, JA, count, size, 0);
		}
		else if (choice == 2)
		{
			if (count == 0)
				printf("Zero line\n"); // n
			else
				error = mult_mtr(matrix, size, 0);
		}
		else if (choice == 3)
		{
			efficient();
		}
		else if (choice == 4)
		{
			if (count == 0)
				printf("There are no zero elements in the matrix\n"); //n
			else
				print_mtr_raz(A, IA, JA, count, size);
		}
		else if (choice == 5)
		{
			print_mtr(matrix, size);
		}
	}

	if (error)
		printf("Memory allocation error\n"); //n
	free_mtr(matrix, size);

	if (count != 0)
	{
		if (!A)
			free(A);
		if (!IA)
			free(IA);
		if (!JA)
			free(JA);
	}
	return error;
}