#pragma once
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;
stack<string> errortag;
//vector<char> error_location;
/*
 Description:
     -> this functions loops over xml string by character and checks for
        opening and closing tags in terms of correctness and matching.

     -> this function stores the opening tags and check them against closing tags.
     -> if they match the content of stack is cleared and the function returns true.
     -> if they don't match then the function returns false.
     -> if a closing tag is missing, the stack is not empty and the function returns false.

     time complexity = O(n)
     space complexity = O(n)
     where n is size of the string.

*/
bool detection(string& xml);

// General solution
string correction(string& xml);
