#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include"hash.h"


int len_list(node_hash *head)
{
    int len = 0;
    for ( ; head; head = head->next)
        len++;
    return len;
}

int next_prime_number(int number)
{
    while (1)
    {
        int count_del = 0;
        number++;
        for(int i = 2; i < number - 1; i++)
            if (!(number%i))
                count_del++;

        if (!count_del)
            return number;
    }
}
node_hash* add_end(node_hash *head, node_hash *elem)
{
    node_hash *cur = head;
    if (!head)
        return elem;
    for ( ; cur->next; cur = cur->next)
    {
        int cmp = strcmp(cur->word, elem->word);
        if (!cmp)
            return head;
    }

    int cmp = strcmp(cur->word, elem->word);
    if (!cmp)
    {
        return head;
    }
    cur->next = elem;
    return head;
}

node_hash* create_hash_node(char *word)
{
    node_hash *node;

    node = malloc(sizeof(node_hash));
    char *new_word = malloc((SIZE_WORD + 1)*sizeof(char));

    if (node && new_word)
    {
        for(int i = 0; word[i]; i++)
            new_word[i] = word[i];
        new_word[strlen(word)] = '\0';

        node->word = new_word;
        node->next = NULL;
    }

    return node;
}

int calc_index(char *word, int len_table)
{
    int len = strlen(word);
    unsigned long long sum = 0;
    for(int i = len - 1; i > -1; i--)
    {
        sum += (word[i] - OFFSET);
    }
    return sum%len_table;
}

node_hash **insert_in_hash_table(node_hash **table, int *len_table,
                                 node_hash *node)
{
    int new_len;
    node_hash **new_table;
    int index = calc_index(node->word, *len_table);
    table[index] = add_end(table[index], node);
    int len = len_list(table[index]);

    while(len > MAX_LEN_LIST)
    {
        new_len = next_prime_number(*len_table);
        new_table = calloc(new_len, sizeof(node_hash*));

        char *word = malloc((SIZE_WORD+1)*sizeof(char));
        for (int i = 0; i < *len_table; i++)
        {
            for (node_hash *j = table[i]; j; j = j->next)
            {
                word = strcpy(word, j->word);
                node = create_hash_node(word);
                index = calc_index(node->word, new_len);
                new_table[index] = add_end(new_table[index], node);
            }
        }

        len = 0;
        for (int i = 0; i < new_len; i++)
            if (len_list(new_table[i]) > len)
                len = len_list(new_table[i]);

        free(table);
        *len_table = new_len;
        table = new_table;
    }

    return table;
}

void print_table(node_hash **table, int len_table)
{
    for (int i = 0; i < len_table; i++)
    {
        printf("%d ", i);
        node_hash *cur= table[i];
        for ( ; cur; cur = cur->next)
        {
            printf (" -> %s", cur->word);
        }
        if (!cur)
            printf(" -> NULL\n");
    }
    printf("\n");
}




node_hash **build_table(FILE *f, int *len_table)
{
    node_hash **table = NULL;
    int error = SUCCESS;

    if (!error)
    {
        node_hash *node;
        table = calloc(*len_table, sizeof(node_hash*));

        char *word = malloc((SIZE_WORD+1)*sizeof(char));
        while(!feof(f))
        {
            fgets(word, SIZE_WORD, f);
            check_end(word);

            node = create_hash_node(word);
            table = insert_in_hash_table(table, len_table, node);
        }
    }


    return table;
}

int check_int(int *number, int min, int max)
{
    int rc, num, error;
    char tmp;
    rc = scanf("%d%c", &num, &tmp);
    if (rc == 2 && (tmp == '\n' || tmp == ' '))
    {
        if ((num > min) && (num < max))
        {
            *number = num;
            error = SUCCESS;
        }
        else
            error = ERROR_VALUE;

        if (!min && !max && error == ERROR_VALUE)
        {
            *number = num;
            error = SUCCESS;
        }
        return error;
    }
    else if (tmp != '\n')
    {
        while(tmp != '\n')
            scanf("%c", &tmp);
        return ERROR_INPUT;
    }
    else
        return ERROR_INPUT;

    return SUCCESS;
}

void search_in_hash_table(char *word, node_hash **table, int len_table,
                          int *done)
{
    int index = calc_index(word, len_table);
    node_hash *cur = table[index];

    int cmp = strcmp(cur->word, word);
    if (!cmp)
    {
        *done = 1;
        return;
    }
    *done = 0;
    node_hash *prev = cur;
    for( ; cur; cur = cur->next)
    {
        (*done)++;
        int cmp = strcmp(cur->word, word);
        if (!cmp)
        {
            *done = 1;
            return;
        }
        prev = cur;
    }
    *done = 0;
}

int search_in_file(FILE *f, char *s)
{
    rewind(f);
    int flag = 0;
    char *word = malloc((SIZE_WORD+1)*sizeof(char));
    while(!feof(f))
    {
        fgets(word, SIZE_WORD, f);
        check_end(word);
        if (!strcmp(s, word))
        {
            return 1;
        }
    }
    return 0;
}



