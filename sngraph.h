#ifndef SNGRAPH_H
#define SNGRAPH_H

#include "graph.h"
#include <string>
#include <vector>
#include "tree.h"

typedef struct{
    int id;
    std::string name;
    //std::vector<std::string> posts; //Posts ignored for now, need a new struct post to encapsulate body and topics
}user;

class SNgraph : public graph<user>
{
public:
    SNgraph(tree<std::string> parsed);
    void visualize(std::string directory);
};

#endif // SNGRAPH_H
