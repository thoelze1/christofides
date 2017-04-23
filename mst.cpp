#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

//Helper function to find min key value from vertices not in MST yet
int findMin(vector<int> key, vector<bool> mstSet, int numNodes) {
	int minValue = INT_MAX;
	int minIndex;

	for(int i = 0; i < numNodes; i++) {
		if(mstSet[i] == false && key[i] < minValue) {
			minValue = key[i];
			minIndex = i;
		}
	}

	return minIndex;
}

//Helper function to actuall construct the MST as a full adjancency matrix
vector< vector<int> > constructMST(vector< vector<int> > graph, vector<int> mst, int numNodes) {
	vector< vector<int> > mstMatrix(numNodes, vector<int> (numNodes, 0));

	for(int i = 1; i < numNodes; i++) {
		mstMatrix[mst[i]][i] = graph[i][mst[i]];
	}

	return mstMatrix;
}

//Prints MST as an adjacency matrix given the MST matrix and number of nodes
void printMST(vector< vector<int> > mst, int numNodes) {
	for(int i = 0; i < numNodes; i++) {
		for(int j = 0; j < numNodes; j++) {
			cout << mst[i][j] << " ";
		}
		cout << endl;
	}
}


//Finds MST given a 2D vector of a graph and number of nodes
//Used vector and not array because 2D arrays are a pain in C/C++
vector< vector<int> > findMST(vector< vector<int> > graph, int numNodes) {
	vector<int> constructedMST(numNodes);
	vector<int> key(numNodes);
	vector<bool> mstSet(numNodes);

	fill(key.begin(), key.end(), INT_MAX);
	fill(mstSet.begin(), mstSet.end(), false);

	key[0] = 0;
	constructedMST[0] = -1;

	for(int i = 0; i < numNodes - 1; i++) {
		int min = findMin(key, mstSet, numNodes);

		mstSet[min] = true;

		for(int j = 0; j < numNodes; j++) {
			if(graph[min][j] && mstSet[j] == false && graph[min][j] < key[j]) {
				constructedMST[j] = min;
				key[j] = graph[min][j];
			}
		}
	}
	
	return constructMST(graph, constructedMST, numNodes);
}
