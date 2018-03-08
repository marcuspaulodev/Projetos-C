#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin;
    double num;

    fin.open("conjunto.txt");
    if(!fin.is_open())
    {
        cout<<"Abertura do Arquivo Falhou"<<endl;
        return 0;
    }

    fin>>wt;

    while(fin.good)
    {
        cout<<wt<<endl;
        fin >> wt;
    }
    if(fin.eof())
    {
        cout<<"Fim do Arquivo"<<endl;
    }
    else
    {
        if(fin.fail)
        {
            cout<<"Tipo incorreto";
        }
        else
        {
            cout<<"Erro não catalogado"
        }
    }
    fin.close();


    return 0;

}