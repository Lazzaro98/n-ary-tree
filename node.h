/*
    coded by LazzaRo
    node of a tree
*/
#include <iostream>
using namespace std;
#include <Stablo.h>
int m=Stablo::m;
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