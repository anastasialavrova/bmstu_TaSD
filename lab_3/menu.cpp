#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include"input.h"
#include"menu.h"
#include"multiplication.h"
#include"print.h"
#include"struct.h"

int menu_1(void) // ������ ����
{
	//setlocale(LC_ALL, "Russian");
	printf("1) Enter matrix manually\n");
	printf("2) Import from file\n");
	printf("Press option: ");
	int choice;
	if (scanf("%d", &choice))
	{
		if (choice < 3 && choice > 0)
		{
			clean_stdin();
			return choice;
		}
		else
		{
			printf("Unknown parameter\n");
			clean_stdin();
			return -1;
		}
	}
	else
	{
		clean_stdin();
		printf("Unknown parameter\n");
		return -1;
	}
}


int menu_2(void) // ������ ����
{
	//setlocale(LC_ALL, "Russian");
	/*printf("\n1 - ��������� �������-������ �� �������,���������� � ����������� �����,"
		" � ���������� ���������� � ��� �� �����.\n2 - ��������� ����������� ���������� "
		"������ � ���������.\n3 - ������� ������� ���������� �������� � ����� ������ ���"
		" ������������� ���� 2-� ���������� ��� ��������� �������� ���������� ������.\n"
		"4 - ������� ������� � ����������� �����.\n5 - ������� ������� � ������� �����.\n0 - �����\n\n"
		"�����: ");*/
	printf("1) Multiplying the row vector by the matrix stored in a sparse form to get the result in the same form\n");
	printf("2) Multiplication by the standard matrix processing algorithm\n");
	printf("3) Comparison of operation time and memory size\n");
	printf("4) Print the matrix in sparse form\n");
	printf("5) Print the matrix in a simple form.\n");
	printf("0) Exit\n");
	printf("\nPress option: ");
	int choice;
	if (scanf("%d", &choice))
	{
		if (choice < 6 && choice >= 0)
		{
			clean_stdin();
			return choice;
		}
		else
		{
			printf("\nUnknown parameter\n");
			clean_stdin();
			return -1;
		}
	}
	else
	{
		clean_stdin();
		printf("\nUnknown parameter\n");
		return -1;
	}
}