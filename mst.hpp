#ifndef MST_HPP
#define MST_HPP

#include <vector>

int findMin(std::vector<int> key, std::vector<bool> mstSet, int numNodes);
std::vector< std::vector<int> > constructMST(std::vector< std::vector<int> > graph, std::vector<int> mst, int numNodes);
void printMST(std::vector< std::vector<int> > mst, int numNodes);
std::vector< std::vector<int> > findMST(std::vector< std::vector<int> > graph, int numNodes);

#endif