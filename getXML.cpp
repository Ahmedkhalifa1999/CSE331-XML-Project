#include <bits/stdc++.h>
#include"xml_tree.h"
using namespace std;

int get_index(string s, char c)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == c)
            return i;
    }
    return -1;
}
string ltrim(const string &s)
{
	int start = s.find_first_not_of(" \n\r\t\f\v");
	return (start ==string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s)
{
	int end = s.find_last_not_of(" \n\r\t\f\v");
	return (end ==string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) {
	return rtrim(ltrim(s));
}

/* Return root of XML tree */
tnode* getXMLTree(string *xml)
{
    vector<string> x(200);
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
    int k = 1;
    int flag = 0;
    stack < string > tags;
    stack < string > children;
    vector<string> tagss;
    for (auto i = x.begin(); i != x.end(); i++)
    {
        s = *i;
        trim(s);
        int tagname_start = get_index(s, '<') + 1;
        int tagname_end = get_index(s, '>') - 1;
        if (s[tagname_start] == '/')
        {
            s1 = s.substr(tagname_start + 1, tagname_end - tagname_start);
                       cout<<s1<<" ";
            tags.pop();
        }
        else if (tagname_start == 0 && tagname_end == -2){}
        else
        {
            s1 = s.substr(tagname_start, tagname_end - tagname_start + 1);
            cout<<s1<<" ";
            tags.push(s1);

        }
    }
}
