#include "XMLtoJSON/build_xml_tree.h"
/*

   FUNCTION DESCRIPTION :

   *INPUT* :  to the function : minified string

   *OUTPUT* : is node after specifying name (tag name between <> and data between <> and </> ) till
   found its closing tag , if found in data opening tag then get its name , data if found in data
   opening tag , then extract tag name and data and so on ...

   *BASE CASE* : found opening tag , data not contain another opening tag then it's leaf

*/
/*
void build_XML_Tree(std::string s)
{
    long long len = s.length();
    string tagname;
    string tagdata;
    int start;
    int i = 0;
    int level = -1;
    //BASE CASE
    if (s[i] != '<') //Found data not tag
    {
        if (s[i] == '\0')
            return;
        start = i;
        while (s[i] != '/')
        {
            i++;
        }
        tagdata = s.substr(start, i - start - 1); //DATA
        cout << "TAG DATA " << tagdata << '\n';
        while (s[i] != '>') //Closing tag of non leaf element
        {
            i++;
        }
        build_XML_Tree(s.substr(i + 1, s.length() - 1 - tagname.length()));
    }
    else if (s[i] == '<')    // Found tag not data
    {                        // It may be either opening tag or closing tag rather than the leaf node
        if (s[i + 1] == '/') // Closing tag of non leaf element
        {
            start = i + 1;
            while (s[i] != '>')
            {
                i++;
            }
            tagname = s.substr(start + 1, i - start - 1);
            cout << "CLOSING TAG NAME " << tagname << '\n';
            build_XML_Tree(s.substr(i + 1, s.length() - 1 - tagname.length()));
        }
        else
        {
            level;
            start = i;
            while (s[i] != '>')
            {
                i++;
            }
            tagname = s.substr(start + 1, i - start - 1);
            cout << "OPENING TAG NAME " << tagname << '\n';
            build_XML_Tree(s.substr(i + 1, s.length() - 1 - tagname.length()));
        }
    }
}
*/
