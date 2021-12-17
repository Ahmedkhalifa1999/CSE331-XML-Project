#include "minify.h"
#include <ctype.h>

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

