#include "table.h"
#include "sort.h"

int main()
{
	int choice = 0;
	int rec_num = 0;
	int flag_sort = 0;
	student *stud = (student *)malloc(sizeof(student) * MAX_SIZE);
	key_table *key = (key_table *)malloc(sizeof(key_table) * MAX_SIZE);
	while (1)
	{
		printf("Menu:\n");
		printf("1) Add new record\n");
		printf("2) Delete record\n");
		printf("3) Show table\n");
		printf("4) Show key table\n");
		printf("5) Sort table\n");
		printf("6) Sort key table\n");
		printf("7) Find students\n");
		printf("8) Show sorting perfomance\n");
		printf("9) Show sorting table by key");
		//printf("0) Exit\n");

		printf("\nPress option: ");
		if (scanf("%i", &choice) == 0)
			choice = 9;
		if (choice > 9 || choice < 1)
		{
			printf("Wrong parametr\n");
			exitMenu();
		}

		switch (choice)
		{
			// добавить запись
		case 1:
			if (rec_num == MAX_SIZE)
			{
				printf("Table overflow\n");
				exitMenu();
				break;
			}

			printf("\n");
			printf("  Choose adding:\n");
			printf("  1. Import from file\n");
			printf("  2. Input manually\n");
			printf("  0. Exit to main menu\n");

			printf("\nPress option: ");
			if (scanf("%i", &choice) == 0)
				choice = 9;

			if (choice == 1)
			{
				FILE *f = fopen("in_stud.txt", "r");

				if (checkFile(f) == NO_ERROR)
				{
					recFromFile(stud, key, &rec_num, f, MAX_SIZE);
					printf("Total number of records: %i\n", rec_num);
					fclose(f);
				}

				exitMenu();
			}
			// добавить запись вручную
			else if (choice == 2)
			{
				recTable(stud, key, &rec_num);
				exitMenu();
			}

			
			// вернуться в меню
			else if (choice == 0)
			{
				exitMenu();
			}

			else
			{
				printf("\nUnknown parameter\n");
			}
			break;

			// удалить запись
			case 2:
				if (rec_num == 0)
				{
					printf("\nTable is empty\n");
					exitMenu();
					break;
				}

				int num, answ;

				printf("\nInput index of recording (int, range = [0..%i]): ", rec_num - 1);
				if ((scanf("%i", &num) == 0) || (num > rec_num - 1) || (num < 0))
				{
					printf("Input error\n");
					exitMenu();
					break;
				}

				printf("Do you really want to delete apartment in '%s'? (1: yes; 0: no): ", stud[num].name);
				if ((scanf("%i", &answ) == 0) || (answ > 1) || (answ < 0))
				{
					printf("Input error\n");
					exitMenu();
					break;
				}

				if (answ == 0)
				{
					system("clear");
					break;
				}

				if (answ == 1)
				{
					for (int i = num; i < rec_num - 1; ++i)
					{
						stud[i] = stud[i + 1];
						key[i] = key[i + 1];
					}
					rec_num--;
				}

				exitMenu();
				break;
			
			// вывести таблицу
			case 3:
				printTable(stud, key, &rec_num, &flag_sort);
				//exitMenu();
				break;

			
			// вывести таблицу ключей
			case 4:
				printKeyTable(key, &rec_num);
				exitMenu();
				break;
			
			// сортировка
			case 5:
				if (rec_num == 0)
				{
				printf("\nTable is empty\n");
				exitMenu();
				break;
				}

			//flag_sort = 1;
				b_sort(stud, rec_num);
				exitMenu();
				break;

			
			// сортировка по ключу
			case 6:
				if (rec_num == 0)
				{
					printf("\nTable is empty\n");
					exitMenu();
					break;
				}
				key_quick_sort(key, 0, rec_num - 1);
				exitMenu();
				break;
			
			// поиск студентов заданного параметра
			case 7:
				findApartment(stud, key, rec_num);
				exitMenu();
				break;

			// скорость и память различных видов сортировки
			case 8:
				sorting_test();
				exitMenu();
				break;

			case 9:
				print_table_by_key(stud, key, &rec_num);

			// выход

		}
	}
	return NO_ERROR;
}
