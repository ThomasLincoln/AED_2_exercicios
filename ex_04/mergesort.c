
#include <stdio.h>
#include <stdlib.h>

//função para juntar dois vetores
void merge(int arr[], int esq, int meio, int dir)
{
	int i, j, k;
	int n1 = meio - esq + 1;
	int n2 = dir - meio;

// vetores aux
	int aux1[n1], aux2[n2];

	//dar valores para os vetores aux
	for (i = 0; i < n1; i++)
		aux1[i] = arr[esq + i];
	for (j = 0; j < n2; j++)
		aux2[j] = arr[meio + 1 + j];

// juntar os vetores aux
	i = 0; 
	j = 0; 
	k = esq; 
	while (i < n1 && j < n2) {
		if (aux1[i] <= aux2[j]) {
			arr[k] = aux1[i];
			i++;
		}
		else {
			arr[k] = aux2[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = aux1[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = aux2[j];
		j++;
		k++;
	}
}

// cria subarrays, para ordenação
void mergeSort(int arr[], int esq, int dir)
{
	if (esq < dir) {

		int meio = esq + (dir - esq) / 2;

		mergeSort(arr, esq, meio);
		mergeSort(arr, meio + 1, dir);

		merge(arr, esq, meio, dir);
	}
}

void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	return 0;
}
