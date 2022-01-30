#include "SearchGraphNode.hpp"


SearchGraphNode::SearchGraphNode(/* args */)
{
    this->parentNode = nullptr;
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

void SearchGraphNode::setGraphNode(GraphNode* myGraphNode){
    this->myGraphNode = myGraphNode;
}

GraphNode* SearchGraphNode::getGraphNode(){
    return this->myGraphNode;
}

unsigned int SearchGraphNode::getNodeId(){
    return this->myGraphNode->getId();
}

void SearchGraphNode::setTotalCost(float totalCost){
    this->totalCost = totalCost;
}

const float SearchGraphNode::getTotalCost(){
    return this->totalCost;
}