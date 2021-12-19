#include "binaryTree.h"
#include "compression.h"

template <typename T>
binaryTree<T>::binaryTree() {}

template <typename T>
binaryTree<T>::binaryTree(T data) {
    binaryTree::data = data;
}

template <typename T>
binaryTree<T>* binaryTree<T>::getRight() {
    return binaryTree<T>::right;
}

template <typename T>
binaryTree<T>* binaryTree<T>::getLeft() {
    return binaryTree::left;
}

template <typename T>
void binaryTree<T>::setRight(binaryTree<T>* child) {
    binaryTree<T>::right = child;
}

template <typename T>
void binaryTree<T>::setLeft(binaryTree<T>* child) {
    binaryTree<T>::left = child;
}

template <typename T>
void binaryTree<T>::setRight(T data) {
    binaryTree<T>::right = new binaryTree<T>(data);
}

template <typename T>
void binaryTree<T>::setLeft(T data) {
    binaryTree<T>::left = new binaryTree<T>(data);
}

template <typename T>
bool binaryTree<T>::isLeaf() {
    return (binaryTree<T>::left == nullptr) && (binaryTree<T>::right == nullptr);
}

template <typename T>
binaryTree<T>::~binaryTree() {
    if (binaryTree<T>::right != nullptr) delete binaryTree<T>::right;
    if (binaryTree<T>::left != nullptr) delete binaryTree<T>::left;
}

template <typename T>
int binaryTree<T>::getDepth() {
    if (binaryTree<T>::right == nullptr && binaryTree<T>::left == nullptr) return 1;
    int rightDepth = binaryTree<T>::right -> getDepth();
    int leftDepth = binaryTree<T>::left -> getDepth();
    return 1 + ((rightDepth > leftDepth)? rightDepth : leftDepth);
}

template class binaryTree<huffmanNode>;
template class binaryTree<huffmanCode>;
