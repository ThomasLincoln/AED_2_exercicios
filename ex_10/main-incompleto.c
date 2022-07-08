#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum nodeColor { RED, BLACK };
#define BLACK 0
#define RED 1

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

int altura_vermelha(struct Node *raiz){
    if(raiz == NULL){
        return 0;
    }
  return (raiz->color) * 1 + maior_valor(altura_vermelha(raiz->link[0]),
                         altura_vermelha(raiz->link[1]));
}

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

// vai pegar o nó com menor valor na arvore
struct Node *valor_minimo_node(struct Node *node) {
  struct Node *atual = node;
  while (atual->link[0] != NULL) {
    atual = atual->link[0];
  }
  return atual;
}

struct Node *deletar_node(struct Node *raiz, int chave) {
  // deletar normal
  if (raiz == NULL) {
    return raiz;
  }
  if (chave < raiz->data) {
    raiz->link[0] = deletar_node(raiz->link[0], chave);
  } else if (chave > raiz->data) {
    raiz->link[1] = deletar_node(raiz->link[1], chave);
  }

  // se ele nao for menor nem maior_valor é pq ele é o proprio node a ser
  // removido
  else {
    if (raiz->link[1] == NULL || raiz->link[0] == NULL) {

      // se retornar algo é pq não é null, então ele tem um filho só
      struct Node *node_aux = raiz->link[0] ? raiz->link[0] : raiz->link[1];
      // caso q não tem child
      if (node_aux == NULL) {
        node_aux = raiz;
        raiz = NULL;
      } else {
        *raiz = *node_aux;
        free(node_aux);
      }
    } else {
      // caso em que tem dois filhos
      struct Node *node_aux = valor_minimo_node(raiz->link[1]);
      raiz->data = node_aux->data;
      raiz->link[1] = deletar_node(raiz->link[1], node_aux->data);
    }
  }

  // se a árvore não tiver node retorna ela msm
  if (raiz == NULL) {
    return raiz;
  }
  return raiz;
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

  int vetor_aux3[10000];
  for (int i = 0; i < 10000; i++) {
    vetor_aux3[i] = -1;
  }
  while (data >= 0) {
    // printf("Insira o numero a ser lido: ");
    scanf("%i", &data);
    if (data >= 0) {
      insertion(data);
      // printf("-----insercao 1-----\n");
      // print_tree(root, 0);
      
    }
  }

  vetor_aux[0] = calcular_tamanho(root) - 1;
  vetor_aux[1] = calcular_tamanho(root->link[0]);
  vetor_aux[2] = calcular_tamanho(root->link[1]);

  busca = 0;
  int i = 0, cont = 0;
  while (busca >= 0) {
    scanf("%i", &busca);
    vetor_aux3[cont] = busca;
    cont++;
  }
  scanf("%i", &busca2);
  printf("%i, %i, %i\n", vetor_aux[0], vetor_aux[1], vetor_aux[2]);
  for (i = 0; i < cont; i++) {
    node_encontrado = busca_node_2(root, vetor_aux3[i]);
    if (node_encontrado != NULL) {
      vetor_aux2[0] = calcular_tamanho(node_encontrado) - 1;
      if (vetor_aux2[0] >= 1) {
        vetor_aux2[1] = calcular_tamanho(node_encontrado->link[0]);
        vetor_aux2[2] = calcular_tamanho(node_encontrado->link[1]);
      }
      printf("%i, %i, %i\n", vetor_aux2[0], vetor_aux2[1], vetor_aux2[2]);
      vetor_aux2[0] = vetor_aux2[1] = vetor_aux2[2] = 0;
      deletar_node(root, vetor_aux3[i]);
      // printf("----remocao------\n");
      // print_tree(root, 0);
    } else if(vetor_aux3[i] >=0){
      insertion(vetor_aux3[i]);
      // printf("------insercao 2----\n");
      // print_tree(root, 0);
    }
  }
  // while (busca >= 0) {
  //   // printf("Digite um número para buscar: ");
  //   scanf("%i", &busca);
  //   if(busca<=1)
  //   scanf("%i", &busca2);
  //   if(foi == false){
  //     foi = true;
  //   }
  // }

  // printf("\n");
  // print_tree(root, 0);
  node_encontrado = busca_node_2(root, busca2);
  if (node_encontrado == NULL) {
    printf("Valor nao encontrado");
  } else{
    int altura = altura_vermelha(node_encontrado);
    printf("%i", altura);
  }


  return 0;
}


// ⠀⠀⠀⠀⠀⠀⠀⠈⢶⣶⣦⣤⣤⣤⣤⣤⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠘⠿⠟⣛⣛⣛⡛⠛⠻⠿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣿⣿⣿⣿⢀⡀⠀⠈⠻⣿⣿⣷⡄⠀⠀⠀⠀⣀⣤
// ⠀⠀⠀⠀⢠⣶⣿⠿⠛⣉⣭⣍⠛⢿⣿⠘⣿⣿⣿⣷⡜⣿⣿⣿⣎⢿⣿⣿⣿⣿
// ⠀⠀⠀⣴⣿⡿⠁⠀⠀⣿⣿⣿⠀⠀⠃⠀⢸⣿⣿⠉⠁⢿⣿⣿⣿⠎⠉⢻⣿⠇
// ⠀⠀⣼⣿⣿⠀⠀⠀⠀⣿⣿⣿⠀⠀⠀⠀⢸⣿⣿⠀⠀⣸⣿⣿⠃⠀⠀⠘⠁⠀
// ⢀⣾⣿⣿⡇⠀⠀⠀⠀⣿⣿⣿⠀⠀⠀⠀⢸⣿⣿⠀⠀⣿⣿⠇⠀⠀⠀⠀⠀⠀
// ⢹⣿⣿⣿⡇⠀⠀⠀⠀⣿⣿⣿⠀⠀⠀⠀⢸⣿⣿⠀⠾⠿⠋⠀⠀⠀⣠⠀⠀⠀
// ⠀⢿⣿⣿⣷⠀⠀⠀⠀⣿⣿⣿⣿⣿⣷⣶⣦⣍⠻⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀
// ⠀⠈⢻⣿⣿⣦⠀⠀⠀⣿⣿⣿⠉⠉⠉⠙⠻⣿⣷⣌⠉⠉⠉⠉⢻⣿⠟⠀⠀⠀
// ⠀⠀⠀⠙⢿⣿⣷⣤⡀⠿⢿⣿⠀⠀⠀⠀⢰⣜⢿⣿⣧⡀⠀⠀⠈⠋⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠙⠿⢿⣿⣿⣶⣶⣶⣶⣾⡇⢸⣿⣦⠻⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠈⣍⣉⣛⠋⠉⠉⠀⢸⣿⣿⠀⠙⣿⣿⣦⣀⠀⠀⣀⡄⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⡀⠀⠀⠀⣾⣿⣿⡀⠀⠈⢿⣿⣿⣿⣿⠟⠁⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠺⠿⣿⣿⣷⡀⠀⠚⠿⣿⣿⣷⡄⠀⠀⠙⠿⠟⠉⠀⠀⠀
