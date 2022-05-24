// Thomas Lincoln 156.603
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

int particionar(int array_aux[], int baixo, int alto) {
  int pivo = array_aux[alto];
  int i = (baixo - 1);
  for (int j = baixo; j < alto; j++) {
    if (array_aux[j] <= pivo) {
      i++;
      swap(&array_aux[i], &array_aux[j]);
    }
  }
  swap(&array_aux[i + 1], &array_aux[alto]);
  return (i + 1);
}

void quicksort(int array[], int baixo, int alto, int k) {
  if (baixo < alto) {
    int particao = particionar(array, baixo, alto);

    if (particao + 1 > k) {
      quicksort(array, baixo, particao - 1, k);
    }
    if (particao + 1 < k) {
      quicksort(array, particao + 1, alto, k);
    }
  }
}

int main(void) {
  int k, n, *vetor, i;
  scanf("%i", &k);
  scanf("%i", &n);
  vetor = (int *)malloc(n * (sizeof(int)));
  // ler infos
  for (i = 0; i < n; i++) {
    scanf("%i", &vetor[i]);
  }

  // quicksort
  quicksort(vetor, 0, n - 1, k);

  // printar array
  printf("%io menor elemento eh o %i\n", k, *(vetor + (k - 1)));

  for (i = 0; i < n; i++) {
    printf("%i ", vetor[i]);
  }
  return 0;
}