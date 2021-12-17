#include <bits/stdc++.h>
using namespace std;

/* Tree Node Class */
class tnode
{
    int data;
    vector<tnode *> children;
public:
    tnode(int data);
    tnode *getChild(int index);
    void setChild(tnode *node);
    int getSize();
    int getData(tnode *node);
};
/* Tree Class */
class tree
{
    tnode *root;
public:
    tree();
    void setRoot(tnode *root);
};