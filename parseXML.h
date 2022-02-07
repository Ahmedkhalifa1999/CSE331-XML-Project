#include <iostream>
#include <stack>
#include <string>
#include "tree.h"
#include <fstream>


/*
Description : extracting closing or openning tag name
*/

std::string extract(int *left, std::string *mini);

/*
Description : extracting data
*/

std::string extractdata(int *left, std::string *mini);

/*
Description :
input to function minified XML we build the XML tree out of it.
*/

void parseXML(std::string &mini, tree<std::string> &xml);
