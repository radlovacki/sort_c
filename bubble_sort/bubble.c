#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *generisi_niz(int n)
{
    int *niz = (int *)malloc(n * sizeof(int));
    if (niz == NULL)
    {
        fprintf(stderr, "Greska: neuspela alokacija memorije!\n");
        exit(EXIT_FAILURE);
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
        niz[i] = rand() % 100 + 1;
    return niz;
}

void ispisi_niz(int *niz, int n)
{
    printf("[ ");
    for (int i = 0; i < n; i++)
    {
        printf("%d", niz[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf(" ]\n");
}

void bubble_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp   = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main(void)
{
    int n;
    printf("Unesite broj elemenata niza: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Greska: broj elemenata mora biti pozitivan ceo broj.\n");
        return EXIT_FAILURE;
    }
    int *niz = generisi_niz(n);
    printf("\nNasumicno generisan niz (%d elemenata):\n", n);
    ispisi_niz(niz, n);
    bubble_sort(niz, n);
    printf("\nNiz nakon sortiranja izborom (Selection Sort):\n");
    ispisi_niz(niz, n);
    free(niz);
    niz = NULL;
    return 0;
}
