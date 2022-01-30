#include "BSTNode.hpp"

BSTNode::BSTNode(){
    this->node = nullptr;
    this->leftNode = nullptr;
    this->rightNode = nullptr;
    this->parentNode = nullptr;
}

BSTNode::~BSTNode(){
    //Doesn't delete its node, parent or children nodes
}

void BSTNode::setNode(SearchGraphNode* node){
    this->node = node;
}

void BSTNode::setLeftNode(BSTNode* leftNode){
    this->leftNode = leftNode;
}

void BSTNode::setParentNode(BSTNode* parentNode){
    this->parentNode = parentNode;
}

void BSTNode::setRightNode(BSTNode* rightNode){
    this->rightNode = rightNode;
}

SearchGraphNode* BSTNode::getNode(){
    return this->node;
}

BSTNode* BSTNode::getLeftNode(){
    return this->leftNode;
}

BSTNode* BSTNode::getRightNode(){
    return this->rightNode;
}

BSTNode* BSTNode::getParentNode(){
    return this->parentNode;
}

float BSTNode::getTotalCost(){
    return this->getNode()->getTotalCost();
}

void BSTNode::updateMyPlaceAsChildWith(BSTNode* newNode){
    if(this->parentNode->getLeftNode() == this){
        this->parentNode->setLeftNode(newNode);
    }else if(this->parentNode->getRightNode() == this){
        this->parentNode->setRightNode(newNode);
    }
}