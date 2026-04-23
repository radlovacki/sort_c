#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EL_SPAN 1999

int countDigits(int number, int negatives)
{
    if (number == 0)
        return 1 + negatives;
    int digits = negatives;
    number = abs(number);
    while (number > 0)
    {
        digits++;
        number /= 10;
    }
    return digits;
}

void printArray(int a[], int n)
{
    int digits = countDigits((int)EL_SPAN / 2, 1);
    int i = 0;
    printf("[");
    for (i = 0; i < n; i++)
    {
        if (i % 10 == 0 && i != 0)
        {
            printf("\n ");
        }
        printf("%*d ", digits, a[i]);
    }
    printf("]\n");
}

void randArray(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i] = rand() % EL_SPAN - (int)EL_SPAN / 2;
    }
}

int test_array(int a[], int n)
{
    if (n <= 1)
        return 1;

    int direction = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] < a[i + 1])
        {
            direction = 1;
            break;
        }
        else if (a[i] > a[i + 1])
        {
            direction = -1;
            break;
        }
    }

    if (direction == 0)
        return 1;

    for (int i = 0; i < n - 1; i++)
    {
        if (direction == 1 && a[i] > a[i + 1])
            return 0;
        if (direction == -1 && a[i] < a[i + 1])
            return 0;
    }

    return 1;
}

int test_sort(void (*f)(int[], int), int n, int iters)
{
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr)
    {
        perror("malloc");
        return 1;
    }
    int digits = countDigits(iters, 0);
    for (int i = 0; i < iters; i++)
    {
        randArray(arr, n);
        printf("[ITER %*d/%d]", digits, i + 1, iters);
        f(arr, n);
        if (test_array(arr, n))
        {
            printf("\033[1;32m\t SUCCEEDED \033[0m\n");
        }
        else
        {
            printf("\033[1;31m\t FAILED\033[0m\n");
            printArray(arr, n);
            free(arr);
            printf("Aborting upcoming tests...\n");
            return 2;
        }
    }
    free(arr);
    return 0;
}

int test_multiple_sorts(void (*f[])(int[], int), const char *names[], int sort_cnt, int start_n, int max_n, int iters)
{
    int *arr = (int *)malloc(max_n * sizeof(int));
    double *times = (double *)malloc(sort_cnt * iters * sizeof(double));

    if (!arr || !times)
    {
        perror("malloc");
        free(arr);
        free(times);
        return 1;
    }

    clock_t start_t, end_t;

    for (int el = start_n; el <= max_n; el *= 10)
    {
        int *temp_arr = (int *)malloc(el * sizeof(int));
        if (!temp_arr)
        {
            perror("malloc temp_arr");
            break;
        }

        printf("Benchmarking %d elements...\n", el);

        for (int i = 0; i < iters; i++)
        {
            randArray(arr, el);

            for (int j = 0; j < sort_cnt; j++)
            {
                printf("\r [%d/%d] Testing: %s... \033[K",
                       i + 1, iters, names[j]);
                fflush(stdout);

                for (int k = 0; k < el; k++)
                    temp_arr[k] = arr[k];

                start_t = clock();
                f[j](temp_arr, el);
                end_t = clock();

                times[j * iters + i] = (double)(end_t - start_t) / CLOCKS_PER_SEC;
            }
        }

        printf("\r\033[K");

        printf("Average result for %d elements (%d iterations):\n", el, iters);
        for (int j = 0; j < sort_cnt; j++)
        {
            double total_time = 0;
            for (int i = 0; i < iters; i++)
            {
                total_time += times[j * iters + i];
            }
            printf("  [%s] %lf seconds\n", names[j], total_time / iters);
        }
        printf("\n");
        free(temp_arr);
    }

    free(arr);
    free(times);
    return 0;
}
