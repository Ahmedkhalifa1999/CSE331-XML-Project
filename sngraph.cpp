#include "sngraph.h"

SNgraph::SNgraph(tree<std::string> parsed)
{
    user newUser;
    std::list<int> followers;
    for (tree<std::string>* userNode : parsed.children) {
        newUser.id = stoi(userNode->getChild(0)->data);
        newUser.name = userNode->getChild(1)->data;
        for (tree<std::string>* post : userNode->getChild(2)->children) {
            newUser.posts.push_back(post->data);
        }
        for (tree<std::string>* follower : userNode->getChild(3)->children) {
            followers.push_back(stoi(follower->data));
        }
        addNode(newUser, followers);
        followers.clear();
    }
}

void SNgraph::visualize() {

}
