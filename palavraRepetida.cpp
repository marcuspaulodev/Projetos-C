#include<iostream>
#include<string>

using namespace std;

int main()
{
    string ant = "";
    string atual;

    while(cin >> atual)
    {
        if(ant == atual)
        {
            cout<<"palavra repetida: "<<atual<<endl;
        }
        ant = atual;
    }

    return 0;
}