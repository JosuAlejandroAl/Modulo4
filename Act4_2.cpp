// A C++ program to print topological
// sorting of a graph using indegrees.
#include <bits/stdc++.h>
using namespace std;
 
// Class to represent a graph
class Graph {
    // No. of vertices'
    int V;
 
    // Pointer to an array containing
    // adjacency listsList
    list<int>* adj;
    bool isCyclicUtil(int u, bool visited[], int parent);
public:
    // Constructor
    Graph(int V);
 
    // Function to add an edge to graph
    void addEdge(int u, int v);
    void addedge(int r, int s);
    bool isTree();
    // prints a Topological Sort of
    // the complete graph
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
 
// The function to do
// Topological Sort.
void Graph::topologicalSort()
{
    // Create a vector to store
    // indegrees of all
    // vertices. Initialize all
    // indegrees as 0.
    vector<int> in_degree(V, 0);
 
    // Traverse adjacency lists
    // to fill indegrees of
    // vertices.  This step
    // takes O(V+E) time
    for (int u = 0; u < V; u++) {
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }
 
    // Create an queue and enqueue
    // all vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);
 
    // Initialize count of visited vertices
    int cnt = 0;
 
    // Create a vector to store
    // result (A topological
    // ordering of the vertices)
    vector<int> top_order;
 
    // One by one dequeue vertices
    // from queue and enqueue
    // adjacents if indegree of
    // adjacent becomes 0
    while (!q.empty()) {
        // Extract front of queue
        // (or perform dequeue)
        // and add it to topological order
        int u = q.front();
        q.pop();
        top_order.push_back(u);
 
        // Iterate through all its
        // neighbouring nodes
        // of dequeued node u and
        // decrease their in-degree
        // by 1
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
 
            // If in-degree becomes zero,
            // add it to queue
            if (--in_degree[*itr] == 0)
                q.push(*itr);
 
        cnt++;
    }
 
    // Check if there was a cycle
    if (cnt != V) {
        cout << "There exists a cycle in the graph\n";
        return;
    }
 
    // Print topological order
    for (int i = 1; i < top_order.size(); i++)
        cout << top_order[i] << " ";
    cout << endl;
}

bool Graph::isCyclicUtil(int r, bool visited[], int parent)
{
    // Mark the current node as visited
    visited[r] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[r].begin(); i != adj[r].end(); ++i)
    {
        // If an adjacent is not visited, then recur for
        // that adjacent
        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, r))
              return true;
        }
 
        // If an adjacent is visited and not parent of current
        // vertex, then there is a cycle.
        else if (*i != parent)
           return true;
    }
    return false;
}
 
// Returns true if the graph is a tree, else false.
bool Graph::isTree()
{
    // Mark all the vertices as not visited and not part of
    // recursion stack
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // The call to isCyclicUtil serves multiple purposes.
    // It returns true if graph reachable from vertex 0
    // is cyclcic. It also marks all vertices reachable
    // from 0.
    if (isCyclicUtil(0, visited, -1))
             return false;
 
    // If we find a vertex which is not reachable from 0
    // (not marked by isCyclicUtil(), then we return false
    for (int s = 0; s < V; s++)
        if (!visited[s])
           return false;
 
    return true;
}

 
// Driver program to test above functions
int main()
{
    // Create a graph given in the
    // above diagram
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
