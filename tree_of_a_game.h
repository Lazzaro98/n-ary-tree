/*
        coded by LazzaRo
*/
#include <iostream>
#include "stack_of_a_game.h"
#include "node_of_a_game.h"
using namespace std;
class Stablo{
        int maxDub;
        Node* koren;
public:
    Stablo(int k){ m=k;koren=nullptr;maxDub=0;}
    Node* getKoren(){return koren;}
    void addNode(Node* newOne);
    int sirinaStabla();
    bool postoji(){return m;}
    friend ostream& operator <<(ostream& it, const Stablo& t);
    void operator+=(Node* newOne){addNode(newOne);}
    void setKoren(Node* cvor){koren=cvor;}
    ~Stablo();
};  ///odavde


Stablo* napraviStabloIgre(Node* cvor){
    brCv=0;
    Stablo *t = new Stablo(5);
    //random prvi igrac:
    char igraci[2]={'r','b'};
    srand(time(NULL));
    int igr=rand()%2;
    char igrac=igraci[(igr+1)%2];
    cout<<endl<<"Prvi igrac: "<<igraci[igr]<<endl;
    t->setKoren(cvor);
    Stack s;
    s.push(t->getKoren());
    Node* sled;//ne poziva konstruktor jer je pokazivac, pa cu posle rucno postaviti pointere na nullptr
    cvor->igrac=igrac;
    cout<<"Koren stabla:"<<t->getKoren();
    while(!s.isEmpty()){
        sled=s.pop();
        while(sled){
            Node* noviCvor;brCv++;
            if(sled->stanje=='0' && !fullMatrix(sled->mat)){
                if(sled->igrac=='r')igrac='b';
                else igrac='r';
                for(int j=0;j<5;j++)sled->next[j]=nullptr;
                for(int j=0;j<5;j++){
                    noviCvor=new Node(sled->mat,'0');
                    int k=sled->mat[5][j]-'0';
                    if(k){
                        int br=noviCvor->mat[5][j]-'1';
                        noviCvor->mat[5][j]=br+'0';
                        noviCvor->mat[k-1][j]=igrac;
                        noviCvor->parent=sled;
                        noviCvor->stanje=proveriPobednika(noviCvor->mat);
                        noviCvor->igrac=igrac;
                        sled->next[j]=noviCvor;
                    }
                }
            }
            for(int i=4;i>0;i--)
                if(sled->next[i])
                    s.push(sled->next[i]);
            sled=sled->next[0];
        }
    }
    return t;
}

void nadjiPobedu(Stablo *t,char igrac){
    Stack s;
    s.push(t->getKoren());
    Node* sled;
    Node* pobednik;
    while(!s.isEmpty()){
        sled=s.pop();
        while(sled){
            pobednik=new Node(matx,'0');
            if(sled->stanje==igrac){
                pobednik=sled;
                goto nasao;
            }
            for(int i=4;i>0;i--)
                if(sled->next[i])
                    s.push(sled->next[i]);
            sled=sled->next[0];
        }
    }
    nasao:
    if(pobednik->stanje=='0'){
        cout<<igrac<<" ne moze nikada da pobedi."<<endl;
        return;
    }
    cout<<"Pobeda "<<igrac<<":"<<endl;
    Node* pom=pobednik;
    Stack st;
    while(pom){
        st.push(pom);
        pom=pom->parent;
        }
    int b=0;
    while(!st.isEmpty()){
        cout<<endl<<"Izgled table nakon "<<b++<<". runde:"<<endl;
        cout<<st.pop()<<endl;
    }
    cout<<"Pobedio je "<<igrac<<endl;
}
