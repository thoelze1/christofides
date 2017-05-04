#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP

#include <vector>

std::vector< std::vector<int> > multigraph(std::vector< std::vector<int> > graph1, int numNodes1, std::vector< std::vector<int> > graph2, int numNodes2);
void testMultigraph();

#endif