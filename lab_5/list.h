#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 100000
#define MAX_LEN 10000
#define ITERATION 10000
#define CPU_GHZ 1.7

typedef struct queue
{
    char name[30];      // Имя очереди
    void* low;          // Адрес нижней границы
    void* up;           // Адрес верхней границы
    void* pin;          // Указатель на "хвост"
    void* pout;         // Указатель на "голову"
    int max_num;        // Число элементов
    size_t size;        // Размер типа данных
    int count_req;      // Число запросов
    int sum_size;       // Средняя длина
    int tmp_size;       // Текущая длина
    int sum_time;       // Общее время
    int out_req;        // Число запросов на выход
    int in_req;         // Число запросов на вход
} queue;

typedef struct node node;
struct node
{
    char inf;
    node *next;
};

node* createElem(char c);
node* pushFront(node *head, node *elem);
node* popFront(node **head);
node* popEnd(node **head);
void freeAll(node *head);
node* queueListPush(node* q, char c, node** used_memory, int *count_used, node** freed_memory, int* count_freed, int* second_used);
node* queueListPop(node** q);
void queueListPrint(node* q);

#endif /* list_h */
