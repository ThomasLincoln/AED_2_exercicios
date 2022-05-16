#include <stdio.h>
#include <stdlib.h>
// -------------------------------------------------
// Thomas Lincoln 156.603 ~ ex 4
// -------------------------------------------------
// área da lista
struct Node {
  int data;
  struct Node *next;
};

void push_in_end(struct Node **cabeca, int novo_dado) {
  struct Node *novo_node = (struct Node *)malloc(sizeof(struct Node));
  struct Node *last = *cabeca;

  novo_node->data = novo_dado;
  novo_node->next = NULL;
  if (*cabeca == NULL) {
    *cabeca = novo_node;
    return;
  }

  while (last->next != NULL) {
    last = last->next;
  }
  last->next = novo_node;
  return;
}

void printList(struct Node *node) {
  while (node != NULL) {
    printf("%d ", node->data);
    node = node->next;
  }
}

// -------------------------------------------------
// área do mergesort

// split (dividir a função em duas)
void split(struct Node *base, struct Node **frente, struct Node **tras) {
  struct Node *slow;
  struct Node *fast;
  slow = base;
  fast = base->next;

  // verificando quando o fast é = null
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      fast = fast->next;
      slow = slow->next;
    }
  }
  *frente = base;
  *tras = slow->next;
  slow->next = NULL;
}

// juntar metades
struct Node *juntar_metades(struct Node *a, struct Node *b) {
  struct Node *resultado = NULL;

  // verificar se um dos dois são nulos
  if (a == NULL) {
    return (b);
  } else if (b == NULL) {
    return (a);
  }

  // verifica qual é maior
  if(a->data <= b->data){
    resultado = a;
    resultado->next = juntar_metades(a->next, b);
  }else{
    resultado = b;
    resultado->next = juntar_metades(a, b->next);
  }
  return(resultado);
}

// Merge sort
void merge_sort(struct Node **head) {
  struct Node *head_aux = *head;
  // cria structs pras duas divisões
  struct Node *a;
  struct Node *b;

  // testa pra ver se a lista não tem só um elemento
  if ((head_aux == NULL) || (head_aux->next == NULL)) {
    return;
  }
  // dividir em a e b
  split(head_aux, &a, &b);

  // classificar as funções
  merge_sort(&a);
  merge_sort(&b);

  // juntar as duas metades
  *head = juntar_metades(a, b);
}

// -------------------------------------------------

int main(void) {
  int N, i, aux;
  struct Node *head = NULL;
  scanf("%i", &N);
  for(i = 0; i < N; i++){
    scanf("%i", &aux);
    push_in_end(&head, aux);
  }
  merge_sort(&head);
  printList(head);
  free(head);
  return 0;
}

// passos merge sort
// 1- verificar se só há um elemento
// 2- se não dividir a lista em 2 e começar o algoritmo
// 3- classificar as 2 metades
// 4- juntar elas