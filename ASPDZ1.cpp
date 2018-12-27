#include <iostream>
#define MAX_SIZE_OF_STACK 1000
#include<math.h>
using namespace std;
int m=0;

//Definicija cvora
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
        friend ostream& operator<< (ostream& ot,Node* t){
            ot<<t->i<<" ";
            return ot;
        }
        ~Node(){
            brisi();
        }
};
Node* newNode(int t){
    Node* x = new Node(t);
    return x;
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
    void ispis();
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
