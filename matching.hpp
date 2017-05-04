#ifndef MATCHING_HPP
#define MATCHING_HPP

#include <vector>

std::vector<int> oddVertices(std::vector< std::vector<int> > graph, int numNodes);
std::vector< std::vector<int> > greedyFlowPM(std::vector< std::vector<int> > graph, int numNodes);
std::vector< std::vector<int> > greedyRandPM(std::vector< std::vector<int> > graph, int numNodes);
void testPM();

#endif
