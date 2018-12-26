#include "array.h"

void queueArrayPush(queue* q, char* elem, char c)
{
    char* pin = q->pin;
    if (q->pin == q->pout && *((char*)q->pin) != '\0')
        printf("The queue is full\n");
        //printf("Очередь заполнена\n");
    else
    {
        *((char*)q->pin) = c;
        if (q->pin != q->up)
            q->pin = pin + 1;
        else
            q->pin = q->low;
    }
    return;
}

char queueArrayPop(queue* q, char* elem)
{
    char* pout = q->pout;
    char ps;
    if (q->pin == q->pout && *((char*)q->pin) == '\0')
    {
        printf("Empty queue\n");
        //printf("Пустая очередь\n");
    }
    else
    {
        ps = *((char*)q->pout);
        *((char*)q->pout) = '\0';
        if (q->pout != q->up)
            q->pout = pout + 1;
        else
            q->pout = q->low;
    }
    return ps;
}

void queueArrayPrint(queue* q, char* elem)
{
    if (q->pin == q->pout && *((char*)q->pin) == '\0')
    {
        printf("Empty queue\n");
        //printf("Пустая очередь\n");
    }
    else
    {
        printf("Current queue: \n");
        //printf("Теуцщаяя очередь: \n");
        char* begin = q->pout;
        char* end = q->pin;
        do
        {
            printf("%c \n", *begin);
            if (begin != q->up)
                begin += 1;
            else
                begin = q->low;
        }
        while(begin != end);
        printf("\n");
    }
}
