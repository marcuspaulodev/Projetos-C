#include <stdio.h>
#include <stdlib.h> 
#define SIZE 10

int maximoValor(int v[], int n);

int main()
{
    int vet[SIZE] = {0,2,5,7,4,3,5,9,4,1};
    int maximo;
    
    maximo = maximoValor(vet, SIZE);

    printf("Maximo Valor = %d\n",maximo);

    return 0;

}
int maximoValor(int v[], int n)
{
    int i = 0;
    int temp;
    int max = 0;

    while (i < n-1 )
    {
        temp = v[i];
        
        if (temp > max)
        {
            max = temp;
        }

        i++;
    }
    return max;
}