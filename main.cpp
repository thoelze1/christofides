#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "graph.hpp"
#include "mst.hpp"
#include "matching.hpp"
#include "multigraph.hpp"
#include "eulerCircuit.hpp"

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

int main(int argc, char *argv[]) {
    srand(time(0));
    
    string correctOutputs = argv[1];
    string line, fileName, answer, dummy;

    vector<string> inputFiles;
    vector<string> inputFilesComplete;
    vector<int> minimumTourValues;
    vector<int> ourTourValues;
    vector< vector<int> > graph;

    //vector< vector<int> > graph = randomGraph(280);
    //vector< vector<int> > graph = readGraph("tsplib-mat/burma14.txt");
    //int numNodes = graph.size();

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

    for(int i = 0; i < inputFiles.size(); i++) {
	graph = readGraph(inputFiles[i]);
	ourTourValues.push_back(chrisApprox(graph, graph.size())); 
	if(ourTourValues.back() == 0) cout << inputFiles[i] << endl;;
    }

    vector<float> ratios;

    for(int i = 0; i < ourTourValues.size(); i++) {
	ratios.push_back((float) ourTourValues[i] / minimumTourValues[i]);
    }

    for(int i = 0; i < ratios.size(); i++) {
	cout << ratios[i] << endl;
    }

    float sum = 0;

    cout << endl;

    for(int i = 0; i < ratios.size(); i++) {
	if(ratios[i] > 2) continue;

        sum += ratios[i];
    }

    cout << sum / (ratios.size() - 1) << endl;

    //printGraph(graph, 14);

    //chrisApprox(graph, 14);
    
    return 0;
}
