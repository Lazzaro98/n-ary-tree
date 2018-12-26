#include <iostream>
#define MAX_SIZE_OF_STACK 100000
#include<time.h>
#include<string.h>
using namespace std;
int m=5;
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
            for(int i=0;i<m;i++)
                next[i]=t.next[i];
            cout<<"Kopirajuci konstruktor pozvan"<<endl;
        }
        void premesti(Node& t){
            stanje=t.stanje;
            parent=t.parent;
            next=t.next;
             for(int i=0;i<6;i++)
                for(int j=0;j<5;j++)
                mat[i][j]=t.mat[i][j];

            t.next=nullptr;
            cout<<"Premestajuci konstruktor pozvan"<<endl;
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
        for(int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if(i==0 || i==6)ot<<"-";
                else if(j==0 || j==6) ot<<"|";
                else ot<<x->mat[i-1][j-1];
                }
            if(i!=6)ot<<endl;
            }
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
    void setKoren(Node* cvor){koren=cvor;}// sta bese ovo
    ~Stablo();
};
/*int ktr=0;
Stablo* napraviStabloIgre(Node* cvor){
    Stablo *t = new Stablo(5);
    cvor->igrac='r';
    t->setKoren(cvor);
    bool gameOver=false;
    char igrac=cvor->igrac;
    int klp=0;
    //while(!gameOver){
    //int trenutnaDub=0,maxDub=slobPolja(cvor->mat);
    //Node** nizCvorova= new Node*[2*pow(5,maxDub)];
        //gameOver=true;
        Stack s;
        s.push(t->getKoren(),0);
        Node* sled;
        while(!s.isEmpty()){
            //trenutnaDub=s.dub();
            sled=s.pop();
            while(sled){
                Node* noviCvor;
                if(!imaPotomke(sled) && sled->stanje=='0' && !fullMatrix(sled->mat)){
                    if(sled->igrac=='r')igrac='b';
                    else {igrac='r';klp++;}
                    gameOver=false;
                    for(int j=0;j<5;j++){
                         noviCvor=new Node(sled->mat,'0');
                        int k=sled->mat[5][j]-'0';
                        if(k){
                            int br=noviCvor->mat[5][j]-'1';
                            noviCvor->mat[5][j]=br+'0';
                            noviCvor->mat[k-1][j]=igrac;
                            sled->next[j]=noviCvor;
                            ktr++;

                        noviCvor->parent=sled;
                        noviCvor->stanje=proveriPobednika(noviCvor->mat);
                        noviCvor->igrac=igrac;
                        cout<<"Igrac: "<<igrac<<" Stanje cvora:"<<noviCvor->stanje<<endl<<noviCvor;
                       // sled->next[j]=noviCvor;
                        }
                        else{
                    noviCvor= new Node(matx,'X');
                    noviCvor->parent=sled;
                    noviCvor->igrac=igrac;
                    sled->next[j]=noviCvor;
                    cout<<noviCvor<<endl;
                }


                    }
                   // if(!trenutnaDub){nizCvorova[0]=sled;cout<<sled;}
                   /* else{
                    int b=pow(5,trenutnaDub);
                    cout<<"B je: "<<b;
                    while(nizCvorova[b])b++;
                    nizCvorova[b]=sled;
                }*/
         //       }

               // cout<<"--------------------------------------------------";
              //  Sleep(1000);
        /*        for(int i=4;i>0;i--)
                    if(sled->next[i])
                        s.push(sled->next[i]);
                sled=sled->next[0];*/
               // trenutnaDub++;

                /*for(int i=0;i<5;i++)
                    cout<<sled->mat[5][i];*/

        //    }

      //  }
       // int b=0;
       // cout<<"niz:"<<endl<<endl<<"-----------------"<<endl<<endl;
      //  while(nizCvorova[b])cout<<nizCvorova[b++]<<"      ";
   /*     cout<<"hahahahaahhahaahahaha";
        //sada jos da ispises:
    int b=1;
    int z=5;
    int zb=5;
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

   // }
   cout<<klp;
   return t;
}

void nadjiPobedu(Stablo* t,char igrac){
            Stack s;
            s.push(t->getKoren(),0);
            Node* sled;
            Node* pob;
            while(!s.isEmpty()){
            //trenutnaDub=s.dub();

            sled=s.pop();

           while(sled){
                pob=new Node(matx,'0');
                if(sled->stanje==igrac){pob=sled;goto nasao;}
                //cout<<sled->stanje<<endl;


                for(int i=4;i>0;i--)
                    if(sled->next[i])
                        s.push(sled->next[i]);
                sled=sled->next[0];
            }

}
nasao:
if(pob->stanje=='0'){cout<<igrac<<" ne moze nikada pobediti.";return;}
            cout<<"Resenje:"<<endl;
            Node* pom=pob;
            while(pom){
                cout<<pom->stanje<<endl;
                cout<<pom;
                pom=pom->parent;
            }
}*/



Stablo* napraviStabloIgre(Node* cvor){
	Stablo *t = new Stablo(5);
	//random prvi igrac:
	char igraci[2]={'r','b'};
	srand(time(NULL));
	unsigned short igr=rand()%2;
	char igrac=igraci[igr];

	t->setKoren(cvor);
	Stack s;
	s.push(t->getKoren(),0);
	Node* sled;
	while(!s.isEmpty()){
		sled=s.pop();
		while(sled){
			Node* noviCvor;
			if(!imaPotomke(sled) && sled->stanje=='0' && !fullMatrix(sled->mat)){
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
						//cout<<noviCvor;
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
	cout<<"Resenje:"<<endl;
	Node* pom=pobednik;
	Stack st;
	while(pom){
		st.push(pom);
		pom=pom->parent;
		}

	while(!st.isEmpty()){
		cout<<st.pop();
	}
}
int main()
{
     char mat[6][5]={' ',' ',' ',' ',' ',
                    ' ',' ',' ',' ',' ',
                    'b','r','b','r','b',
                    'b','r','b','b','r',
                    'r','b','r','b','r',
                    'x','x','x','x','x'};
    Node cvor(mat,0);
    cout<<"Unesite redni broj operacije koju zelite da primenite: "<<endl;
    cout<<" 0. Kreiraj stablo igre."<<endl;
    cout<<" 1. Pronadji pobedu za crvenog."<<endl;
    cout<<" 2. Pronadji pobedu za plavog."<<endl;
    Stablo *t;
    int op;cin>>op;
    switch(op){
            case 0:
                cout<<"Unesite tablu igre: "<<endl;
                for(int i=0;i<5;i++)
                    for(int j=0;j<5;j++)
                        cin.getline(mat[i][j],1);
                setujTablu(mat);

                for(int i=0;i<5;i++)
                    for(int j=0;j<5;j++)
                        cvor.mat[i][j]=mat[i][j];

                cout<<"Pravi se stablo...";
                t=napraviStabloIgre(&cvor);
                cout<<"Stablo napravljeno.";
            break;
            case 1:
                nadjiPobedu(t,'r');
            break;
            case 2:
                nadjiPobedu(t,'b');
            break;
            }
 //cout<<proveriPobednika(mat);
    //Node cvor2(cvor);  return 0;
}

