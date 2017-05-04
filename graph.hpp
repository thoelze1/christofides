#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

std::vector< std::vector<int> > readGraph(std::string inputFileName);
std::vector< std::vector<int> > randomGraph(int numNodes);
void printGraph(std::vector< std::vector<int> > graph, int numNodes);

#endif
