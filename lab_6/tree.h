

#ifndef TREE_TREE_H
#define TREE_TREE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"define_tree_hash.h"

typedef struct tree_node node_t;
// узел дерева
struct tree_node
{
    char *word;
    int balance;
    struct tree_node *left;
    struct tree_node *right;
};

// создание нового узла
struct tree_node* create_node(char *word);

node_t* create_tree(node_t *root, FILE *f);
node_t* create_bal_tree(node_t *root, FILE *f);
void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree);
struct tree_node* bal_insert(struct tree_node *root, struct tree_node *node);
node_t* balance(node_t* p);
node_t* rotateleft(node_t* q);
node_t* rotateright(node_t* p);
void fixheight(node_t* p);
int height(node_t* p);
int bfactor(node_t* p);
//node_t * search (node_t* tree, const char* name, int *flag);
node_t *search(char *rem, node_t *tree, int *done, int *flag);

#endif //TREE_TREE_H
