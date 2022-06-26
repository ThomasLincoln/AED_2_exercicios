/*
 ----------------------------------------
| Thomas Lincoln - 156.603
 ----------------------------------------
 
[x] Inicialização
[] Pesquisa
[x] Inserção
[x] Remoção
[x] Calcular Altura do Nó
 
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
 
// nó da árvore
struct Node {
  int chave;
  struct Node *esquerda;
  struct Node *direita;
  int tamanho;
};
 
int maior_valor(int a, int b);
 
// calcular altura do nó
int calcular_tamanho(struct Node *N) {
  if (N == NULL) {
    return 0;
  }
  return 1 + maior_valor(calcular_tamanho(N->esquerda), calcular_tamanho(N->direita));
}
 
// pegar o maior_valor valor
int maior_valor(int a, int b) {
  return (a > b) ? a : b; 
  }
 
// Cria um novo node
struct Node *novo_Node(int chave) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->chave = chave;
  node->esquerda = NULL;
  node->direita = NULL;
  node->tamanho = 0;
  return (node);
}
 
struct Node *rodar_pra_direita(struct Node *y) {
  struct Node *x = y->esquerda;
  struct Node *T2 = x->direita;
 
  // rotação em si
  x->direita = y;
  y->esquerda = T2;
 
  // atualizar o peso
  x->tamanho = calcular_tamanho(x);
  y->tamanho = calcular_tamanho(y);
 
  // return o novo node att
  return (x);
}
 
struct Node *rodar_pra_esquerda(struct Node *x) {
  struct Node *y = x->direita;
  struct Node *T2 = y->esquerda;
 
  // rotação em si
  y->esquerda = x;
  x->direita = T2;
 
  // att de tamanho
  x->tamanho = calcular_tamanho(x);
  y->tamanho = calcular_tamanho(y);
 
  // retorna o novo node
  return y;
}
 
// verificar o balanceamento
int balanceada(struct Node *N) {
  if (N == NULL) {
    return 0;
  }
  return calcular_tamanho(N->esquerda) - calcular_tamanho(N->direita);
}
 
// Inserir Node
struct Node *inserir(struct Node *node, int chave) {
  if (node == NULL) {
    return (novo_Node(chave));
  }
 
  // inserção padrão de arvore binária
  if (chave < node->chave) {
    node->esquerda = inserir(node->esquerda, chave);
  } else if (chave > node->chave) {
    node->direita = inserir(node->direita, chave);
  } else {
    return node;
  }
 
  // att o tamanho do node pai
  node->tamanho = calcular_tamanho(node);
  // conseguir o fator de balanceamento
  int balanca = balanceada(node);
  // caso esquerda esquerda
  if (balanca > 1 && chave < node->esquerda->chave) {
    return (rodar_pra_direita(node));
  }
  // caso direita direita
  if (balanca < -1 && chave > node->direita->chave) {
    return (rodar_pra_esquerda(node));
  }
  // caso esquerda direita
  if (balanca > 1 && chave > node->esquerda->chave) {
    node->esquerda = rodar_pra_esquerda(node->esquerda);
    return (rodar_pra_direita(node));
  }
 
  if (balanca < -1 && chave < node->direita->chave) {
    node->direita = rodar_pra_direita(node->direita);
    return (rodar_pra_esquerda(node));
  }
  return node;
}
 
// vai pegar o nó com menor valor na arvore
struct Node *valor_minimo_node(struct Node *node) {
  struct Node *atual = node;
  while (atual->esquerda != NULL) {
    atual = atual->esquerda;
  }
  return atual;
}
 
struct Node *deletar_node(struct Node *raiz, int chave) {
  // deletar normal
  if (raiz == NULL) {
    return raiz;
  }
  if (chave < raiz->chave) {
    raiz->esquerda = deletar_node(raiz->esquerda, chave);
  } else if (chave > raiz->chave) {
    raiz->direita = deletar_node(raiz->direita, chave);
  }
 
  // se ele nao for menor nem maior_valor é pq ele é o proprio node a ser removido
  else {
    if (raiz->direita == NULL || raiz->esquerda == NULL) {
 
      // se retornar algo é pq não é null, então ele tem um filho só
      struct Node *node_aux = raiz->esquerda ? raiz->esquerda : raiz->direita;
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
      struct Node *node_aux = valor_minimo_node(raiz->direita);
      raiz->chave = node_aux->chave;
      raiz->direita = deletar_node(raiz->direita, node_aux->chave);
    }
  }
 
  // se a árvore não tiver node retorna ela msm
  if (raiz == NULL) {
    return raiz;
  }
 
  // att o tamanho de tuuuudo;
  raiz->tamanho =
      1 + maior_valor(calcular_tamanho(raiz->esquerda), calcular_tamanho(raiz->direita));
 
  // Ver se ela ta balanceada
  int state_balanceamento = balanceada(raiz);
 
  // assim como na hr de inserir, temos 4 situações que temos que analisar
 
  // caso esquerda esquerda
  if (state_balanceamento > 1 && balanceada(raiz->esquerda) >= 0) {
    return (rodar_pra_direita(raiz));
  }
 
  // caso esquerda direita
  if (state_balanceamento > 1 && balanceada(raiz->esquerda) < 0) {
    raiz->esquerda = rodar_pra_esquerda(raiz->esquerda);
    return (rodar_pra_direita(raiz));
  }
 
  // caso direita direita
  if (state_balanceamento < -1 && balanceada(raiz->direita) <= 0) {
    return (rodar_pra_esquerda(raiz));
  }
 
  // caso direita esquerda
  if (state_balanceamento < -1 && balanceada(raiz->direita) > 0) {
    raiz->direita = rodar_pra_direita(raiz->direita);
    return (rodar_pra_esquerda(raiz));
  }
  return raiz;
}
 
bool busca_node(struct Node *raiz, int chave) {
  if (raiz == NULL) {
    return false;
  }
 
  if (raiz->chave == chave) {
    return true;
  }
  if (chave < raiz->chave) {
    return (busca_node(raiz->esquerda, chave));
  }else{
    return (busca_node(raiz->direita, chave));
  }
}
 
struct Node * libera (struct Node * node){
    if (node!=NULL) {
        libera(node->esquerda); /* libera sae */
        libera(node->direita); /* libera sad */
        free(node); /* libera raiz */
    }
    return NULL;
}
 
    
struct Node* busca_node_2(struct Node *raiz, int chave) {
  if (raiz == NULL || raiz->chave == chave) {
    return raiz;
  }
  if (chave < raiz->chave) {
    return (busca_node_2(raiz->esquerda, chave));
  }else{
    return (busca_node_2(raiz->direita, chave));  
  }
}
 
int main(void) {
  int aux = 0, aux2 = 0;
  bool result;
  int *vetor_aux;
  vetor_aux = malloc(3 * sizeof(int));
 
  for(int i = 0; i < 3; i++){
    vetor_aux[i] = 0;
  }
 
  int *vetor_aux2;
  vetor_aux2 = malloc(3 * sizeof(int));
 
  for(int i = 0; i < 3; i++){
    vetor_aux2[i] = 0;
  }
  
  struct Node *root = NULL;
  struct Node *node_encontrado = NULL; 
  // primeira linha
  while (aux >= 0) {
    // printf("Insira o numero a ser inserido: ");
    scanf("%i", &aux);
    if (aux >= 0) {
      root = inserir(root, aux);
    }
  }
  vetor_aux[0] = calcular_tamanho(root) - 1;
  vetor_aux[1] = calcular_tamanho(root->esquerda);
  vetor_aux[2] = calcular_tamanho(root->direita);
  while (aux2 >= 0) {
 
    // printf("Insira o numero a ser pesquisado: ");
    scanf("%i", &aux2);
    // preciso verificar se existe, se existir eu removo, se não eu adciono
    if (aux2 >= 0) {
      if (busca_node_2(root, aux2) == NULL) {
        root = inserir(root, aux2);
      } else{
        root = deletar_node(root, aux2);
      }
    }
  }
  // preOrder(root);
  // printf("Insira o numero a ser pesquisado 2: ");
  scanf("%i", &aux);
  node_encontrado = busca_node_2(root, aux);
  vetor_aux2[0] = calcular_tamanho(node_encontrado)-1;
  if(vetor_aux2[0]>= 0){
   vetor_aux2[1] = calcular_tamanho(node_encontrado->esquerda);
   vetor_aux2[2] = calcular_tamanho(node_encontrado->direita);  
  }
  // if(node_encontrado->chave == NULL){
  //   printf("a");
  // }
 
 
  
  printf("%i, %i, %i\n", vetor_aux[0], vetor_aux[1], vetor_aux[2]);
// if(node_encontrado == NULL){
// }else{
    if(vetor_aux2[0]>=0){
  printf("%i, %i, %i", vetor_aux2[0], vetor_aux2[1], vetor_aux2[2]);
    }else{
   printf("Valor nao encontrado");
    }
 
  libera(root);
  free(node_encontrado);
 
  return 0;
}
 
/*
 
16 14 20 12 11 19 18 15 17 13 -1
14 19 15 20 -1
100
*/