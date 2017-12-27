#include<iostream>
#include<string>

using namespace std;

int main()
{

    string nome;
    int idade;

    cout<<"Entre com seu primeiro nome: "<<endl;
    cin >> nome;
    cout << endl;

    cout<<"Entre com sua idade: "<<endl;
    cin>> idade;
    cout<<endl;

    cout<<"Ola "<<nome<<"(idade "<<idade<<")"<<endl;

    return 0;
}