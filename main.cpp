#include <cstdlib>
#include <ctime>

#include "graph.hpp"
#include "mst.hpp"
#include "matching.hpp"

using namespace std;

int main() {
    srand(time(0));
    int numNodes = 4;
    vector< vector<int> > graph = randomGraph(numNodes);
    printGraph(graph, numNodes);
    vector< vector<int> > mst = findMST(graph, numNodes);
    printGraph(mst, numNodes);
    vector< vector<int> > matching = greedyRandPM(mst, numNodes);
    printGraph(matching, numNodes);
    /*vector< vector<int> > graph = randomGraph(numNodes);
    vector< vector<int> > graph = randomGraph(numNodes);*/
    return 0;
}
