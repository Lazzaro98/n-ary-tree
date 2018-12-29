/*
    coded by LazzaRo
    Tree of the nodes, with overloaded operators
*/
#include <iostream>
#include "stack_of_nodes.h";
#include "node.h"
using namespace std;
int m=0;
class Stablo{
        int maxDub;
        Node* koren;
public:
    Stablo(int k){ koren=nullptr;maxDub=0;}
    Node* getKoren(){return koren;}
    void addNode(Node* newOne);
    int sirinaStabla();
    bool postoji(){return m;}
    friend ostream& operator <<(ostream& it, const Stablo& t);
    void operator+=(Node* newOne){addNode(newOne);}
    void ispis();
    ~Stablo();
};
//ispis
ostream& operator<<(ostream& it, Stablo &t){
    it<<"Stablo u preorder poretku: ";
    Stack s;
    s.push(t.getKoren());
    Node* sled;
    while(!s.isEmpty()){
        sled=s.pop();
        while(sled){
            it<<sled->i<<" ";
            for(int i=m-1;i>0;i--)
                if(sled->next[i])
                    s.push(sled->next[i]);
            sled=sled->next[0];
        }
    }
    return it<<endl;
}
//funkcija dodavanja cvora - preklopljen operator +=
void Stablo::addNode(Node* newOne){
    if(!koren){koren=newOne;return;}
    int trenutnaDub=0;
    Stack s;
    s.push(koren,trenutnaDub);
    Node* sled;
    while(!s.isEmpty()){
        trenutnaDub=s.dub();
        if(trenutnaDub>maxDub)maxDub=trenutnaDub;
        sled=s.pop();
        while(sled){
            if(trenutnaDub==(maxDub-1))
                for(int i=0;i<m;i++)
                    if(!sled->next[i]){
                        sled->next[i]=newOne;
                        Node* pom= sled->next[i];
                        pom->parent=sled;
                        return;
                    }
            for(int i=m-1;i>0 && sled->next[i-1];i--)
                if(sled->next[i])
                    s.push(sled->next[i],trenutnaDub+1);
            sled=sled->next[0];
            trenutnaDub++;
            if(trenutnaDub>maxDub && sled)maxDub=trenutnaDub;
        }
    }
    sled=koren;
    while(sled->next[0])sled=sled->next[0];
    sled->next[0]=newOne;
    maxDub++;
    return;
}
//sirina
int Stablo::sirinaStabla(){
    if(maxDub==1)return 1;
    int br1=0,br2=0,trenutnaDub=0;
    Stack s;
    s.push(koren,trenutnaDub);
    Node* sled;
    while(!s.isEmpty()){
        trenutnaDub=s.dub();
        sled=s.pop();
        while(sled){
            if(trenutnaDub==maxDub)br1++;
            if(trenutnaDub==(maxDub-1))br2++;

            for(int i=m-1;i>0;i--)
                if(sled->next[i])
                    s.push(sled->next[i],trenutnaDub+1);
            sled=sled->next[0];
            trenutnaDub++;
        }
    }
    return max(br1,br2);
}
/*int pow(int n,int k){
    int p=1;
    while(k--)p*=n;
    return p;
}*/
int adresnaFja(int dub){
    if(!dub)return dub;
    int i=0;
    while((dub--)>-1)i+=pow(m,dub);
    return i;
}
/*void Stablo::ispis(){
    if(!koren){return;}
    if(m==1)
    {
        Node *pom=koren;
        while(pom){cout<<pom<<endl;pom=pom->next[0];}
        return;
    }
    int trenutnaDub=0;
    Stack s;
    s.push(koren,trenutnaDub);
    Node* sled;
    int vel=pow(m,maxDub)/2;
    Node** nizCvorova = new Node*[vel];
    while(!s.isEmpty()){
        trenutnaDub=s.dub();
        sled=s.pop();
        while(sled){
                    int b=adresnaFja(trenutnaDub);
                    cout<<"Trenutna dubina"<<trenutnaDub <<" --- "<<b<<endl;
                    while(nizCvorova[b]!=nullptr)b++;
                    nizCvorova[b]=sled;
                   // if(m==1)cout<<nizCvorova[b]<<endl;
            for(int i=m-1;i>0;i--)
                if(sled->next[i])
                    s.push(sled->next[i],trenutnaDub+1);
            sled=sled->next[0];
            trenutnaDub++;
        }
    }
    cout<<"stigao";
    if(m>1){
    int b=1;
    int z=m;
    int zb=m;
    //int lvl=0;//level
    if(!nizCvorova[0])return;
    //for(int h=0;h<maxDub-lvl+1;h++)cout<<" ";
    cout<<nizCvorova[0]<<endl;
    //for(int h=0;h<maxDub-lvl+1;h++)cout<<" ";
    while(nizCvorova[b]){
    cout<<nizCvorova[b];
//cout<<b;
    if(b==(zb)){
        z*=m;
        zb+=z;
        cout<<endl;
        //for(int h=0;h<maxDub-lvl;h++)cout<<" ";
        //lvl++;
        }
        b++;
    }
    }
}*/
void Stablo::ispis(){
    if(!koren)return;
    int trenutnaDub=0;
    Stack s;
    s.push(koren,trenutnaDub);
    Node* sled;
    int vel=pow(m,maxDub+1);
    Node** nizCvorova=new Node*[vel];
    for(int i=0;i<vel;i++)nizCvorova[i]=nullptr;
    while(!s.isEmpty()){
        trenutnaDub=s.dub();
        sled=s.pop();
        while(sled){
            int poz=adresnaFja(trenutnaDub);
            while(nizCvorova[poz])poz++;
            nizCvorova[poz]=sled;
            if(m==1)cout<<sled<<endl;
            for(int i=m-1;i>0 && sled->next[i];i--)
                if(sled->next[i])
                    s.push(sled->next[i],trenutnaDub+1);
            sled=sled->next[0];
            trenutnaDub++;
        }
    }
    int b=1,z=m,zb=m;
    if(!nizCvorova[0])return;
    if(m>1){
    cout<<nizCvorova[0]<<endl;
    while(nizCvorova[b]){
        cout<<nizCvorova[b];
        if(b==zb){
            z*=m;
            zb+=z;
            cout<<endl;
        }
        b++;
    }
    }
}
//destruktor
Stablo::~Stablo(){
    Stack s;
    s.push(koren);
    Node* sled;
    while(!s.isEmpty()){
        sled=s.pop();
        while(sled){
            for(int i=m-1;i>0;i--)
                if(sled->next[i])
                    s.push(sled->next[i]);
            Node* pom=sled;
            sled=sled->next[0];
            delete pom;
        }
    }
    maxDub=0;
    koren=nullptr;
    m=0;
}