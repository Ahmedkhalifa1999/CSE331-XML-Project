#include "tree.h"

tree* tree::getChild(unsigned int index) {
    if (index < tree::children.size()) return tree::children[index];
    else return nullptr;
}

void tree::addChild(tree* child) {
    tree::children.push_back(child);
}

bool tree::isLeaf() {
    return tree::children.empty();
}
