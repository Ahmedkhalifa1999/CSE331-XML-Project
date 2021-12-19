#include <bits/stdc++.h>
#include"xml_tree.h"
using namespace std;
/* used to search for certain character in a given string and return its index*/
/* remove spacing at start of string */
string ltrim(const string &s)
{
	int start = s.find_first_not_of(" \n\r\t\f\v");
	return (start ==string::npos) ? "" : s.substr(start);
}
/* remove spacing at end of string */
string rtrim(const string &s)
{
	int end = s.find_last_not_of(" \n\r\t\f\v");
	return (end ==string::npos) ? "" : s.substr(0, end + 1);
}
/* remove spacing at start and end of string */
string trim(const string &s) {
	return rtrim(ltrim(s));
}

/* Return root of XML tree */
tnode* getXMLTree(string *xml)
{
    /* Converting the XML string to vector of strings each element represents a line */
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
    x.push_back((*xml).substr(prev, i - prev)); /* NOW vector is successfully filled by XML lines */


    string s = "", s1 = "";            /* s used to copy each vector element in it  */
                                       /* s1 used hold value of tag name after extractions from <> or </> */
    stack < string > tags;             /* tags stack used to hold values of openning tags till corresponding closing tag */
    stack < string > children;         /* children stack used to hold values of tags represent children to a parent tag */
    for (auto i = x.begin(); i != x.end(); i++)
    {
        s = *i;
        trim(s);                                     /* Remove Spacing at start and end of string */
        int tagname_start = get_index(s, '<') + 1;   /* index of first character in tag name without <> */
        int tagname_end = get_index(s, '>') - 1;     /* index of last character in tag name without <> */
        if (s[tagname_start] == '/')                 /*if found closing tag */
        {
            s1 = s.substr(tagname_start + 1, tagname_end - tagname_start);   /*extact closing tag's name , this step was needed to save value of last poped tag*/
            tags.pop();                                                      /*pop from stack last tag */
        }
        else if (tagname_start == 0 && tagname_end == -2){}                  /*neither openning or closing tag , attribute value */
        else                                                                 /*if found closing tag */
        {
            s1 = s.substr(tagname_start, tagname_end - tagname_start + 1);   /* extract openning tag name , push it at the stack */
            tags.push(s1);
        }
    }
}
