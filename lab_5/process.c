#include "process.h"
#include "list.h"

void workArray(int n, int interval, interval_time t1, interval_time t2, interval_time t3, interval_time t4, int flag)
{
    char* que1;
    queue d1;
    //strcpy(d1.name, "(1-ая очередь)");
    strcpy(d1.name, "(First queue)");
    d1.size = sizeof(char);
    d1.max_num = MAX_QUEUE;
    que1 = (char *)malloc(d1.max_num * sizeof(char));
    d1.low = que1;
    d1.up = que1 + d1.max_num;
    d1.pin = que1;
    d1.pout = que1;
    for (int i = 0; i < d1.max_num; i++)
        que1[i] = '\0';
    d1.count_req = 0;
    d1.sum_size = 0;
    d1.tmp_size = 0;
    d1.sum_time = 0;
    d1.out_req = 0;
    d1.in_req = 0;

    char* que2;
    queue d2;
    //strcpy(d2.name, "(2-ая очередь)");
    strcpy(d2.name, "(Second queue)");
    d2.size = sizeof(char);
    d2.max_num = MAX_QUEUE;
    que2 = (char*)malloc(d2.max_num * sizeof(char));
    d2.low = que2;
    d2.up = que2 + d2.max_num;
    d2.pin = que2;
    d2.pout = que2;
    for (int i = 0; i < d2.max_num; i++)
        que2[i] = '\0';
    d2.count_req = 0;
    d2.sum_size = 0;
    d2.tmp_size = 0;
    d2.sum_time = 0;
    d2.out_req = 0;
    d2.in_req = 0;

    double time = 0.0;
    int type = 0;
    double tr1 = 0., tr2= 0., tr_obr = 0.;
    int req_in1 = 0, req_in2 = 0, req_out1 = 0, req_out2 = 0;
    int req_show = 0;

    double total_time_out1 = 0;
    double total_time_out2 = 0;
    time_t rtime1 = clock();

    int out_of_second = 0;
    while(req_out1 < n)
    {
        if((d1.pin == d1.pout && *((char*)d1.pin) != '\0') || (d2.pin == d2.pout && *((char*)d2.pin) != '\0'))
        {
            printf("The queue is full\n");
            //printf("Очередь заполнена\n");
            break;
        }

        if (tr1 == 0.)
            tr1 = getTime(t1);

        if (tr2 == 0.)
            tr2 = getTime(t2);

        if(tr_obr == 0.)
        {
            if (!(d1.pin == d1.pout && *((char*)d1.pin) == '\0'))
            {
                tr_obr = getTime(t3);
                type = 1;
                queueArrayPop(&d1, que1);
                d1.tmp_size--;
                d1.sum_size += d1.tmp_size;
                d1.count_req++;
                d1.out_req++;
                total_time_out1 += tr_obr;
            }

            else if(!(d2.pin == d2.pout && *((char*)d2.pin) == '\0'))
            {
                tr_obr = getTime(t4);
                type = 2;
                queueArrayPop(&d2, que2);
                d2.tmp_size--;
                d2.sum_size += d2.tmp_size;
                d2.count_req++;
                d2.out_req++;
                total_time_out2 += tr_obr;
            }
        }

        else
        {
            if (type == 2 && !(d1.pin == d1.pout && *((char*)d1.pin) == '\0'))
            {
                queueArrayPush(&d2, que2, '2');

                d2.tmp_size++;
                d2.sum_size += d2.tmp_size;
                d2.count_req++;
                d2.in_req++;
                total_time_out2 -= tr_obr;
                tr_obr = 0.;
                out_of_second++;
                continue;
            }
        }

        double tmin = 0.;

        if(tr_obr == 0.)
            tmin = fmin(tr1, tr2);

        else
            tmin = fmin(tr1, fmin(tr2, tr_obr));

        if(tmin == tr_obr )
        {
            tr_obr = 0.;
            if(type == 1)
                req_out1++;

            if(type == 2)
                req_out2++;

        }
        if (req_out1 == n)
            break;

        if(tmin == tr1)
        {
            queueArrayPush(&d1, que1, '1');
            d1.tmp_size++;
            d1.sum_size += d1.tmp_size;
            d1.count_req++;
            d1.in_req++;
            req_in1++;
        }

        if (tmin == tr2)
        {
            queueArrayPush(&d2, que2, '2');
            d2.tmp_size++;
            d2.sum_size += d2.tmp_size;
            d2.count_req++;
            d2.in_req++;
            req_in2++;
        }

        tr1 -= tmin;
        tr2 -= tmin;

        if(tr_obr >= tmin)
            tr_obr -= tmin;
        time += tmin;

        if(req_out1 % interval == 0 && req_out1 != req_show)
        {
            req_show = req_out1;
            //printf("Обработано заявок 1-го типа: %d\n", req_out1);;
            printf("Type 1 applications processed: %d\n", req_out1);
            showLen(&d1);
            showLen(&d2);
            printf("\n");
        }
    }

    time_t rtime2 = clock();
    int real_time = rtime2 - rtime1;
    //printf("Общее время моделирования: %f е.в.\n", time);
    //printf("Число вошедших и вышедших (1 тип): %d %d\n", req_in1, req_out1);
    //printf("Число вошедших и вышедших (2 тип): %d %d\n", req_in2, req_out2);
    //printf("'Выброшено' заявок 2-го типа: %d\n", out_of_second);
    //printf("Время: %d мкс\n\n", real_time);
    printf("Total simulation time: %f time units\n", time);
    printf("Number of elements entered and left (1 type): %d %d\n", req_in1, req_out1);
    printf("Number of elements entered and left (2 type): %d %d\n", req_in2, req_out2);
    printf("Type 2 applications 'thrown away': %d\n", out_of_second);
    printf("Time: %d microseconds\n\n", real_time);

    double av_t_in1 = (t1.min + t1.max) / 2;
    double av_t_out1 = (t3.min + t3.max) / 2;
    double av_t_in2 = (t2.min + t2.max) / 2;

    double total_t_in1 = n * av_t_in1;
    double total_t_out1 = n * av_t_out1;

    double t_modelling = fmax(total_t_in1, total_t_out1);

    double wait_count_in1 = time / av_t_in1;
    double wait_count_in2 = time / av_t_in2;

    //printf("Среднее время обработки заявки 1-го типа: %lf\n", av_t_in1);
    //printf("Среднее время обработки заявки 2-го типа: %lf\n", av_t_in2);

    if (wait_count_in1 > 0)
    {
        double pogr_in1 = fabs(100 * (req_in1 - wait_count_in1) / wait_count_in1);
        //printf("Погрешность ввода (1-ая очередь): %lf", pogr_in1);
        printf("Input error (1st queue): %lf", pogr_in1);
        printf("%c", '%');
        printf("\n");
    }
    else
        printf("waiting count_in1: 0\n");
        //printf("Ожидание count_in1: 0\n");

    if (wait_count_in2 > 0)
    {
        double pogr_in2 = fabs(100 * (req_in2 - wait_count_in2) / wait_count_in2);
        //printf("Погрешность ввода (2-ая очередь): %lf", pogr_in2);
        printf("Input error (2st queue): %lf", pogr_in2);
        printf("%c", '%');
        printf("\n");
    }
    else
        printf("waiting count_in2: 0\n");
        //printf("Ожидание count_in2: 0\n");

    double total_working = total_time_out1 + total_time_out2;

    double downtime = fabs(time - total_working);
    printf("The time when OA did not work: %lf time units\n", downtime);
    //printf("Время, когда ОА не работал: %lf е.в.\n", downtime);

    if (t_modelling > 0)
    {
        double pogr_out = fabs(100 * (time - t_modelling)/t_modelling);
        printf("Output error: %lf", pogr_out);
        //printf("Погрешность вывода: %lf", pogr_out);
        printf("%c", '%');
        printf("\n\n");
    }
    else
        printf("Simulation time: 0\n");
        //printf("Время моделирования: 0\n");

    free(que1);
    free(que2);
}

void workList(int n, int interval, interval_time t1, interval_time t2, interval_time t3, interval_time t4, int flag)
{
    node* ret;
    node* freed_memory[MAX_QUEUE];
    int count_freed = 0;
    node* used_memory[MAX_QUEUE];
    int count_used = 0;
    int second_used = 0;

    node* que1 = NULL;
    queue d1;
    //strcpy(d1.name, "(1-ая очередь)");
    strcpy(d1.name, "(First queue)");
    d1.size = sizeof(node*);
    d1.max_num = MAX_QUEUE;
    d1.pin = NULL;
    d1.pout = NULL;
    d1.count_req = 0;
    d1.sum_size = 0;
    d1.tmp_size = 0;
    d1.sum_time = 0;
    d1.out_req = 0;
    d1.in_req = 0;

    node* que2 = NULL;
    queue d2;
    //strcpy(d2.name, "(2-ая очередь)");
    strcpy(d2.name, "(Second queue)");
    d2.size = sizeof(node*);
    d2.max_num = MAX_QUEUE;
    d2.pin = NULL;
    d2.pout = NULL;
    d2.count_req = 0;
    d2.sum_size = 0;
    d2.tmp_size = 0;
    d2.sum_time = 0;
    d2.out_req = 0;
    d2.in_req = 0;

    double time = 0.0;
    int type = 0;
    double tr1 = 0., tr2 = 0., tr_obr = 0.;
    int req_in1 = 0, req_in2 = 0, req_out1 = 0, req_out2 = 0;
    int req_show = 0;

    double total_time_out1 = 0;
    double total_time_out2 = 0;
    time_t rtime1 = clock();

    int out_of_second = 0;
    while(req_out1 < n)
    {
        if(d1.tmp_size >= MAX_QUEUE || d2.tmp_size >= MAX_QUEUE)
        {
            printf("The queue is full\n");
            //printf("Очередь заполнена\n");
            break;
        }

        if (tr1 == 0.)
            tr1 = getTime(t1);

        if (tr2 == 0.)
            tr2 = getTime(t2);

        if(tr_obr == 0.)
        {
            if (que1 != NULL)
            {
                tr_obr = getTime(t3);
                type = 1;
                ret = queueListPop(&que1);
                if (ret != NULL)
                {
                    freed_memory[count_freed++] = ret;
                    free(ret);
                }
                d1.tmp_size--;
                d1.sum_size += d1.tmp_size;
                d1.count_req++;
                d1.out_req++;
                total_time_out1 += tr_obr;
            }
            else if(que2 != NULL)
            {
                tr_obr = getTime(t4);
                type = 2;
                ret = queueListPop(&que2);
                if (ret != NULL)
                {
                    freed_memory[count_freed++] = ret;
                    free(ret);
                }
                d2.tmp_size--;
                d2.sum_size += d2.tmp_size;
                d2.count_req++;
                d2.out_req++;
                total_time_out2 += tr_obr;
            }
        }

        else
        {
            if (type == 2 && que1 != NULL)
            {
                que2 = queueListPush(que2, '2', used_memory, &count_used, freed_memory, &count_freed, &second_used);

                d2.tmp_size++;
                d2.sum_size += d2.tmp_size;
                d2.count_req++;
                d2.in_req++;
                total_time_out2 -= tr_obr;
                tr_obr = 0.;
                out_of_second++;

                continue;
            }
        }

        double tmin = 0.;

        if(tr_obr == 0.)
            tmin = fmin(tr1, tr2);

        else
            tmin = fmin(tr1, fmin(tr2, tr_obr));

        if(tmin == tr_obr )
        {
            tr_obr = 0.;
            if(type == 1)
                req_out1++;

            if(type == 2)
                req_out2++;

        }
        if (req_out1 == n)
            break;

        if(tmin == tr1)
        {
            que1 = queueListPush(que1, '1', used_memory, &count_used, freed_memory, &count_freed, &second_used);

            d1.tmp_size++;
            d1.sum_size += d1.tmp_size;
            d1.count_req++;
            d1.in_req++;

            req_in1++;
        }

        if (tmin == tr2)
        {
            que2 = queueListPush(que2, '2', used_memory, &count_used, freed_memory, &count_freed, &second_used);

            d2.tmp_size++;
            d2.sum_size += d2.tmp_size;
            d2.count_req++;
            d2.in_req++;
            req_in2++;
        }

        tr1 -= tmin;
        tr2 -= tmin;


        if(tr_obr >= tmin)
            tr_obr -= tmin;
        time += tmin;
        if(req_out1 % interval == 0 && req_out1 != req_show)
        {
            req_show = req_out1;
            printf("Type 1 applications processed: %d\n", req_out1);;
            //printf("Обработано заявок 1-го типа: %d\n", req_out1);;
            showLen(&d1);
            showLen(&d2);
            //printf("Среднее время обработки заявки 1-го типа: 3.000000\n");
            //printf("Среднее время обработки заявки 2-го типа: 1.500000\n");
            printf("\n");
        }
    }

    time_t rtime2 = clock();
    int real_time = rtime2 - rtime1;
    //printf("Общее время моделирования: %f е.в.\n", time);
    //printf("Число вошедших и вышедших (1 тип): %d %d\n", req_in1, req_out1);
    //printf("Число вошедших и вышедших (2 тип): %d %d\n", req_in2, req_out2);
    //printf("'Выброшено' заявок 2-го типа: %d\n", out_of_second);
    //printf("Время: %d мкс\n\n", real_time);
    printf("Total simulation time: %f time units\n", time);
    printf("Number of elements entered and left (1 type): %d %d\n", req_in1, req_out1);
    printf("Number of elements entered and left (2 type): %d %d\n", req_in2, req_out2);
    printf("Type 2 applications 'thrown away': %d\n", out_of_second);
    printf("Time: %d microseconds\n\n", real_time);

    double av_t_in1 = (t1.min + t1.max) / 2;
    double av_t_out1 = (t3.min + t3.max) / 2;
    double av_t_in2 = (t2.min + t2.max) / 2;

    double total_t_in1 = n * av_t_in1;
    double total_t_out1 = n * av_t_out1;

    double t_modelling = fmax(total_t_in1, total_t_out1);

    double wait_count_in1 = time / av_t_in1;
    double wait_count_in2 = time / av_t_in2;

    if (wait_count_in1 > 0)
    {
        double pogr_in1 = fabs(100 * (req_in1 - wait_count_in1) / wait_count_in1);
        printf("Input error (1st queue): %lf", pogr_in1);
        //printf("Погрешность ввода (1-ая очередь): %lf", pogr_in1);
        printf("%c", '%');
        printf("\n");
    }
    else
        printf("Waiting count_in1: 0\n");
        //printf("Ожидание count_in1: 0\n");

    if (wait_count_in2 > 0)
    {
        double pogr_in2 = fabs(100 * (req_in2 - wait_count_in2) / wait_count_in2);
        printf("Input error (2st queue): %lf", pogr_in2);
        //printf("Погрешность ввода (2-ая очередь): %lf", pogr_in2);
        printf("%c", '%');
        printf("\n");
    }
    else
        printf("Waiting count_in2: 0\n");
        //printf("Ожидание count_in2: 0\n");

    double total_working = total_time_out1 + total_time_out2;

    double downtime = fabs(time - total_working);

    printf("The time when OA did not work: %lf time units\n", downtime);
    //printf("Время, когда ОА не работал: %lf е.в.\n", downtime);

    if (t_modelling > 0)
    {
        double pogr_out = fabs(100 * (time - t_modelling) / t_modelling);
        printf("Output error: %lf", pogr_out);
        //printf("Погрешность вывода: %lf", pogr_out);
        printf("%c", '%');
        printf("\n\n\n");
    }
    else
        printf("Expected simulation time: 0\n");
        //printf("Ожидаемое время моделирования: 0\n");

    if(flag == 1)
    {
        //printf("Число повторно использованных адресов после освобождения памяти: %d\n", second_used);
        //printf("Число неиспользованных адресов после освобождения памяти: %d\n", count_freed);
        //printf("Неиспользованные адреса:\n");
        printf("Number of reused addresses after freeing memory: %d\n", second_used);
        printf("Number of unused addresses after freeing memory: %d\n", count_freed);
        printf("Unused addresses:\n");
        for (int i = 0; i < fmin(30, count_freed); i++)
            printf("%p\n", (void *)freed_memory[i]);
    }

    freeAll(que1);
    freeAll(que2);
}
