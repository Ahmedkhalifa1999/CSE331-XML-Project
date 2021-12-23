#ifndef XML_TREE
#define X XML_TREE

#include "XMLtoJSON/xml_tree.h"
#include "compression.h"
/*

   FUNCTION DESCRIPTION :

   *INPUT* : to the function : minified XML string

   *OUTPUT* : is pointer to the root tag (whole tree) after specifying name (tag name between <> and data between <> and </> )
   till found its closing tag , if found in data opening tag then get its name , data if found in data opening tag , then
   extract tag name and data and so on ...

   *BASE CASE* : found opening tag , data not contain another opening tag then it's leaf

*/
//void build_XML_Tree(std::string s);

#endif // XML_TREE
