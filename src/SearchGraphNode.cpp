#include "SearchGraphNode.hpp"


SearchGraphNode::SearchGraphNode(/* args */)
{
}

SearchGraphNode::~SearchGraphNode()
{
}

void SearchGraphNode::setParentNode(SearchGraphNode* newParentNode){
    this->parentNode = newParentNode;
}

void SearchGraphNode::setPathCost(const unsigned int pathCost){
    this->pathCostToNode = pathCost;
}

SearchGraphNode* SearchGraphNode::getParentNode(){
    return this->parentNode;
}

const unsigned int SearchGraphNode::getPathCost(){
    return this->pathCostToNode;
}