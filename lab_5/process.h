#ifndef process_h
#define process_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "array.h"
#include "process.h"
#include "time.h"
#include "display.h"

void workArray(int n, int interval, interval_time t1, interval_time t2, interval_time t3, interval_time t4, int flag);

void workList(int n, int interval, interval_time t1, interval_time t2, interval_time t3, interval_time t4, int flag);

#endif /* process_h */
