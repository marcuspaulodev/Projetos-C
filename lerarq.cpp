#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin;
    double num;
    int qtLidos, test;

    cout<<"Digite um Numero para Verificar se é Valido: "<<endl;
    cin>>test;

    fin.open("conjunto.txt");
    if(!fin.is_open())
    {
        cout<<"Abertura do Arquivo Falhou"<<endl;
        return 0;
    }

    fin>>num;
    qtLidos = 0;

    while(fin.good())
    {
        if(test == num)
        {
            cout<<"Numero "<<num<<"Encontrado "<<endl;
            break;
        }
        cout<<num<<endl;
        fin >> num;
        ++qtLidos;
    }
    if(fin.eof())
    {
        cout<<"Fim do Arquivo"<<endl;
        cout<<"Total de Numeros Lidos: "<<qtLidos<<endl;
    }
    else
    {
        if(fin.fail())
        {
            cout<<"Tipo incorreto";
        }
        else
        {
            cout<<"Erro não catalogado";
        }
    }
    fin.close();


    return 0;

}