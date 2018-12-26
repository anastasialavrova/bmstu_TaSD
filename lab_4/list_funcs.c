#include "list_funcs.h"
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

void push(list_t** list, char elem, int *size)
{
    if (MAX_SIZE_LIST > *size)
    {
        list_t* node = malloc(sizeof(list_t));
        node->symb = elem;
        node->next = *list;
        (*size)++;
        *list = node;
    }
    else
    {
        puts("Stack is overflow!");
    }
}

void push_mem(del_mem **list, void *p)
{
    del_mem *node = malloc(sizeof(list_t));
    node->p = p;
    node->next = *list;
    *list = node;
}

void print_from_head_mem(const del_mem *list, int size)
{
    if (size == 0)
    {
        puts("Stack is empty!\n");
    }
    else
    {
        if (list)
        {
            printf("%p ", list->p);
            print_from_head_mem(list->next, size);
        }
        printf("\n");
    }
}

char pop(list_t** list, del_mem **list_del, int *size, int *size_del)
{
    if (0 != *size)
    {
        list_t *temp = *list;
        push_mem(list_del, &temp->symb);
        (*size_del)++;
        char data = temp->symb;
        *list = temp->next;
        (*size)--;
        free(temp);
        return data;
    }
    else
    {
        puts("Stack is empty!\n");
        return '\0';
    }
}

void print_from_head_with_addresses(const list_t *list, int size)
{
    if (size == 0)
    {
        puts("Stack is empty!");
    }
    else
    {
        if (list)
        {
            void *p = &(list->symb);
            printf("%6c %p\n", list->symb, p);
            print_from_head_with_addresses(list->next, size);
        }
        printf("\n");
    }
}


void print_from_head(const list_t *list, int size)
{
    if (size == 0)
    {
        puts("Stack is empty!");
    }
    else
    {
        if (list)
        {
            printf("%c ", list->symb);
            print_from_head(list->next, size);
        }
        printf("\n");
    }
}

void print_from_tail(const list_t *list)
{
    if (list)
    {
        print_from_tail(list->next);
        printf("%c ", list->symb);
    }
    printf("\n");
}