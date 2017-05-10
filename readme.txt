HOW TO COMPILE
--------------

make


HOW TO CLEAN
------------

make clean


HOW TO RUN
----------

make run


DATA STRUCTURES
---------------

Adjancency matrices were used to represent the graph. They were implemented using 2D vectors of ints.

Adjancency list was used once to help with eulerian circuit algorithm. Also implemented as a 2D
vector of ints.


COMPUTATION TIME
----------------

O(|V|^2)

Prim's algorithm runs in O(|V|^2) with an adjacency matrix representation. For each node, you have to
search through a vector of edge weights. The search takes O(|V|) and is repeated V times; giving you
O(|V|^2).

Find number of odd vertices runs in O(|V|^2) because you have to search through the entire 2D matrix.

Low Weight Matching runs in 0(|V|^2) because it runs on all the odd degree vertices in the MST and 
check the edge weight with all of its neighbors. In the worst case, the entire graph is of odd degree
and every vertex goes through all of it's neighbors.

Merge MST and Perfect Matching runs in 0(|V|^2) because you have to iterate through two adjacency
matrices.

Euler Circuit runs in 0(|E|) because you exhaust all of the edges in the graph. However, this
becomes 0(|V|^2) because we are only using complete graphs.

Finding the Hamiltonian Cycle runs in 0(|E|) because you go through the eulerian circuit, which
is by definition of length |E| and as mentioned previously, 0(|E|) = 0(|V|^2) because of
complete graphs.

The overall time complexityis 0(|V|^2) because all of these time complexities added together
grows overall at a rate of 0(|V|^2).


FUNCTIONS
---------

See comments above each in .cpp files.

