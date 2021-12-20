#include "compression.h"
#include "binaryTree.h"
#include <vector>
#include <queue>
#include <bitset>

static bool compareNodes(binaryTree<huffmanNode>* elem1, binaryTree<huffmanNode>* elem2);
static huffmanCode getHuffmanCode(binaryTree<huffmanNode>* tree, char character);
static void ArrayifyTree(binaryTree<huffmanNode>* tree, char array[], int index = 0);
static long long power(long long base, long long exp);

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

    //Building huffman tree
    while(nodes.size() > 1) {
        binaryTree<huffmanNode>* right = nodes.top();
        nodes.pop();
        binaryTree<huffmanNode>* left = nodes.top();
        nodes.pop();
        binaryTree<huffmanNode>* newTree = new binaryTree<huffmanNode>({0, (right -> data).frequency + (left -> data).frequency});
        newTree -> setRight(right);
        newTree -> setLeft(left);
        nodes.push(newTree);
    }
    binaryTree<huffmanNode>* huffmanTree = nodes.top();

    //Building translation table
    huffmanCode translations[256];
    for (int i = 0; i < 256; i++) {
        if (frequencyArray[i] > 0) translations[i] = getHuffmanCode(huffmanTree, (char) i);
    }

    std::string text;
    //Encoding huffman tree as text
    int depth = huffmanTree -> getDepth();
    text.push_back((char)depth);
    char array[power(2, depth) - 1];
    for (int i = 0; i < (depth * depth) - 1; i++) {
        array[i] = 0;
    }
    ArrayifyTree(huffmanTree, array);
    for (char character: array) {
        text.push_back(character);
    }

    //Encoding string length in bits
    unsigned long long totalBitCount = 0;
    for (int i = 0; i < 256; i++) {
        totalBitCount += frequencyArray[i] * translations[i].length;
    }
    for (int i = 7; i >= 0; i--) {
        text.push_back(totalBitCount >> i*8);
    }

    //Encoding actual compressed text according to translation table
    char currentByte = 0;
    int bitIndex = 7;
    for (char character: *data) {
        std::bitset<256> currentCode = translations[(int)character].code;
        for (int i = translations[(int)character].length - 1; i >= 0; i--) {
            if (currentCode[i] == 1) currentByte = currentByte | (1 << bitIndex);
            bitIndex--;
            if (bitIndex == -1) {
                text.push_back(currentByte);
                currentByte = 0;
                bitIndex = 7;
            }
        }
    }
    if (bitIndex != 7) text.push_back(currentByte);

    delete huffmanTree; //delete dynamically allocated binary huffman tree

    return text;
}

std::string decompress(std::string* data) {

}

static bool compareNodes(binaryTree<huffmanNode>* elem1, binaryTree<huffmanNode>* elem2) {
    return (elem1->data).frequency > (elem2->data).frequency;
}

static huffmanCode getHuffmanCode(binaryTree<huffmanNode>* tree, char character) {
    if (tree->data.character == 0) {
        huffmanCode right = getHuffmanCode(tree->getRight(), character);
        huffmanCode left = getHuffmanCode(tree->getLeft(), character);
        if (right.length != -1) {
            right.code[right.length] = 1;
            right.length++;
            return right;
        }
        else if (left.length != -1) {
            left.code[left.length] = 0;
            left.length++;
            return left;
        }
        else {
            return huffmanCode{};
        }
    }
    else if (tree->data.character == character) {
        huffmanCode initial;
        initial.length++;
        return initial;
    }
    else {
        return huffmanCode{};
    }
}

static void ArrayifyTree(binaryTree<huffmanNode>* tree, char array[] , int index) {
    array[index] = tree->data.character;
    if (tree->getRight() != nullptr) ArrayifyTree(tree->getLeft(), array, 2 * index + 1);
    if (tree->getLeft() != nullptr) ArrayifyTree(tree->getRight(), array, 2 * index + 2);
}

static long long power(long long base, long long exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}
