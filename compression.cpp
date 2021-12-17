#include "compression.h"
#include "binaryTree.h"
#include <vector>
#include <queue>
#include <bitset>

bool compareNodes(binaryTree<huffmanNode>* elem1, binaryTree<huffmanNode>* elem2) {
    return (elem1->data).frequency > (elem2->data).frequency;
}

std::string compress(std::string *data) {
    //Creating freuqncy array for elements
    unsigned long long frequencyArray[256] = {0};
    for (char character: *data) {
        frequencyArray[(int)character]++;
    }

    //Creating a priority queue for all characters and their frequencies
    std::priority_queue<binaryTree<huffmanNode>*, std::vector<binaryTree<huffmanNode>*>, decltype(&compareNodes)> nodes(compareNodes);
    for (int i = 0; i < 256; i++) {
        if (frequencyArray[i] > 0) nodes.push(new binaryTree<huffmanNode>(huffmanNode {(char)i, frequencyArray[i]}));
    }

    //Getting number of huffman tree nodes
    char nodeCount = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencyArray[i] > 0) nodeCount++;
    }

    //Building huffman tree and translation table
    int bitCounts[256] = {0};
    std::bitset<256> codes[256];
    int bitCount = nodeCount-1;
    bool firstLoop = true;
    while(nodes.size() > 1) {
        binaryTree<huffmanNode>* tree1 = nodes.top();
        nodes.pop();
        binaryTree<huffmanNode>* tree2 = nodes.top();
        nodes.pop();
        binaryTree<huffmanNode>* newTree = new binaryTree<huffmanNode>({0, (tree1 -> data).frequency + (tree2 -> data).frequency});
        newTree -> setRight(tree1);
        newTree -> setLeft(tree2);
        nodes.push(newTree);
        if(tree1 -> isLeaf()) {
            bitCounts[(int)(tree1 -> data).character] = bitCount;
            if (firstLoop) {
                codes[(int)(tree1 -> data).character][0] = 1;
                for (int i = 1; i < bitCount; i++) {
                    codes[(int)(tree1 -> data).character][i] = 1;
                }
            }
            else {
                codes[(int)(tree1 -> data).character][0] = 0;
                for (int i = 1; i < bitCount; i++) {
                    codes[(int)(tree1 -> data).character][i] = 1;
                }
                bitCount--;
            }
        }
        if(tree2 -> isLeaf()) {
            bitCounts[(int)(tree2 -> data).character] = bitCount;
            codes[(int)(tree2 -> data).character][0] = 0;
            for (int i = 1; i < bitCount; i++) {
                codes[(int)(tree2 -> data).character][i] = 1;
            }
            bitCount--;
        }
        firstLoop = false;
    }
    binaryTree<huffmanNode>* huffmanTree = nodes.top();

    //Encoding text according to produced translation table
    std::string text;
    //Encoding string length in bits
    unsigned long long totalBitCount = 0;
    for (int i = 0; i < 256; i++) {
        totalBitCount += frequencyArray[i] * bitCounts[i];
    }
    for (int i = 7; i >= 0; i--) {
        text.push_back(totalBitCount >> i*8);
    }
    //Encoding actual compressed text
    char currentByte = 0;
    int bitIndex = 7;
    for (char character: *data) {
        std::bitset<256> currentCode = codes[(int)character];
        for (int i = bitCounts[(int)character]; i >= 0; i--) {
            if (currentCode[i] == 1) currentByte = currentByte & (1 << bitIndex);
            bitIndex--;
            if (bitIndex == -1) {
                text.push_back(currentByte);
                currentByte = 0;
                bitIndex = 7;
            }
        }
    }


    //Encoding huffman tree as text
    std::string tree;
    tree.push_back(nodeCount);
    binaryTree<huffmanNode>* currentNode = huffmanTree;
    while(!currentNode -> isLeaf()) {
        tree.push_back(currentNode -> getLeft() -> data.character);
        currentNode = currentNode -> getRight();
    }
    tree.push_back(currentNode -> data.character);

    delete huffmanTree; //delete dynamically allocated binary huffman tree

    return tree + text;
}

std::string decompress(std::string* data) {

}

static binaryTree<huffmanNode> stringToTree(std::string* data) {

}

static std::string treeToString(binaryTree<huffmanNode>* tree) {

}
