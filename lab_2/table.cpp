#include "table.h"

int checkFile(FILE *f)
{
	if (!f)
	{
		printf("Opening file error\n");
		return OPEN_ERROR;
	}

	if (fgetc(f) == EOF)
	{
		printf("Empty file\n");
		fclose(f);
		return EMPTY;
	}

	rewind(f);
	return NO_ERROR;
}

// функция считывает char
int readChar(char *s, FILE *f, int len)
{
	int ch, i = 0;
	ch = fgetc(f);
	if (ch == '\n')
		return EMPTY;

	while (1)
	{
		if (i > len)
			return OUT_OF_RANGE;

		if (ch == EOF)
			return ch;

		if (ch == '\n')
		{
			s[i] = '\0';
			return NO_ERROR;
		}

		s[i++] = ch;
		ch = fgetc(f);
	}
	return NO_ERROR;
}

/*int readChar_year(char *s, FILE *f, int len)
{
	int ch, i = 0, cnt = 0;
	ch = fgetc(f);
	if (ch == '\n')
		return EMPTY;

	while (1)
	{
		if (i > len)
			return OUT_OF_RANGE;

		if (ch == EOF)
			return ch;

		if (ch == '\n')
		{
			s[i] = '\0';
			return NO_ERROR;
		}
		if ((ch >= 57) || (ch <= 48))
			return SYMBOL;

		s[i++] = ch;
		ch = fgetc(f);
	}
	for (int j = 0; j < )
	return NO_ERROR;
}
*/
// функция считывает int
int readInt(int *n, FILE *f, int min_range, int max_range)
{
	char *num;
	int ch, i = 0;
	num = (char*)calloc(50, sizeof(*num));
	ch = fgetc(f);
	if (ch == '\n')
		return EMPTY;

	while (1)
	{
		if (ch == EOF)
			return ch;
		if (ch == '\n')
		{
			num[i] = '\0';
			break;
		}
		/*if ((ch > 57) || (ch < 48))
			return SYMBOL;*/
		else
			num[i++] = ch;
		ch = fgetc(f);
	}

	ch = atoi(num);
	free(num);

	if ((ch > max_range) || (ch < min_range))
	{
		return OUT_OF_RANGE;
	}

	*n = ch;
	return NO_ERROR;
}

int check_st(int status, int cur_rec)
{
	if (status == EOF)
		return -1;
	else if (status == OUT_OF_RANGE)
	{
		printf("Record #%i: total area is out of range\n", cur_rec);
		return -1;
	}
	else if (status == SYMBOL)
	{
		printf("Record #%i: total area contains wrong symbol (input int number)\n", cur_rec);
		return -1;
	}
	else if (status == EMPTY)
	{
		printf("Record #%i: total area is empty\n", cur_rec);
		return -1;
	}
	else if (status == NO_ERROR)
	{
		return 0;
	}
}

// функция добавляет запись из файла
void recFromFile(student *stud, key_table *key, int *rec_num, FILE *f, int size)
{
	int cur_rec = 0;
	char *entry;
	entry = (char*)calloc(31, sizeof(*entry));
	int number, status;

	while(1)
	{
		if (*rec_num == size)
		{
			printf("Table overflow\n");
			break;
		}

		// тип жилья
		status = readInt(&number, f, -1, 2);
		if (check_st(status, cur_rec) == 0)
			stud[*rec_num].type_home = number;
		else
			break;

		// имя
		status = readChar(entry, f, CHAR_SIZE);
		if (check_st(status, cur_rec) == 0)
			strcpy(stud[*rec_num].name, entry);
		else
			break;

		// пол
		status = readInt(&number, f, -1, 2);
		if (check_st(status, cur_rec) == 0)
			stud[*rec_num].sex = number;
		else
			break;

		// возраст
		status = readInt(&number, f, 16, 100);
		if (check_st(status, cur_rec) == 0)
		{
			stud[*rec_num].age = number;
			key[*rec_num].age = stud[*rec_num].age;
		}
		else
			break;

		// средний балл
		status = readInt(&number, f, 0, 101);
		if (check_st(status, cur_rec) == 0)
			stud[*rec_num].mark = number;
		else
			break;

		// год поступления
		status = readChar(entry, f, CHAR_SIZE);
		if (check_st(status, cur_rec) == 0)
			strcpy(stud[*rec_num].year, entry);
		else
			break;

		// если живет дома
		if (stud[*rec_num].type_home == 1)
		{
			// улица
			status = readChar(entry, f, CHAR_SIZE);
			if (check_st(status, cur_rec) == 0)
				strcpy(stud[*rec_num].type.home.street, entry);
			else
				break;

			// номер дома
			status = readInt(&number, f, 0, 100);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.home.num_house = number;
			else
				break;

			// номер квартиры
			status = readInt(&number, f, 0, 500);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.home.num_flat = number;
			else
				break;
		}
		// если живет в общежитии
		else
		{
			// номер общежития
			status = readInt(&number, f, 0, 500);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.hostel.num_comm = number;
			else
				break;

			// номер комнаты
			status = readInt(&number, f, 0, 500);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.hostel.num_room = number;
			else
				break;
		}

		key[*rec_num].index = *rec_num;
		stud[*rec_num].index = *rec_num;
		(*rec_num)++;
		cur_rec++;
		fscanf(f, "\n");
	}

	if (size == MAX_SIZE)
		printf("%i records added successfully.\n", cur_rec);
	free(entry);
}

void printTable(student *stud, key_table *key, int *rec_num, int *flag_sort)
{
	if (*rec_num == 0)
	{
		printf("\nTable is empty\n");
		return;
	}

	char sx1[] = "male";
	char sx2[] = "female";
	char hm1[] = "home";
	char hm2[] = "community";

	printf("\n");
	printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	printf("| num | name                           | type of home  | sex     | age  | mark  | year          |      street      | number of house | number of flat | number of hostel | number of room|\n");
	printf("|-----|--------------------------------|---------------|---------|------|-------|---------------|------------------|-----------------|----------------|------------------|---------------|\n");

	int k_index;
	for (int i = 0; i < *rec_num; i++)
	{
		k_index = i;
		if (*flag_sort == 1)
			k_index = key[i].index;
		printf("| %2d  | %30s | %13s | %7s | %4d | %5d | %13s |", i, stud[k_index].name, (stud[k_index].type_home == 1 ? hm1 : hm2), 
			(stud[k_index].sex == 1 ? sx1 : sx2), stud[k_index].age, stud[k_index].mark, stud[k_index].year);
		if (stud[k_index].type_home == 1)
		{
			printf("%17s | %14d  | %14d | **************** | ************* |", stud[k_index].type.home.street, stud[k_index].type.home.num_house,
				stud[k_index].type.home.num_flat);
		}
		else
		{
			printf(" **************** | *************** | ************** | %16d | %13d |", stud[k_index].type.hostel.num_comm, stud[k_index].type.hostel.num_room);
		}
		printf("\n");
	}
	printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
}

// функция добавляет запись вручную
void recTable(student *stud, key_table *key, int *rec_num)
{
	printf("\n");
	int answ = 1;
	int cur_rec = 0;
	char *entry;
	entry = (char*)calloc(31, sizeof(*entry));
	int number, status;

	while (1)
	{
		if (*rec_num == MAX_SIZE)
		{
			printf("Table overflow\n");
			break;
		}

		fgetc(stdin);

		// тип жилья
		printf("Input type of home (0 - hostel, 1 - house): ");
		status = readInt(&number, stdin, -1, 2);

		if (check_st(status, cur_rec) == 0)
			stud[*rec_num].type_home = number;
		else
			break;

		// имя
		printf("Input name: ");
		status = readChar(entry, stdin, CHAR_SIZE);

		if (check_st(status, cur_rec) == 0)
			strcpy(stud[*rec_num].name, entry);
		else
			break;

		// пол
		printf("Input sex (0 - female, 1 - male): ");
		status = readInt(&number, stdin, -1, 2);

		if (check_st(status, cur_rec) == 0)
			stud[*rec_num].sex = number;
		else
			break;

		// возраст
		printf("Input age: ");
		status = readInt(&number, stdin, 15, 100 );

		if (check_st(status, cur_rec) == 0)
		{
			stud[*rec_num].age = number;
			key[*rec_num].age = stud[*rec_num].age;
		}
		else
			break;

		// баллы
		printf("Input integer mark [0...100]: ");
		status = readInt(&number, stdin, 0, 101);

		if (check_st(status, cur_rec) == 0)
			stud[*rec_num].mark = number;
		else
			break;

		// год поступления
		printf("Input year (dd.mm.yyyy): ");
		status = readChar(entry, stdin, CHAR_SIZE);

		if (check_st(status, cur_rec) == 0)
			strcpy(stud[*rec_num].year, entry);
		else
			break;
		if (stud[*rec_num].type_home == 1)
		{
			// улица
			printf("Input street: ");
			status = readChar(entry, stdin, CHAR_SIZE);
			if (check_st(status, cur_rec) == 0)
				strcpy(stud[*rec_num].type.home.street, entry);
			else
				break;

			// номер дома
			printf("Input number of house: ");
			status = readInt(&number, stdin, 0, 500);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.home.num_house = number;
			else
				break;

			// номер квартиры
			printf("Input number of flat: ");
			status = readInt(&number, stdin, 0, 500);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.home.num_flat = number;
			else
				break;
		}
		// если живет в общежитии
		else
		{
			// номер общежития
			printf("Input number of hostel: ");
			status = readInt(&number, stdin, 0, 500);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.hostel.num_comm = number;
			else
				break;

			// номер комнаты
			printf("Input number of room: ");
			status = readInt(&number, stdin, 0, 500);
			if (check_st(status, cur_rec) == 0)
				stud[*rec_num].type.hostel.num_room = number;
			else
				break;
		}


		key[*rec_num].index = *rec_num;
		stud[*rec_num].index = *rec_num;
		(*rec_num)++;
		cur_rec++;

		printf("Do you want to add one more record? (1: yes; 0: no): ");
		if ((scanf("%i", &answ) == 0) || (answ > 1) || (answ < 0))
		{
			printf("Input error!\n");
			break;
		}

		if (answ == 0)
			break;
	}
	free(entry);
	printf("%i records added successfully.\nTotal number of records: %i\n", cur_rec, *rec_num);
}

void exitMenu()
{
	printf("Press enter to continue ");
	while (getchar() != '\n');
	getchar();
	//system("clear");
}

// функция нахождения студента по указанного года рождения, проживающего в общежитии
void findApartment(student *stud, key_table *key, int rec_num)
{
	if (rec_num == 0)
	{
		printf("\nTable is empty!\n");
		return;
	}

	int year, flag = 0;
	int k_index;
	printf("Input year: ");

	if (scanf("%d", &year) == 0)
	{
		printf("Input error\n");
		return;
	}

	if (year > 2018 && year < 1950)
	{
		printf("Error!\n");
		return;
	}

	char sx1[] = "male";
	char sx2[] = "female";
	char hm1[] = "home";
	char hm2[] = "community";

	for (int i = 0; i < rec_num; i++)
	{
		k_index = key[i].index;
		int d = 1, year_s = 0;
		for (int j = 6; j <= 9; j++)
		{
			year_s += (stud[k_index].year[j] - '0');
			if (j != 9)
				year_s *= 10;
		}

		if ((stud[k_index].type_home == 0) && (year_s == year))
		{
			if (flag == 0)
			{
				//flag = 1;
				printf("\n");
				printf("|----------------------------------------------------------------------------------------------------------------------------------|\n");
				printf("| num | name                           | type of home  | sex     | age  | mark  | year          | number of hostel | number of room|\n");
				printf("|-----|--------------------------------|---------------|---------|------|-------|---------------|------------------|---------------|\n");
				printf("| %2d  | %30s | %13s | %7s | %4d | %5d | %13s |  %15d | %13d |", i, stud[k_index].name, (stud[k_index].type_home == 1 ? hm1 : hm2), 
					(stud[k_index].sex == 1 ? sx1 : sx2), stud[k_index].age, stud[k_index].mark, 
					stud[k_index].year, stud[k_index].type.hostel.num_comm, stud[k_index].type.hostel.num_room);
				printf("\n|----------------------------------------------------------------------------------------------------------------------------------|\n");
			}
		}
	}		
}

void printKeyTable(key_table *key, int *rec_num)
{
	if (*rec_num == 0)
	{
		printf("\nTable is empty\n");
		return;
	}

	printf("\n");
	printf("|-------------|-----------|---------------|\n");
	printf("| Table index | Key index |      Age      |\n");
	printf("|-------------|-----------|---------------|\n");

	for (int i = 0; i < *rec_num; i++)
	{
		printf("| %11i | %9i | %13i |\n", i, key[i].index, key[i].age);

		if (i != *rec_num - 1)
			printf("|-------------|-----------|---------------|\n");
		else
			printf("|-------------|-----------|---------------|\n");
	}
}

void print_table_by_key (student *stud, key_table *key, int *rec_num)
{
	if (*rec_num == 0)
	{
		printf("\nTable is empty\n");
		return;
	}

	char sx1[] = "male";
	char sx2[] = "female";
	char hm1[] = "home";
	char hm2[] = "community";

	printf("\n");
	printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	printf("| num | name                           | type of home  | sex     | age  | mark  | year          |      street      | number of house | number of flat | number of hostel | number of room|\n");
	printf("|-----|--------------------------------|---------------|---------|------|-------|---------------|------------------|-----------------|----------------|------------------|---------------|\n");

	int k_index;
	for (int i = 0; i < *rec_num; i++)
	{
		k_index = key[i].index;
		printf("| %2d  | %30s | %13s | %7s | %4d | %5d | %13s |", i, stud[k_index].name, (stud[k_index].type_home == 1 ? hm1 : hm2),
			(stud[k_index].sex == 1 ? sx1 : sx2), stud[k_index].age, stud[k_index].mark, stud[k_index].year);
		if (stud[k_index].type_home == 1)
		{
			printf("%17s | %14d  | %14d | **************** | ************* |", stud[k_index].type.home.street, stud[k_index].type.home.num_house,
				stud[k_index].type.home.num_flat);
		}
		else
		{
			printf(" **************** | *************** | ************** | %16d | %13d |", stud[k_index].type.hostel.num_comm, stud[k_index].type.hostel.num_room);
		}
		printf("\n");
	}
	printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
}
