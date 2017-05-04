#include <cstdlib>
#include <ctime>
#include <iostream>

#include "graph.hpp"
#include "mst.hpp"
#include "matching.hpp"
#include "multigraph.hpp"
#include "eulerCircuit.hpp"

using namespace std;

void chrisApprox(vector< vector<int> > graph, int numNodes) {
    // mst
    vector< vector<int> > mst = findMST(graph, numNodes);
    //printGraph(mst, numNodes);
    //cout << endl;
    
    // odd vertices in mst
    vector<int> odds = oddVertices(mst, numNodes);
    //cout << odds.size();
    //cout << endl;
    //for(int i = 0; i < odds.size(); i++) {
    //    cout << odds[i];
    //    cout << " ";
    //}
    //cout << endl;
    
    // matching
    vector< vector<int> > matching = greedyRandPM(graph, numNodes, odds);
    //printGraph(matching, numNodes);
    //cout << endl;
    
    // multigraph
    vector< vector<int> > multi = multigraph(mst, numNodes, matching, numNodes);
    //printGraph(multi, numNodes);
    //cout << endl;
    
    // eulerian to hamiltonian
    vector<int> path = findEulerCycle(multi, numNodes);
    for(int i = 0; i < path.size(); i++) {
        cout << path[i];
        cout << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    
    // random graph
    int numNodes = 5;
    vector< vector<int> > graph = randomGraph(numNodes);
    printGraph(graph, numNodes);
    cout << endl;
    /*
    vector< vector<int> > graph = readGraph("p01_d.txt");
    int numNodes = graph.size();
    */

    chrisApprox(graph, numNodes);
    
    return 0;
}
