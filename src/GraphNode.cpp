#include "GraphNode.hpp"

GraphNode::GraphNode(/* args */)
{
}

GraphNode::~GraphNode()
{
}

void GraphNode::addReachableNode(unsigned int nodeId, unsigned int cost){
    this->costToOtherNodes.insert(std::make_pair<>(nodeId, cost));
}

void GraphNode::setXPos(unsigned int newXPos){
    this->xPos = newXPos;
}

void GraphNode::setYPos(unsigned int newYPos){
    this->yPos = newYPos;
}

unsigned int GraphNode::getXPos(){
    return this->xPos;
}

unsigned int GraphNode::getYPos(){
    return this->yPos;
}

void GraphNode::setId(unsigned int newId){
    this->id = newId;
}

unsigned int GraphNode::getId(){
    return this->id;
}
    