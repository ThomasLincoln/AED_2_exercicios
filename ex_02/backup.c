/*
| Thomas Lincoln
| 156.603
| Exercício 2
*/
#include <stdio.h>
#include <stdlib.h>

// função para calcular os livros
int calcula_livro(int vales_atuais, int custo_vale, int livros) {
  if(vales_atuais < custo_vale){
    return livros;
  }else{
    livros ++;
    vales_atuais -= custo_vale;
    vales_atuais ++;
    return calcula_livro(vales_atuais, custo_vale, livros);
  }
  // while (vales_atuais >= custo_vale) {
  //   livros++;
  //   vales_atuais -= custo_vale;
  //   vales_atuais++;
  // }
  // return livros;
}

int main(void) {
  int dinheiro, preco, vale, N_testes, i, vales_atuais =0, livros = 0;

  scanf("%i", &N_testes);

  
  for (i = 0; i < N_testes; i++) {
    livros = 0;
    vales_atuais = 0;
    // printf("\n---inserção de infos---\n");
    // printf("Insira o dinheiro total: ");
    scanf("%i", &dinheiro);
    // printf("\n---------------------\n");
    // printf("Insira o preco total: ");
    scanf("%i", &preco);
    // printf("\n---------------------\n");
    // printf("Insira o vale total: ");
    scanf("%i", &vale);
    // printf("\n--------------------\n");
    // printf("dinheiro: %i, preco: %i, vale: %i\n", dinheiro, preco, vale);
    // printf("\n-------------------\n");

    while (dinheiro >= preco) {
      vales_atuais++;
      livros++;
      dinheiro -= preco;
    }
    livros = calcula_livro(vales_atuais, vale, livros);
    printf("%i", livros);
  }
  return 0;
}