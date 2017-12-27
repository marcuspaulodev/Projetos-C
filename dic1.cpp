#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    vector<string> palavras;
    string temp;
    while(cin>>temp)
    {
        palavras.push_back(temp);
    }
    cout<<"Numero de palavras digitadas: "<< palavras.size()<<endl;

    sort(palavras.begin(),palavras.end());

    for(int i=0;i<palavras.size();++i)
    {
        if(i==0||palavras[i-1]!=palavras[i])
        {
            cout <<palavras[i]<<endl;
        }
    }

    return 0;
}