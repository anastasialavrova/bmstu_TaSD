#include<stdio.h>
#include<iostream>
#include<stdlib.h>

#include"table.h"
#include"sort.h"

// сортировки для общей таблицы

void b_sort(student *stud, int rec_num)
{
	int i, j;
	student *t = (student*)malloc(sizeof(student));

	for (i = rec_num - 1; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (stud[j].age > stud[j + 1].age)
			{
				*t = stud[j];
				stud[j] = stud[j + 1];
				stud[j + 1] = *t; 
			}
		}
	}

	free(t);
}

void quick_sort(student *stud, int first, int last)
{
	int i = first;
	int j = last;
	int x = stud[(first + last) / 2].age;

	student *temp = (student *)malloc(sizeof(student));

	do
	{
		while (stud[i].age < x)
			i++;
		while (stud[j].age > x)
			j--;

		if (i <= j)
		{
			if (stud[i].age > stud[j].age)
			{
				*temp = stud[i];
				stud[i] = stud[j];
				stud[j] = *temp;
			}
			i++;
			j--;
		}
	} while (i <= j);

	free(temp);

	if (i < last)
		quick_sort(stud, i, last);
	if (first < j)
		quick_sort(stud, first, j);
}


// сортировки для таблицы ключей

void key_quick_sort(key_table *key, int first, int last)
{
	int i = first;
	int j = last;
	int x = key[(first + last) / 2].age;

	key_table *temp = (key_table *)malloc(sizeof(key_table));

	do
	{
		while (key[i].age < x)
			i++;
		while (key[j].age > x)
			j--;

		if (i <= j)
		{
			if (key[i].age > key[j].age)
			{
				*temp = key[i];
				key[i] = key[j];
				key[j] = *temp;
			}
			i++;
			j--;
		}
	} while (i <= j);

	free(temp);

	if (i < last)
		key_quick_sort(key, i, last);
	if (first < j)
		key_quick_sort(key, first, j);
}


void key_sort(key_table *key, int rec_num)
{
	int i, j;
	key_table *temp = (key_table *)malloc(sizeof(key_table));

	for (i = rec_num - 1; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (key[j].age > key[j + 1].age)
			{
				*temp = key[j];
				key[j] = key[j + 1];
				key[j + 1] = *temp;
			}
		}
	}

	free(temp);
}


void inputTestTable(student *stud, key_table *key, int *rec_num, int size)
{
	while (1)
	{
		if (*rec_num == size)
			break;

		stud[*rec_num].type_home = 0;
		strcpy(stud[*rec_num].name, "\0");
		stud[*rec_num].sex = rand() % 1 + 0;
		stud[*rec_num].age = rand() % 100 + 16;
		stud[*rec_num].mark = rand() % 100 + 0;
		strcpy(stud[*rec_num].year, "\0");
		stud[*rec_num].type.hostel.num_comm = rand() % 20 + 1;
		stud[*rec_num].type.hostel.num_room = rand() % 70 + 1;
		key[*rec_num].index = *rec_num;
		(*rec_num)++;
	}
}


void sorting_test()
{
	int rec_num = 0;
	unsigned long long t0, t1;
	unsigned long long s_1, s_2, s_3, ks_1, ks_2, ks_3;
	unsigned long long srt, qsrt, ksrt, kqsrt;
	student *main_table;
	key_table *key_table_out;

	printf("|---------------------------|------------|------------|------------|------------|\n");
	printf("| Table size                | %10i | %10i | %10i | Average    |\n", SORT_1, SORT_2, SORT_3);
	printf("|---------------------------|------------|------------|------------|------------|\n");

	main_table = (student *)malloc(sizeof(student) * SORT_1);
	key_table_out = (key_table *)malloc(sizeof(key_table)*SORT_1);

	inputTestTable(main_table, key_table_out, &rec_num, SORT_1);

	t0 = clock();
	b_sort(main_table, rec_num);
	t1 = clock();
	s_1 = t1 - t0;

	t0 = clock();
	key_sort(key_table_out, rec_num);
	t1 = clock();
	ks_1 = t1 - t0;

	free(main_table);
	free(key_table_out);
	rec_num = 0;

	main_table = (student *)malloc(sizeof(student) * SORT_2);
	key_table_out = (key_table *)malloc(sizeof(key_table) * SORT_2);

	inputTestTable(main_table, key_table_out, &rec_num, SORT_2);

	t0 = clock();
	b_sort(main_table, rec_num);
	t1 = clock();
	s_2 = t1 - t0;

	t0 = clock();
	key_sort(key_table_out, rec_num);
	t1 = clock();
	ks_2 = t1 - t0;

	free(main_table);
	free(key_table_out);
	rec_num = 0;

	main_table = (student *)malloc(sizeof(student) * SORT_3);
	key_table_out = (key_table *)malloc(sizeof(key_table) * SORT_3);

	inputTestTable(main_table, key_table_out, &rec_num, SORT_3);

	t0 = clock();
	b_sort(main_table, rec_num);
	t1 = clock();
	s_3 = t1 - t0;

	t0 = clock();
	key_sort(key_table_out, rec_num);
	t1 = clock();
	ks_3 = t1 - t0;

	free(main_table);
	free(key_table_out);
	rec_num = 0;

	srt = (s_1 + s_2 + s_3) / 3;
	ksrt = (ks_1 + ks_2 + ks_3) / 3;

	printf("| Bubble sort (secs)        | %10.6f | %10.6f | %10.6f | %10.6f |\n", ((float)s_1) / CLOCKS_PER_SEC, ((float)s_2) / CLOCKS_PER_SEC, ((float)s_3) / CLOCKS_PER_SEC, ((float)srt) / CLOCKS_PER_SEC);
	printf("|---------------------------|------------|------------|------------|------------|\n");
	printf("| Bubble key sort (secs)    | %10.6f | %10.6f | %10.6f | %10.6f |\n", ((float)ks_1) / CLOCKS_PER_SEC, ((float)ks_2) / CLOCKS_PER_SEC, ((float)ks_3) / CLOCKS_PER_SEC, ((float)ksrt) / CLOCKS_PER_SEC);
	printf("|---------------------------|------------|------------|------------|------------|\n");

	main_table = (student *)malloc(sizeof(student) * SORT_1);
	key_table_out = (key_table *)malloc(sizeof(key_table) * SORT_1);

	inputTestTable(main_table, key_table_out, &rec_num, SORT_1);

	t0 = clock();
	quick_sort(main_table, 0, rec_num - 1);
	t1 = clock();
	s_1 = t1 - t0;

	t0 = clock();
	key_quick_sort(key_table_out, 0, rec_num - 1);
	t1 = clock();
	ks_1 = t1 - t0;

	free(main_table);
	free(key_table_out);
	rec_num = 0;

	main_table = (student *)malloc(sizeof(student) * SORT_2);
	key_table_out = (key_table *)malloc(sizeof(key_table) * SORT_2);

	inputTestTable(main_table, key_table_out, &rec_num, SORT_2);

	t0 = clock();
	quick_sort(main_table, 0, rec_num - 1);
	t1 = clock();
	s_2 = t1 - t0;

	t0 = clock();
	key_quick_sort(key_table_out, 0, rec_num - 1);
	t1 = clock();
	ks_2 = t1 - t0;

	free(main_table);
	free(key_table_out);
	rec_num = 0;

	main_table = (student *)malloc(sizeof(student) * SORT_3);
	key_table_out = (key_table *)malloc(sizeof(key_table) * SORT_3);

	inputTestTable(main_table, key_table_out, &rec_num, SORT_3);

	t0 = clock();
	quick_sort(main_table, 0, rec_num - 1);
	t1 = clock();
	s_3 = t1 - t0;

	t0 = clock();
	key_quick_sort(key_table_out, 0, rec_num - 1);
	t1 = clock();
	ks_3 = t1 - t0;

	free(main_table);
	free(key_table_out);
	rec_num = 0;

	qsrt = (s_1 + s_2 + s_3) / 3;
	kqsrt = (ks_1 + ks_2 + ks_3) / 3;

	printf("| Quick sort (secs)         | %10.6f | %10.6f | %10.6f | %10.6f |\n", ((float)s_1) / CLOCKS_PER_SEC, ((float)s_2) / CLOCKS_PER_SEC, ((float)s_3) / CLOCKS_PER_SEC, ((float)qsrt) / CLOCKS_PER_SEC);
	printf("|---------------------------|------------|------------|------------|------------|\n");
	printf("| Quick key sort (secs)     | %10.6f | %10.6f | %10.6f | %10.6f |\n", ((float)ks_1) / CLOCKS_PER_SEC, ((float)ks_2) / CLOCKS_PER_SEC, ((float)ks_3) / CLOCKS_PER_SEC, ((float)kqsrt) / CLOCKS_PER_SEC);
	printf("|---------------------------|------------|------------|------------|------------|\n");


	s_1 = sizeof(student) * SORT_1;
	s_2 = sizeof(student) * SORT_2;
	s_3 = sizeof(student) * SORT_3;

	printf("| Main table memory (bytes) | %10llu | %10llu | %10llu | ---------- |\n", s_1, s_2, s_3);
	printf("|---------------------------|------------|------------|------------|------------|\n");

	ks_1 = sizeof(key_table) * SORT_1 + s_1;
	ks_2 = sizeof(key_table) * SORT_2 + s_2;
	ks_3 = sizeof(key_table) * SORT_3 + s_3;

	printf("| Key table memory (bytes)  | %10llu | %10llu | %10llu | ---------- |\n", ks_1, ks_2, ks_3);
	printf("|---------------------------|------------|------------|------------|------------|\n");

	printf("\n    Conclusion:\n");
	printf("Quick sort is %llu%% faster than Bubble sort.\n", (100 * srt / qsrt) - 100);
	printf("Key table sort is %llu%% faster than main table sort.\n", (100 * srt / ksrt) - 100);
	printf("Main table with key table uses %llu%% more bytes than main table without key table.\n", (100 * ks_1 / s_1) - 100);
}