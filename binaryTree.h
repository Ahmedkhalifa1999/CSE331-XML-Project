class binaryTree{
public:
    binaryTree* left = nullptr;
    binaryTree* right = nullptr;

    binaryTree* getLeft();
    binaryTree* getRight();
    void setRight(binaryTree* child);
    void setLeft(binaryTree* child);
    bool isLeaf();

    ~binaryTree();
};
