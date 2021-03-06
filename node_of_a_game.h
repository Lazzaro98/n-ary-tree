/*
     coded by LazzaRo
*/
#include <iostream>
using namespace std;
     char mat[6][5]={' ',' ',' ',' ',' ',
                    ' ',' ',' ',' ',' ',
                    'r','b','b','r','r',
                    'b','r','r','b','b',
                    'r','b','b','r','r',
                    '2','2','2','2','2'};//primer matrice

    char matx[6][5]=   {'\\',' ',' ',' ','/',
                    ' ','\\',' ','/',' ',
                    ' ',' ','\\',' ',' ',
                    ' ','/',' ','\\',' ',
                    '/',' ',' ',' ','\\',
                    ' ',' ',' ',' ',' '};// X matrica
int m=0,brCv=0;
int pow(int n,int k){
    int p=1;
    while(k--)p*=n;
    return p;
}
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
           // cout<<"Kopirajuci pozvan;";
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
       // cout<<endl<<" ";
        //for(int i=0;i<5;i++)cout<<x->mat[5][i];
        //cout<<endl;
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
