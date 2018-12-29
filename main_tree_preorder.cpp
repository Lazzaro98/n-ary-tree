/*
    coded by LazzaRo
    main
*/
#include "Stablo.h"
#include "stack_of_nodes.h"
#include"node.h"
#include <iostream>
using namespace std;
int main(){
    int b;Node* cvor;
    Stablo *stablo=new Stablo(0);
    int m=Stablo::m;
    while(true){
    cout<<"Unesite redni broj operacije koju zelite da primenite:"<<endl;
    cout<<"0. Kreiranje m-arnog stabla"<<endl;
    cout<<"1. Dodavanje cvora"<<endl;
    cout<<"2. Ispis stabla"<<endl;
    cout<<"3. Brisanje stabla"<<endl;
    cout<<"4. Odredjivanje sirine stabla"<<endl;
    cout<<"5. Ispis stabla(po redovima-nivoima)"<<endl;
    cout<<"6. Izlaz"<<endl;
    int k;cin>>k;

    switch(k){
        case 0:
            cout<<"Unesite red stabla m: ";cin>>m;cout<<endl;
            stablo=new Stablo(m);
            break;
        case 1:
            if(stablo->postoji()){
            cout<<"Unesite broj koji zelite da dodate: ";
            cin>>b;
            cvor=newNode(b);
            *stablo+=cvor;
            cout<<"Broj "<<b<<" je dodat u stablo."<<endl<<endl;
            }
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl<<endl;
            break;
        case 2:
            if(stablo->postoji())cout<<*stablo<<endl;
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl<<endl;
            break;
        case 3:
            if(stablo->postoji()){delete stablo;cout<<"Stablo je obrisano."<<endl<<endl;}
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl<<endl;
            break;
        case 4:
            if(stablo->postoji())cout<<"Sirina stabla je "<<stablo->sirinaStabla()<<endl;
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl<<endl;
            break;
        case 6:
            exit(1);
            break;
        default:
        cout<<"Takva operacija ne postoji. Pokusajte ponovo"<<endl;
            break;
        case 5:
            if(stablo->postoji()){
                cout<<"Ispis stabla po nivoima: "<<endl;
                stablo->ispis();
                cout<<endl;
            }
            else
                cout<<"ERROR: Prvo morate kreirati stablo"<<endl<<endl;
            break;
       //switch
    }//while(true)

}
}
