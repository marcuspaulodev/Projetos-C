#include <stdio.h>
#include <stdlib.h> 
#define SIZE 10

int retornaMaximo(int v[], int n);

int main(){

    int vet[SIZE] = {0,2,5,7,4,3,5,9,4,1};
    int max;

    max = retornaMaximo(vet, SIZE);

    printf("Maximo = %d\n", max);

    return 0;
}

int retornaMaximo(int v[], int n)
{
    if(n == 1)
    {

           return v[0];

    }
    else
    {

        int x;
        x = retornaMaximo(v, n-1);
        if(x > v[n-1])
        {
            return x;
        }
        else
        {
            return v[n-1];
        }

    }

}