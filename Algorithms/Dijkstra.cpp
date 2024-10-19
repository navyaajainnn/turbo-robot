#include <iostream>
#include <vector>
#include <queue>
#include <climits> // For INT_MAX
using namespace std;

class Graph{
   //number of vertices 
   int V;
   //adjacency list for storing weight and vertex 
   vector<vector<pair<int, int>>> adj;

public:
   //constructor
   Graph(int V);

   // function to add an edge to graph
    void addEdge(int u, int v, int wt);

    // prints shortest path from source
    void shortestPath(int src);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj.resize(V); // Resizing the adjacency list to V vertices
}

void addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w}); // Add edge u to v with weight w
    adj[v].push_back({u, w}); // For undirected graph, add v to u as well
}

void shortestPath(int src)
{
    // Create a priority queue (min heap) to store vertices and their corresponding weight that
    //are being processed.
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;

    // Create a vector for distances and initialize all
    // distances as INT_MAX
    vector<int> dist(V, INT_MAX);

    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push({0, src});
    dist[src] = 0;

    /* Looping till priority queue becomes empty */
    while (!pq.empty()) {
        // As we are using a min heap, the topmost element is gonna be the one with 
        // least weight. Pop it out and using this distance, we peak into the adjacency list
        // of the node. If we see that the distance of neighbouring node can be lowered down
        // then we modify it as per the following:
        int distance= pq.top().first;
        int node= pq.top().second;
        pq.pop();
      
        // iterate through the adjacency list and check neighbouring nodes 
         for(auto it:adj[node]){
           int vertex= it.first;
           int weight= it.second;
           
           //if weight plus the distance found so far is less than the dist[vertex],
           // then we update it and push it in priority queue
           if(weight + distance< dist[vertex]){
             dist[vertex]= weight + distance;
             pq.push({dist[vertex], vertex});
           }
           
         }
    }

    // Print the shortest distances stored in dist[]
    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < V; ++i)
        cout << i << " \t\t " << dist[i] << "\n";
}

int main() {
    // Create a graph with 9 vertices
    Graph g(9);

    // Add edges (u, v, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    // Print shortest paths from vertex 0
    g.shortestPath(0);

    return 0;
}
