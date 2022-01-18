#include "Graph.hpp"

Graph::Graph(/* args */)
{
}

Graph::~Graph()
{
}

void Graph::addNode(unsigned int nodeId, GraphNode node){
    this->graphNodes.insert(std::make_pair<>(nodeId, node));
}

void Graph::removeNode(unsigned int nodeId){
    this->graphNodes.erase(nodeId);
}

/**
 * @brief Returns a specific node inside Graph. Assumes that the node really exists. Otherwise, it will
 * raise an exception. To check if a Node exists, call hasNode()
 * 
 * @param nodeId 
 * @return GraphNode 
 */
GraphNode Graph::findNode(unsigned int nodeId){
    return this->graphNodes.at(nodeId);
}

bool Graph::hasNode(unsigned int nodeId){
    return this->graphNodes.count(nodeId) > 0;
}

unsigned int Graph::getSize(){
    return this->graphNodes.size();
}