#include "graph.h"

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
void graph<nodeType>::connectNodes(int source, int destination)
{
    adjacencyList[source].push_back(destination);
}
