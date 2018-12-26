#pragma once

#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define NO_ERROR 0          // ошибок нет
#define OPEN_ERROR -1       // ошибка открытия файла
#define EMPTY -2            // пустой файл
#define SYMBOL -3           // некорректный ввод
#define OUT_OF_RANGE -4     // выход за пределы чисел

#define CHAR_SIZE 32        // размер адресса
#define MAX_SIZE 50         // максимальный размер таблицы

typedef struct              //структура проживающих дома
{
	char street[CHAR_SIZE]; // улица
	int num_house;          //номер дома
	int num_flat;           // номер квартиры
}house;

typedef struct             //структура проживающих в общежитии
{
	int num_comm;          //номер общежития
	int num_room;          // номер комнаты
}comm;

typedef union             // объединение
{
	house home;           // проживающие дома
	comm hostel;          // проживающие в общежитии 
}type;

typedef struct            // структура каждого студента
{
	int type_home;        // тип проживания
	char name[CHAR_SIZE]; //имя студента
	int sex;              // пол
	int age;              // возраст
	int mark;             // средний балл
	char year[CHAR_SIZE]; // дата поступления
	int index;            // индекс
	type type;
}student;

typedef struct                      // структура таблицы ключей
{
	int index;                     
	int age;                       
} key_table;

int checkFile(FILE *f);
int readChar(char *s, FILE *f, int len);
int readInt(int *n, FILE *f, int min_range, int max_range);
void recFromFile(student *houses, key_table *key, int *rec_num, FILE *f, int size);
void printTable(student *stud, key_table *key, int *rec_num, int *flag_sort);
void recTable(student *stud, key_table *key, int *rec_num);
void findApartment(student *stud, key_table *key, int rec_num);
void printKeyTable(key_table *key, int *rec_num);
void print_table_by_key(student *stud, key_table *key, int *rec_num);
void exitMenu();


#endif /* Header_h */


