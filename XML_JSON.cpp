#include <bits/stdc++.h>
using namespace std;
/*
Sample input :
<root>
  <child>
    <subchild>
    aaaa
    cccccccccccc
    </subchild>
  </child>
  <child>
    <subchild>
    bbbbbb
    </subchild>
  </child>
</root>
*/
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
//Time complexity : O(n) , n string length
// space complexity : O(1)
int get_index(string s, char c)
{
    for (unsigned int i = 0; i < s.length(); i++)
    {
        if (s[i] == c)
            return i;
    }
    return -1;
}
/*
Function Description:
This function used to convert the xml format file input as text into another
text in json format directly.
// Space complexity : O(n) , n stack size
// Time Complexity : O(n^2)  , xml lines(n) , each line length(m)
*/
//array x contains our xml code
// array j contains our json code
void convert(string x[], string j[], int size_x)
{
    int end2;
    string s, s1, s2;
    int k = 1;
    int flag = 0;
    stack<string> tags; //build a stack that reads tags to save them till upcoming correspoding closing tag
                        //Loop on xml code line by line
    j[0] = '{';
    for (int i = 0; i < size_x; i++, k++)
    {
        s = x[i];
        //s= removeSpaces(x[i]);
        //now we want to get index of '<' and '>' to extract tag name from it
        //if we find indeces not = -1 then we are either at start or end tag
        int tagname_start = get_index(s, '<') + 1;
        int tagname_end = get_index(s, '>') - 1;
        //    cout<<tagname_start<<" "<<tagname_end;
        if (s[tagname_start] == '/')
        {
            s1 = s.substr(tagname_start + 1, tagname_end - (tagname_start)); //O(n)
            s2 = s1;                                                         //we save it to see it there's another tag on its level
            j[k] = '}';
            tags.pop(); //O(1)
        }
        //in case the line is not a closing or opening tag but attribute value
        else if (tagname_start == 0 && tagname_end == -2)
        {
            if (flag)
                j[k] = s; //saving attribute value
            else
                continue;
        }
        //found openning tag either <>...</> or <> lines </>
        else
        {
            end2 = get_index(s, ' '); //O(n)
            if (end2 > tagname_start && end2 < tagname_end)
                s1 = s.substr(tagname_start, end2 - tagname_start + 1); //O(n)
            else
                s1 = s.substr(tagname_start, tagname_end - tagname_start + 1); //O(n)
            tags.push(s1);                                                     //O(1)
            flag = 1;                                                          // setting flag means that we are somewhere between openning and closing tags
            if (s1 != s2)                                                      //check if children belongs to the same parent or not
                j[k] = "'" + s1 + "'" + ":" + "{";
            else
                j[k] = ", {";
        }
    }
    j[k++] = '}';
    for (int i = 0; i < 200; i++)
    {
        cout << j[i] << ' ';
    }
}
/*
Function Description :
input xml line by line till terminates at root's end tag
Time complexity : O(n^2) , number of lines in xml file , length of each line , larger size of them is n so O(n^2)
approximated complexity
*/
void input_xml(string input[], int *i)
{
    int start, end;
    string line, t;
    string de = "</";

    while (getline(cin, line))
    {
        if (*i == 0)
        {
            t = line;
            start = get_index(line, '<') + 1;
            end = get_index(line, '>');
        }
        if (line == (de + t.substr(start, end - start + 1))) //O(n)
            break;
        input[(*i)++] = line;
    }
}
