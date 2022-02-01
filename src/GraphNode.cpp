#include "GraphNode.hpp"

GraphNode::GraphNode(/* args */)
{
}

GraphNode::~GraphNode()
{
}

/**
 * @brief 
 * 
 * @param nodeId The node to be reached 
 * @param cost Edge weight
 */
void GraphNode::addReachableNode(unsigned int nodeId, double cost){
    this->costToOtherNodes.insert(std::make_pair<>(nodeId, cost));
}

void GraphNode::printMyInfo(){
    std::cout<<"Node Id: "<<this->id<<" Xpos: "<<this->xPos<<" yPos: "<<this->yPos<<std::endl;
    std::unordered_map<unsigned int, double>::iterator myEdgesIterator;
    for(myEdgesIterator = this->costToOtherNodes.begin(); myEdgesIterator != this->costToOtherNodes.end(); myEdgesIterator++){
        std::cout<<myEdgesIterator->first<<":"<<myEdgesIterator->second<<std::endl;
    }
}

void GraphNode::setXPos(float newXPos){
    this->xPos = newXPos;
}

void GraphNode::setYPos(float newYPos){
    this->yPos = newYPos;
}

float GraphNode::getXPos(){
    return this->xPos;
}

float GraphNode::getYPos(){
    return this->yPos;
}

void GraphNode::setId(unsigned int newId){
    this->id = newId;
}

unsigned int GraphNode::getId(){
    return this->id;
}

std::unordered_map<unsigned int, double >* GraphNode::getCostToOtherNodes(){
    return &this->costToOtherNodes;
}