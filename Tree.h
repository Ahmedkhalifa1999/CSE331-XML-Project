#include <vector>

class tree{
public:
    std::vector<tree*> children;

    tree* getChild(unsigned int index);
    void addChild(tree* child);
    bool isLeaf();

    ~tree();
};
