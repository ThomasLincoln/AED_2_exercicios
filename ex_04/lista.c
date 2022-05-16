// código pra fazer uma lista


#include <stdio.h>

struct Node {
  int data;
  struct Node *next;
};

void push_head(struct Node **cabeca, int novo_dado) {
  // aloca memória
  struct Node* novo_node = (struct Node*)malloc(sizeof(struct Node));

  // colocar o valor
  novo_node->data = novo_dado;
  novo_node->next = (*cabeca);
  (*cabeca) = novo_node;
}

void push_after(struct Node *node_anterior, int novo_dado) {
  if (node_anterior == NULL) {
    return;
  }
  struct Node* novo_node = (struct Node*)malloc(sizeof(struct Node));
  novo_node->data = novo_dado;
  novo_node->next = node_anterior->next;
  node_anterior->next = novo_dado;
}

void push_in_end(struct Node **cabeca, int novo_dado) {
  struct Node* novo_node = (struct Node*)malloc(sizeof(struct Node));
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

void printList(struct Node *node){
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}



int main(void) {
  int N, i, aux;
  struct Node* head = NULL;
  printf("Insira o valor de N: ");
  scanf("%i", &N);
  for(i=0; i<N; i++){
    scanf("%i", &aux);
    push_in_end(&head, aux);
  }
    printList(head);
  return 0;
}