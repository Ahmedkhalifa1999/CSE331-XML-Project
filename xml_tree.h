#include <bits/stdc++.h>
using namespace std;

/* Tree Node Class */
class tnode
{
 public:
    string data;
    string name;
    vector<tnode *> children;
public:
    //tnode();
    tnode *getChild(int index);
    void setChild(tnode *node);
    int getSize();
    string getData(tnode *node);
    ~tnode();
};
/* Tree Class */
class tree
{
    tnode *root;
public:
    tree();
    void setRoot(tnode *root);
};
tnode* build_XML_Tree2(string xml);
