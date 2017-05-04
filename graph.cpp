#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// numNodes is the number of nodes in the graph
// returns a graph with random [0,9] edge weights
vector< vector<int> > randomGraph(int numNodes) {
    vector< vector<int> > randomGraph(numNodes, vector<int>(numNodes));
    for(int i = 0; i < numNodes; i++) {
        for(int j = i; j < numNodes; j++) {
            if(i == j) {
                randomGraph[i][j] = 0;
            } else {
                randomGraph[i][j] = rand() % 10;
                randomGraph[j][i] = randomGraph[i][j];
            }
        }
    }
    return randomGraph;
}

// graph is an adjacency matrix
// numNodes is the number of nodes in graph
// prints graph as a matrix
void printGraph(vector< vector<int> > graph, int numNodes) {
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            cout << " ";
            cout << graph[i][j];
        }
        cout << endl;
    }
}