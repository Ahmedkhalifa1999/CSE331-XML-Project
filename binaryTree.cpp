#include "binaryTree.h"

template<typename dataType>
binaryTree<dataType>::binaryTree(dataType data) {
    binaryTree::data = data;
}

template<typename dataType>
binaryTree<dataType>* binaryTree<dataType>::getRight() {
    return binaryTree::right;
}

template<typename dataType>
binaryTree<dataType>* binaryTree<dataType>::getLeft() {
    return binaryTree::left;
}

template<typename dataType>
void binaryTree<dataType>::setRight(binaryTree* child) {
    binaryTree::right = child;
}

template<typename dataType>
void binaryTree<dataType>::setLeft(binaryTree* child) {
    binaryTree::left = child;
}