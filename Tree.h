#include <vector>

template<typename dataType>
class tree{
public:
    dataType data;
    std::vector<tree*> children;

    tree();
    tree(dataType data);

    tree* getChild(int index);
    void addChild(tree* child);
    void setChild(int index, tree* child);
    bool isLeaf();

    ~tree();
};
