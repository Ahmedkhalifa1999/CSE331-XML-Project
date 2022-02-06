#include "compression.h"
#include "binaryTree.h"
#include <vector>
#include <queue>
#include <bitset>
#include <ctype.h>

static bool compareNodes(binaryTree<huffmanNode>* elem1, binaryTree<huffmanNode>* elem2);
static huffmanCode getHuffmanCode(binaryTree<huffmanNode>* tree, char character);
static void arrayifyTree(binaryTree<huffmanNode>* tree, char array[], int index = 0);
static long long power(long long base, long long exp);
static binaryTree<char>* treeifyArray(char array[], int index = 0);
static std::vector<char> compressArrayifiedTree(char array[], int length);
static std::vector<char> decompressArrayifiedTree(char* compressed, int length);

std::string minify(std::string* text) {
    std::string minified;
    bool isTag = false;
    bool isText = false;
    unsigned long long length = text->length();
    for (unsigned int i = 0; i < length; i++) {
        char character = text -> at(i);
        if (character == '<') {
            isTag = true;
            isText = false;
            while(isspace(minified[minified.length()-1])) minified.pop_back();
        }
        else if (character == '>') isTag = false;
        else if (!isTag && !isText) {
            if (isspace(character)) continue;
            else isText = true;
        }
        minified.push_back(character);
    }
    return minified;
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
    //Encoding huffman tree as text (INEFFICIENT FOR SMALL FILES)
    int depth = huffmanTree -> getDepth();
    char array[power(2, depth) - 1];
    for (int i = 0; i < power(2, depth) - 1; i++) {
        array[i] = 0;
    }
    arrayifyTree(huffmanTree, array);
    std::vector compressedTree = compressArrayifiedTree(array, power(2, depth) - 1);
    text.push_back((char)(compressedTree.size() >> 8));
    text.push_back((char)compressedTree.size());
    for (char character: compressedTree) {
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
    //Build huffman tree
    char* treeArray = data->data() + 2;
    std::vector<char> decompressedTree = decompressArrayifiedTree(treeArray, (data->at(0) << 8) | data->at(1));
    binaryTree<char>* huffmanTree = treeifyArray(decompressedTree.data());

    //Decode Text according to huffman tree
    //Get string length in bits from code
    int index = ((data->at(0) << 8) | data->at(1)) + 2; //length of tree array + bytes encoding its length
    unsigned long long totalBitCount = 0;
    for (int i = 7; i >= 0; i--) {
        totalBitCount |= (data->at(index) << i*8);
        index++;
    }
    //Get actual text from code
    std::string text;
    std::string compressed = data->substr(index);
    binaryTree<char>* currentNode = huffmanTree;
    unsigned long long currentBitCount = 0;
    for (char byte: compressed) {
        for (int i = 7; i >= 0; i--) {
            currentBitCount++;
            if ((byte & (1 << i)) == 0) {
                currentNode = currentNode->getLeft();
            }
            else {
                currentNode = currentNode->getRight();
            }
            if (currentNode->isLeaf()) {
                text.push_back(currentNode->data);
                currentNode = huffmanTree;
                if (currentBitCount == totalBitCount) break;
            }
        }
    }

    delete huffmanTree; //delete dynamically allocated binary huffman tree

    return text;
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

static void arrayifyTree(binaryTree<huffmanNode>* tree, char array[] , int index) {
    array[index] = tree->data.character;
    if (tree->getLeft() != nullptr) arrayifyTree(tree->getLeft(), array, 2 * index + 1);
    if (tree->getRight() != nullptr) arrayifyTree(tree->getRight(), array, 2 * index + 2);
}

static long long power(long long base, long long exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

static binaryTree<char>* treeifyArray(char array[], int index) {
    if (array[index] != 0) return new binaryTree<char>(array[index]);
    binaryTree<char>* node = new binaryTree<char>(0);
    node->setLeft(treeifyArray(array, 2 * index + 1));
    node->setRight(treeifyArray(array, 2 * index + 2));
    return node;
}


//UNTESTED
static std::vector<char> compressArrayifiedTree(char array[], int length) {
    std::vector<char> compressed;
    compressed.push_back(0);
    int i = 0;
    while (array[i] == 0 && (unsigned char)compressed.back() < (unsigned char)255) {
        compressed.back()++;
        i++;
    }
    while (i < length) {
        compressed.push_back(array[i++]);
        compressed.push_back(0);
        while (array[i] == 0 && i < length && (unsigned char)compressed.back() < (unsigned char)255) {
            compressed.back()++;
            i++;
        }
    }
    return compressed;
}

//UNTESTED
static std::vector<char> decompressArrayifiedTree(char* compressed, int length) {
    std::vector<char> uncompressed;
    unsigned char zeroCount = compressed[0];
    while(zeroCount > 0) {
        uncompressed.push_back(0);
        zeroCount--;
    }
    for (int i = 1; i < length; i+=2) {
        uncompressed.push_back(compressed[i]);
        zeroCount = compressed[i+1];
        while(zeroCount > 0) {
            uncompressed.push_back(0);
            zeroCount--;
        }
    }
    return uncompressed;
}
