#include "list.h"

node* createElem(char c)
{
    node *elem = malloc(sizeof(node));
    if (elem)
    {
        elem->inf = c;
        elem->next = NULL;
    }
    return elem;
}

node* pushFront(node *head, node *elem)
{
    elem->next = head;
    return elem;
}

node* popFront(node **head)
{
    node* cur = NULL;
    if (head)
    {
        cur = (*head);
        (*head) = (*head)->next;
    }
    return cur;
}

node* popEnd(node **head)
{
    node* end = NULL;
    if (*head != NULL)
    {
        node *cur = (*head);
        if (cur->next)
        {
            for ( ; cur->next->next; cur = cur->next)
                ;
            end = cur->next;
            cur->next = NULL;
        }
        else
        {
            end = cur;
            *head = NULL;
        }
    }
    return end;
}

void freeAll(node *head)
{
    node *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

node* queueListPush(node* q, char c, node** used_memory, int *count_used, node** freed_memory, int* count_freed, int* second_used)
{
    node* item = NULL;
    item = createElem(c);
    if (item)
    {
        used_memory[*(count_used++)] = item;
        int znak = 0;
        for (int i = 0; i < *count_freed; i++)
        {
            if (item == freed_memory[i])
            {
                freed_memory[i] = NULL;
                znak = 1;
            }
            if (znak)
                freed_memory[i] = freed_memory[i+1];
        }
        if (znak)
        {
            *count_freed -= 1;
            *second_used += 1;
        }
        q = pushFront(q, item);
    }
    else
        printf("The queue is full\n");
        //printf("Очередь заполнена\n");
    return q;
}

node* queueListPop(node** q)
{
    node* cur = NULL;
    cur = popEnd(q);
    if (cur == NULL)
        printf("The queue is empty\n");
        //printf("Очередь пустая\n");
    return cur;
}

void queueListPrint(node* q)
{
    node* cur = q;
    if (q == NULL)
        printf("The queue is empty\n");
        //printf("Очередь пустая\n");
    else
    {
        printf("current queue: \n");
        //printf("текущая очередь: \n");
        for ( ; cur; cur = cur->next)
            printf("%c\n", cur->inf);
        printf("\n");
    }
}
