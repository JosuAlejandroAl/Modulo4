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
    vector<int> in_degree(V, 0);
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
        cout << top_order[i] << " ";
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
int main()
{
    Graph g(14);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 1);
    g.addEdge(3, 2);
    g.addEdge(4, 7);
    g.addEdge(4, 8);
    g.addEdge(5, 1);
    g.addEdge(5, 4);
    g.addEdge(5, 6);
    g.addEdge(6, 10);
    g.addEdge(6, 11);
    g.addEdge(7, 9);
    g.addEdge(8, 9);
    g.addEdge(8, 10);
    g.addEdge(9, 12);
    g.addEdge(10, 12);
    g.addEdge(10, 13);
    g.addEdge(11, 10);
    g.isTree()? cout << "Graph is Tree\n":
                cout << "Graph is not Tree\n";
 
    cout << "Following is a Topological Sort of\n";
    g.topologicalSort();
 
    return 0;
}
//1A 2B 3C 4D 5E 6F 7G 8H 9I 10J 11K 12L 13M

//3 5 2 1 6 4 11 7 8 9 10 12 13
