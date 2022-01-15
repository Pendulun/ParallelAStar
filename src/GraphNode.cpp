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
