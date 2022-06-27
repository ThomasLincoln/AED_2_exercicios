#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum nodeColor { RED, BLACK };

struct Node {
  int data, color;
  struct Node *link[2];
};

struct Node *root = NULL;

// Create a red-black tree
struct Node *createNode(int data) {
  struct Node *newnode;
  newnode = (struct Node *)malloc(sizeof(struct Node));
  newnode->data = data;
  newnode->color = RED;
  newnode->link[0] = newnode->link[1] = NULL;
  return newnode;
}

// Insert an node
void insertion(int data) {
  struct Node *stack[98], *ptr, *newnode, *xPtr, *yPtr;
  int dir[98], ht = 0, index;
  ptr = root;
  if (!root) {
    root = createNode(data);
    return;
  }

  stack[ht] = root;
  dir[ht++] = 0;
  while (ptr != NULL) {
    if (ptr->data == data) {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    ptr = ptr->link[index];
    dir[ht++] = index;
  }
  stack[ht - 1]->link[index] = newnode = createNode(data);
  while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
    if (dir[ht - 2] == 0) {
      yPtr = stack[ht - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 0) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[1];
          xPtr->link[1] = yPtr->link[0];
          yPtr->link[0] = xPtr;
          stack[ht - 2]->link[0] = yPtr;
        }
        xPtr = stack[ht - 2];
        xPtr->color = RED;
        yPtr->color = BLACK;
        xPtr->link[0] = yPtr->link[1];
        yPtr->link[1] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    } else {
      yPtr = stack[ht - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED)) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 1) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[0];
          xPtr->link[0] = yPtr->link[1];
          yPtr->link[1] = xPtr;
          stack[ht - 2]->link[1] = yPtr;
        }
        xPtr = stack[ht - 2];
        yPtr->color = BLACK;
        xPtr->color = RED;
        xPtr->link[1] = yPtr->link[0];
        yPtr->link[0] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  root->color = BLACK;
}

// Delete a node
void deletion(int data) {
  struct Node *stack[98], *ptr, *xPtr, *yPtr;
  struct Node *pPtr, *qPtr, *rPtr;
  int dir[98], ht = 0, diff, i;
  enum nodeColor color;

  if (!root) {
    printf("Tree not available\n");
    return;
  }

  ptr = root;
  while (ptr != NULL) {
    if ((data - ptr->data) == 0)
      break;
    diff = (data - ptr->data) > 0 ? 1 : 0;
    stack[ht] = ptr;
    dir[ht++] = diff;
    ptr = ptr->link[diff];
  }

  if (ptr->link[1] == NULL) {
    if ((ptr == root) && (ptr->link[0] == NULL)) {
      free(ptr);
      root = NULL;
    } else if (ptr == root) {
      root = ptr->link[0];
      free(ptr);
    } else {
      stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
    }
  } else {
    xPtr = ptr->link[1];
    if (xPtr->link[0] == NULL) {
      xPtr->link[0] = ptr->link[0];
      color = xPtr->color;
      xPtr->color = ptr->color;
      ptr->color = color;

      if (ptr == root) {
        root = xPtr;
      } else {
        stack[ht - 1]->link[dir[ht - 1]] = xPtr;
      }

      dir[ht] = 1;
      stack[ht++] = xPtr;
    } else {
      i = ht++;
      while (1) {
        dir[ht] = 0;
        stack[ht++] = xPtr;
        yPtr = xPtr->link[0];
        if (!yPtr->link[0])
          break;
        xPtr = yPtr;
      }

      dir[i] = 1;
      stack[i] = yPtr;
      if (i > 0)
        stack[i - 1]->link[dir[i - 1]] = yPtr;

      yPtr->link[0] = ptr->link[0];

      xPtr->link[0] = yPtr->link[1];
      yPtr->link[1] = ptr->link[1];

      if (ptr == root) {
        root = yPtr;
      }

      color = yPtr->color;
      yPtr->color = ptr->color;
      ptr->color = color;
    }
  }

  if (ht < 1)
    return;

  if (ptr->color == BLACK) {
    while (1) {
      pPtr = stack[ht - 1]->link[dir[ht - 1]];
      if (pPtr && pPtr->color == RED) {
        pPtr->color = BLACK;
        break;
      }

      if (ht < 2)
        break;

      if (dir[ht - 2] == 0) {
        rPtr = stack[ht - 1]->link[1];

        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[ht - 1]->color = RED;
          rPtr->color = BLACK;
          stack[ht - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 0;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht++;

          rPtr = stack[ht - 1]->link[1];
        }

        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
            (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[1] || rPtr->link[1]->color == BLACK) {
            qPtr = rPtr->link[0];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[0] = qPtr->link[1];
            qPtr->link[1] = rPtr;
            rPtr = stack[ht - 1]->link[1] = qPtr;
          }
          rPtr->color = stack[ht - 1]->color;
          stack[ht - 1]->color = BLACK;
          rPtr->link[1]->color = BLACK;
          stack[ht - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      } else {
        rPtr = stack[ht - 1]->link[0];
        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[ht - 1]->color = RED;
          rPtr->color = BLACK;
          stack[ht - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 1;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht++;

          rPtr = stack[ht - 1]->link[0];
        }
        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
            (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[0] || rPtr->link[0]->color == BLACK) {
            qPtr = rPtr->link[1];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[1] = qPtr->link[0];
            qPtr->link[0] = rPtr;
            rPtr = stack[ht - 1]->link[0] = qPtr;
          }
          rPtr->color = stack[ht - 1]->color;
          stack[ht - 1]->color = BLACK;
          rPtr->link[0]->color = BLACK;
          stack[ht - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      }
      ht--;
    }
  }
}

void print_tree(struct Node *tree, int altura) {
  int i;

  // se o no for vazio
  if (tree == NULL) {
    return;
  }

  // vai para a direita da arvore, aumentando a altura em 1 sempre que acontece
  // isso
  print_tree(tree->link[1], altura + 1);

  for (i = 0; i < altura; i++) {
    printf("\t");
  }

  printf("%d %d\n", tree->data, tree->color);
  print_tree(tree->link[0], altura + 1);
}

struct Node *busca_node_2(struct Node *raiz, int chave) {
  if (raiz == NULL || raiz->data == chave) {
    return raiz;
  }
  if (chave < raiz->data) {
    return (busca_node_2(raiz->link[0], chave));
  } else {
    return (busca_node_2(raiz->link[1], chave));
  }
}

int maior_valor(int a, int b);

// calcular altura do nó
int calcular_tamanho(struct Node *N) {
  if (N == NULL) {
    return 0;
  }
  return 1 + maior_valor(calcular_tamanho(N->link[0]),
                         calcular_tamanho(N->link[1]));
}

// pegar o maior_valor valor
int maior_valor(int a, int b) { return (a > b) ? a : b; }

int altura(struct Node *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = altura(raiz->link[0]);
        int dir = altura(raiz->link[1]);
        if(esq > dir && raiz->color == BLACK){
            return esq + 1;
        }
        else if(raiz->color == BLACK){
            return dir + 1;
        }
    }
}

int main() {
  int ch, data = 0, busca, busca2;
  bool foi = false;
  struct Node *node_encontrado = NULL;
  int *vetor_aux;
  vetor_aux = malloc(3 * sizeof(int));
  for (int i = 0; i < 3; i++) {
    vetor_aux[i] = 0;
  }
  int *vetor_aux2;
  vetor_aux2 = malloc(3 * sizeof(int));
  for (int i = 0; i < 3; i++) {
    vetor_aux2[i] = 0;
  }

  int vetor_aux3[100];
  for (int i = 0; i < 100; i++) {
    vetor_aux3[i] = -1;
  }
  while (data >= 0) {
    // printf("Insira o numero a ser lido: ");
    scanf("%i", &data);
    if (data >= 0) {
      insertion(data);
    }
  }

  vetor_aux[0] = calcular_tamanho(root) - 1;
  vetor_aux[1] = calcular_tamanho(root->link[0]);
  vetor_aux[2] = calcular_tamanho(root->link[1]);

  busca = 0;
  int i = 0;

while (busca >= 0) {
  // printf("Digite um número para buscar: ");
  scanf("%i", &busca);
  if(busca<0)
  scanf("%i", &busca2);
  if(foi == false){
  printf("%i, %i, %i", vetor_aux[0], vetor_aux[1], vetor_aux[2]);
    foi = true;
  }
  node_encontrado = busca_node_2(root, busca);
  if(node_encontrado!= NULL){
    vetor_aux2[0] = calcular_tamanho(node_encontrado) - 1;
    if(vetor_aux2[0]>=1){
    vetor_aux2[1] = calcular_tamanho(node_encontrado->link[0]);
    vetor_aux2[2] = calcular_tamanho(node_encontrado->link[1]);
    }
    printf("\n%i, %i, %i", vetor_aux2[0], vetor_aux2[1], vetor_aux2[2]);
    vetor_aux2[0] = vetor_aux2[1] = vetor_aux2[2] = 0; 
  }else{
    insertion(busca);
  }
}

node_encontrado = busca_node_2(root, busca2);
if(node_encontrado == NULL){
  printf("Valor nao encontrado");
}else if(node_encontrado->color == BLACK){
  printf("%i", altura(node_encontrado)-1);
}

  // print_tree(root, 0);

  return 0;
}