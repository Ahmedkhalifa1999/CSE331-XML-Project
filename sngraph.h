#ifndef SNGRAPH_H
#define SNGRAPH_H

#include "graph.h"
#include <string>
#include <vector>
#include "tree.h"

typedef struct{
    int id;
    std::string name;
    std::vector<std::string> posts;
}user;

class SNgraph : public graph<user>
{
public:
    SNgraph(tree<std::string> parsed);
};

#endif // SNGRAPH_H
