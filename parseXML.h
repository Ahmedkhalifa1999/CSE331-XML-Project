#include <iostream>
#include <stack>
#include <string>
#include "Tree.h"
#include <fstream>


/*
Description : extracting closing or openning tag name
*/

string extract(int *left, string *mini);

/*
Description : extracting data
*/

string extractdata(int *left, string *mini);

/*
Description :
input to function minified XML we build the XML tree out of it.
*/

void parseXML(string &mini, tree<string> &xml);