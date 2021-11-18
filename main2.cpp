#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <map>
#include <algorithm>
//Compilado con la version C++11
using namespace std;

struct Node;

struct Edge{
	Edge* next;
	Node* ady;
};

struct Node{
	Node* next;
	Edge* ady;
	char letra;
};

struct grafo{
	Node* head;
	void Grafo();
	bool Empty();
	Node* getNode(char letra);
	void insertEdge(Node* og, Node* dt);
	void insertNode(char letra);
	void ListAdy();
	void DFS(Node* og);
	void BFS(Node* og);
};

void grafo::Grafo(){//complejidad O(1)
	head = NULL;
}

bool grafo::Empty(){//complejidad O(n)
	if (head==NULL){
		return true;
	}
	return false;
}

Node* grafo::getNode(char letra){//complejidad O(n)
	Node* aux;
	aux = head;
	while (aux != NULL){
		if(aux->letra == letra){
			return aux;
		}
		aux = aux -> next;
	}
	return NULL;
}

void grafo::insertNode(char _letra){//complejidad O(n)
	Node* nw = new Node;
	nw->letra =_letra;
	nw->next = NULL;
	nw->ady = NULL;
	if(Empty()){
		head = nw;
	}else{
		Node* aux;
		aux = head;
		while (aux->next != NULL){
			aux = aux -> next;
		}
		aux -> next = nw;
	}
}

void grafo::insertEdge(Node* og, Node* dt){//complejidad O(n)
	Edge* nw = new Edge;
	nw->next = NULL;
	nw->ady = NULL;
	Edge* aux;
	aux=og->ady;
	if(aux == NULL){
		og->ady = nw;
		nw->ady = dt;
	}else{
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = nw;
		nw->ady = dt;
	}
}

void grafo::ListAdy(){//complejidad O(n)
	Node *naux;
	Edge *aaux;
	naux = head;
	while(naux != NULL){
		cout << naux->letra;
		aaux = naux->ady;
		while (aaux != NULL){
			cout << " - " << aaux->ady->letra;
			aaux = aaux->next;
		}
		naux = naux->next;
		cout << endl;
	}
}

void grafo::BFS(Node* og){//complejidad O(n)^2
	int flag,flag2;
	Node* act;
	queue<Node*> tail;
	list<Node*> lista;
	list<Node*>::iterator i;
	tail.push(og);
	while(!tail.empty()){
		flag = 0;
		act = tail.front();
		tail.pop();
		for ( i = lista.begin(); i != lista.end(); i++){
			if(*i == act){
				flag = 1;
			}
		}
		if(flag == 0){
			cout << act->letra << " ";
			lista.push_back(act);
			Edge* aux;
			aux = act->ady;
			while(aux!= NULL){
				flag2 = 0;
				for(i=lista.begin();i!= lista.end();i++){
					if(aux->ady == *i){
						flag2 = 1;
					}
				}
				if (flag2 == 0){
					tail.push(aux->ady);
				}
				aux = aux->next;	
			}
		}
	}
}

bool ordenar(Node* a, Node* b){//complejidad O(n)
	return a->letra > b->letra;
}

void grafo::DFS(Node* og){//complejidad O(n)^2
	int flag,flag2;
	Node* act;
	stack<Node*> pila;
	vector<Node*> vt;
	list<Node*> lista;
	list<Node*>::iterator i;
	pila.push(og);
	while (!pila.empty()){
		flag = 0;
		act = pila.top();
		pila.pop();
		for ( i = lista.begin(); i != lista.end(); i++){
			if(*i == act){
				flag = 1;
			}
		}
		if ( flag == 0){
			cout << act->letra << " ";
			lista.push_back(act);
			Edge* aux;
			aux = act->ady;
			while (aux!=NULL){
				vt.push_back(aux->ady);
				aux = aux->next;
			}
			sort(vt.begin(),vt.end(),ordenar);
			for (Node* v : vt){
				pila.push(v);	
			}
			vt.clear();
		}
	}
}

int main(){
    int n=0;
	bool m;
    cin >> n;
    bool matriz[n][n];
	struct grafo* head;
	head->Grafo();
	vector <char> alfa= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	for (int i = 0; i < n; i++){
		head->insertNode(alfa[i]);
        for (int j = 0; j < n; j++){
            cin >> m;
            matriz[i][j]=m;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << matriz[i][j] << " ";
			if (matriz[i][j] != 0){
				head->insertEdge(head->getNode(alfa[i]),head->getNode(alfa[j]));
			}
        }
        cout << endl;
    }
    cout << endl;
	head->ListAdy();
	cout << endl;
	head->BFS(head->getNode('A'));
	cout << endl;
	head->DFS(head->getNode('A'));
	cout << endl;
    return 0;
}
