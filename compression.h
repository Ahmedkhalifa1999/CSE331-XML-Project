#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>

typedef struct{
    char character;
    unsigned long long frequency;
} huffmanNode;

std::string compress(std::string* data);

std::string decompress(std::string* data);

#endif // COMPRESSION_H
