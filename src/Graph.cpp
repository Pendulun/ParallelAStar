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

GraphNode Graph::findNode(unsigned int nodeId){
    return this->graphNodes.at(nodeId);
}

unsigned int Graph::getSize(){
    return this->graphNodes.size();
}