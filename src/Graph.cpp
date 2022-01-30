#include "Graph.hpp"

Graph::Graph(/* args */)
{
}

Graph::~Graph()
{
}

void Graph::addNode(unsigned int nodeId, GraphNode node){
    if(!this->hasNode(nodeId)){
        this->graphNodes.insert(std::make_pair<>(nodeId, node));
    }
    
}

void Graph::removeNode(unsigned int nodeId){
    if(!this->hasNode(nodeId)){
        this->graphNodes.erase(nodeId);
    }
}

/**
 * @brief Creates a directed edge from Node "fromNodeIdx" to Node "toNodeIdx" with weight "weight".
 * If Node "fromNodeIdx" doesnt exists, it will be created. This doesnt happens with Node "toNodeIdx"
 * as a Node only needs the Node Idx to connect to it.
 * 
 * To create an undirected edge, call this function twice or call addUndirectedEgde    
 * 
 * @param fromNodeIdx 
 * @param toNodeIdx 
 * @param weight 
 */
void Graph::addDirectedEdge(unsigned int fromNodeIdx, unsigned int toNodeIdx, float weight){
        //Adiciono uma aresta para outro nó no grafo
        this->createNodeIfDoesntExists(fromNodeIdx);

        GraphNode& fromGraphNode = this->findNode(fromNodeIdx);
        fromGraphNode.addReachableNode(toNodeIdx, weight);

}

/**
 * @brief Creates an undirected edge from Node "fromNodeIdx" to Node "toNodeIdx" with weight "weight".
 * If Node "fromNodeIdx" doesnt exists, it will be created. This also happens with Node "toNodeIdx".
 * 
 * @param fromNodeIdx 
 * @param toNodeIdx 
 * @param weight 
 */
void Graph::addUndirectedEgde(unsigned int fromNodeIdx, unsigned int toNodeIdx, float weight){
    this->addDirectedEdge(fromNodeIdx, toNodeIdx, weight);
    this->addDirectedEdge(toNodeIdx, fromNodeIdx, weight);
}

bool Graph::createNodeIfDoesntExists(unsigned int nodeId){
    if(!this->hasNode(nodeId)){
        GraphNode newNode;
        newNode.setId(nodeId);
        this->addNode(nodeId, newNode);
        return true;
    }
    return false;
}

/**
 * @brief Returns a specific node inside Graph. Assumes that the node really exists. Otherwise, it will
 * raise an exception. To check if a Node exists, call hasNode()
 * 
 * @param nodeId 
 * @return GraphNode 
 */
GraphNode& Graph::findNode(unsigned int nodeId){
    return this->graphNodes.at(nodeId);
}

bool Graph::hasNode(unsigned int nodeId){
    return this->graphNodes.count(nodeId) > 0;
}

unsigned int Graph::getSize(){
    return this->graphNodes.size();
}

void Graph::printGraph(){
    std::unordered_map<unsigned int, GraphNode>::iterator graphIterator;
    for(graphIterator = this->graphNodes.begin(); graphIterator != this->graphNodes.end(); graphIterator++){
        graphIterator->second.printMyInfo();
    }
    std::cout<<"Initial Node: "<<this->initialNodeIdx;
    std::cout<<" Final Node: "<<this->finalNodeIdx<<std::endl;
}

void Graph::setInitialPosition(const unsigned int initialNodeIdx){
    this->initialNodeIdx = initialNodeIdx;
}

void Graph::setFinalPosition(const unsigned int finalNodeIdx){
    this->finalNodeIdx = finalNodeIdx;
}

unsigned int Graph::getInitialPos(){
    return this->initialNodeIdx;
}

unsigned int Graph::getFinalPos(){
    return this->finalNodeIdx;
}