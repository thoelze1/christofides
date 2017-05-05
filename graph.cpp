#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

#include "graph.hpp"

using namespace std;

// inputFileName: name of a text file
// returns a graph
vector< vector<int> > readGraph(string inputFileName) {
    string line;
    vector< vector<int> > graph;
    ifstream infile(inputFileName);
    while(getline(infile, line)) {
        vector<int> lineData;
        stringstream lineStream(line);
        string value;
        while(lineStream >> value) {
            lineData.push_back(stoi(value));
        }
        graph.push_back(lineData);
    }
    return graph;
}

// numNodes is the number of nodes in the graph
// returns a graph with random [0,9] edge weights
vector< vector<int> > randomGraph(int numNodes) {
    vector< vector<int> > randomGraph(numNodes, vector<int>(numNodes));
    for(int i = 0; i < numNodes; i++) {
        for(int j = i; j < numNodes; j++) {
            if(i == j) {
                randomGraph[i][j] = 0;
            } else {
                randomGraph[i][j] = rand() % 9 + 1;
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
            printf("%10d",graph[i][j]);
            //cout << " ";
            //cout << graph[i][j];
        }
        cout << endl;
    }
}
