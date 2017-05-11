#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "graph.hpp"
#include "mst.hpp"
#include "matching.hpp"
#include "multigraph.hpp"
#include "eulerCircuit.hpp"

#define MIN_NODES	1000
#define MAX_NODES	5000
#define TRIALS		1

using namespace std;

int christofidesApprox(vector< vector<int> > graph, int numNodes) {

    // find mst of graph
    vector< vector<int> > mst = findMST(graph, numNodes);

    // find odd vertices in mst
    vector<int> odds = oddVertices(mst, numNodes);
 
    // find minimal matching on odd vertices from mst in original graph
    vector< vector<int> > matching = greedyRandPM(graph, numNodes, odds);
 
    // combine mst and minimal matching
    vector< vector<int> > multi = multigraph(mst, numNodes, matching, numNodes);
    
    // find hamiltonian cycle in combined graph
    vector<int> path = findEulerCycle(multi, numNodes);

    // compute cost of hamiltonian cycle cost
    int cost = cycleCost(graph, numNodes, path);
    
    return cost;
}

void testRunTime() {

    vector< vector<int> > graph;

    for(int numNodes = MIN_NODES; numNodes <= MAX_NODES; numNodes += 1000) {

        graph = randomGraph(numNodes);

        clock_t begin = clock();
        christofidesApprox(graph, numNodes);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        cout << setw(std::to_string(MAX_NODES).size()) << right << numNodes << " Nodes: ";
        cout << setw(5) << right << fixed << setprecision(2) << elapsed_secs << "s" << endl;
    }

}

void testCorrectness() {

    string line, fileName, answer, dummy;

    string correctOutputs = "tsplib-mat-outputs.txt";

    vector<string> inputFiles;
    vector<int> minimumTourValues;

    ifstream infile(correctOutputs);

    while(getline(infile, line)) {
        stringstream s(line);
        s >> fileName >> dummy >> answer;
        inputFiles.push_back(fileName);
        minimumTourValues.push_back(stoi(answer));
    }

    for(int i = 0; i < inputFiles.size(); i++) {
        inputFiles[i].append(".txt");
        inputFiles[i].insert(0, "tsplib-mat/");
    }
    
    vector<float> intervalTotals;
    float avgRatio = 0;

    for(int j = 0; j < TRIALS; j++) {

        vector<int> ourTourValues;
        vector< vector<int> > graph;
        for(int i = 0; i < inputFiles.size(); i++) {
            graph = readGraph(inputFiles[i]);
            ourTourValues.push_back(christofidesApprox(graph, graph.size())); 
            if(ourTourValues.back() == 0) cout << inputFiles[i] << endl;;
        }
    
        vector<float> ratios(ourTourValues.size());
    
        for(int i = 0; i < ourTourValues.size(); i++) {
            ratios[i] = ((float) ourTourValues[i] / minimumTourValues[i]);
            avgRatio += ratios[i];
        }
    
        float sum = 0;
    
        vector<int> intervals;
        int index;
        for(int i = 0; i < ratios.size(); i++) {
            if(ratios[i] > 3) continue;
            sum += ratios[i];
            index = (int)((ratios[i]-1)*10);   
            if(index + 1 > intervals.size()) {
                intervals.resize(index + 1);
            }
            if(index + 1 > intervalTotals.size()) {
                intervalTotals.resize(index + 1);
            }
            intervals[index]++;
            intervalTotals[index]++;
        }
    
    }
 
    cout << "Let C be a constant factor" << endl;
    cout << "Let H be the cost of the optimal Hamiltonian cycle" << endl;

    cout << endl;

    string headerLeft = "  C";
    string headerRight = "Solutions < C*H";

    cout << headerLeft << " | " << headerRight << endl;
    cout << "----|----------------" << endl;

    for(int i = 0; i < intervalTotals.size(); i++) {
        intervalTotals[i] = ((float)intervalTotals[i])/(90*TRIALS)*100;
        cout << setw(headerLeft.size()) << right << fixed << setprecision(1) << ((0.1*i)+1.1) << " | ";
        cout << setw(headerRight.size() - 1) << right << fixed << setprecision(1) << intervalTotals[i] << "%" << endl;
    }

    cout << endl;
    cout << "Average ratio of solution to optimal solution: " << fixed << setprecision(2) << avgRatio/(inputFiles.size()*TRIALS) << endl;
    
}

int main(int argc, char *argv[]) {
    
    srand(time(0));

    cout << endl << "--Testing Run Time--" << endl << endl;
    testRunTime();

    cout << endl << "--Testing Correctness--" << endl << endl;
    testCorrectness();

    cout << endl;

    return 0;
}
