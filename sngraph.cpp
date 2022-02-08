#include "sngraph.h"
#include <fstream>

SNgraph::SNgraph(tree<std::string> parsed)
{
    user newUser;
    std::list<int> followers;
    for (tree<std::string>* userNode : parsed.children) {
        newUser.id = stoi(userNode->getChild(0)->getChild(0)->data);
        newUser.name = userNode->getChild(1)->getChild(0)->data;
        /*
        //Posts ignored for now
        for (tree<std::string>* post : userNode->getChild(2)->children) {
            newUser.posts.push_back(post->data);
        }
        */
        for (tree<std::string>* follower : userNode->getChild(3)->children) {
            followers.push_back(stoi(follower->getChild(0)->getChild(0)->data));
        }
        addNode(newUser, followers);
        followers.clear();
    }
}

void SNgraph::visualize() {
    std::string str;

    //Farah's Code starts here
    str = "diagraph test { \n";

        for (unsigned long long i = 0; i < nodes.size(); i++)
        {
            str += std::to_string(nodes[i]);  //lazm integer 3shan tostring
            str += " -> {";
            for (int adjacent : adjacencyLists[i]) {
                str += std::to_string(adjacent);
                str += " , ";
            }
            str.erase(str.end() - 2, str.end());
            str += "} \n";

        }
        str += "}";
       // cout << str; //MAZBOT

    /*for(unsigned long long i=0 ; i < nodes.size() ; i++)
    {
        str += std::to_string(nodes[i].id);
        str += " -> ";
        for(int adjacent: adjacencyLists[i]){
            str += std::to_string(adjacent);
            str += " , ";
        }
        str.erase(str.end()-2 , str.end());
        str += "\n";
    }
    //Farah's code ends here*/

    std::ofstream out("Source.dot");
    out << str;
    out.close();
}
