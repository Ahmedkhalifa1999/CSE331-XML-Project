template<typename T>
class binaryTree{
public:
    T data;
    binaryTree* left = nullptr;
    binaryTree* right = nullptr;

    binaryTree(T data);

    binaryTree* getLeft();
    binaryTree* getRight();
    void setRight(binaryTree* child);
    void setLeft(binaryTree* child);
    void setRight(T data);
    void setLeft(T data);
    bool isLeaf();

    ~binaryTree();
};
