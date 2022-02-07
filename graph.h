#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

template<typename nodeType>
class graph
{
    std::vector<nodeType> nodes; //A vector of nodes in graph
    std::vector<std::list<int>> adjacencyList; //A vector of containers, each container represents the adjacency list of node with same index in nodes
public:
    graph();
    void addNode(nodeType node);
    void connectNodes(int source, int destination);
};



#endif // GRAPH_H
