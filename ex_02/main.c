/*
| Thomas Lincoln
| 156.603
| Exercício 2
*/
#include <stdio.h>
#include <stdlib.h>

// função para calcular os livros
int calcula_livros(int vales_atuais, int custo_vale, int livros_return)
{
    // isso aqui vai comprar os livros q da com o vale
    int livros_aux = vales_atuais / custo_vale;
    // isso att o número de vales
    vales_atuais = (vales_atuais % custo_vale) + livros_aux;
  // add os livros comprados no vale com os livros atuais
  livros_return += livros_aux;

    //verifica se ainda da pra comprar vale, se não der, ele retorna o vtotal de livros
    if(vales_atuais < custo_vale){
        return livros_return;
    }
  //se ainda der pra comprar com vale ele retorna a função
    return calcula_livros(vales_atuais, custo_vale, livros_return);
 
}

int main(void)
{
    int dinheiro, preco, vale, N_testes, i, vales_atuais = 0, livros = 0, livros_aux = 0;

    scanf("%i", &N_testes);

    if (N_testes <= 10)
    {

        for (i = 0; i < N_testes; i++)
        {
            int aux = 0;
            livros = 0;
            vales_atuais = 0, dinheiro = 0, preco = 0, vale = 0;
            scanf("%i %i %i", &dinheiro, &preco, &vale);

            livros_aux = dinheiro / preco;
            vales_atuais = livros_aux;
            livros = calcula_livros(vales_atuais, vale, livros_aux);
            printf("%i \n", livros);
        }
    }
    return 0;
}