#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <unordered_map>
#include "GraphNode.hpp"

class Graph
{
private:
    std::unordered_map<unsigned int, GraphNode> graphNodes;
public:
    Graph(/* args */);
    ~Graph();
    void addNode(unsigned int nodeId, GraphNode node);
    void removeNode(unsigned int nodeId);
    GraphNode findNode(unsigned int nodeId);
    unsigned int getSize();
    bool hasNode(unsigned int nodeId);
};
#endif