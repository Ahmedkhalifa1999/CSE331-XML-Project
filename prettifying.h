#include <string>
#include <iostream>

using namespace std;

/*
* Function to prettify the XML file by keeping the indentation for each level.
* time complexity = O(n^2) + O(n^2) + O(n) + O(n) = O(n^2)
* space complexity = O(2n) + O(2n) + O(2n) + O(n) = O(n)
*/
void prettifying(string* text);