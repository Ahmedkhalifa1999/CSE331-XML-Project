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

    tnode* build_XML_Tree2(string xml){
        tnode* result = new tnode();
        string tagname;
        string tagdata = "";
        int start;
        int i = 0;
        stack<string> tags;
        start = i;

        while (xml[i] != '>')
        {
            i++;
        }
        result->name = xml.substr(start + 1, i - start - 1);
        //mn awwel el opening tag lghayet elclosing tag)
        while (i < xml.length() - (tagname.length() + 3))
        {
            start = i;
            while (xml[i] != '>')
            {
                i++;
            }
            string childTagname = xml.substr(start + 1, i - start - 1);
            bool found = false;
            while (!found)
            {
                while (xml[i] != '<')
                    i++;
                i++;
                if (xml[i++] == '/')
                {
                    string currentClosingTag = "";
                    while (xml[i] != '>')
                    {
                        currentClosingTag.push_back(xml[i]);
                        i++;
                    }
                    if (childTagname == currentClosingTag)
                    {
                        found = true;
                        result->children.push_back(build_XML_Tree2(xml.substr(start, i - start + 1)));
                    }
                    i++;
                }
            }
        }
        result->data = "";
        return result;
}
