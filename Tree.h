#ifndef TREE_H
#define TREE_H

#include <vector>

template<typename T>
class tree{
public:
    T data;
    std::vector<tree*> children;

    tree(T data);

    tree* getChild(unsigned int index);
    void addChild(tree* child);
    void addChild(T data);
    bool isLeaf();

    //~tree();
};

#endif //TREE_H
