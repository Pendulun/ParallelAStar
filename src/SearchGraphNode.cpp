#include "SearchGraphNode.hpp"


SearchGraphNode::SearchGraphNode(/* args */){
    this->parentNode = nullptr;
    this->pathCostToNode = 0.0;
    this->totalCost = 0.0;
    this->myGraphNode = nullptr;
    this->lastActionCost = 0.0;
}

SearchGraphNode::~SearchGraphNode(){
}

void SearchGraphNode::setParentNode(SearchGraphNode* newParentNode){
    this->parentNode = newParentNode;
}

void SearchGraphNode::setPathCost(double pathCost){
    this->pathCostToNode = pathCost;
}

void SearchGraphNode::setLastActionCost(double lastActionCost){
    this->lastActionCost = lastActionCost;
}

double SearchGraphNode::getLastActionCost(){
    return this->lastActionCost;
}

SearchGraphNode* SearchGraphNode::getParentNode(){
    return this->parentNode;
}

double SearchGraphNode::getPathCost(){
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

double SearchGraphNode::getTotalCost(){
    return this->totalCost;
}