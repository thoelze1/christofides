#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

#include "graph.hpp"

using namespace std;

// inputFileName: Name of a text file that contains
//                an adjacency matrix of a graph. Line
//                i of the text file contains the i-th 
//                row of adjacency matrix. The text
//                file contains n lines with n delimited
//                entries each.
// returns the graph in inputFileName as an adjacency
// matrix
vector< vector<int> > readGraph(string inputFileName) {

    vector< vector<int> > graph;

    ifstream infile(inputFileName);
    string line;

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

// numNodes: the number of nodes desired in the graph
// returns a complete graph with random [0,9] edge weights
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

/**
    THIS FUNCTION IS UNFINISHED AND EXTRANEOUS

    We want to write a function in the future
    that generates a metric graph with random
    edge weights. This function was not nece-
    ssary for our implementation but is inde-
    pendent study.

vector< vector<int> > metricGraph(int numNodes) {
    vector< vector<int> > randomGraph(numNodes, vector<int>(numNodes));
    vector< vector< vector<int> > > triangles(numNodes, vector< vector<int>(numNodes) >(numNodes);
    for(int j = 0; j < numNodes; j++) {
        for(int i = 0; i <= j; i++) {
            if(i == j) {
                randomGraph[i][j] = 0;
            } else {
                int minWeight = 0;
                int maxWeight = numeric_limits<int>::max();
                for(int p = 0; p < i; k++) {
                    for(int q = p + 1; q < j)
                }
                randomGraph[i][j] = metricWeight;
                randomGraph[j][i] = metricWeight;
            }
        }
    }
    return randomGraph;
}
*/

// graph: an adjacency matrix
// numNodes: the number of nodes in graph
// Prints graph as a well-formatted adjacency matrix
void printGraph(vector< vector<int> > graph, int numNodes) {

    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            printf("%10d",graph[i][j]);
        }
        cout << endl;
    }

}
