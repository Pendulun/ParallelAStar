#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <unordered_map>
#include <iterator>
#include "GraphNode.hpp"

class Graph
{
private:
    std::unordered_map<unsigned int, GraphNode> graphNodes;
    unsigned int initialNodeIdx;
    unsigned int finalNodeIdx;
public:
    Graph(/* args */);
    ~Graph();
    void addNode(unsigned int nodeId, GraphNode node);
    void removeNode(unsigned int nodeId);
    GraphNode& findNode(unsigned int nodeId);
    
    void addDirectedEdge(unsigned int fromNodeIdx, unsigned int toNodeIdx, float weight);
    void addUndirectedEgde(unsigned int fromNodeIdx, unsigned int toNodeIdx, float weight);
    bool createNodeIfDoesntExists(unsigned int nodeId);
    
    unsigned int getSize();
    bool hasNode(unsigned int nodeId);
    void printGraph();

    void setInitialPosition(const unsigned int initialNodeIdx);
    void setFinalPosition(const unsigned int finalNodeIdx);
    unsigned int getInitialPos();
    unsigned int getFinalPos();

};
#endif