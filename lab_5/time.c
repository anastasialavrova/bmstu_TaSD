#include "time.h"

double getTime(interval_time t)
{
    return (t.max - t.min) * (double)(rand() / (double)RAND_MAX) + t.min;
}
