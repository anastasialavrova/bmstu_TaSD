#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct ja
{
	int num;
	struct ja *next;
};

void free_ja(struct ja * JA);
void add_elem(struct ja **JA);
void clean_stdin(void);
void free_mtr(int **mtr, int size);