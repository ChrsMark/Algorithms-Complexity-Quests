#include <iostream>
#include <vector>
#include <ctime>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int N, M, K;
struct Edge
{
    int src, dest;
    long weight;
};

Edge* result;

struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges. Since the graph is
    // undirected, the edge from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    struct Edge* edge;
};


// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
 
// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};
void pritnEdge(Edge myEdge ){
	cout <<"("<< myEdge.src <<","<<myEdge.dest<<")="<<myEdge.weight;
}

void quickSort( struct Edge [], int, int);
int partition( struct Edge [], int, int);

/*next 3 functions are originated from -> http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/ */
/* although they have been modified a bit according to the specific needs*/
void Union(struct subset [], int , int );
int find(struct subset subsets[], int i);
void KruskalMST(struct Graph* graph);


int main() {
  
    cin >> N >> M >> K;               //read input
    
    
    struct Graph* graph = createGraph(N, M);
    result = new Edge[M];

    
   
    //read input and create the graph 
	for(int i = 0; i < M; i++){
    	cin >> graph->edge[i].src >> graph->edge[i].dest >> graph->edge[i].weight;

	}	
	
	
	KruskalMST(graph);
	
	return 0;  
}


// The main function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph)
{
    int V = graph->V;
    struct Edge result[V];  // Tnis will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges
 
    // Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
    quickSort(graph->edge, 0, M-1);
 	
    // Allocate memory for creating V ssubsets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 	
    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
    	if(e==M) break; //no more edges
    	
        // Step 2: Pick the smallest edge. And increment the index
        // for next iteration
        struct Edge next_edge = graph->edge[i++];
 		
        int x = find(subsets, next_edge.src);
        if(x==-1) break; //no more edges
        
        int y = find(subsets, next_edge.dest);
        if(y==-1) break; //no more edges
 		
        // If including this edge does't cause cycle, include it
        // in result and increment the index of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 	
    // print the contents of result[] to display the built MST
    /*printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
                                                   result[i].weight);*/
    if(e<K) cout<<"infinity\n";
    else cout<<result[e-K-1].weight<<"\n";
    return;
}

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
	
	if(i>=M) return (-1);//we may have no more edges!!!
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 


void quickSort( struct Edge a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
    // divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
    
}



int partition( struct Edge a[], int l, int r) {
   int pivot, i, j;
   struct Edge t;
   pivot = a[l].weight;
   i = l; j = r+1;
        
   while( 1)
   {
    do ++i; while( a[i].weight >= pivot && i <= r );
    do --j; while( a[j].weight  < pivot );
    if( i >= j ) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}
