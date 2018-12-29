#include <iostream>
using namespace std;
int main()
{
    Node cvor(mat,'0');
    while(true){
    cout<<endl<<"Unesite redni broj operacije koju zelite da primenite: "<<endl;
    cout<<" 0. Kreiraj (novo) stablo igre."<<endl;
    cout<<" 1. Pronadji pobedu za crvenog."<<endl;
    cout<<" 2. Pronadji pobedu za plavog."<<endl;
    cout<<"Unesite redni broj operacije koju zelite da pozovete:";
    Stablo *stablo;
    int op;cin>>op;
    switch(op){
            case 0:
               cout<<endl<<"Unesite tablu igre(r-crveni igrac, b-plavi igrac, . - prazn0 polje): "<<endl;
               for(int i=0;i<5;i++)
                    for(int j=0;j<5;j++)
                        cin>>cvor.mat[i][j];
                for(int i=0;i<5;i++)
                    for(int j=0;j<5;j++)
                        if(cvor.mat[i][j]=='.')cvor.mat[i][j]=' ';//unosim ih kao tackice jer cin ne prepoznaje razmak
                setujTablu(cvor.mat);
                cout<<endl<<"Pravi se stablo...";
                stablo=napraviStabloIgre(&cvor);
                cout<<endl<<"Stablo je napravljeno."<<endl;
            break;
            case 1:
                if(stablo->postoji())nadjiPobedu(stablo,'r');
                else cout<<"Prvo napravite stablo pa pozovite ovu operaciju."<<endl;
            break;
            case 2:
                if(stablo->postoji())nadjiPobedu(stablo,'b');
                else cout<<"Prvo napravite stablo pa pozovite ovu operaciju."<<endl;
            break;
            case 3:
                exit(1);
                break;
            case 121:
                cout<<"Broj cvorova:"<<brCv;
            break;
            default:
                cout<<"Takva operacija ne postoji, pokusajte ponovo."<<endl;
                break;
    }
    }
    return 0;
}
