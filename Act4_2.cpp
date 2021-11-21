#include <bits/stdc++.h>
using namespace std;
 
class Graph {
    int V;
    list<int>* adj;
    bool isCyclicUtil(int u, bool visited[], int parent);
public:
    Graph(int V);
    void addEdge(int u, int v);
    void addedge(int r, int s);
    bool isTree();
    void topologicalSort();
	void loadGraph(Graph &g,int m);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::addedge(int r, int s)
{
    adj[r].push_back(s);
    adj[s].push_back(r);
}

void Graph::topologicalSort()
{
	vector <char> alfa= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    vector<int> in_degree(V, 0);
	char a;
    for (int u = 0; u < V; u++) {
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }
    queue<int> q;
    for (int i = 0; i < V; i++)
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
    if (cnt != V) {
        cout << "There exists a cycle in the graph\n";
        return;
    }
    for (int i = 1; i < top_order.size(); i++)
        cout << alfa[top_order[i]-1] << " ";
    cout << endl;
}

bool Graph::isCyclicUtil(int r, bool visited[], int parent)
{
    visited[r] = true;
    list<int>::iterator i;
    for (i = adj[r].begin(); i != adj[r].end(); ++i)
    {
        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, r))
              return true;
        }
        else if (*i != parent)
           return true;
    }
    return false;
}
bool Graph::isTree()
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    if (isCyclicUtil(0, visited, -1))
             return false;
    for (int s = 0; s < V; s++)
        if (!visited[s])
           return false;
 
    return true;
}

void Graph::loadGraph(Graph &g,int m){
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
