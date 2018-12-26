
#ifndef TREE_HASH_H
#define TREE_HASH_H

#include"define_tree_hash.h"

typedef struct node_table node_hash;

struct node_table
{
    char *word;
    struct node_table *next;
};

int len_list(node_hash *head);
int next_prime_number(int number);
node_hash* add_end(node_hash *head, node_hash *elem);
node_hash* create_hash_node(char *word);
int calc_index(char *word, int len_table);
node_hash **insert_in_hash_table(node_hash **table, int *len_table,
                                 node_hash *node);
void print_table(node_hash **table, int len_table);
node_hash **build_table(FILE *f, int *len_table);
int check_int(int *number, int min, int max);
void check_end (char *str);
void search_in_hash_table(char *word, node_hash **table, int len_table,
                          int *done);
int search_in_file(FILE *f, char *s);

#endif //TREE_HASH_H
