#ifndef time_h
#define time_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct interval_time
{
    double min;
    double max;
} interval_time;

double getTime(interval_time t);

#endif /* time_h */
