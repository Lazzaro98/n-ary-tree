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
            setujTablu(mat);

            next=new Node*[m];
            for(int i=0;i<m;i++)
                next[i]=nullptr;
        }
        void kopiraj(const Node&t){
            stanje=t.stanje;
            for(int i=0;i<6;i++)
                for(int j=0;j<6;j++)
                    mat[i][j]=t.mat[i][j];

            parent=t.parent;
            next=new Node*[m];
            for(int i=0;i<m;i++)
                next[i]=t.next[i];
        }
        void premesti(Node& t){
            stanje=t.stanje;
            parent=t.parent;
            next=t.next;
             for(int i=0;i<6;i++)
                for(int j=0;j<6;j++)
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
        friend ostream& operator << (ostream& ot, Node*x);
        ~Node(){
            brisi();
        }
};
Node* newNode(char **k,char st){
    Node* x = new Node(k,st);
    return x;
}
bool imaPotomke(Node* x){
    for(int i=0;i<5;i++)
        if(x->next[i])return true;
    return false;
}
ostream& Node::operator <<(ostream& ot, Node* x){
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(i==0 || i==7)ot<<"-";
            else if(j==0 || j==7) ot<<"|";
            else ot<<x->mat[i][j];
    return ot<<endl;
}//ispis cvora

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
    Stablo(int k){ koren=nullptr;maxDub=0;}
    Node* getKoren(){return koren;}
    void addNode(Node* newOne);
    int sirinaStabla();
    bool postoji(){return m;}
    friend ostream& operator <<(ostream& it, const Stablo& t);
    void operator+=(Node* newOne){addNode(newOne);}
    void setKorenTable(char**mat);// sta bese ovo
    ~Stablo();
};

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
    for(int j=0;j<5;j++){
        int br=0;
        for(int i=0;i<5;i++)
            if(mat[i][j])br++;
        mat[5][j]=br;
    }
}
bool fullMatrix(char**mat){
    if(mat[5][0] || mat[5][1] || mat[5][2] || mat[5][2])return true;
    return false;
}
char proveriPobednika(char**mat){
    char igraci[1]={'r','b'};
    for(int k=0;k<2;k++)
        for(int i=0;i<5;i++)
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

Stablo napraviStabloIgre(char**mat){
    Stablo t=new Stablo(5);
    t.setujTablu(mat);
    bool gameOver=false;
    char igrac='r';
    while(!gameOver){
        gameOver=true;
        Stack s;
        s.push(t.getKoren());
        Node* sled;
        while(!s.isEmpty()){
            sled=s.pop();
            while(sled){
                for(int i=4;i>0;i--)
                    if(sled->next[i])
                        s.push(sled->next[i]);
                    Node* pom = sled->next[0];
                //obrada:
                    if(!imaPotomke(sled) && !sled->stanje){
                        gameOver=false;
                        for(int j=0;j<5;j++){//ovde moze kopirajuci konstruktor
                            int k = sled->mat[5][j];
                            for(int i=0;i<5&&k>=0;i++){
                                if(i!=k)mat[i][j]=sled->mat[i][j];
                                if(i==k){mat[i][j]=igrac;sled->mat[5][j]--;}
                            }//for j
                        }//for i
                    for(int i=0;i<5;i++)mat[5][i]=sled->mat[5][i];//prenos brojeva koji oznacvaju koliko slobodnih mesta ima u matrici po kolonama
                    Node* noviCvor=new Node(mat,proveriPobednika(mat));
                    sled->next[j]=noviCvor;
                    }//if imaPotomke
                    sled=pom;//idemo dalje kroz stablo.                        
            }//while sled
        }//while isEmpty
        if(igrac=='r')igrac='b';
        if(igrac=='b')igrac='r';
    }//while gameOver
    return t;
}

