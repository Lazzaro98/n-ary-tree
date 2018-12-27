#include <iostream>
#define MAX_SIZE_OF_STACK 100000
#include<time.h>
using namespace std;
int m=0;
int pow(int n,int k){
    int p=1;
    while(k--)p*=n;
    return p;
}
char matx[6][5]=   {'\\',' ',' ',' ','/',
                    ' ','\\',' ','/',' ',
                    ' ',' ','\\',' ',' ',
                    ' ','/',' ','\\',' ',
                    '/',' ',' ',' ','\\',
                    ' ',' ',' ',' ',' '};

void setujTablu(char (&mat)[6][5]){
    for(int j=0;j<5;j++){
        int br=0;
        for(int i=0;i<5;i++)
            if(mat[i][j]==' ')br++;
        mat[5][j]=br+'0'; // glupava konverzija nije bila automatska OK!
    }
}
int slobPolja(char mat[6][5]){
int br=0;
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(mat[i][j]==' ')br++;
    return br;
}
bool fullMatrix(char mat[6][5]){
    if(mat[5][0]!='0' || mat[5][1]!='0' || mat[5][2]!='0' || mat[5][3]!='0' || mat[5][4]!='0')return false;
    return true;
}
char proveriPobednika(char mat[6][5]){
    char igraci[2]={'r','b'};
    for(int k=0;k<2;k++){
        for(int i=0;i<5;i++)
            for(int j=0;j<3;j++)
                {
                    if(mat[i][j]==igraci[k] && mat[i][j+1]==igraci[k] && mat[i][j+2]==igraci[k])
                        return igraci[k];
                    if(mat[j][i]==igraci[k] && mat[j+1][i]==igraci[k] && mat[j+2][i]==igraci[k])
                        return igraci[k];
                }
                for(int i=0;i<3;i++)
                    for(int j=2;j<5;j++){
                    //cout<<i<<j<<endl;
                    if(mat[i][j]==igraci[k] && mat[i+1][j-1]==igraci[k] && mat[i+2][j-2]==igraci[k])
                        return igraci[k];
                   // cout<<i<<j<<endl;
                    if(mat[i][j-2]==igraci[k] && mat[i+1][j-1]==igraci[k] && mat[i+2][j]==igraci[k])
                        return igraci[k];
                }
                }
    return '0';
}

struct Node{
        char stanje;
        char mat[6][5];
        char igrac;
        Node* parent;
        Node** next;
        Node (char x[6][5],char st):stanje(st),parent(nullptr),igrac(' '){

            for(int i=0;i<5;i++)
                for(int j=0;j<5;j++)
                    mat[i][j]=x[i][j];
            setujTablu(mat);

            next=new Node*[m];
            for(int i=0;i<m;i++)
                next[i]=nullptr;
        }
        void kopiraj(const Node& t){
            stanje=t.stanje;
            for(int i=0;i<6;i++)
                for(int j=0;j<5;j++)
                    mat[i][j]=t.mat[i][j];

            parent=t.parent;
            next=new Node*[m];
            for(int i=0;i<5;i++)
                next[i]=t.next[i];
            //cout<<"Kopirajuci konstruktor pozvan"<<endl;
        }
        void premesti(Node& t){
            stanje=t.stanje;
            parent=t.parent;
            next=t.next;
             for(int i=0;i<6;i++)
                for(int j=0;j<5;j++)
                mat[i][j]=t.mat[i][j];

            t.next=nullptr;
            //cout<<"Premestajuci konstruktor pozvan"<<endl;
        }
        void brisi(){delete[]next;}
        Node(const Node& t){
            //kopiraj(t);
            cout<<"Kopirajuci pozvan;";
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
        friend ostream& operator << (ostream& ot, Node* x){
        ot<<endl;
        for(int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if(i==0 || i==6)ot<<"-";
                else if(j==0 || j==6) ot<<"|";
                else ot<<x->mat[i-1][j-1];
                }
            if(i!=6)ot<<endl;
            }
        cout<<endl<<" ";
        for(int i=0;i<5;i++)cout<<x->mat[5][i];
        cout<<endl;
        return ot;
        }

        ~Node(){
            brisi();
        }
};
bool imaPotomke(Node* x){
    for(int i=0;i<m;i++)
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
    Node* sled;
    cvor->igrac=igrac;
    cout<<"Koren stabla:"<<t->getKoren();
    while(!s.isEmpty()){
        sled=s.pop();
        while(sled){
            Node* noviCvor;
            if(sled->stanje=='0' && !fullMatrix(sled->mat)){
                if(sled->igrac=='r')igrac='b';
                else igrac='r';
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
}
int main()
{
     char mat[6][5]={' ',' ',' ',' ',' ',
                    ' ',' ',' ',' ',' ',
                    'r','b','b','r','r',
                    'b','r','r','b','b',
                    'r','b','b','r','r',
                    'x','x','x','x','x'};
    Node cvor(mat,'0');
    while(true){
    cout<<endl<<"Unesite redni broj operacije koju zelite da primenite: "<<endl;
    cout<<" 0. Kreiraj (novo) stablo igre."<<endl;
    cout<<" 1. Pronadji pobedu za crvenog."<<endl;
    cout<<" 2. Pronadji pobedu za plavog."<<endl;
    Stablo *t;
    int op;cin>>op;
    char c;
    switch(op){
            case 0:
               cout<<"Unesite tablu igre: "<<endl;
               for(int i=0;i<5;i++)
                    for(int j=0;j<5;j++)
                        cin>>mat[i][j];
                for(int i=0;i<5;i++)
                    for(int j=0;j<5;j++)
                        if(mat[i][j]=='.')mat[i][j]=' ';
                setujTablu(mat);
               for(int i=0;i<6;i++)
                    for(int j=0;j<5;j++)
                        cvor.mat[i][j]=mat[i][j];
                cout<<endl<<"Pravi se stablo...";
                t=napraviStabloIgre(&cvor);
                cout<<endl<<"Stablo je napravljeno."<<endl;
            break;
            case 1:
                if(t->postoji())nadjiPobedu(t,'r');
                else cout<<"Prvo napravite stablo pa pozovite ovu operaciju."<<endl;
            break;
            case 2:
                if(t->postoji())nadjiPobedu(t,'b');
                else cout<<"Prvo napravite stablo pa pozovite ovu operaciju."<<endl;
            break;

            case 3:
                exit(1);
                break;
            default:
                cout<<"Takva operacija ne postoji, pokusajte ponovo."<<endl;
                break;
    }
    }
    return 0;
}
