#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *generateDynArray(int n)
{
    srand(time(NULL));
    int *a = (int *)malloc(n * sizeof(int));
    if (a == NULL)
    {
        perror("malloc");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() % 199 - 99;
        }
    }
    return a;
}

void printArray(int *a, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        if (i % 10 == 0 && i != 0)
        {
            printf("\n ");
        }
        printf("%3d", a[i]);
        if (i != n - 1)
        {
            printf(", ");
        }
    }
    printf(" ]\n");
}

void separator()
{
    printf("\n===============================================================\n\n");
}
