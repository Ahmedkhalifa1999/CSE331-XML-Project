#include "graph.h"
#include "SNgraph.h"

template<typename nodeType>
graph<nodeType>::graph()
{

}

template<typename nodeType>
void graph<nodeType>::addNode(nodeType node)
{
    nodes.push_back(node);
}

template<typename nodeType>
void graph<nodeType>::addNode(nodeType node, std::list<int> adjacent)
{
    nodes.push_back(node);
    adjacencyLists.push_back(adjacent);
}

template<typename nodeType>
void graph<nodeType>::connectNodes(int source, int destination)
{
    adjacencyLists[source].push_back(destination);
}

template class graph<user>;
