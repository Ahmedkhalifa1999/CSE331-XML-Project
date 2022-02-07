#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

template<typename nodeType>
class graph
{
    std::vector<nodeType> nodes; //A vector of nodes in graph
    std::vector<std::list<int>> adjacencyLists; //A vector of lists, each list represents the adjacency list of node with same index in nodes
public:
    graph();
    void addNode(nodeType node);
    void addNode(nodeType node, std::list<int> adjacent);
    void connectNodes(int source, int destination);
};



#endif // GRAPH_H
