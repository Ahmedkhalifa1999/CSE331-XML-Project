#include <bits/stdc++.h>
using namespace std;

/* Tree Node Class */
class tnode
{
    string data;
    vector<tnode *> children;
public:
    tnode(string data);
    tnode *getChild(int index);
    void setChild(tnode *node);
    int getSize();
    string getData(tnode *node);
};
/* Tree Class */
class tree
{
    tnode *root;
public:
    tree();
    void setRoot(tnode *root);
};
