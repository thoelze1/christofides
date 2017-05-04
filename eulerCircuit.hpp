#ifndef EULERCIRCUIT_HPP
#define EULERCIRCUIT_HPP

#include <vector>

std::vector< std::vector<int> > matrixToList(std::vector< std::vector<int> > graph, int numNodes);
std::vector<int> findEulerCycleHelper(std::vector< std::vector<int> > graph, int numNodes);
std::vector<int> findEulerCycle(std::vector< std::vector<int> > graph, int numNodes);

#endif
