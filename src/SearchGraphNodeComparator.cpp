#include "SearchGraphNodeComparator.hpp"

bool SearchGraphNodeComparator::operator()(std::pair<float, SearchGraphNode> n1, std::pair<float, SearchGraphNode> n2){
    return n1.second.getPathCost() > n2.second.getPathCost(); 
}