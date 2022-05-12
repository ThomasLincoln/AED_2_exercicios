#include <stdio.h>


int search(int arr[], int l, int r, int x, int count)
{
  count++;
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == x)
			return count;

		if (arr[mid] > x)
			return search(arr, l, mid - 1, x, count);

		return search(arr, mid + 1, r, x, count);
	}
	return -1;
}

int main(void)
{
int tamanho, *lista, i, aux, busca, count = -1;

  // printf("Entre com o tamanho do lista: ");
  scanf("%i", &tamanho);
  // printf("O tamanho sera: %i", tamanho);
  // printf("\n");
  
  // alocar memória
  lista = malloc(tamanho * sizeof(int));

  
  // dar os valores do role
  for(i = 0; i < tamanho; i++){
    scanf("%i", &aux);
    lista[i] = aux;
  }

  // printf("\n------------ \n lista \n ------------\n");
  // for(i = 0; i< tamanho; i++){
  //   printf("%i ", lista[i]);
  // }
  // printf("\n ------------\n");
  // printf("\nInsira o numero de busca: ");
  scanf("%i", &busca);
  // printf("o numero para buscar e: %i", busca);
  // printf("\n ------------\n");
	int result = search(lista, 0, tamanho - 1, busca, count);
	(result == -1)
		? printf("%i nao foi encontrado", busca)
		: printf("%i", result);

  free(lista);
	return 0;
}
