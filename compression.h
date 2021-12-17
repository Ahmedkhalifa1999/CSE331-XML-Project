#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>

typedef struct huffmanNode{
    char character = 0;
    unsigned long long frequency = 0;
} huffmanNode;

std::string compress(std::string* data);

std::string decompress(std::string* data);

#endif // COMPRESSION_H
