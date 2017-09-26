#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define SIZE 10

int buscaPosicao(int v[],int valor);

int main()
{
    int i;
    int vet[SIZE];

    srand(time(NULL));

    for(i = 0; i < SIZE ; i++)
    {
        vet[i] = rand() % SIZE +1;

		printf("Valor  %i : %i" , i+1,  vet[i]);
        printf("\n");
    }

    return 0;

}

int buscaPosicao(int v[], int valor)
{

  if(valor == 0)
  {
     return -1;
  }
  else
  {
        
  }

  return 

}