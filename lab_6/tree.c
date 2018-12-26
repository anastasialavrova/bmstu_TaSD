#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include"tree.h"

void count_node_tree(node_t *tree, int *sum)
{
    if (tree == NULL)
        return;

    *sum += 1;
    count_node_tree(tree->left, sum);
    count_node_tree(tree->right, sum);
}

// обход дерева
void apply_pre(struct tree_node *tree, void (*f)(struct tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

// визуализация и печать дерева
void to_dot(struct tree_node *tree, void *param)
{
    FILE *f = param;
    if (tree->left)
        fprintf(f, "\"%s \" -> \"%s \";\n", tree->word, tree->left->word);

    if (tree->right)
        fprintf(f, "\"%s \" -> \"%s \";\n", tree->word, tree->right->word);

}

// трансляция на язык дот
void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    apply_pre(tree, to_dot, f);
    fprintf(f, "}\n");
}


// вставка нового узла в обычном дереве
struct tree_node* insert(struct tree_node *tree, struct tree_node *node)
{
    int cmp;

    if (tree == NULL)
        return node;

    cmp = strcmp(node->word, tree->word);
    if (cmp < 0)
    {
        tree->left = insert(tree->left, node);
    }
    else if (cmp > 0)
    {
        tree->right = insert(tree->right, node);
    }

    return tree;
}

// проверка строки на \n
void check_end (char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n')
            str[i] = '\0';
}

// создание нового дерева
node_t* create_tree(node_t *root, FILE *f)
{
    node_t *node;
    char *word = malloc((SIZE_WORD+1)*sizeof(char));
    while(!feof(f))
    {
        fgets(word, SIZE_WORD, f);
        check_end(word);

        node = create_node(word);
        root = insert(root, node);
    }
    return root;
}

// рассчет высоты узла
int height(node_t* p)
{
    return p ? p->balance : 0;
}

// новый узел в сбалансированном дереве
node_t* create_bal_tree(node_t *root, FILE *f)
{
    node_t *node;
    char *word = malloc((SIZE_WORD+1)*sizeof(char));
    while(!feof(f))
    {
        fgets(word, SIZE_WORD, f);
        check_end(word);

        node = create_node(word);
        root = bal_insert(root, node);
    }
    return root;
}

// проверка узла на сбалансированность
int bfactor(node_t* p)
{
    if (height(p->right) == 1 && !p->left)
        return 2;
    else if (height(p->left) == 1 && !p->right)
        return -2;
    else
        return height(p->right)-height(p->left);
}

// балансировка дерева
node_t* balance(node_t* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p) == 2 )
    {
        if(bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p) == -2 )
    {
        if (bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}


// вставка узла в сбалансированное дерево
struct tree_node* bal_insert(struct tree_node *root, struct tree_node *node)
{
    int cmp;

    if (root == NULL)
    {
        return node;
    }
    cmp = strcmp(node->word, root->word);
    if (cmp < 0)
    {
        root->left = bal_insert(root->left, node);
        root = balance(root);
    }
    else if (cmp > 0)
    {
        root->right = bal_insert(root->right, node);
        root = balance(root);
    }
    root = balance(root);
    return root;
}

// пересчет высоты узла после балансировки
void fixheight(node_t* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->balance = (hl>hr?hl:hr)+1;
}

// правый поворот
node_t* rotateright(node_t* p)
{
    node_t* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}


// левый поворот
node_t* rotateleft(node_t* q)
{
    node_t* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

struct tree_node* create_node(char *word)
{
    struct tree_node *node;
    node = malloc(sizeof(struct tree_node));
    char *new_word = malloc((SIZE_WORD + 1)*sizeof(char));
    for(int i = 0; word[i]; i++)
        new_word[i] = word[i];
    new_word[strlen(word)] = '\0';
    if (node)
    {
        node->word = new_word;
        node->balance = 0;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

node_t *search(char *rem, node_t *tree, int *done, int *flag)
{
    int cmp;

    if (tree == NULL)
        return tree;

    cmp = strcmp(rem, tree->word);
    if (!cmp)
    {
        *flag = 1;
        (*done)++;
        return tree;
    }
    else if (cmp < 0)
    {
        if (!*flag)
            (*done)++;
        tree->left = search(rem, tree->left, done, flag);
    }
    else if (cmp > 0)
    {
        if (!flag)
            (*done)++;
        tree->right = search(rem, tree->right, done, flag);
    }
    return tree;
}






