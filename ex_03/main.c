#include <stdio.h>
#include <stdlib.h>

int search(int arr[], int in, int fim, int x)
{
    if (fim >= in)
    {
        int mid = (fim + in) / 2;

        if (x > arr[mid] && x <= arr[mid + 1])
        {
            return mid + 1;
        }
        if (arr[mid] > x)
        {
            if (mid == 0)
            {
                return 0;
            }
            else
            {
                return search(arr, in, mid - 1, x);
            }
        }
        return search(arr, mid + 1, fim, x);
    }
    return -1;
}

int insertion_sort(int vetor[], int N, int nivel_rec, int i)
{
    if (nivel_rec == 0)
    {
        return 0;
    }

    int chave = N - nivel_rec;
    int indice = search(vetor, 0, chave - 1, vetor[chave]);

    printf("%i %i %i\n", nivel_rec, vetor[chave], indice);

    int ultimo = vetor[i];
    int j = i;

    while (j > 0 && vetor[j - 1] > ultimo)
    {
        vetor[j] = vetor[j - 1];
        j--;
    }
    vetor[j] = ultimo;

    if (i + 1 <= N)
    {
        insertion_sort(vetor, N, nivel_rec - 1, i+1);
    }
}

int main(void)
{
    int N, i, *vetor;
    //   printf("Insira o valor N: ");
    scanf("%i", &N);
    vetor = (int *)malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
    {
        scanf("%i", &vetor[i]);
    }

    insertion_sort(vetor, N, N - 1, 1);
    for (i = 0; i < N; ++i)
    {
        printf("%d ", vetor[i]);
    }
    return 0;
}

