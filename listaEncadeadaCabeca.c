#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct sElemento
{
    int id;
    char nome[SIZE];
    struct sELemento* pProx;
}tElemento;

tElemento* icializarListaCabeca();

int main()
{


    return 0;

}

tElemento* icializarListaCabeca()
{

    tElemento* lista = (tElemento*) calloc(1,sizeof(tElemento));

    strcpy(lista->nome,"");
    lista->id = 1;
    lista->pProx = NULL;

    return lista;

}