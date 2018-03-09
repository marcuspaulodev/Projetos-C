#include <iostream>
#include <fstream>
#define M 1531
using namespace std;

void inicializaHash(int v[], int tam); 
void insereHash(int v[],int chave);
int funcaoHash(int n);

int num;

int main()
{

    int qtLidos, numero;

    int hash[M];

    cout << "Digite um numero inteiro: "<<endl;
    cin>>num;

    cout << "Numero digitado: " << num << endl;

    ifstream fin;

    inicializaHash(hash,M);

    fin.open("conjunto.txt");
    if(!fin.is_open())
    {
        cout<<"Abertura do Arquivo Falhou"<<endl;
        return 0;
    }
    else
    {

        fin>>numero;
        qtLidos = 0;

        while(fin.good())
        {
            fin>>numero;
            ++qtLidos;
        }

        if(fin.eof())
        {
            cout<<"Fim do Arquivo"<<endl;
            cout<<"Total de Numeros Lidos: "<<qtLidos<<endl;
        }        


    }

    return 0;

}

void inicializaHash(int v[], int tam)
{
 
    int i;

    for(i = 0; i < tam; i++){
        v[i] = NULL;
    }


}
void insereHash(int v[],int chave)
{

}
int funcaoHash(int n)
{
    return (n%TAM);

}