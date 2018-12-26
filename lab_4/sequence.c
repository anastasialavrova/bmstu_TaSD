#include "sequence.h"
#include "structs.h"
#include "list_funcs.h"
#include "arr_funcs.h"
#include <stdio.h>
#include <malloc.h>

int sequence(list_t *list, del_mem *list_del, int size, int size_del, char string[])
{
    if (size == 0)
    {
        puts("Stack is empty!");
    }
    else
    {
        char dop[300];
        int i = 0, flag = 1, size1 = size;
        int gop = 0, g = 0;
        print_from_head(list, size);
        char *word = calloc(size + 1, sizeof(char));
        while (size1)
        {
            arr_pop(&string, size1);
            size1--;
        }
        while (list)
        {
            char x = pop(&list, &list_del, &size, &size_del);
            if (x == '(' || x == '{' || x == '[') {
                dop[gop] = x;
                gop++;
            }

            if (x == ')' || x == '}' || x == ']')
            {
                if (gop == 0)
                {
                    printf("NO");
                    gop = -1;
                    g--;
                    break;
                }
                if (dop[gop - 1] == '(' && x != ')')
                {
                    printf("NO");
                    gop = -1;
                    g--;
                    break;
                }
                if (dop[gop - 1] == '[' && x != ']')
                {
                    printf("NO");
                    gop = -1;
                    g--;
                    break;
                }
                if (dop[gop - 1] == '{' && x != '}')
                {
                    printf("NO");
                    gop = -1;
                    g--;
                    break;
                }
                else
                {
                    gop--;
                }
            }
            i++;
        }
        if (gop == 0)
        {
            printf("OK");
        }
        else
        {
            if (g == 0)
                printf("NO");
        }
    }
    return 0;
}