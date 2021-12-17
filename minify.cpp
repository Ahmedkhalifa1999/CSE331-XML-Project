#include "minify.h"

std::string minify(std::string* text) {
    std::string minified;
    for (char character: *text) {
        if (character == ' ') continue;
        if (character == '\n') continue;
        if (character == '\t') continue;
        minified.push_back(character);
    }
    return minified;
}
