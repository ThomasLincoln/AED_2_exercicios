#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **mat, int a, int b) {
  char aux[20];
  strcpy(aux, mat[a]);
  strcpy(mat[a], mat[b]);
  strcpy(mat[b], aux);
}

void max_heap_fai(char **matriz, int tamanho_busca, int i) {
  int left = 2 * i;
  int right = left + 1;
  int maior = i;
  if (left <= tamanho_busca && strcmp(matriz[left], matriz[maior]) > 0) {
    maior = left;
  }
  if (right <= tamanho_busca && strcmp(matriz[right], matriz[maior]) > 0) {
    maior = right;
  }
  if (maior != i) {
    // true
    swap(matriz, i, maior);
    max_heap_fai(matriz, tamanho_busca, maior);
  }
  return;
}

void build_max_heap(char **matriz, int tamanho_busca) {
  int n = tamanho_busca;
  for (int i = (n / 2); i > 0; i--) {
    max_heap_fai(matriz, tamanho_busca, i);
  }
}

char *heap_extract_max(char **matriz, int tamanho_busca) {
  char *max = (char *)malloc(20 * sizeof(char));
  strcpy(max, matriz[1]);
  int ultimo = tamanho_busca;
  strcpy(matriz[1], matriz[ultimo]);
  matriz[ultimo] = "";
  max_heap_fai(matriz, tamanho_busca, 1);
  return max;
}

void heapsort(char **matriz, int tamanho_busca, char **v) {
  build_max_heap(matriz, tamanho_busca);
  char *aux;
  aux = (char *)malloc(20 * sizeof(char));
  printf("build_heap: ");
  for (int i = 1; i <= tamanho_busca; i++) {
    printf("%s ", matriz[i]);
  }
  int n = tamanho_busca;
  while (n > 0) {
    aux = heap_extract_max(matriz, tamanho_busca);
    strcpy(v[n], aux);
    n--;
  }
  free(aux); 
  printf("\npalavras: ");
  for (int i = 1; i <= tamanho_busca; i++) {
    printf("%s ", v[i]);
  }
}

int main(void) {
  int N, E;
  // printf("Jogador 1 insira o N: ");
  scanf("%i", &N);
  // printf("\n o valor inserido foi: %i", N);

  // alocando as linhas da matriz
  char **matriz = (char **)malloc((N + 1) * sizeof(char *));
  // alocando as colunas da matriz
  for (int i = 1; i <= N; i++) {
    matriz[i] = (char *)malloc(20 * sizeof(char));
  }

  // leio a frase
  // printf("\ninsira as palavras: ");
  for (int i = 1; i <= N; i++) {
    scanf("%s", matriz[i]);
    for (int j = 0; j < strlen(matriz[i]); j++) {
      if (matriz[i][j] > 122 || matriz[i][j] < 97) {
        printf("a palavra %s eh invalida", matriz[i]);
        return 0;
      }
    }
  }

  // pegar o tamanho da frase selecionada
  // printf("\nInsira a quantidade de palavras selecionadas: ");
  scanf("%i", &E);
  // printf("Numero selecionado: %i", E);

  // alocando as linhas da matriz selecionado
  char **matriz_select = (char **)malloc((E + 1) * sizeof(char *));
  // alocando as colunas da matriz selecionado
  for (int i = 1; i <= E; i++) {
    matriz_select[i] = (char *)malloc(20 * sizeof(char));
  }
  // alocando as linhas da matriz selecionado
  char **matriz_fim = (char **)malloc((E + 1) * sizeof(char *));
  // alocando as colunas da matriz selecionado
  for (int i = 1; i <= E; i++) {
    matriz_fim[i] = (char *)malloc(20 * sizeof(char));
  }
  // informar os indices
  // printf("\n informe os indices: ");
  int aux;
  for (int i = 1; i <= E; i++) {

    // printf("\n informe o indice %i: ", i);
    scanf("%i", &aux);
    strcpy(matriz_select[i], matriz[aux + 1]);
  }
  heapsort(matriz_select, E, matriz_fim);


  // desalocando a matriz
  for (int i = 1; i < N; i++) {
    free(matriz[i]);
  }
  free(matriz);

  // desalocando a matriz selecionada
  for (int i = 0; i < E; i++) {
    free(matriz_select[i]);
  }
  free(matriz_select);

  return 0;
}

//                _,........__
//             ,-'            "`-.
//           ,'                   `-.
//         ,'                        \
//       ,'                           .
//       .'\               ,"".       `
//      ._.'|             / |  `       \
//      |   |            `-.'  ||       `.
//      |   |            '-._,'||       | \
//      .`.,'             `..,'.'       , |`-.
//      l                       .'`.  _/  |   `.
//      `-.._'-   ,          _ _'   -" \  .     `
// `."""""'-.`-...,---------','         `. `....__.
// .'        `"-..___      __,'\          \  \     \
// \_ .          |   `""""'    `.           . \     \
//   `.          |              `.          |  .     L
//     `.        |`--...________.'.        j   |     |
//       `._    .'      |          `.     .|   ,     |
//          `--,\       .            `7""' |  ,      |
//             ` `      `            /     |  |      |    _,-'"""`-.
//              \ `.     .          /      |  '      |  ,'          `.
//               \  v.__  .        '       .   \    /| /              \
//                \/    `""\"""""""`.       \   \  /.''                |
//                 `        .        `._ ___,j.  `/ .-       ,---.     |
//                 ,`-.      \         ."     `.  |/        j     `    |
//                /    `.     \       /         \ /         |     /    j
//               |       `-.   7-.._ .          |"          '         /
//               |          `./_    `|          |            .     _,'
//               `.           / `----|          |-............`---'
//                 \          \      |          |
//                ,'           )     `.         |
//                 7____,,..--'      /          |
//                                   `---.__,--.'mh