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

int chrisApprox(vector< vector<int> > graph, int numNodes) {
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
   /* 
    cout << "Path: ";
    for(int i = 0; i < path.size(); i++) {
        cout << path[i];
        cout << " ";
    }
    cout << endl;
   */ 
    // cost
    int cost = cycleCost(graph, numNodes, path);
    
    return cost;
}

void testRunTime() {

    vector< vector<int> > graph;

    for(int numNodes = MIN_NODES; numNodes <= MAX_NODES; numNodes += 1000) {

        graph = randomGraph(numNodes);

        clock_t begin = clock();
        chrisApprox(graph, numNodes);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        cout << setw(std::to_string(MAX_NODES).size()) << right << numNodes << " Nodes: ";
        cout << setw(10) << left << elapsed_secs << "s" << endl;
    }

}

void testCorrectness() {

    string line, fileName, answer, dummy;

    string correctOutputs = "outputs.txt";

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
    
    vector<float> totals;

    for(int j = 0; j < TRIALS; j++) {

        vector<int> ourTourValues;
        vector< vector<int> > graph;
        for(int i = 0; i < inputFiles.size(); i++) {
            graph = readGraph(inputFiles[i]);
            ourTourValues.push_back(chrisApprox(graph, graph.size())); 
            if(ourTourValues.back() == 0) cout << inputFiles[i] << endl;;
        }
    
        vector<float> ratios(ourTourValues.size());
    
        for(int i = 0; i < ourTourValues.size(); i++) {
            ratios[i] = ((float) ourTourValues[i] / minimumTourValues[i]);
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
            if(index + 1 > totals.size()) {
                totals.resize(index + 1);
            }
            intervals[index]++;
            totals[index]++;
        }
    
    }
  
    string headerLeft = "Factor of Optimal Cost";
    string headerRight = "Solutions Within Factor";

    cout << headerLeft << " | " << headerRight << endl; 

    for(int i = 0; i < totals.size(); i++) {
        totals[i] = ((float)totals[i])/(90*TRIALS)*100;
        cout << setw(headerLeft.size()) << ((0.1*i)+1.1) << " | " << setw(headerRight.size()) << totals[i] << "%" << endl;
    }
    
}

int main(int argc, char *argv[]) {
    
    srand(time(0));

    cout << endl;
    cout << "--Testing Run Time--" << endl;
    testRunTime();

    cout << endl;
    cout << "--Testing Correctness--" << endl;
    cout << endl;
    testCorrectness();
    cout << endl;

    return 0;
}
