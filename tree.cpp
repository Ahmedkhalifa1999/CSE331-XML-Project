#include "tree.h"
#include <string>

template<typename T>
tree<T>::tree(T data) {
    tree::data = data;
}

template<typename T>
tree<T>* tree<T>::getChild(unsigned int index) {
    if (index < tree<T>::children.size()) return tree<T>::children[index];
    else return nullptr;
}

template<typename T>
void tree<T>::addChild(tree<T>* child) {
    tree<T>::children.push_back(child);
}

template<typename T>
void tree<T>::addChild(T data) {
    tree<T>::children.push_back(new tree(data));
}

template<typename T>
bool tree<T>::isLeaf() {
    return tree<T>::children.empty();
}

/*
template<typename T>
tree<T>::~tree() {
    for (tree<T>* child: tree<T>::children) {
        if (child != nullptr) delete child;
    }
}
*/

template class tree<std::string>;
