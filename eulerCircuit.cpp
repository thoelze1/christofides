#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <set>

#include "eulerCircuit.hpp"

using namespace std;

//Helper function to convert matrixToList
vector< vector<int> > matrixToList(vector< vector<int> > graph, int numNodes) {
	vector< vector<int> > adjList(numNodes);

	for(int i = 0; i < numNodes; i++) {
		for(int j = 0; j < numNodes; j++) {
			if(graph[i][j] > 0) {
				adjList[i].push_back(j);
			}
		} 
	}

	return adjList;
}

// graph: adjacency matrix
// numNodes: number of nodes in graph
// cycle: a cycle of numNodes+1 nodes (must start and end on same node)
// returns the sum of the weights of the edges traverse in the cycle
int cycleCost(vector< vector<int> > graph, int numNodes, vector<int> cycle) {
	int cost = 0;
	if(cycle.size()!=numNodes+1) {
		cout << "cycleCost() received a cycle of wrong size" << endl;
		return 0;
        }
        if(cycle[0]!=cycle[numNodes]) {
		cout << "cycleCost() received a path. not a cycle" << endl;
		return 0;
	}
	for(int i = 0; i < cycle.size() - 1; i++) {
        cost += graph[cycle[i]][cycle[i+1]];
	}
	return cost;
}

//Takes an adjacency list representation because getting it to work
//with matrix was really difficult for some reason

//Conversion is fairly trivial because weights do not matter when
//finding any Eulerian Circuit in an undirected graph
vector<int> findEulerCycleHelper(vector< vector<int> > graph, int numNodes) {
	unordered_map<int, int> edgeCount;
	
	for(int i = 0; i < graph.size(); i++) {
		edgeCount[i] = graph[i].size();
	}
	
	stack<int> currentPath;
	vector<int> cycle;

	currentPath.push(0);
	int currentNode = 0;

	while(!currentPath.empty()) {
		if(edgeCount[currentNode]) {
			currentPath.push(currentNode);
			int nextNode = graph[currentNode].back();
			edgeCount[currentNode]--;
			graph[currentNode].pop_back();

			currentNode = nextNode;
		}

		else {
			cycle.push_back(currentNode);

			currentNode =  currentPath.top();
			currentPath.pop();
		}
	}

	return cycle;
}

//Main function
//Takes matrix representation of graph
//Converts matrix to list
//Finds an Eulerian Circuit
//Returns a vector<int> of the path

vector<int> findEulerCycle(vector< vector<int> > graph, int numNodes) {
	//Converts graph to adj list representation
	vector< vector<int> > graphList = matrixToList(graph, numNodes);
	
	//Finds the Eulerian Cycle in reverse
	vector<int> cycleEuler = findEulerCycleHelper(graphList, numNodes);
	
	//Reverses the previously found cycle
	reverse(cycleEuler.begin(), cycleEuler.end());


	//Removes duplicates from path to obtain Hamiltonian Cycle
	set<int> seenNums;

	auto it = begin(cycleEuler);

	while(it != end(cycleEuler)) {
		if(seenNums.find(*it) != end(seenNums)) {
			it = cycleEuler.erase(it);
		}

		else {
			seenNums.insert(*it);
			it++;
		}
	}

	//Adds starting node again to complete cycle
	cycleEuler.push_back(cycleEuler[0]);

	return cycleEuler;
}
