#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "graph.h"
#include "multigraph.hpp"

using namespace std;

// graph1: adjacency matrix
// numNodes2: number of nodes in graph1
// graph2: adjacency matrix
// numNodes2: number of nodes in graph2
// returns simple graph by eliminating duplicate edges with non-minimal weight
vector< vector<int> > multigraph(vector< vector<int> > graph1, int numNodes1, vector< vector<int> > graph2, int numNodes2) {
    if(numNodes1 != numNodes2) {
        cout << "multigraph() received graphs of different sizes" << endl;
    }
    vector< vector<int> > multigraph(numNodes1, vector<int>(numNodes1));
    int minWeight;
    for(int i = 0; i < numNodes1; i++) {
        for(int j = 0; j < numNodes2; j++) {
           if((graph1[i][j]==0)&&(graph2[i][j]==0)) minWeight = 0;
           else if(graph1[i][j]==0) minWeight = graph2[i][j];
           else if(graph2[i][j]==0) minWeight = graph1[i][j];
           else minWeight = (graph1[i][j]<graph2[i][j])? graph1[i][j]: graph2[i][j];
           multigraph[i][j] = minWeight;
        }
    }
    return multigraph;
}

// test greedy perfect matching
void testMultigraph(){
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
