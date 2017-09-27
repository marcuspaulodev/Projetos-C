#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Struct-----------------------------------------------------------------------------------------------------------
typedef struct produtos{
	int id;
	char nome[50];
	float preco;
	struct sElemento* pProx;
}tprodutos;

//Funções---------------------------------------------------------------------------------------------------------------
float cabecalho(tprodutos vet[]);
void dinheiro(float din);
void cartao(float car);
void vale(float val);
void linha();
void menu();
void inserirInicio(tprodutos* pInicio, char* nome, float preco, int id);
void cadastrarProduto(char* desc, float price, tprodutos* prod);
int buscarUltimoId(tprodutos* prod);
void removerProduto(tprodutos* prod, int id);
tprodutos* buscarAnterior(tprodutos* prod, int id);

tprodutos* inicializarListaComCabeca()
{
	// Aloca espaço para elemento CABEÇA
    tprodutos* pInicio = (tprodutos*) calloc(1, sizeof(tprodutos));
	// Inicializa campos do elemento
	strcpy(pInicio->nome, "");
	pInicio->id = 1;
	pInicio->preco = -1;
    pInicio->pProx = NULL;

    return pInicio;
}


int main(){
	//Valiaveis-------------------------------------------------------------------------------------------------------------

	int pr = 50;
	int i=0;
	int cont;
	FILE * pArquivo;

 	tprodutos *vet= (tprodutos*) calloc(pr, sizeof(tprodutos));
	char op, opcadastro;

	//ABRE O CUPOM .TXT E LÊ O BANCO DE DADOS EM CSV--------------------------------------------------------------------------------------------
	FILE * Venda = fopen ("Venda.txt", "a");
				if (Venda == NULL){
					printf ("Erro na Emissao!!!");
					return 1;
				}
	
	pArquivo= fopen("arquivo.csv", "r");//Leitura o arquivo 
	char produto[40];
	float valor;
	int id;

	if (pArquivo == NULL){
		printf("Erro na abertura!!!");
		return 1;
	}	

	while(fscanf(pArquivo, "%[^;];%f;%d\n", &produto, &valor, &id)!=EOF){
		vet[i].id= id;
		strcpy(vet[i].nome, produto);
		vet[i].preco= valor;
		inserirInicio(vet, vet[i].nome, vet[i].preco, vet[i].id);
		cont++;
		i++;
	}

	fclose(pArquivo);
	
	//FINALIZA A LEITURA DO BANCO DE DADOS--------------------------------------------------------------------------	

	//INICIALIZAÇÃO DO LAÇO DO MENU DO SISTEMA---------------------------------------------------------------------------
	tprodutos *p= (tprodutos*) calloc(pr, sizeof(tprodutos));

	do{
	menu();
	scanf("%c", &op);
	fflush(stdin);
		switch(op){
			case 'c':
			case 'C':
			{
				char con = 's';
				char descricao[50];
				float preco;
				do
				{
	
					printf("------------CADASTRO DE PRODUTOS-----------------\n");
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
							do
							{

								printf("INFORME A DESCRICAO DO PRODUTO: \n");
								scanf("%s",&descricao);
								fflush(stdin);
								printf("INFORME O PRECO DO PODUTO: \n");
								scanf("%f", &preco);			
								fflush(stdin);												
								cadastrarProduto(descricao,preco,vet);
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
							removerProduto(vet,rmID);
						}
					}
				}
				while(con!='s');
				fflush(stdin);
				break;
							
			}	
			case 'p':
			case 'P':{		
		
				int con, cons;	
					printf("*****TERMINAL DE CONSULTA*****\n\n");
					do{	
					
						printf("-1 PRA SAIR\n");			
						printf("INFORME O CODIGO PRA CONSULTA: ");
						scanf("%i", &con);
						if(con!=-1){
						int cons= pesquisaLinear(vet, pr, con);
						printf("CODIGO: %i  PRODUTO: %s  PRECO: %.2f\n", vet[cons].id , vet[cons].nome, vet[cons].preco );
						}
						
		
				}while(con!=-1);
				fflush (stdin);
				break;
					}
			case 'v':;
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
				//bubble( vet, cont );
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
						printf("Opção errada!!!\n\n");
						fflush(stdin);
						break;
				}
	
}while(op!='s');
	fclose (Venda);
	printf("\n");
	system ("pause");
	return 0;
}


//FUNÇÕES PRA USO DO MAIN-----------------------------------------------------------------------------------------------------------
void menu(){
	printf("*****MENU*****\n\n");
						printf("C-CADASTRO DE PRODUTOS\n");
						printf("P-CONSULTA PRODUTOS\n");
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
					//return 1;
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
					//return 1;
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
					//return 1;
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
					//return 1;
		}
		fprintf(Venda, "%s", "-----------------------------------------------------\n");
	
}
void formaPag()
{
	printf("*****FORMA DE PAGAMENTO*****\n\n");
	printf("5-DINHEIRO\n");
	printf("6-CARTAO\n");
	printf("7-VALE\n");
	printf("Qual a forma de pagamento? ");
}

int pesquisaLinear(tprodutos *colecao, int n, int chave){
	int i;
	for(i=0; i<=n; i++){
		if(chave== colecao[i].id)
		return i;
	}
}

void inserirInicio(tprodutos* pInicio, char* nome, float preco, int id)
{
	// Aloca espaço para elemento NOVO
	tprodutos* pNovo = (tprodutos*) malloc(sizeof(tprodutos));
	// Inicializa campos do elemento
	strcpy(pNovo->nome, nome);
    pNovo->id = pInicio->id;
	pNovo->pProx = NULL; 
    
	// Atualiza elemento CABEÇA (incrementa o próximo valor do ID)
    pInicio->id = pInicio->id + 1; 

	// Anexa elemento NOVO (cuidado com a ordem! Dica: comece atribuindo os campos NULL)
	pNovo->pProx = pInicio->pProx;
//	pInicio->pProx = pNovo;
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
	
	fprintf(pArquivo, "%s;%f;%d\n", &newprod->nome, newprod->preco, newprod->id);
	fclose(pArquivo);	
	
	prod->id = prod->id+1;
	
	tprodutos* p = prod;

    while (p->pProx != NULL) {
        p = p->pProx;
    }
    
    p->pProx = newprod;
	
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
	// Inicializações
    tprodutos* p 	  = prod; 	// Ponteiro temporario. NÃO ignoro o elemento inicial!
	tprodutos* result = NULL;

	if(prod->pProx == NULL) 	// Verifica se lista é vazia
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

void removerProduto(tprodutos* prod, int id)
{
	char produto[50];

	int i,j,cont =0;

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

	printf("Abre arquivo\n");
	
	pArquivo= fopen("arquivo.csv", "w");//Leitura o arquivo 
	if (pArquivo == NULL){
		printf("Erro na abertura!!!");
		//return 1;
	}	

	printf("Arquivo aberto\n");

	while(i <= cont)
	{
		if(i!=id)
		{
			if(prod[i].preco !=0)
			{
				fprintf(pArquivo, "%s;%f;%d\n", &prod[i].nome, prod[i].preco, prod[i].id);					
			
			}
		
		}
	i++;
	}	
	fclose(pArquivo);
}
