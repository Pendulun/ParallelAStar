#ifndef __SEARCHGRAPHNODECOMPARATOR_H__
#define __SEARCHGRAPHNODECOMPARATOR_H__
#include <utility>  
#include "SearchGraphNode.hpp"

class SearchGraphNodeComparator
{
public:
    bool operator()(std::pair<float, SearchGraphNode> n1, std::pair<float, SearchGraphNode> n2);
};
#endif