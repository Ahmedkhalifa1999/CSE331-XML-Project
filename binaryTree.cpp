#include "binaryTree.h"

binaryTree* binaryTree::getRight() {
    return binaryTree::right;
}

binaryTree* binaryTree::getLeft() {
    return binaryTree::left;
}

void binaryTree::setRight(binaryTree* child) {
    binaryTree::right = child;
}

void binaryTree::setLeft(binaryTree* child) {
    binaryTree::left = child;
}

bool binaryTree::isLeaf() {
    return (binaryTree::left == nullptr) && (binaryTree::right == nullptr);
}

binaryTree::~binaryTree() {
    if (binaryTree::right != nullptr) delete binaryTree::right;
    if (binaryTree::left != nullptr) delete binaryTree::left;
}
