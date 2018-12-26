#include <stdio.h>
#include "scanf.h"
#include <stdlib.h>
#include "list_funcs.h"
#include "arr_funcs.h"
#include <string.h>
#include "efficience.h"
#include"sequence.h"


int main()
{
    int flag = 0, choise = 0, type = 0, g1 = 0, g2 = 0;
    list_t *list = NULL;
    del_mem *list_del = NULL;
    char *arr = calloc(MAX_SIZE_VEC, sizeof(char));
    int size = 0, size_del = 0;
    char elem = ' ';
    printf("1) Вектор\n"
           "2) Односвязный список\n");
    while (type < 1 || type > 2)
    {
        puts("Введите пункт: \n");
        scan_int(&type);
    }
    while (flag == 0)
    {
        if (type == 1)
        {
            printf("\nМеню:\n"
                   "1) Вывести стек на экран\n"
                   "2) Добавить в стек элемент\n"
                   "3) Удалить элемент из стека\n"
                   "4) Определить, является ли строка правильной скобочной последовательностью\n"
                   "5) Эффективность\n"
                   "6) Выход\n"
                   "Введите пункт:  ");
            while (choise < 1 || choise > 6)
            {
                //puts("Введите число от 1 до 8\n");
                scan_int(&choise);
                if (choise < 1 || choise > 6)
                {
                    puts("Некорректный параметр!\n");
                    puts("Введите пункт:  ");
                }
            }
            switch (choise)
            {
                case 1:
                    if (g1 == 0)
                        print_arr(arr, size);
                    else
                        printf("Stack is empty!\n");
                    choise = 0;
                    break;
                case 2:
                    printf("Введите элемент: ");
                    printf("%c", elem);
                    int err = 1;
                    g1 = 0;
                    while (err)
                    {
                        //scan_char(&elem);
                        scanf("%c", &elem);
                        if (elem == '[' || elem == '{' || elem == '(' || elem == ')' || elem == '}' || elem == ']')
                        {
                            err=0;
                            //puts("Некорректный параметр!\n");
                            //puts("Введите элемент:  ");
                        }
                        else
                        {
                            puts("Некорректный параметр!\n");
                            puts("Введите элемент:  ");
                        }
                        //scanf("%c", &elem);
                    }
                    arr_push(&arr, elem, size);
                    push(&list, elem, &size);
                    choise = 0;
                    break;
                case 3:
                    arr_pop(&arr, size);
                    pop(&list, &list_del, &size, &size_del);
                    choise = 0;
                    break;
                case 4:
                    size = sequence(list, list_del, size, size_del, arr);
                    size_del = size;
                    //flag = 1;
                    choise = 0;
                    break;
                case 5:
                    efficience();
                    choise = 0;
                    break;
                case 6:
                    choise = 0;
                    break;
                default:
                    break;
            }
        }

        if (type == 2)
        {
            printf("\nМеню:\n"
                   "1) Вывести стек на экран\n"
                   "2) Добавить элемент в стек\n"
                   "3) Удалить элемент из стека\n"
                   "4) Показать освобожденные адреса\n"
                   "5) показать текущее состояние стека с адресами\n"
                   "6) Определить, является ли строка правильной скобочной последовательностью\n"
                   "7) Эффективность\n"
                   "8) Выход\n"
                   "Введите пункт:  ");
            while (choise < 1 || choise > 8)
            {
                //puts("Введите число от 1 до 8\n");
                scan_int(&choise);
                if (choise < 1 || choise > 8)
                {
                    puts("Некорректный параметр!\n");
                    puts("Введите пункт:  ");
                }
            }
            switch (choise)
            {
                case 1:
                    if (g2 == 0)
                        print_from_head(list, size);
                    else
                        printf("Stack is empty!\n");
                    choise = 0;
                    break;
                case 2:
                    printf("Введите элемент стека: ");
                    int err = 1;
                    g2 = 0;
                    while (err)
                    {
                        //scan_char(&elem);
                        scanf("%c", &elem);
                        if (elem == '[' || elem == '{' || elem == '(' || elem == ')' || elem == '}' || elem == ']')
                        {
                            err=0;
                            //puts("Некорректный параметр!\n");
                            //puts("Введите элемент:  ");
                        }
                        else
                        {
                            puts("Некорректный параметр!\n");
                            puts("Введите элемент:  ");
                        }
                        //scanf("%c", &elem);
                    }
                    arr_push(&arr, elem, size);
                    push(&list, elem, &size);
                    choise = 0;
                    break;
                case 3:
                    arr_pop(&arr, size);
                    pop(&list, &list_del, &size, &size_del);
                    choise = 0;
                    break;
                case 4:
                    print_from_head_mem(list_del, size_del);
                    choise = 0;
                    break;
                case 5:
                    print_from_head_with_addresses(list, size);
                    choise = 0;
                    break;
                case 6:
                    size = sequence(list, list_del, size, size_del, arr);
                    size_del = size;
                    //flag = 1;
                    choise = 0;
                    break;
                case 7:
                    efficience();
                    choise = 0;
                    break;
                case 8:
                    flag = 1;
                    choise = 0;
                    break;
                default:
                    break;
            }
        }
    }
    free(arr);
    return 0;
}
