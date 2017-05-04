#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// graph: adjacency matrix
// numNodes: number of nodes in graph
// returns list of vertices in graph with odd degree
vector<int> oddVertices(vector< vector<int> > graph, int numNodes) {
    vector<int> oddVertices;
    int degree;
    for(int i = 0; i < numNodes; i++) {
        degree = 0;
        for(int j = 0; j < numNodes; j++) {
            if(graph[i][j] > 0) degree++;
        }
        if(degree&1) oddVertices.push_back(i);
    }
    return oddVertices;
} 

// graph: adjacency matrix
// numNodes: number of nodes in graph
// returns minimal weight maximum matching adjacency matrix
vector< vector<int> > greedyFlowPM(vector< vector<int> > graph, int numNodes) {
    vector< vector<int> > matching(numNodes,vector<int>(numNodes));
    vector<int> freeVertices = oddVertices(graph, numNodes);

    // implementation

    return matching;
}

// graph: adjacency matrix
// numNodes: number of nodes in graph
// returns minimal weight maximum matching adjacency matrix
vector< vector<int> > greedyRandPM(vector< vector<int> > graph, int numNodes) {
    vector< vector<int> > matching(numNodes,vector<int>(numNodes));
    vector<int> freeVertices = oddVertices(graph, numNodes);
    int randIndex, randVertex, adjVertex, minIndex, minVertex, minWeight;
    srand(time(0));
    while(!freeVertices.empty()) {
        // pop a random vertex from free vertex list
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

// test greedy perfect matching
void testPM(){
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
    printGraph(greedyRandPM(graph, numNodes), numNodes);
}