#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <map>
using namespace std;
 
class Graph {
    int vert;
    list<int>* adj;
    bool Cycle(int u, bool visited[], int parent);
public:
    Graph(int vert);
    void addEdge(int u, int v);
    void addedge(int r, int s);
    bool isTree();
    void topologicalSort();
	void loadGraph(Graph &g,int m);
};
 
Graph::Graph(int vert)//complejidad O(n)
{
    this->vert = vert;
    adj = new list<int>[vert];
}
 
void Graph::addEdge(int u, int v)//complejidad O(n)
{
    adj[u].push_back(v);
}

void Graph::addedge(int r, int s)//compljidad O(n)
{
    adj[r].push_back(s);
    adj[s].push_back(r);
}

void Graph::topologicalSort()//complejidad de O ((V+E) log(V))
{
	vector <char> alfa= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    vector<int> in_degree(vert, 0);
	char a;
    for (int u = 0; u < vert; u++) {
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }
    queue<int> q;
    for (int i = 0; i < vert; i++)
        if (in_degree[i] == 0)
            q.push(i);
    int cnt = 0;
    vector<int> top_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        top_order.push_back(u);
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            if (--in_degree[*itr] == 0)
                q.push(*itr);
        cnt++;
    }
    if (cnt != vert) {
        cout << "No es un grafo\n";
        return;
    }
    for (int i = 1; i < top_order.size(); i++)
        cout << alfa[top_order[i]-1] << " ";
    cout << endl;
}

bool Graph::Cycle(int r, bool visited[], int parent)//Complejidad O(n)
{
    visited[r] = true;
    list<int>::iterator i;
    for (i = adj[r].begin(); i != adj[r].end(); ++i)
    {
        if (!visited[*i])
        {
           if (Cycle(*i, visited, r))
              return true;
        }
        else if (*i != parent)
           return true;
    }
    return false;
}
bool Graph::isTree()//Complejidad O(n)
{
    bool *visited = new bool[vert];
    for (int i = 0; i < vert; i++)
        visited[i] = false;
    if (Cycle(0, visited, -1))
             return false;
    for (int s = 0; s < vert; s++)
        if (!visited[s])
           return false;
 
    return true;
}

void Graph::loadGraph(Graph &g,int m){//complejidad O(n)
	vector <char> alfa= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char a, b;
	int a1,b1;
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		for (int j = 0; j < m; j++){
			if (a==alfa[j]){
				a1 = j+1;
			}
			if (b==alfa[j]){
				b1 = j+1;
			}
		}
		g.addEdge(a1,b1);
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	if(n<=0){
		cout << -1 << endl;
	}else{
		n=n+1;
    Graph g((n));
	g.loadGraph(g,m);
	if (n<=1){
		cout << boolalpha << false << endl;
	}else{
		cout << boolalpha << g.isTree() << endl;
	}
    g.topologicalSort();
	}
    return 0;
}
