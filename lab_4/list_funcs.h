#ifndef TISD4_LIST_FUNCS_H
#define TISD4_LIST_FUNCS_H

#include "structs.h"

void push(list_t** list, char elem, int *size);
char pop(list_t** list, del_mem **list_del, int *size, int *size_del);
void print_from_head_mem(const del_mem *list, int size);
void push_mem(del_mem **list, void *p);
void print_from_tail(const list_t *list);
void print_from_head(const list_t *list, int size);
void print_from_head_with_addresses(const list_t *list, int size);

#endif //TISD4_LIST_FUNCS_H
