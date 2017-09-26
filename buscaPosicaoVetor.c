#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define SIZE 10

int buscaPosicao(int v[],int valor);

int main()
{
    int i;
    int vet[SIZE];
    int vl, pos;

    srand(time(NULL));

    for(i = 0; i < SIZE ; i++)
    {
        vet[i] = rand() % SIZE +1;

		printf("Valor  %i : %i" , i+1,  vet[i]);
        printf("\n");
    }

    printf("Digite o Valor que Deseja Buscar: \n");
    scanf("%d",&vl);

    pos = buscaPosicao(vet, vl);

    printf("Posicao do Valor %d eh %d", vl, pos);

    return 0;

}

int buscaPosicao(int v[], int valor)
{

  int i = 0;  

  if(valor == 0)
  {
     return -1;
  }
  else
  {
      while(i < SIZE)
      {
        if (valor == v[i])
        {

            return i;   
             
        }
        else
        {
            i++;
        }
        
      }  return -1;

  }

}