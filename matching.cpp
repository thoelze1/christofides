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

int main() {
    srand(time(0));
    //testPM();
    //testMultigraph();
	return 0;
}
