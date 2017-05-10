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
   
    int numNodes = stoi(argv[1]); 
    vector< vector<int> > graph = randomGraph(numNodes);
    //vector< vector<int> > graph = readGraph("tsplib-mat/burma14.txt");

	/*
    string correctOutputs = argv[1];
    string line, fileName, answer, dummy;

    vector<string> inputFiles;
    vector<int> minimumTourValues;

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
    
    int iterations = 10;
    vector<float> totals(20);
    for(int j = 0; j < iterations; j++) {
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

    for(int i = 0; i < ratios.size(); i++) {
        //cout << ratios[i] << endl;
    }
    // cout << endl;

    float sum = 0;


    vector<int> intervals(20);
    for(int i = 0; i < ratios.size(); i++) {
        if(ratios[i] > 3) continue;
        sum += ratios[i];
        intervals[(int)((ratios[i]-1)*10)]++;
        totals[(int)((ratios[i]-1)*10)]++;
    }

    for(int i = 0; i < intervals.size(); i++) {
        cout << "Iteration " << j << " " << ((0.1*i)+1) << ": " << intervals[i] << endl;
    }

    cout << sum / (ratios.size() - 1) << endl;

    }
    for(int i = 0; i < totals.size(); i++) {
        cout << "Total " << ((0.1*i)+1) << ": " << totals[i] << endl;
    }

    for(int i = 0; i < totals.size(); i++) {
        totals[i] = ((float)totals[i])/(90*iterations)*100;
        cout << "Average " << ((0.1*i)+1) << ": " << totals[i] << "%%" << endl;
    }
    */
    //printGraph(graph, 14);
    
    clock_t begin = clock();

    chrisApprox(graph, numNodes);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs << endl;
    
    return 0;
}
