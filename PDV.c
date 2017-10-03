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

//Funções---------------------------------------------------------------------------------------------------------------
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


int main(){
	//Valiaveis-------------------------------------------------------------------------------------------------------------
	int pr = 50;
	int i=0;
	int cont;
	FILE * pArquivo;
 	tprodutos *vet= (tprodutos*) calloc(pr, sizeof(tprodutos));
 	tprodutos* pInicio = inicializarListaComCabeca();
 	
	char op;
	//ABRE O CUPOM .TXT E LÊ O BANCO DE DADOS EM CSV--------------------------------------------------------------------------------------------
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
	
	while(fscanf(pArquivo, "%[^;];%f\n", &produto, &valor)!=EOF){
	
		strcpy(aux.nome,produto);
		aux.preco = valor;

		//printf("Produto = %s Valor= %.2f \n", produto, valor);
		inserirFim(pInicio, &aux);
		cont++;
	}
	
	fclose(pArquivo);
	
	//FINALIZA A LEITURA DO BANCO DE DADOS---------------------------------------------------------------------------
	
	
	

	//INICIALIZAÇÃO DO LAÇO DO MENU DO SISTEMA---------------------------------------------------------------------------
	do{
	menu();
	scanf("%c", &op);
		switch(op){
			case 'c':;
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
	// Aloca espaço para elemento CABEÇA
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
	// Aloca espaço para elemento NOVO
	tprodutos* pNovo = (tprodutos*) calloc (1,sizeof(tprodutos));
	// Inicializa campos do elemento
	strcpy(pNovo->nome,aux->nome);
    pNovo->id = pInicio->id;
    pNovo->preco=aux->preco;
    pNovo->pProx = NULL; 

    // Atualiza elemento CABEÇA (incrementa o próximo valor do ID)
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
	// Inicializações
    tprodutos* p = pInicio->pProx; 	// Ponteiro temporario. Pulo a cabeça da lista. 

    while (p != NULL) 	// verifica se já chegou no final da lista
    {
        if (p->id == id)
        {
           printf("ID: %i \tProduto: %s \tPreco: %.2f\n", p->id, p->nome, p->preco);
           break;
        }

        p = p->pProx; // vai para o pProxio elemento
    }
}


