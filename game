#include <iostream>
#define MAX_SIZE_OF_STACK 1000
using namespace std;
int m=0;

//Definicija cvora
struct Node{
        char stanje;
        char mat[5][5];
        Node* parent;
        Node** next;
        Node (char **x,char st):stanje(st),parent(nullptr){

            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                    mat[i][j]=x[i][j];


            next=new Node*[m];
            for(int i=0;i<m;i++)
                next[i]=nullptr;
        }
        void kopiraj(const Node&t){

            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                    mat[i][j]=t.mat[i][j];

            parent=t.parent;
            next=new Node*[m];
            for(int i=0;i<m;i++)
                next[i]=t.next[i];
        }
        void premesti(Node& t){
            parent=t.parent;
            next=t.next;
             for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                mat[i][j]=t.mat[i][j];

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
Node* newNode(char **k,char st){
    Node* x = new Node(k,st);
    return x;
}
bool imaPotomke(Node* x){//za m=3
    for(int i=0;i<4;i++)
        if(x->next[i])return true;
    return false;
}
//Definicja steka
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

//Definicija stabla
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
    ~Stablo();
};
//ispis
/*ostream& operator<<(ostream& it, Stablo &t){
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
}*/
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

void Stablo::addNodeModif(Node* newOne){
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

void setujTablu(char**mat){
    for(int j=0;j<4;j++){
        int br=0;
        for(int i=0;i<4;i++)
            if(mat[i][j])br++;
        mat[4][j]=br;
    }
}
bool full(char**mat){
    if(mat[4][0] || mat[4][1] || mat[4][2] || mat[4][2])return true;
    return false;
}
char proveriPobednika(char**mat){
    char igraci[1]={'r','b'};
    for(int k=0;k<2;k++)
        for(int i=0;i<3;i++)
            for(int j=2;j<5;j++)
                {
                    if(mat[i][j]==igraci[k] && mat[i][j-1]==igraci[k] && mat[i][j-2])
                        return igraci[k];
                    if(mat[j][i]==igraci[k] && mat[j-1][i]==igraci[k] && mat[j-2][i]==igraci[k])
                        return igraci[k];
                    if(mat[i][j-2]==igraci[k] && mat[i+1][j-1]==igraci[k] && mat[i+2][j]==igraci[k])
                        return igraci[k];
                    if(mat[j-2][i]==igraci[k] && mat[j-1][i+1]==igraci[k] && mat[j][i+2]==igraci[k])
                        return igraci[k];
                }
    return '0';
}

Stablo napraviStabloIgre(Stablo t,char**mat){
    int potez=0;
    while(!full(mat)){
        Stack s;
        s.push(t.getKoren());
        Node* sled;
        while(!s.isEmpty()){
            sled=s.pop();
            while(sled){
                //obrada
                if(!imaPotomke(sled) && !sled->stanje)
                    for(int i=0;i<4;i++){
                        addNodeModif(mat,i,potez);
                    }
                //obrada
                for(int i=3;i>0;i--)
                    if(sled->next[i])
                        s.push(sled->next[i]);
                sled=sled->next[0];
            }
        }
        potez=(potez+1)%2;
    }
}

int main(){
    int b;Node* cvor;
    Stablo *stablo=new Stablo(0);

    while(true){
    cout<<"Unesite redni broj operacije koju zelite da primenite:"<<endl;
    cout<<"0. Kreiranje m-arnog stabla"<<endl;
    cout<<"1. Dodavanje cvora"<<endl;
    cout<<"2. Ispis stabla"<<endl;
    cout<<"3. Brisanje stabla"<<endl;
    cout<<"4. Odredjivanje sirine stabla"<<endl;
    cout<<"5. Izlaz"<<endl;
    int k;cin>>k;

    switch(k){
        case 0:
            cout<<"Unesite red stabla m: ";cin>>m;
            stablo=new Stablo(m);
            break;
        case 1:
            if(stablo->postoji()){
            cout<<"Unesite broj koji zelite da dodate: ";
            cin>>b;
            cvor=newNode(b);
            *stablo+=cvor;
            }
            else cout<<"ERROR: Prvo morate kreirati stablo"<<endl;
            break;
        case 2:
            if(stablo->postoji())cout<<*stablo<<endl;
            else cout<<"ERROR: Prvo morate kreirati stablo."<<endl;
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
        default:
        cout<<"Takva operacija ne postoji. Pokusajte ponovo"<<endl;
            break;
        }
       //switch
    }//while(true)

}
