#include "sngraph.h"
#include <fstream>

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

void SNgraph::visualize(std::string directory) {
    std::string str;

    //Farah's Code start here
    for(int i=0 ; i < nodes.size() ; i++)
    {
        str += nodes[i].id;
        str += " -> ";
        for(int adjacent: adjacencyLists[i]){
            str += adjacent;
            str += " , ";
        }
        str.erase(str.end()-2 , str.end());
        str += "\n";
    }
    //Farah's code ends here

    std::ofstream out(directory + "Source.dot");
    out << str;
    out.close();
}
