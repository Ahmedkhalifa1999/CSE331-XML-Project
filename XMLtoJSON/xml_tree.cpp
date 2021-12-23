#include"xml_tree.h"
/* Tree Node Class */
    tnode *  tnode:: getChild(int index)
    {
        return children[index];
    }
    void tnode:: setChild(tnode *node)
    {
        children.push_back(node);
    }
    int tnode:: getSize()
    {
        return children.size();
    }
    string tnode:: getData(tnode *node)
    {
        return node->data;
    }

    tree::tree()
    {
        root = nullptr;
    };
    void tree:: setRoot(tnode *root)
    {
        this->root = root;
    }
    tnode *build_XML_Tree(string xml)
    {
        /**/
        tnode *result = new tnode();
        string tagname;
         string tagdata = "";
        long long start;
        long long i = 0;
        /**/
        start = i;            /* this is index of < */
        while (xml[i] != '>') /* extract first tag first in the string passed to the function */
        {
            i++;
        }
        /* i index of > */
        /* xml[i] = '>'; */
        tagname = xml.substr(start + 1, i - (start + 1));
        result->name = tagname; /* pass the extracted tag name to node as name (removed opening and closing tags)*/
                                // cout << result->name << "->Node" << '\n';                       /* MZBOTAA*/

        while (i < xml.length() - (tagname.length() + 3)) /* index < xml length passed to string - (</>) bto3 elnode ele extracted ably 3ltol de*/
        {
       // while(xml[i]!='\0'){
            i++; /* to make i = index of <*/
                 // cout << xml[i] << '\n'; /* rest of string go through loop to get opening and closing tag */
            /*  xml[i] ='<' */
            start = i;
            while (xml[i] != '>')
            {
                i++;
            }
            string childTagname = xml.substr(start + 1, i - (start + 1)); /* extracting first tag (childtag) in the mini xml */
                                                                          //  cout << childTagname << "->Child" << '\n';                  /* mzbota*/
            i++;                                                          /* added 1 bec last i refers to index of > */
            start = i;
            bool found = false;                                           /* flag to check if the current tag is the closing tag for child tag or not */
            while (!found)                                                /* this loop will search for the closing tag of the recent extracted tag (childtag)*/
            {
                if(xml[i]=='<'){
                 while(xml[i]!='>'){
                     i++;
                 }
                 i++;
                }
                /* xml[i] = '>'; */
                /* Handling Case if found is data*/ /* start refers to the index of first data char if data found */
                if (xml[i] != '<')             /* ADDED CODE */
                {
                   int start2 = i;
                     while (xml[i] != '<') /* if found not openning tag but data*/
                    {
                        i++;
                    }                                           /* last i value is index of < of a closing tag */
                    tagdata = (xml.substr(start2, i - (start2))); /* ADDED CODE data */
                     return result;
                }
                if (xml[i + 1] == '/')
                {
                   // cout<<'c'<< xml[i+1] << '\n';             /* MZBOTA */
                    string currentClosingTag = "";
                    i+=2;           /* i skips < and / and jump to index of first character in closing tag name*/
                    //start = i;
                    while (xml[i] != '>')
                    {
                    //cout<<'c'<< xml[i] << '\n'; /* MZBOTA*/
                        currentClosingTag.push_back(xml[i]);
                        i++;
                    }
                    /* i is index of > */
                  //  cout<<'c'<< xml[i] << '\n';
                    //cout<<currentClosingTag<<"-->CurrentTag"<<'\n';
                    if (childTagname == currentClosingTag)
                    {
                        found = true;
                        result->children.push_back(build_XML_Tree2(xml.substr(start, i - start)));
                      // cout<<"Children"<<xml.substr(start, i - start)<<'\n';
                   }
                   // i++;
                }
            }
        }
        result->data = "";
        return result;
    }
