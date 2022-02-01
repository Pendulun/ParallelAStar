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

void SearchGraphNode::setPathCost(const double pathCost){
    this->pathCostToNode = pathCost;
}

SearchGraphNode* SearchGraphNode::getParentNode(){
    return this->parentNode;
}

const double SearchGraphNode::getPathCost(){
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

void SearchGraphNode::setTotalCost(double totalCost){
    this->totalCost = totalCost;
}

const double SearchGraphNode::getTotalCost(){
    return this->totalCost;
}