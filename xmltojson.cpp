/*********************************************************************
 *
 * File Name : xmltojson.cpp
 *
 * Description : Source file for Xml to json conversion
 *
 * Author : Ghada Alaa
 *
 **********************************************************************/
#include "xmltojson.h"
#include "minify.h"
/*
 Function Description:
 remove spacing at end of string */
string rtrim(const string &s)
{
    int end = s.find_last_not_of(" \n\r\t\f\v");                      /* O(n*l) n : length of string , l : number of occurences of the string */
    return (end == string::npos) ? "" : s.substr(0, end + 1);         /* O(n) , n : size of substring */
}
/*
Function Description:

Time & Space Complexity Analysis :
Time complexity : O(n) , n string length
Space complexity : O(1)
*/
int get_index(string s, char c)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == c)
            return i;
    }
    return -1;
}
/*
Function Description:

Time & Space Complexity Analysis :
Time complexity : O(n) , n space count/string length
Space complexity : O(1)
*/
string insertSpacing(int cnt)
{
    string str = "";
    for (int i = 0; i < cnt; i++)
    {
        str += " ";
    }
    return str;
}
/*
Function Description:
This function used to convert the xml input as string into json format directly.
 Space complexity : O(n) , n stack size
 Time Complexity : O(n^2)  , xml lines(n) , each line length(m)
*/
string xmltojson(string *xml)
{
    string json;
    vector<string> x(1);
    vector<string> j(1);
    int l = 0;
    int prev = -1, i;
    for (i = 0; i < (*xml).length(); i++)
    {
        if ((*xml)[i] == '\n')
        {
            x.push_back((*xml).substr(prev + 1, i - prev));
            prev = i + 1;
        }
    }
    x.push_back((*xml).substr(prev, i - prev));
    string s, s1, s2 = "";
    string s3;
    int flag = 0;
    int level = -1 ;
    stack<string> tags; //build a stack that reads tags to save them till upcoming correspoding closing tag
    j[0] = "{\n";
    for (auto i = x.begin(); i != x.end(); i++)
    {
        s3 = *i;
        s = minify(&s3);
        //now we want to get index of '<' and '>' to extract tag name from it
        //if we find indeces not = -1 then we are either at start or end tag
        int tagname_start = get_index(s, '<') + 1;
        int tagname_end = get_index(s, '>') - 1;
        if (s[tagname_start] == '/')
        {
            s1 = s.substr(tagname_start + 1, tagname_end - (tagname_start)); //O(n)
            s2 = s1;
            level--;                                                         //we save it to see it there's another tag on its level
            j.push_back(insertSpacing( level + 7  ) + "}\n");
            tags.pop(); //O(1)
        }
        //in case the line is not a closing or opening tag but attribute value
        else if (tagname_start == 0 && tagname_end == -2)
        {
            s = rtrim(s);
            if (flag)
            {
                level ++;                                                    //y3ny ana gwa nafs el tag
                j.push_back(insertSpacing( level + 10 )+'"' + s + '"'+ '\n'); //saving attribute value
                level--;
            }
            else
                continue;
        }
        //found openning tag either <>...</> or <> lines </>
        else
        {
            s1 = s.substr(tagname_start, tagname_end - tagname_start + 1); //O(n)
            tags.push(s1);
            level++;
            flag = 1;     // setting flag means that we are somewhere between openning and closing tags
            if (s1 != s2) //check if children belongs to the same parent or not
                j.push_back(insertSpacing( level + 3 )+'"' + s1 + '"'+ ":" + "{\n");
            else
                j.push_back(insertSpacing( level + 3 - 2 ) + ", {\n");
        }
    }
    j.push_back("}");
    for (auto i = j.begin(); i != j.end(); i++)
    {
        json += *i;
    }
    return json;
}
