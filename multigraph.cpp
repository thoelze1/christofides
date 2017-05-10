#include <iostream>

#include "multigraph.hpp"
#include "graph.hpp"

using namespace std;

// graph1: adjacency matrix
// numNodes2: number of nodes in graph1
// graph2: adjacency matrix
// numNodes2: number of nodes in graph2
//
// Returns a simple graph that represents the union of graph1 and graph2 
// by making a new graph that contains edge sets of both graphs where
//  duplicate edges with non-minimal weight are removed
vector< vector<int> > multigraph(vector< vector<int> > graph1, int numNodes1, vector< vector<int> > graph2, int numNodes2) {

    // sanity check: make sure input graphs are same size
    if(numNodes1 != numNodes2) {
        cout << "multigraph() received graphs of different sizes" << endl;
    }

    // initialize multigraph
    vector< vector<int> > multigraph(numNodes1, vector<int>(numNodes1));

    // keep track of the minimum weight edge in case duplicate edges are found
    int minWeight;

    // construct multigraph by checking each possible edge in input graphs
    for(int i = 0; i < numNodes1; i++) {
        for(int j = 0; j < numNodes2; j++) {
           // no edge present in either graph
           if((graph1[i][j]==0)&&(graph2[i][j]==0)) minWeight = 0;
           // edge present in graph 1
           else if(graph1[i][j]==0) minWeight = graph2[i][j];
           // edge present in graph 2
           else if(graph2[i][j]==0) minWeight = graph1[i][j];
           // edge present in both graphs
           else minWeight = (graph1[i][j]<graph2[i][j])? graph1[i][j]: graph2[i][j];
           multigraph[i][j] = minWeight;
        }
    }

    return multigraph;
}

// Prints 2 random graphs, calls multigraph() on the random graphs,
// and prints the output of multigraph() so that the user can verify it
void testMultigraph() {
 
    // create 2 graphs
    int numNodes = 5;
    vector< vector<int> > graph1 = randomGraph(numNodes);
    vector< vector<int> > graph2 = randomGraph(numNodes);
 
    // print original graph
    printGraph(graph1, numNodes);
    cout << endl;
    printGraph(graph2, numNodes);
    cout << endl;

    //print new graph
    printGraph(multigraph(graph1, numNodes, graph2, numNodes), numNodes);
    cout << endl;
}
