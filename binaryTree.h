template<typename dataType>
class binaryTree{
public:
    dataType data;
    binaryTree* left;
    binaryTree* right;

    binaryTree(dataType data);

    binaryTree* getLeft();
    binaryTree* getRight();
    void setRight(binaryTree* child);
    void setLeft(binaryTree* child);
    bool isLeaf();

    ~binaryTree();
};