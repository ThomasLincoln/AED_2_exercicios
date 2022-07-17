#include <stdio.h>
#include <stdlib.h>

// 1º criar as structs
struct node {
  int dado;
  struct node *next;
};

struct hash {
  struct node *first;
  int tamanho;
};

int h(int n, int N) { return (n % N); }

// init na hash;
void init(int N, struct hash *hash) {
  int i;
  hash = (struct hash *)malloc(N * sizeof(struct hash));
  for (i = 0; i < N; i++) {
    hash[i].first = (struct node *)malloc(sizeof(struct node));
    hash[i].first = NULL;
    hash[i].tamanho = 0;
  }
  struct node *aux = hash[3].first;
}

// printar
void print(struct hash *hash, int N, int key) {
  int i;
    struct node *temp = hash[key].first;
    printf("[%i] ", key);
    while (temp) {
      printf("%i ", temp->dado);
      temp = temp->next;
    }
}

void inserir(int valor, int N, struct hash *hash) {
  // criar um novo node com o valor
  struct node *new_node = malloc(sizeof(struct node));
  new_node->dado = valor;
  new_node->next = NULL;
  // calcular o hash key
  int key = h(valor, N);
  // printf("\nEstamos inserindo: %i na key: %i e o next é %p\n", valor, key, new_node->next);
  // struct node *aux = hash[3].first;

  // primeiro a gente ve se a hash na linha key  ta vazia
  if (hash[key].first == NULL) {
    hash[key].first = new_node;
    // printf("----------------------------");
    // printf("\nSe você ta lendo isso é pq ta inserindo %i no primeiro ponto
    // de: %i\n", valor, key);

  } else { // colisão
    struct node *temp = hash[key].first;
    while (temp->next) {
      temp = temp->next;
    }
    // printf("\n--------------------\n");
    // printf("Inserindo %i na key [%i] e o anterior é %i", new_node->dado,key,
    // temp->dado ); printf("\n--------------------\n");
    temp->next = new_node;
    // print(hash, N);
    // printf("\nInserido: %i\n", temp->next->dado);
  }
}

// busca retorna 0 se nao achou e 1 se achou
int busca_node(int valor, int N, struct hash *hash) {
  // calcular o hash key
  int key = h(valor, N);
  struct node *temp = hash[key].first;
  while (temp) {
    if (temp->dado == valor) {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

void remove_node(int valor, int N, struct hash *hash) {
  int key = h(valor, N);
  struct node *temp = hash[key].first, *prev = hash[key].first;

  if (temp->dado == valor) {
    hash[key].first = temp->next;
    free(temp);
    return;
  }
  while (temp != NULL && temp->dado != valor) {
    prev = temp;
    temp = temp->next;
  }
  if(temp == NULL){
    return;
  }
  prev->next = temp->next;
  free(temp);
}

int main() {
  int N = 0, i, aux = 0;
  scanf("%i", &N);
  // inicializa uma hash
  struct hash *hash;
  hash = (struct hash *)malloc(N * sizeof(struct hash));
  for (i = 0; i < N; i++) {
    hash[i].first = NULL;
    hash[i].tamanho = 0;
  }
  init(N, hash);
  // 3 4 9 2 5 1 8 1 2
  while (aux >= 0) {
    // printf("\nInsira um número: ");
    scanf("%i", &aux);
    inserir(aux, N, hash);
  }
  // printf("\n\n\n\n");
  // print(hash, N);
  int busca = 0;
  scanf("%i", &busca);
  if(busca_node(busca, N, hash) == 1){
    remove_node(busca, N, hash);   
  }else{
    printf("Valor nao encontrado");
  }
  scanf("%i", &busca);
  print(hash, N,busca);
  return 0;
}