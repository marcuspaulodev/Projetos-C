#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Struct-----------------------------------------------------------------------------------------------------------
typedef struct sprodutos{
	int id;
	char nome[100];
	float preco;
	struct sprodutos* pProx;
}tprodutos;

//Fun��es---------------------------------------------------------------------------------------------------------------
float cabecalho(tprodutos vet[]);
void dinheiro(float din);
void cartao(float car);
void vale(float val);
void linha();
void menu();
void formaPag();
tprodutos* inicializarListaComCabeca();
void inserirFim(tprodutos* pInicio, tprodutos* aux);
void buscar(tprodutos* pInicio, int id);
void cadastrarProduto(char* desc, float price, tprodutos* prod);
void removerProduto(tprodutos* prod, int id);
void alterarProduto(tprodutos* prod ,int id,char* Nome,float Preco);
tprodutos* buscarAnterior(tprodutos* prod, int id);
int buscarUltimoId(tprodutos* prod);


int main(){
	printf("1");
	//Valiaveis-------------------------------------------------------------------------------------------------------------
	int pr = 50;
	int i=0;
	int cont;
	FILE * pArquivo;
 	tprodutos *vet= (tprodutos*) calloc(pr, sizeof(tprodutos));
 	tprodutos* pInicio = inicializarListaComCabeca();
 	printf("2");
	char op;
	char opcadastro;
	//ABRE O CUPOM .TXT E L� O BANCO DE DADOS EM CSV--------------------------------------------------------------------------------------------
	FILE * Venda = fopen ("Venda.txt", "a");
				if (Venda == NULL){
					printf ("Erro na Emissao!!!");
					return 1;
				}
	
	pArquivo= fopen("arquivo.csv", "r");//Leitura o arquivo 
	tprodutos aux;
	char produto[100];
	float valor;
	//tprodutos* ler = (tprodutos*) calloc(1, sizeof(tprodutos));
	if (pArquivo == NULL){
		printf("Erro na abertura!!!");
		return 1;
	}	
	printf("3");
	while(fscanf(pArquivo, "%[^;];%f\n", &produto, &valor)!=EOF){
	
		strcpy(aux.nome,produto);
		aux.preco = valor;

		//printf("Produto = %s Valor= %.2f \n", produto, valor);
		inserirFim(pInicio, &aux);
		cont++;
	}
	printf("4");
	fclose(pArquivo);
	
	//FINALIZA A LEITURA DO BANCO DE DADOS---------------------------------------------------------------------------
	
	
	printf("5");

	//INICIALIZA��O DO LA�O DO MENU DO SISTEMA---------------------------------------------------------------------------
	do{
	menu();
	scanf("%c", &op);
		switch(op){
			case 'c':
			case 'C':{		
		
				int con, cons;	
					printf("*****TERMINAL DE CONSULTA*****\n\n");
					do{	
					
						printf("-1 PRA SAIR\n");			
						printf("INFORME O CODIGO PRA CONSULTA: ");
						scanf("%i", &con);
						if(con!=-1){
						buscar(pInicio, con);
						}
						
		
					}
					
					while(con!=-1);
					fflush (stdin);
					break;

					}
			case 'p':
			case 'P':{
						do
						{
							printf("*****CADASTRO DE PRODUTOS******\n\n");
							printf("I - INSERIR\n");
							printf("A - ALTERAR\n");
							printf("E - EXCLUIR\n");
							printf("S - VOLTAR\n");
							printf("DIGITE A OPCAO DESEJADA: ");
							scanf("%c",&opcadastro);
							fflush(stdin);
							switch(opcadastro)	
							{
								case 'i':
								case 'I':
								{
									char descricao[50];
									float preco;
									char con;
									do
									{
		
										printf("INFORME A DESCRICAO DO PRODUTO: \n");
										scanf("%s",&descricao);
										fflush(stdin);
										printf("INFORME O PRECO DO PODUTO: \n");
										scanf("%f", &preco);			
										fflush(stdin);												
										cadastrarProduto(descricao,preco,pInicio);
										printf("INSERIR UM NOVO PRODUTO?\n");
										printf("s-SIM\n");
										printf("n-NAO\n");
										scanf("%c",&con);
									}
									while(con!='n');
									fflush(stdin);
									break;
								}
								case 'e':
								case 'E':
								{	
									int rmID;
									printf("DIGITE O CODIGO DO PRODUTO QUE DESEJA EXCLUIR: ");
									scanf("%d",&rmID);
									removerProduto(pInicio,rmID);
								}
								case 'a':
								case 'A':
								{
									int altID;
									char novoNome[50];
									float novoPreco;
		
									printf("DIGITE O CODIGO DO PRODUTO QUE DESEJA ALTERAR: ");
									scanf("%d",&altID);
									
									printf("Digite o novo nome do Produto: \n");
									scanf("%s",&novoNome);
									fflush(stdin);
		
									printf("Digite o novo Preco do produto: \n");
									scanf("%f",&novoPreco);
									
									alterarProduto(pInicio,altID,novoNome,novoPreco);
								}
							}						
						}
						while(opcadastro != 's');
						fflush(stdin);
						break;
					 }
			case 'v':
			case 'V':{
				
						float total=cabecalho(vet);
						printf("\n");
						printf("TOTAL DA COMPRA===== %.2f\n\n", total);
						int fpag;
						float din, car, val,sub= 0, troco, resto= total;
						do{
							formaPag();
							scanf("%i", &fpag);
							switch (fpag){
								case 5: {
									printf("Qual o valor: ");
									scanf("%f", &din);
									if(din>total){
										dinheiro(din);
										troco= din-total;
										fprintf(Venda, "%s", "TROCO\t\t\t\t\t");
										fprintf(Venda, "%.2f", troco);
										fprintf(Venda, "%s", "\n");
										sub=total;
										fflush(stdin);
									}
									 if(din <total){
										sub+= din;
										if(resto>din){
										resto-=din;
										printf("Falta=====%.2f:\n\n ", resto);
										}
										dinheiro(din);
										fflush(stdin);
									}
									if(din==total){
										dinheiro(din);
										sub= total;
										fflush(stdin);
									}
									if(total<sub){
										troco= sub-total;
										fprintf(Venda, "%s", "TROCO\t\t\t\t\t");
										fprintf(Venda, "%.2f", troco);
										fprintf(Venda, "%s", "\n");
										sub=total;
										fflush(stdin);
									}
									
									break;
								}
								case 6: {
									printf("Qual o valor: ");
									scanf("%f", &car);
									sub+= car;
									cartao(car);
									if(resto>car){
										resto-=car;
										printf("Falta=====%.2f:\n\n ", resto);
										fflush(stdin);
										}
									break;
								}
								case 7: {
									printf("Qual o valor: ");
									scanf("%f", &val);
									sub+=val;
									vale(val);
									if(resto>val){
										resto-=val;
										printf("Falta=====%.2f:\n\n ", resto);
										fflush(stdin);
										}
									break;
								}
							}
						}while(total>sub);
							linha();
					}
			case 'i':;
			case 'I':{
				if (op== 'i' || op =='I'){
					fflush(stdin);
			
				fflush(stdin);
				}
				
				break;
			}
			case 's':;
			case 'S':
						printf("OBRIGADO PELO USO!!!\n\n");
						fflush(stdin);
						break;
					
					default:
						printf("Op��o errada!!!\n\n");
						fflush(stdin);
						break;
				}
	
}while(op!='s');
	fclose (Venda);
	printf("\n");
	system ("pause");
	return 0;
}


//FUN��ES PRA USO DO MAIN-----------------------------------------------------------------------------------------------------------
void menu(){
	printf("*****MENU*****\n\n");
						printf("C-CONSULTA PRODUTOS\n");
						printf("V-TERMINAL DE VENDA\n");
						printf("I-RELATORIO POR ID\n");
						printf("S-SAIR\n");
						printf("QUAL OPCAO DESEJA: ");
}


float cabecalho(tprodutos vet[]){
	FILE * Venda = fopen ("Venda.txt", "w");
				if (Venda == NULL){
					printf ("Erro na Emissao!!!");
					return 1;
				}
				//	tprodutos vet[50];
				
				int quant, provenda, qtiten= 0;
				float total;
		printf("*****TERMINAL DE VENDA*****\n\n");
						
						fprintf(Venda, "%s", "\t\t\tPVD TESTE\n");
						fprintf(Venda, "%s", "\t\tPDV TESTE CUPONS LTDA\n");
						fprintf(Venda, "%s", "R.CORONEU GURGEL S/N, CENTRO MOSSORO/RN \n");
						fprintf(Venda, "%s", "CNPJ: 12.123.123/0001-12\n");
						fprintf(Venda, "%s", "IE:11.123.123-1\n");
						fprintf(Venda, "%s", "-----------------------------------------------------\n");
						fprintf(Venda, "%s", "\t\t\tCUPOM FISCAL \n");
						fprintf(Venda,"%s","CODIGO");
						fprintf(Venda, "%s", "\t");
						fprintf(Venda,"%s","DESCRICAO");
						fprintf(Venda, "%s", "\t\t");
						fprintf(Venda,"%s","PRECO");
						fprintf(Venda, "%s", "\t");
						fprintf(Venda,"%s","QUANT.");
						fprintf(Venda, "%s", "\t");
						fprintf(Venda,"%s","TOTAL");
						fprintf(Venda, "%s", "\n");
						fprintf(Venda, "%s", "-----------------------------------------------------\n");
		do{	
					
						printf("-1--SAIR/-2--EXCLUIR ITEN \n");			
						printf("INFORME O PRODUTO DESEJADO: ");
						scanf("%i", &provenda);
						fflush(stdin);
						
						if(provenda>=0 && provenda <=100000){
						fflush(stdin);
						printf("CODIGO: %i  PRODUTO: %s  PRECO: %.2f\n", provenda, vet[provenda].nome, vet[provenda].preco );
						printf("Quantidade?");
						scanf("%i", &quant);
						if(quant >0){
						total += quant*vet[provenda].preco;
						
						fprintf(Venda,"%i",provenda);
						fprintf(Venda, "%s", "\t");
						fprintf(Venda, "%s", vet[provenda].nome);
						fprintf(Venda, "%s", "\t\t");
						fprintf(Venda, "%.2f X ", vet[provenda].preco);
						fprintf(Venda, "%.i", quant);
						fprintf(Venda, "%s", "\t");
						fprintf(Venda, "%.2f", quant*vet[provenda].preco);
						fprintf(Venda, "%s", "\n");
						qtiten ++;
						}						
						
					}
					else if(provenda== -2){
						fflush(stdin);
						int excluir;
						printf("INFORME O PRODUTO P/EXCLUIR: ");
						scanf("%i", &excluir);
						printf("CODIGO: %i  PRODUTO: %s  PRECO: %.2f\n", excluir, vet[excluir].nome, vet[excluir].preco );
						printf("Quantidade?");
						scanf("%i", &quant);
						if(quant >0){
						total -= quant*vet[excluir].preco;
						
						fprintf(Venda, "%s", "CANLEDADO\n");
						fprintf(Venda,"%i",excluir);
						fprintf(Venda, "%s", "\t");
						fprintf(Venda, "%s", vet[excluir].nome);
						fprintf(Venda, "%s", "\t\t");
						fprintf(Venda, "%.2f X ", vet[excluir].preco);
						fprintf(Venda, "%.i", quant);
						fprintf(Venda, "%s", "\t");
						fprintf(Venda, "%.2f", quant*vet[excluir].preco);
						fprintf(Venda, "%s", "\n");
						fprintf(Venda, "%s", "--------");
						fprintf(Venda, "%s", "\n");
						qtiten --;
						
						}						
						
					}
				}while(provenda!=-1);
				fprintf(Venda, "%s", "-----------------------------------------------------\n");
						fprintf(Venda, "%s", "TOTAL DE ITENS\t\t\t\t");
						fprintf(Venda, "%i", qtiten);
						fprintf(Venda, "%s", "\n");
						fprintf(Venda, "%s", "SUBTOTAL R$\t\t\t\t");
						fprintf(Venda, "%.2f", total);
						fprintf(Venda, "%s", "\n");
						fprintf(Venda, "%s", "-----------------------------------------------------\n");
						fprintf(Venda, "%s", "FORMA DE PAGAMENTO...\t\t\tVALOR PAGO");
						fprintf(Venda, "%s", "\n");
			fclose (Venda);
		return total;				
}

void dinheiro(float din){
		FILE * Venda = fopen ("Venda.txt", "a");
		if (Venda == NULL){
					printf ("Erro na Emissao!!!");
		}

		fprintf(Venda, "%s", "DINHEIRO\t\t\t\t");
		fprintf(Venda, "%.2f", din);
		fprintf(Venda, "%s", "\n");
		fclose(Venda);
		}
		
void cartao(float car){
		FILE * Venda = fopen ("Venda.txt", "a");
		if (Venda == NULL){
					printf ("Erro na Emissao!!!");
		}

	fprintf(Venda, "%s", "CARTAO\t\t\t\t\t");
	fprintf(Venda, "%.2f", car);
	fprintf(Venda, "%s", "\n");
	fclose(Venda);
		}
		
void vale(float val){
		FILE * Venda = fopen ("Venda.txt", "a");
		if (Venda == NULL){
					printf ("Erro na Emissao!!!");
		}

	fprintf(Venda, "%s", "VALE\t\t\t\t\t");
	fprintf(Venda, "%.2f", val);
	fprintf(Venda, "%s", "\n");
	fclose(Venda);
	}
	
void linha(){
	FILE * Venda = fopen ("Venda.txt", "a");
		if (Venda == NULL){
					printf ("Erro na Emissao!!!");
		}
		fprintf(Venda, "%s", "-----------------------------------------------------\n");
	
}
void formaPag(){
	printf("*****FORMA DE PAGAMENTO*****\n\n");
	printf("5-DINHEIRO\n");
	printf("6-CARTAO\n");
	printf("7-VALE\n");
	printf("Qual a forma de pagamento? ");
}


//INICIALIZAR LISTA---------------------------------------------------------------------------------------------
	

tprodutos* inicializarListaComCabeca()
{
	// Aloca espa�o para elemento CABE�A
    tprodutos* pInicio = (tprodutos*) calloc(1, sizeof(tprodutos));
	// Inicializa campos do elemento
	strcpy(pInicio->nome,"");
	pInicio->id = 1;
	pInicio->preco = 0.0;
    pInicio->pProx = NULL;

    return pInicio;
}

void inserirFim(tprodutos* pInicio, tprodutos* aux)
{
	// Aloca espa�o para elemento NOVO
	tprodutos* pNovo = (tprodutos*) calloc (1,sizeof(tprodutos));
	// Inicializa campos do elemento
	strcpy(pNovo->nome,aux->nome);
    pNovo->id = pInicio->id;
    pNovo->preco=aux->preco;
    pNovo->pProx = NULL; 

    // Atualiza elemento CABE�A (incrementa o pr�ximo valor do ID)
    pInicio->id = pInicio->id + 1;

	// Percorre ate o ultimo elemento
    tprodutos *p = pInicio;

    while (p->pProx != NULL) {
        p = p->pProx;
    }
    
    // Anexa elemento NOVO
    p->pProx = pNovo;
}

void buscar(tprodutos* pInicio, int id)
{
	// Inicializa��es
    tprodutos* p = pInicio->pProx; 	// Ponteiro temporario. Pulo a cabe�a da lista. 

    while (p != NULL) 	// verifica se j� chegou no final da lista
    {
        if (p->id == id)
        {
           printf("ID: %i \tProduto: %s \tPreco: %.2f\n", p->id, p->nome, p->preco);
           break;
        }

        p = p->pProx; // vai para o pProxio elemento
    }
}


void cadastrarProduto(char* desc, float price, tprodutos* prod)
{
	int lastId;
	FILE* pArquivo;
	tprodutos* newprod = (tprodutos*) calloc(1,sizeof(tprodutos));	
	
	lastId = buscarUltimoId(prod);
	
	strcpy(newprod->nome, desc);
	newprod->id = lastId;
	newprod->preco = price;
	
	pArquivo= fopen("arquivo.csv", "a");//Leitura o arquivo 
	if (pArquivo == NULL){
		printf("Erro na abertura!!!");
		//return 1;
	}	
	
	fprintf(pArquivo, "%s;%f;\n", &newprod->nome, newprod->preco);
	fclose(pArquivo);	
	
	prod->id = prod->id+1;
	
	tprodutos* p = prod;

    while (p->pProx != NULL) {
        p = p->pProx;
    }
    
    p->pProx = newprod;
	
}
void removerProduto(tprodutos* prod, int id)
{
	char produto[50];

	int i,j,cont =0;

	tprodutos* rmprod = (tprodutos*) calloc(1,sizeof(tprodutos)) ;

	FILE* pArquivo;	
	FILE* pArquivo2;

	pArquivo2 = fopen("arquivo.csv","r");
	if (pArquivo2 == NULL){
		printf("Erro na abertura!!!");
		//return 1;
	}		

	while(fscanf(pArquivo2, "%[^;];\n", &produto)!=EOF)
	{
		cont++;		
		printf("%d\n",cont);
	}

	fclose(pArquivo2);
	
	pArquivo= fopen("arquivo.csv", "w");//Leitura o arquivo 
	if (pArquivo == NULL){
		printf("Erro na abertura!!!");
		//return 1;
	}	

	rmprod = prod->pProx;

	while(rmprod->pProx != NULL)
	{
		if(rmprod->id!=id)
		{
			if(rmprod->preco !=0)
			{
				fprintf(pArquivo, "%s;%f;\n", &rmprod->nome, rmprod->preco);					
			
			}
		
		}
	rmprod = rmprod->pProx;
	}	
	fclose(pArquivo);
}
void alterarProduto(tprodutos* prod ,int id,char* Nome,float Preco)
{
	
	int i,cont = 0;	

	char produto[50];

	FILE* pArquivo;	
	FILE* pArquivo2;

	tprodutos* altProd = (tprodutos*) calloc(1,sizeof(tprodutos));

	pArquivo2 = fopen("arquivo.csv","r");
	if (pArquivo2 == NULL){
		printf("Erro na abertura!!!");
		//return 1;
	}		

	while(fscanf(pArquivo2, "%[^;];\n", &produto)!=EOF)
	{
		cont++;		
	}

	fclose(pArquivo2);
	
	pArquivo= fopen("arquivo.csv", "w");//Leitura o arquivo 
	if (pArquivo == NULL){
		printf("Erro na abertura!!!");
		//return 1;
	}	

	altProd = prod->pProx;

	while(altProd->pProx !=NULL)
	{
		if((altProd->id==id) && (altProd->preco !=0))
		{
	
			fprintf(pArquivo, "%s;%f;\n", Nome, Preco);
		
		}
		else
		{
			if(altProd->preco !=0)
			{
				fprintf(pArquivo, "%s;%f;\n", &altProd->nome, altProd->preco);					
			
			}
		}
	altProd = altProd->pProx;
	}	
	fclose(pArquivo);				

}
int buscarUltimoId(tprodutos* prod)
{
	int i=0;
	tprodutos* p = prod->pProx;

	if(p == NULL)
	{
		return prod->id;
	}
		
	else
	{
	
		while (p != NULL)
		{
			//printf("Entrou laco\n");
			if(p->pProx == NULL)
			{
			//	printf("%d",i);
				return p->id;
			}
			p = p->pProx;		
		}
	}
}

tprodutos* buscarAnterior(tprodutos* prod, int id)
{
	// Inicializa��es
    tprodutos* p 	  = prod; 	// Ponteiro temporario. N�O ignoro o elemento inicial!
	tprodutos* result = NULL;

	if(prod->pProx == NULL) 	// Verifica se lista � vazia
	{
		result = NULL;
	}	
	else
	{
        result = prod;

		while (p != NULL)
    	{
	        if (p->id == id) {
	           return result;
	        }

			result = p;		// Armazena o ponteiro anterior
        	p = p->pProx;
    	}
	}

    return NULL;
}
