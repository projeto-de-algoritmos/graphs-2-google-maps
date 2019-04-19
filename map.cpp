#include <stdio.h> 
#include <limits.h>
#include <chrono> 
#include <iostream> 
using namespace std; 
using namespace std::chrono; 

   
// Number of vertices in the graph 
#define V 9 
   
int minDistance(int dist[], bool sptSet[]) { 
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < V; v++) 
     if (sptSet[v] == false && dist[v] <= min) 
         min = dist[v], min_index = v; 
   
   return min_index; 
} 
   
// A utility function to print the constructed distance array 
int printSolution(int dist[], int n) { 
    printf("Vertex Distance from Source\n"); 
    for (int i = 0; i < V; i++) {
        printf("%d to %d\n", i, dist[i]); 
    }
    
} 
   
void dijkstra(int graph[V][V], int src) { 
    auto start = high_resolution_clock::now(); 
    int dist[V];     // Hold the shortest distance from src to i 

    bool sptSet[V]; 

    for (int i = 0; i < V; i++) 
    dist[i] = INT_MAX, sptSet[i] = false; 

    dist[src] = 0; 
   
     // Find shortest path for all vertices 
    for (int count = 0; count < V-1; count++) { 

        int u = minDistance(dist, sptSet); 

        sptSet[u] = true; 

        for (int v = 0; v < V; v++) 

            // Update dist[v] only if is not in sptSet, there is an edge from  
            // u to v, and total weight of path from src to  v through u is  
            // smaller than current value of dist[v] 
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX  
                                        && dist[u]+graph[u][v] < dist[v]) 
            dist[v] = dist[u] + graph[u][v]; 
    } 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
  
    cout << "Duration: " << duration.count() << "ms" << endl; 
    printSolution(dist, V); 
} 
   

int main() { 
    // Map
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0}, 
                        {4, 0, 8, 0, 0, 0, 0, 11, 0}, 
                        {0, 8, 0, 7, 0, 4, 0, 0, 2}, 
                        {0, 0, 7, 0, 9, 14, 0, 0, 0}, 
                        {0, 0, 0, 9, 0, 10, 0, 0, 0}, 
                        {0, 0, 4, 14, 10, 0, 2, 0, 0}, 
                        {0, 0, 0, 0, 0, 2, 0, 1, 6}, 
                        {8, 11, 0, 0, 0, 0, 1, 0, 7}, 
                        {0, 0, 2, 0, 0, 0, 6, 7, 0} 
                        }; 
    dijkstra(graph, 0); 
   
    return 0; 
} 