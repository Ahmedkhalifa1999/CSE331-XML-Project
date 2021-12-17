#include "compression.h"
#include "binaryTree.h"
#include <vector>
#include <queue>

bool compareNodes(binaryTree<huffmanNode>* elem1, binaryTree<huffmanNode>* elem2) {
    return (elem1->data).frequency > (elem2->data).frequency;
}

std::string compress(std::string *data) {
    //Creating freuqncy array for elements
    unsigned long long frequencyArray[256];
    for (char character: *data) {
        frequencyArray[(int)character]++;
    }

    //Creating a priority queue for all characters and their frequencies
    std::priority_queue<binaryTree<huffmanNode>*, std::vector<binaryTree<huffmanNode>*>, decltype(&compareNodes)> nodes(compareNodes);
    for (int i = 0; i < 256; i++) {
        nodes.push(new binaryTree<huffmanNode>(huffmanNode {(char)i, frequencyArray[i]}));
    }

    //Building huffman tree
    while(nodes.size() > 1) {
        binaryTree<huffmanNode>* tree1 = nodes.top();
        nodes.pop();
        binaryTree<huffmanNode>* tree2 = nodes.top();
        nodes.pop();
        binaryTree<huffmanNode>* newTree = new binaryTree<huffmanNode>({0, (tree1 -> data).frequency + (tree2 -> data).frequency});
        newTree -> setRight(tree1);
        newTree -> setLeft(tree2);
        nodes.push(newTree);
    }
    binaryTree<huffmanNode>* huffmanTree = nodes.top();

    //Building translation table from huffman tree


    //Encoding text according to produced huffman tree
    std::string text;

    //Encoding huffman tree as text
    std::string tree;

    delete huffmanTree; //delete dynamically allocated binary huffman tree

    return tree + text;
}

std::string decompress(std::string* data) {

}

static binaryTree<huffmanNode> stringToTree(std::string* data) {

}

static std::string treeToString(binaryTree<huffmanNode>* tree) {

}
