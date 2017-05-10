#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "graph.hpp"
#include "matching.hpp"

using namespace std;

// graph: adjacency matrix
// numNodes: number of nodes in graph
// Returns list of vertices in graph with odd degree
vector<int> oddVertices(vector< vector<int> > graph, int numNodes) {

    vector<int> oddVertices;

    int degree;
    for(int i = 0; i < numNodes; i++) {
        degree = 0;
        for(int j = 0; j < numNodes; j++) {
            if(graph[i][j] > 0) degree++;
        }
        if(degree & 1) oddVertices.push_back(i);
    }

    return oddVertices;
} 

// graph: adjacency matrix
// numNodes: number of nodes in graph
// freeVertices: list of vertices in graph to match
// Returns a new graph as an adjacency matrix whose edge set represents the minimal weight
// maximum matching on the freeVertices of graph
vector< vector<int> > greedyRandPM(vector< vector<int> > graph, int numNodes, vector<int> freeVertices) {

    vector< vector<int> > matching(numNodes,vector<int>(numNodes));
    int randIndex, randVertex, adjVertex, minIndex, minVertex, minWeight;

    while(!freeVertices.empty()) {

        randIndex = rand() % freeVertices.size();
        randVertex = freeVertices[randIndex];
        freeVertices.erase(freeVertices.begin() + randIndex);

        // initialize minimum values
        minWeight = numeric_limits<int>::max();

        // determine actual  minimum values
        for(int i = 0; i < freeVertices.size(); i++) {
            adjVertex = freeVertices[i];
            if((graph[randVertex][adjVertex]>0)&&(graph[randVertex][adjVertex]<minWeight)) {
                minWeight = graph[randVertex][adjVertex];
                minIndex = i;
                minVertex = adjVertex;
            }
        }

        matching[randVertex][minVertex] = minWeight;
        matching[minVertex][randVertex] = minWeight;
        freeVertices.erase(freeVertices.begin() + minIndex);
    }

    return matching;
}

// Prints a random graph, determines the set of odd vertices,
// calls greedyRandPM() on the random graphs using the set of odd vertices,
// and prints the output graph representing the perfect matching so that
// the user can verify it
void testPM() {

    // create graph
    int numNodes = 20;
    vector< vector<int> > graph = randomGraph(numNodes);

    // print original graph
    printGraph(graph, numNodes);
    cout << endl;

    // print odd degree vertices 
    vector<int> freeVertices = oddVertices(graph, numNodes);
    for(int i = 0; i < freeVertices.size(); i++) {
        cout << freeVertices[i];
        cout << " ";
    }
    cout << endl;

    // print matching
    printGraph(greedyRandPM(graph, numNodes, oddVertices(graph, numNodes)), numNodes);
    cout << endl;
}
