#ifndef TISD4_STRUCTS_H
#define TISD4_STRUCTS_H
#define MAX_SIZE_VEC 1000000
#define MAX_SIZE_LIST 1000000

//#define MAX_SIZE_VEC 5
//#define MAX_SIZE_LIST 5


typedef struct single_linked_list
{
    char symb;
    struct single_linked_list *next;
}list_t;

typedef struct deleted_memory
{
    void *p;
    struct deleted_memory *next;
}del_mem;

#endif //TISD4_STRUCTS_H
