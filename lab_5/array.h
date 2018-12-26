#ifndef array_h
#define array_h

#include <stdio.h>
#include "list.h"

void queueArrayPush(queue* q, char* elem, char c);
char queueArrayPop(queue* q, char* elem);
void queueArrayPrint(queue* q, char* elem);

#endif /* array_h */
