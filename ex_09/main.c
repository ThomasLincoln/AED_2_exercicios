#include <stdlib.h>
#include <stdio.h>
 
/*
 -----------------------
| Thomas Lincoln        |
| 156603
 -----------------------
*/
//Quests
//[x] Inicialização da árvore flamento
//[] Pesquisa
//[] Inserção
//[] Calculo da altura do nó
//[] Calcula da altura-negra

struct Node_vp{
    int dado; //numero do node
    int cor; //1-red 0-black
    struct Node_vp * pai;//pai do node
    struct Node_vp *direita;//filho da direita
    struct Node_vp *esquerda;//filho da esquerda
};

struct Node_vp* insere_node(struct Node_vp* raiz_aux, struct Node_vp* aux){
    if(raiz_aux == NULL){
        return aux;
    }
    if(aux->dado < raiz_aux->dado){
        raiz_aux->esquerda = insere_node(raiz_aux->esquerda, aux);
        raiz_aux->esquerda->pai = raiz_aux;
        
    }else if(aux->dado > raiz_aux->dado){
        raiz_aux->direita = insere_node(raiz_aux->direita, aux);
        raiz_aux->direita->pai = raiz_aux;
    }
    return raiz_aux;
}


//agora as funções de rotação de uma árvore e tal
//direita
void rodar_direita(struct Node_vp* node_temporario, struct Node_vp* root){
    struct Node_vp* esquerda = node_temporario->esquerda;
    node_temporario->esquerda = esquerda->direita; 
    
    if(node_temporario->esquerda){
        node_temporario->esquerda->pai = node_temporario;
    }

    esquerda->pai = node_temporario->pai;
    
    if(!node_temporario->pai){
        root = esquerda;
    }else if(node_temporario == node_temporario->pai->esquerda){
        node_temporario->pai->esquerda = esquerda;
    }else{
        node_temporario->pai->direita = esquerda;
    }
    
    esquerda->direita = node_temporario;
    node_temporario->pai = esquerda;
}

//esquerda
void rodar_esquerda(struct Node_vp *  node_temporario, struct Node_vp* root){
    struct Node_vp* direita = node_temporario->direita;
    node_temporario->direita = direita->esquerda;
    
    if(node_temporario->direita){
        node_temporario->direita->pai = node_temporario;
    }
    
    direita->pai = node_temporario->pai;
    
    if(!node_temporario->pai){
        root = direita;
    }else if(node_temporario == node_temporario->pai->esquerda){
        node_temporario->pai->esquerda = direita;
    }else{
        node_temporario->pai->direita = direita;
    }
    
    direita->esquerda = node_temporario;
    node_temporario->pai = direita;
}


//-------------função para arrumar a árvore ------------------//
void fixed_tree(struct Node_vp * raiz, struct Node_vp* node_temporario){
    struct Node_vp * pai_node_temp = NULL;
    struct Node_vp * avo_node_temp = NULL;

    while((node_temporario != raiz) && (node_temporario->cor != 0) && (node_temporario->pai->cor == 1)){
        pai_node_temp = node_temporario->pai;
        avo_node_temp = node_temporario->pai->pai;
        //primeiro vemos caso o pai do node temp é o filho esquerdo do avo de node temp
        if(pai_node_temp == avo_node_temp->esquerda){
            
            struct Node_vp* tio_node_temp = avo_node_temp->direita;
            //caso em que o tio do nodetemp é vermelho, só precisa recolorir
            
            if(tio_node_temp != NULL && tio_node_temp->cor == 1){
                avo_node_temp->cor = 1;
                pai_node_temp->cor = 0;
                tio_node_temp->cor = 0;
                node_temporario = avo_node_temp;
            }else{
                //caso node temp é o filho da direita, precisa rodar pra esquerda;
                if(node_temporario == pai_node_temp->direita){
                    rodar_esquerda(pai_node_temp, raiz);
                    node_temporario = pai_node_temp;
                    pai_node_temp = node_temporario->pai;
                }
                //caso node temp é o filho da esquerda, precisa rodar pra direita;
                rodar_direita(avo_node_temp, raiz);
                int aux_cor = pai_node_temp->cor;
                pai_node_temp->cor = avo_node_temp->cor;
                avo_node_temp->cor = aux_cor;
                node_temporario = pai_node_temp;
            }
        }else{ 
            //caso em que o pai é o filho direito do avo do node temp
            struct Node_vp * tio_node_temp = avo_node_temp->esquerda;
            //caso em que o tio do node temp é vermelho, só precisa recolorir
            if((tio_node_temp != NULL) && (tio_node_temp->cor == 1)){
                avo_node_temp->cor = 1;
                pai_node_temp->cor = 0;
                tio_node_temp->cor = 0;
                node_temporario = avo_node_temp;
            }else{
                //caso em que note temp é o filho da esquerda, precisa rodar pra direita;
                if(node_temporario == pai_node_temp->esquerda){
                    rodar_direita(pai_node_temp, raiz);
                    node_temporario = pai_node_temp;
                    pai_node_temp = node_temporario->pai;
                }
                //caso em que o note temp é filho da direita do seu pai, precisa rodar pra esquerda;
                rodar_esquerda(avo_node_temp, raiz);
                int aux_cor = pai_node_temp->cor;
                pai_node_temp->cor = avo_node_temp->cor;
                avo_node_temp->cor = aux_cor;
                node_temporario = pai_node_temp;
            }
        }
    }
    raiz->cor = 0;
}
void inorder(struct Node_vp* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->esquerda);
    printf("%d ", trav->dado);
    inorder(trav->direita);
}


int main(){
    // struct Node_vp *node_temporario = NULL;
    struct Node_vp *root = NULL;

    int n = 7;
    int a[7] = { 7, 6, 5, 4, 3, 2, 1 };
 
    for (int i = 0; i < n; i++) {
 
        // allocating memory to the node and initializing:
        // 1. color as red
        // 2. parent, left and right pointers as NULL
        // 3. data as i-th value in the array
        struct Node_vp* node_temporario
            = (struct Node_vp*)malloc(sizeof(struct Node_vp));
        node_temporario->direita = NULL;
        node_temporario->esquerda = NULL;
        node_temporario->pai = NULL;
        node_temporario->dado = a[i];
        node_temporario->cor = 1;
 
        // calling function that performs bst insertion of
        // this newly created node
        root = insere_node(root, node_temporario);
 
        // calling function to preserve properties of rb
        // tree
        fixed_tree(root, node_temporario);
    }
 
    printf("Inorder Traversal of Created Tree\n");
    inorder(root);


    // printf("teste\n");
    return 0;
}