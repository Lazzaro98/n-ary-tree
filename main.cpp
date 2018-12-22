#include <iostream>
#define MAX_SIZE_OF_STACK 1000
using namespace std;
int m=0;

struct Node{
        int i;
        Node* parent;
        Node** next;
        Node (int br):i(br),parent(nullptr){
            next=new Node*[m];
            for(int i=0;i<m;i++)
                next[i]=nullptr;
        }
        void kopiraj(const Node&t){
            i=t.i;
            parent=t.parent;
            next=new Node*[m];
            for(int i=0;i<m;i++)
                next[i]=t.next[i];
        }
        void premesti(Node& t){
            i=t.i;
            parent=t.parent;
            next=t.next;
            t.next=nullptr;
        }
        void brisi(){delete[]next;}
        Node(const Node& t){
            kopiraj(t);
        }
        Node(Node&& t){
                premesti(t);
        }
        Node& operator=(const Node& t){
            if(this!=&t){brisi();kopiraj(t);}
            return *this;
        }
        Node& operator=(Node&& t){
            if(this!=&t){brisi();premesti(t);}
            return *this;
        }
        ~Node(){
            brisi();
        }
};
Node* newNode(int t){
    Node* x = new Node(t);
    return x;
}
class Stack{
    int top;
    Node* niz[MAX_SIZE_OF_STACK];
    int nizDub[MAX_SIZE_OF_STACK];
public:
    Stack(){top=0;}
    bool push(Node* cvor,int br);
    Node* pop();
    bool isEmpty();
    int dub();//dubina cvora koji se popuje
};

bool Stack::push(Node* cvor,int br=-1){//ako se ne unese drugi argument, nece se  cuvati na steku dubina
    if(top==MAX_SIZE_OF_STACK)
    {
        cout<<"ERROR:Overflow"<<endl;
        return false;
    }
    else
    {
        niz[++top]=cvor;
        if(br!=-1)nizDub[top]=br;
        return true;
    }
}
Node* Stack::pop(){
    if(!top)
    {
        cout<<"ERROR:Underflow";
        return 0;
    }
    else
    {
        Node* x=niz[top--];
        return x;
    }
}
bool Stack::isEmpty(){return !top;}
int Stack::dub(){return nizDub[top];}

class Stablo{
        int maxDub;
        Node* koren;
public:
        Stablo(int k);//setujemo m
        void ispis();
        void addNode(Node* newOne);
        int sirinaStabla();
        bool postoji(){return m;}
        ~Stablo();
};
Stablo::Stablo(int k){
  //  m=k;
    koren=nullptr;
    maxDub=0;
}
void Stablo::ispis(){
    cout<<"Stablo u preorder poretku: ";
    Stack s;
    s.push(koren);
    Node* sled;
    while(!s.isEmpty()){
        sled=s.pop();
        while(sled){
            cout<<sled->i<<" ";
            for(int i=m-1;i>0;i--)
                if(sled->next[i])
                    s.push(sled->next[i]);
            sled=sled->next[0];
        }
    }
    cout<<endl;
}
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

int main()
{
    int b=0;Node* cvor;
    Stablo* stablo=new Stablo(0);

    while(true){
        cout<<"Unesite redni broj operacije koju zelite da primenite:"<<endl;
    cout<<"0. Kreiranje m-arnog stabla"<<endl;
    cout<<"1. Dodavanje cvora"<<endl;
    cout<<"2. Ispis stabla"<<endl;
    cout<<"3. Brisanje stabla"<<endl;
    cout<<"4. Odredjivanje sirine stabla"<<endl;
    cout<<"5. Izlaz"<<endl;
    int k;cin>>k;
    switch(k) {
        case 0:
            cout<<"Unesite red stabla m: ";cin>>m;
            stablo=new Stablo(m);
            break;
        case 1:
            if(stablo->postoji()){
            cout<<"Unesite broj koji zelite da dodate: ";cin>>b;
            cvor=newNode(b);
            stablo->addNode(cvor);
            }
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl;
            break;
        case 2:
            if(stablo->postoji()){stablo->ispis();cout<<endl;}
            else cout<<"ERROR: Prvo morate kreirati stablo."<<endl;
            //stablo->ispisR(koren);cout<<endl;cout<<endl;
            break;
        case 3:
            if(stablo->postoji()){delete stablo;cout<<"Stablo je obrisano."<<endl;}
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl;
            break;
        case 4:
            if(stablo->postoji())cout<<"Sirina stabla je "<<stablo->sirinaStabla()<<endl;
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl;
            break;
        case 5:
            exit(1);
            break;
    }
    }
    return 0;
}
