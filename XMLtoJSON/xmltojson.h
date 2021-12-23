/*********************************************************************
 *
 * File Name : xmltojson.h
 *
 * Description : Header file for Xml to json conversion functions
 *
 * Author : Ghada Alaa
 *
 **********************************************************************/

#ifndef XML_TO_JSON
#define XML_TO_JSON
#include <bits/stdc++.h>
using namespace std;
/*
 Function Description:
 remove spacing at end of string */
string rtrim(const string &s);
/*
Function Description:

Time & Space Complexity Analysis :
Time complexity : O(n) , n string length
Space complexity : O(1)
*/
int get_index(string s, char c);

/*
Function Description:

Time & Space Complexity Analysis :
Time complexity : O(n) , n space count/string length
Space complexity : O(1)
*/
string insertSpacing(int cnt);
/*
Function Description:

This function used to convert the xml input as string into json format directly.
Space complexity : O(n) , n stack size
Time Complexity : O(n^2)  , xml lines(n) , each line length(m)
*/
string xmltojson(string *xml);
#endif /*XML_TO_JSON */
