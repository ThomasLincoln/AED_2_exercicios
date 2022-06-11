#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
7
programar
VAMOS
palavra
eh
futebol
computador
legal
3 2
*/

void normalizar(char **A, int N, int max) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < max; j++) {
      if (A[i][j] > 64 && A[i][j] <= 90) {
        A[i][j] += 32;
      }
    }
    printf("%s.\n", A[i]);
  }
}

void counting_sort(char **A, char **B, int N, int aux) {
  // criar vetor C
 // int vetor_C[27];
  int *vetor_C;
  vetor_C = (int*)malloc(27*sizeof(int));
  for (int i = 0; i < 27; i++) {
    vetor_C[i] = 0;
  }
  // salvar a quantidade de cada elemento
  for (int i = 0; i < N; i++) {
    if (A[i][aux] == 0) {
      vetor_C[A[i][aux]]++;
    } else {
      vetor_C[A[i][aux] - 96]++;
    }
  }  
  printf("\n");
  // somar o x com o x-1
  for (int i = 0; i < 27; i++) {
    vetor_C[i] += vetor_C[i - 1];
    printf("%d ", vetor_C[i]);
  }
  

  for (int i = N - 1; i >= 0; i--) {
    if (A[i][aux] == 0) {
      vetor_C[A[i][aux]]--;
      B[vetor_C[A[i][aux]]] = A[i];
    } else {
      vetor_C[A[i][aux] - 96]--;
      B[vetor_C[A[i][aux] - 96]] = A[i];
    }
  }
  free(vetor_C);
}

void radix(char **A, char **B, int max, int N) {
  int aux = max;
  for (int i = aux; i > 0; i--) {
    // ordena matriz
    aux--;
    counting_sort(A, B, N, aux);
    // reatribuir A = B
    for (int j = 0; j < N; j++) {
      A[j] = B[j];
    }
  }
}

int main(void) {
  int N, P, T, tamanho_max = 0;
  char aux[20];

  scanf("%i", &N);
  // alocando matrizA
  char **matrizA = (char **)malloc(N * sizeof(char *));
  char **matrizB = (char **)malloc(N * sizeof(char *));

  for (int i = 0; i < N; i++) {
    matrizA[i] = (char *)malloc(20 * sizeof(char));
    matrizB[i] = (char *)malloc(20 * sizeof(char));
    for (int j = 0; j < 20; j++) {
      matrizA[i][j] = 0;
      matrizB[i][j] = 0;
    }
  }

  // colocando valor na matrizA
  for (int i = 0; i < N; i++) {
    scanf("%s", matrizA[i]);
    if (strlen(matrizA[i]) > tamanho_max) {
      tamanho_max = strlen(matrizA[i]);
    }
  }

  scanf("%i %i", &P, &T);
  normalizar(matrizA, N, tamanho_max);
  printf("%d", tamanho_max);
  radix(matrizA, matrizB, tamanho_max, N);
  for(int i =P-1; i<P+T-1; i++){
      printf("\n%s",matrizA[i]);
  }
  
  // desalocando a matrizA
  for (int i = 0; i < N; i++) {
    free(matrizA[i]);
  }
  free(matrizA);
  free(matrizB);

  return 0;
}