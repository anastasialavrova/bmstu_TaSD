#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime> 

#include"input.h"
#include"menu.h"
#include"multiplication.h"
#include"print.h"
#include"struct.h"
#include"efficient.h"

int mult_mtr1(int **matrix, int size, int *string)
{
	if (string != NULL)
	{
		int *result = (int*)calloc(size, sizeof(int));
		if (result != NULL)
		{
			for (int i = 0; i<size; i++)
				for (int j = 0; j<size; j++)
					result[i] = result[i] + string[j] * matrix[j][i];

			free(result);
		}
		return 0;
	}
	else
		return 1;
}

int mult_mtr_raz1(int *A, int *IA, int *JA, int count, int size, int *string)
{
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

		}
		if (!JAR)
			free(JAR);
		if (!AR)
			free(AR);
		return 0;
	}
	else
		return 1;
	if (!JAS)
		free(JAS);
	if (!AS)
		free(AS);
}

void calculation(int n, int p)
{
	unsigned long long t0, t1;
	unsigned long long s_1, s_2, m_1 = 0.0, m_2 = 0.0;
	int *A = (int*)malloc(n*n / 100 * p * sizeof(int));
	int *IA = (int*)malloc(n*n / 100 * p * sizeof(int));
	int *JA = (int*)malloc((n + 1) * sizeof(int));
	int **matrix = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		matrix[i] = (int*)malloc(sizeof(int)*n);
	int *string = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
	{
		string[i] = rand() % 100 + 1;
	}
	int c = n*n / 100 * p;
	while (c != 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (c != 0)
				{
					int r = rand() % 2 + 0;
					matrix[i][j] = r;
					if (r != 0)
						c--;
				}
				else
					matrix[i][j] = 0;
			}
		}
	}
	c = n*n / 100 * p;

	inputing(matrix, n, c, A, IA, JA);

	t0 = clock();
	mult_mtr1(matrix, n, string);
	t1 = clock();
	s_1 = t1 - t0;

	t0 = clock();
	//mult_mtr_raz1(A, IA, JA, c, n, string);
	mult_mtr1(matrix, n, string);
	t1 = clock();
	s_2 = t1 - t0;

	for (int i = 0; i < n; i++)
	{
		m_1 += sizeof(matrix[i]);
		for (int j = 0; j < n; j++)
			m_1 += sizeof(matrix[i][j]);
	}
	for (int i = 0; i < c+1; i++)
	{
		if (i < c)
		{
			m_2 += sizeof(A[i]);
			m_2 += sizeof(IA[i]);
			m_2 += sizeof(JA[i]);
		}
		else
			m_2 += sizeof(JA[i]);
	}

	output(s_1, s_2, m_1, m_2, n, p);

	free(string);
	free(A);
	free(IA);
	free(JA);
	for (int i = 0; i < n; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}



void efficient()
{
	int n1 = 1000, n2 = 5000, n3 = 9000;
	int p5 = 10, p25 = 25, p50 = 50, p75 = 75, p100 = 100;

	printf("|---------------------------|------------------------------|---------------------------|--------------------------------|-----------------------------|\n");
	printf("| Matrix size               | Simple multiplication (time) | New multiplication (time) | Simple multiplication (memory) | New multiplication (memory) |\n");
	printf("|---------------------------|------------------------------|---------------------------|--------------------------------|-----------------------------|\n");


	//1(1)
	calculation(n1, p5);

	//2(1)
	calculation(n1, p25);

	//3(1)
	calculation(n1, p50);

	//4(1)
	calculation(n1, p75);

	//5(1)
	calculation(n1, p100);

	//1(2)
	calculation(n2, p5);

	//2(2)
	calculation(n2, p25);

	//3(2)
	calculation(n2, p50);

	//4(2)
	calculation(n2, p75);

	//5(2)
	calculation(n2, p100);

	//1(3)
	calculation(n3, p5);

	//2(3)
	calculation(n3, p25);

	//3(3)
	calculation(n3, p50);

	//4(3)
	calculation(n3, p75);

	//5(3)
	calculation(n3, p100);
}

void output(unsigned long long s_1, unsigned long long s_2, unsigned long long m_1, unsigned long long m_2, int n, int p)
{
	printf("| %d elements (%d proc)    |          %10.3f          |          %10.3f       |           %10.1f           |         %10.1f          |\n", n, p, ((float)s_1) / CLOCKS_PER_SEC, ((float)s_2) / CLOCKS_PER_SEC, ((float)m_1), ((float)m_2));
	printf("|---------------------------|------------------------------|---------------------------|--------------------------------|-----------------------------|\n");
}