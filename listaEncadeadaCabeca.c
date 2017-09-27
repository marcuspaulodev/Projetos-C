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

tElemento* inicializarListaCabeca();
void percorrer(tELemento* lista);

int main()
{
    int opcao;

    tElemento* l1 = inicializarListaCabeca;

    do{

        printf("\n");
		printf("MENU: Lista simplesmente encadeada \n");
        printf("1-Percorrer \n");
        printf("2-Proximo ID (na cabeca) \n");
        printf("3-Buscar Elemento Atual \n");
        printf("4-Buscar Elemento Anterior \n");
        printf("5-Inserir no Inicio \n");
        printf("6-Inserir no Fim \n");
        printf("7-Inserir (depois de...) \n");
        printf("8-Remover \n");
        printf("0-Sair \n");
        printf("Qual sua opcao? ");
        scanf("%d", &opcao);
        printf("\n");
            
        switch(opcao)
        {
            case 1:printf("Percorrer\n");
                   break;
                
            case 2: printf("PROXIMO ID (na cabeca) \n");
                   break;

            case 3: printf("BUSCAR NORMAL \n");
                   break;

            case 4: printf("BUSCAR ANTERIOR \n");
                   break;

            case 5: printf("INSERIR INICIO \n");
                   break;

            case 6: printf("INSERIR FIM \n");
                   break;

            case 7: printf("INSERIR DEPOIS DE... \n");
                   break;

            case 8: printf("REMOVER \n");
                   break;

            case 0: printf("Saindo... \n");
                   break;

            default: printf("OPCAO INVALIDA \n");
                    break;
        }
        

        printf("\n\n");
        system("clear");        
    }
    while(opcao != 0);
    return 0;

}

tElemento* inicializarListaCabeca()
{

    tElemento* lista = (tElemento*) calloc(1,sizeof(tElemento));

    strcpy(lista->nome,"");
    lista->id = 1;
    lista->pProx = NULL;

    return lista;

}
void percorrer(tELemento* lista)
{
    tElemento* tmp;

    tmp = lista -> pProx;

    while(tmp->pProx != NULL)
    {
        printf("id = %d",tmp->id);
        printf("nome = %s", tmp->nome);
        tmp = tmp->pProx;
    }

    
}