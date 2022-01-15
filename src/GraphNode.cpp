#include "GraphNode.hpp"

GraphNode::GraphNode(/* args */)
{
}

GraphNode::~GraphNode()
{
}

void GraphNode::addChildNode(GraphNode newChildNode){
    this->childNodes.push_back(newChildNode);
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