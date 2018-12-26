#pragma once

#ifndef sort_h
#define sort_h

#include<stdio.h>
#include<iostream>
#include<stdlib.h>

#include"table.h"

#define SORT_1 1000
#define SORT_2 5000
#define SORT_3 10000

void b_sort(student *stud, int rec_num);
void key_quick_sort(key_table *key, int first, int last);
void inputTestTable(student *stud, key_table *key, int *rec_num, int size);
void sorting_test();

#endif