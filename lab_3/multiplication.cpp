#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime> 

#include"input.h"
#include"menu.h"
#include"multiplication.h"
#include"print.h"
#include"struct.h"

int mult_mtr(int **matrix, int size, int flag)
{
	int *string;
	//setlocale(LC_ALL, "Russian");
	if (flag == 0)
		string = get_string(size);
	else
	{
		string = (int*)malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
		{
			string[i] = rand() % 100 + 1;
		}
	}
	if (string != NULL)
	{
		int *result = (int*)calloc(size, sizeof(int));
		if (result != NULL)
		{
			for (int i = 0; i<size; i++)
				for (int j = 0; j<size; j++)
					result[i] = result[i] + string[j] * matrix[j][i];
			if (flag == 0)
			{
				printf("\nResult line-vector: \n");
				for (int j = 0; j < size; j++)
					printf("%d ", result[j]);
				printf("\n");
			}
			free(result);
		}
		free(string);
		return 0;
	}
	else
		return 1;
}

int mult_mtr_raz(int *A, int *IA, int*JA, int count, int size, int flag1)
{
	int *string;
	if (flag1 == 0)
		string = get_string(size);
	else
	{
		string = (int*)malloc(size * sizeof(int));
		for (int i = 0; i < size; i++)
		{
			string[i] = rand() % 100 + 1;
		}
	}
	int error = 0;
	int count_s = 0;
	for (int m = 0; m < size; m++)
	{
		if (string[m] != 0)
			count_s++;
	}
	int * AS = (int*)malloc(count_s * sizeof(int));
	if (AS == NULL)
		error = 1;
	int * JAS = (int*)malloc((size + 1) * sizeof(int));
	if (JAS == NULL)
		error = 1;
	if (error)
	{
		if (!JAS)
			free(JAS);
		if (!AS)
			free(AS);
		return error;
	}
	if (count_s != 0)
	{
		int flag = 0;
		int s = count_s - 1;
		JAS[size] = count_s;
		for (int i = size - 1; i >= 0; i--)
		{
			flag = 0;
			if (string[i] != 0)
			{
				AS[s] = string[i];
				JAS[i] = s;
				s--;
				flag = 1;
			}
			if (flag == 0)
				JAS[i] = JAS[i + 1];
		}
	}
	else
	{
		if (!JAS)
			free(JAS);
		if (!AS)
			free(AS);
		printf("There are no nonzero elements in the vector line\n");
		return 0;
	}
	if (string != NULL)
	{
		int * AR = (int*)calloc(size, sizeof(int));
		if (AR == NULL)
			error = 1;
		int * JAR = (int*)malloc((size + 1) * sizeof(int));
		if (JAR == NULL)
			error = 1;
		JAR[size] = size - 1;
		if (JAR != NULL && AR != NULL)
		{
			int r = 0;
			int k = 0;
			int count_r = 0;
			for (int i = 0; i<size; i++)
			{
				for (int z = 0, j = JA[i]; j <= JA[i + 1] - 1; z++)
				{
					if (IA[k] == z)
					{
						if (JAS[z] != JAS[z + 1])
						{
							AR[r] += AS[JAS[z]] * A[k];
						}
						k++;
						j++;
					}
				}
				if (AR[r] != 0)
				{
					count_r++;
					JAR[i] = r;
					r++;
				}
				else
					JAR[i] = -1;
			}

			for (int i = size - 1; i >= 0; i--)
				if (JAR[i] == -1)
					JAR[i] = JAR[i + 1];

			if (flag1 == 0 && count_r != 0)
			{
				printf("\nResult:\n");
				printf("A: ");
				for (int i = 0; i < count_r; i++)
					printf("%d ", AR[i]);
				printf("\nJA: ");
				for (int i = 0; i < size + 1; i++)
					printf("%d ", JAR[i]);
				printf("\n");
			}
			if (count_r == 0)
			{
				printf("Zero matrix\n\n");
			}
		}
		if (!JAR)
			free(JAR);
		if (!AR)
			free(AR);
		free(string);
		return 0;
	}
	else
		return 1;
	if (!JAS)
		free(JAS);
	if (!AS)
		free(AS);
}


