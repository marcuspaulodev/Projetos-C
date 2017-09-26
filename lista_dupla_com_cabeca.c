#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Autor: Bruno Monteiro
// Objetivo: Lista duplamente encadeada com elemento cabeça


// Tipo do Elemento
typedef struct sElemento
{
    int id;		    // ID
    char nome[30];	// Nome
    struct sElemento* ante;	// Ponteiro para elemento anterior
    struct sElemento* prox;	// Ponteiro para elemento próximo
} tElemento;



// Assinaturas das funções: (DICA: implementar nessa ordem facilita)
tElemento* inicializarListaDuplaComCabeca();
int inserirInicio(tElemento* inicio, char* nome);
int percorrer(tElemento* inicio);
tElemento* buscar(tElemento* inicio, int key);
int inserirFim(tElemento* inicio, char* nome);
void inserirDepoisDe(tElemento* pInicio, char* nome, int key);
tElemento* remover(tElemento* inicio, int key);


tElemento* inicializarLista()
{
	// Aloca espaço para elemento CABEÇA
	tElemento* lista = (tElemento*) malloc( sizeof(tElemento) );
    // Inicializa campos do elemento
	lista->id = 1;
    strcpy(lista->nome, "");
    lista->ante = NULL;
    lista->prox = NULL;
    
    return lista;
}


int inserirInicio(tElemento* inicio, char* nome)
{
    // Aloca espaço para elemento NOVO
    tElemento *novo = (tElemento*) malloc( sizeof(tElemento) );
    // Inicializa campos do elemento
	novo->id = inicio->id;
	strcpy(novo->nome, nome);
	novo->ante = NULL;
    novo->prox = NULL;
    
    // Atualiza elemento cabeça
    inicio->id = inicio->id + 1;

    // Anexar
    novo->ante = inicio;
    novo->prox = inicio->prox;

	// OBS: ponteiro  segundo  faz backup de  inicio->prox
    tElemento *segundo = inicio->prox;
    inicio->prox = novo;
    
    if(segundo != NULL) {
        segundo->ante = novo;
    }
}


int percorrer(tElemento* inicio)
{
	// Inicializações
    int i = 0;						// Quantidade de elementos
    tElemento* p = inicio->prox; 	// Ponteiro temporario. Pulo o elemento cabeça.

	// verifica se lista está vazia
    if(p == NULL) {
        printf("Lista Vazia!!! \n");
		return 0;
    }

	// Percorro lista
    while(p != NULL)
    {
        i++;
        printf("i: %d \n", i );
        printf("ID: %d \n", p->id );
        printf("NOME: %s \n", p->nome );
        printf("p = %d \n", p);
        printf("ante = %d \n", p->ante);
        printf("prox = %d \n\n", p->prox);
        p = p->prox; // vai para o próximo elemento
    }

	printf("Quantidade de Elementos = %d \n", i);
    return i; // retorna a quantidade de elementos
}


tElemento* buscar(tElemento* inicio, int key)
{
	// Inicializações
    tElemento* p = inicio->prox;	// Ponteiro temporario. Pulo a cabeça da lista. 
    tElemento* result = NULL;		// Ponteiro que retornará o elemento encontrado.
    
    while(p != NULL) 	// verifica se já chegou no final da lista
    {
        if(p->id == key) 
        {
            result = p;
            break;
        }

        p = p->prox; // vai para o próximo elemento
    }

    return result;
}


int inserirFim(tElemento* inicio, char* nome)
{
	// Aloca espaço para elemento NOVO
    tElemento *novo = (tElemento*) malloc( sizeof(tElemento) );
	// Inicializa campos do elemento
    novo->id = inicio->id;
    strcpy(novo->nome, nome);
	novo->ante = NULL;
    novo->prox = NULL;

	// Atualiza elemento CABEÇA (incrementa o próximo valor do ID)
    inicio->id = inicio->id + 1;

	// Percorre ate o ultimo elemento
    tElemento *p = inicio;

    while(p->prox != NULL) {
        p = p->prox;
    }

	// Anexa elemento NOVO
	novo->ante = p;
	novo->prox = NULL;

    p->prox = novo;
}


void inserirDepoisDe(tElemento* inicio, char* nomeNovo, int key)
{
	// Aloca espaço para elemento NOVO
	tElemento* novo = (tElemento*) malloc(sizeof(tElemento));
	// Inicializa campos do elemento
	novo->id = inicio->id;
	strcpy(novo->nome, nomeNovo);
    novo->ante = NULL;
    novo->prox = NULL;

	// Atualiza elemento CABEÇA (incrementa o próximo valor do ID)
    inicio->id = inicio->id + 1;

    // Antecessor
    tElemento* p = buscar(inicio, key);

	if(p == NULL)  // Verifica se o criterio existe
	{
        printf("Criterio invalido \n");
	}
	else
	{
		// Anexa elemento NOVO (dica: comece atribuindo os campos NULL)
    	novo->prox = p->prox;
		novo->ante = p;

		// OBS: ponteiro  segundo  faz backup de  p->prox
	    tElemento *segundo = p->prox;
	    p->prox = novo;
	    
	    if(segundo != NULL) {
	        segundo->ante = novo;
	    }
	}
}


tElemento* remover(tElemento* inicio, int key)
{
    tElemento* p = buscar(inicio, key);
    
    if(p == NULL)
    {
        printf("ID nao encontrado \n");
    }
    else
    {
        // Faz backup dos elementos ao redor de P
        tElemento* esquerda = p->ante;
        tElemento* direita  = p->prox;            
        
        // Anexar
        esquerda->prox = direita;
    
        // Verifica se é o último elemento, pra evitar NULL
        if(direita != NULL) {
            direita->ante = esquerda;
        }
        
        // Isola o elemento recém removido
        p->ante = NULL;
        p->prox = NULL;
    }

    return p;
}



int main()
{    
    tElemento* lista1 = inicializarLista();

    int op;
    int id;
    char nome[30];
    tElemento *result;

    do
    {
    	printf("MENU: Lista duplamente encadeada \n");
        printf("1 - Percorrer \n");
		printf("2 - Proximo ID (na cabeca) \n");
	    printf("3 - Buscar Elemento \n");
        printf("4 - Inserir no Inicio \n");
        printf("5 - Inserir no Fim \n");
		printf("6 - Inserir (depois de...) \n");
        printf("7 - Remover \n");
        printf("0 - Sair \n");
    
        printf("Opcao: ");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
                printf("PERCORRER \n");
                percorrer(lista1);
                break;

			case 2: printf("PROXIMO ID (na cabeca) \n");
                    printf("maior = %d \n", lista1->id);
                    break;

            case 3:
                printf("BUSCAR ELEMENTO \n");
                printf("Qual a chave? ");
                scanf("%d", &id);
                result = buscar(lista1, id);
                if(result != NULL) {
                    printf("result = %d \n", result);
                    printf("ID: %d \n", result->id );
                    printf("NOME: %s \n\n", result->nome );
                }
                else {
                    printf("result VAZIO");
                }
                break;

            case 4:
                printf("Inserir no Inicio \n");
                printf("Nome: ");
                scanf("%s", nome);
                inserirInicio(lista1, nome);
                break;

            case 5:
                printf("Inserir no Fim \n");
                printf("Nome: ");
                scanf("%s", nome);
                inserirFim(lista1, nome);
                break;

            case 6: printf("INSERIR DEPOIS DE... \n");
                    printf("Inserir depois de qual chave? ");
                    scanf("%d", &id);
					printf("Qual o nome? ");
                    scanf("%s", &nome);
                    inserirDepoisDe(lista1, nome, id);
                    break;

            case 7:
                printf("Remover \n");
                printf("ID: ");
                scanf("%d", &id);
                result = remover(lista1, id);
                if(result != NULL) {
                    printf("result = %d \n", result);
                    printf("ID: %d \n", result->id );
                    printf("NOME: %s \n\n", result->nome );
                    free(result);
                }
                else {
                    printf("result VAZIO");
                }
                break;

            case 0:
                printf("Saindo... \n");
                break;

            default: 
                printf("INVALIDO \n");
                break;
        }

		printf("\n\n");
        system("pause"); 	// congela a tela para ver o resultado
        system("cls");		// limpa tela

    }
    while( op != 0);
    

    system("pause");
    return 0;
}
